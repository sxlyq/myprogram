#ifndef DATAMGR_H_
#define DATAMGR_H_
#include "list.h"
#include <stdio.h>
#include "myqueue.h"
#include "myfifo.h"

typedef struct element myelement_t;
typedef myelement_t *myelement_ptr_t;
typedef struct queue_data
{
	uint16_t sensor_id;
	double temperature;
	time_t timestamp;
	int count;
}queue_data_t;

//read room sensor map from path and create sensor node list
list_ptr_t create_sensor_list(const char *path);

//read sensor data from path and store data in list
void read_sensor_data(queue_data_t* sensor_data, list_ptr_t list, FILE *fifo_fp);

#endif
