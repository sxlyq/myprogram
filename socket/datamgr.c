#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <time.h>
#include "datamgr.h"

#ifndef SET_MIN_TEMP 
#error SET_MIN_TEMP is not defined
#endif
#ifndef SET_MAX_TEMP 
#error SET_MAX_TEMP is not defined
#endif

struct element
{
	uint16_t sensorID;
	uint16_t roomID;
	double running_avg;
	queue_t *data;
	time_t last_modified;	
};

static void list_element_free(element_ptr_t *element)
{
	queue_free(&((*(myelement_ptr_t *)element)->data));
	free(*element);
	*element = NULL; 
}

//compare sensorID,if x>y, return 1,if x<=y, return -1. 
static int list_element_compare(element_ptr_t x, element_ptr_t y)
{
	if((((myelement_ptr_t)x)->sensorID) > (((myelement_ptr_t)y)->sensorID))
		return 1;
	else 
		return -1;
}

static void list_element_print(element_ptr_t element)
{
	myelement_ptr_t myelement = (myelement_ptr_t)element;
	printf("roomID: %u, sensorID: %u, running average: %.2f\n",myelement->roomID,myelement->sensorID,myelement->running_avg);
	queue_print(myelement->data);
	printf("\nlast modified: %s\n",asctime(localtime(&(myelement->last_modified))));
}

static void queue_element_free(element_t *element)
{
	free(*element);
	*element = NULL;
}

static void queue_element_print(element_t element)
{
	printf("  %.2f",*(double*)element);
}



//read room sensor map from path and create sensor node list
list_ptr_t create_sensor_list(const char *path)
{
	FILE *fp;
	unsigned int sID;
	unsigned int rID;
	fp = fopen( path, "r" );
	if (!fp) 
	{
		perror("File open failed: ");
	}
	list_ptr_t list = list_create(NULL,&list_element_free,&list_element_compare,&list_element_print);
	while(fscanf(fp,"%u %u\n",&rID,&sID) != EOF)
	{
		myelement_ptr_t element = (myelement_ptr_t)malloc(sizeof(myelement_t));
		if(element == NULL)
			perror("Element malloc failed.");
		element->sensorID = sID;
		element->roomID = rID;
		element->running_avg = 0;
		element->data = queue_create(&queue_element_print,NULL,&queue_element_free);
		if(element->data == NULL)
			perror("Data malloc failed.");
		element->last_modified = 0;
		list = list_insert_sorted(list, element);
	}
	fclose(fp);
	return list;
}

void read_sensor_data(queue_data_t* sensor_data, list_ptr_t list, FILE *fifo_fp)
{
	char note[100];
	int sID = sensor_data->sensor_id;
	if((sID<(((myelement_ptr_t)list_get_element_at_index(list, 0))->sensorID))
	||(sID>(((myelement_ptr_t)list_get_element_at_index(list, list_size(list)))->sensorID)))
	{
		fprintf(stderr,"The data with sensorID %u has been ignored.",sID);
	}
	else
	{
		int upper_limit = list_size(list)-1;
		int lower_limit = 0;
		while(upper_limit - lower_limit > 1)
		{
			if(sID > ((myelement_ptr_t)list_get_element_at_index(list, (upper_limit + lower_limit)/2))->sensorID)
				lower_limit = (upper_limit + lower_limit)/2;
			else
				upper_limit = (upper_limit + lower_limit)/2;
		}
		myelement_ptr_t element;
		if(sID == ((myelement_ptr_t)list_get_element_at_index(list, upper_limit))->sensorID)
			element = (myelement_ptr_t)list_get_element_at_index(list, upper_limit);
		else
			element = (myelement_ptr_t)list_get_element_at_index(list, lower_limit);
		if(queue_size(element->data) == QUEUE_SIZE)
			queue_dequeue(element->data);
		double *queue_element = (double *)malloc(sizeof(double));
		if(queue_element == NULL)
			perror("Element malloc failed.");
		*queue_element = sensor_data->temperature;
		queue_enqueue(element->data, (element_t)queue_element);
		if(queue_size(element->data) < QUEUE_SIZE)
		{
			double sum = 0;
			element_t temp;
			int j;
			for(j=0;j<queue_size(element->data);j++)
			{
				temp = *queue_get_element_at_index(element->data,j);
				sum = sum + *(double*)temp;
			}
			element->running_avg = sum/queue_size(element->data);
		}
		else
		{
			double sum = 0;
			element_t temp;
			int j;
			for(j=0;j<QUEUE_SIZE;j++)
			{
				temp = *queue_get_element_at_index(element->data,j);
				sum = sum + *(double*)temp;
			}
			element->running_avg = sum/QUEUE_SIZE;
		}
		element->last_modified = sensor_data->timestamp;
		if(element->running_avg < SET_MIN_TEMP)
		{
			sprintf(note,"The sensor node with %u in room %u reports it's too cold.\n",element->sensorID,element->roomID);
			fifo_puts(note, fifo_fp);
		}
		if(element->running_avg > SET_MAX_TEMP)
		{
			sprintf(note,"The sensor node with %u in room %u reports it's too hot.\n",element->sensorID,element->roomID);
			fifo_puts(note, fifo_fp);
		}
	}

}




