#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include "list.h"
#include "myqueue.h"
#include "datamgr.h"
#include "sensor_db.h"
#include "tcpsocket.h"
#include "myfifo.h"

#define UNIT_SIZE 10
#define FIFO_NAME 	"logFifo"

#ifndef SET_TIMEOUT
#error SET_TIMEOUT(in seconds) is not defined
#endif

typedef struct
{
	Socket socket;
	time_t last_active;
	uint16_t ID;
	int flag;       // Initially,flag is 0. After receiving data from socket, flag is 1.
}mysocket;


int list_errno;

void clean_client(element_ptr_t *element)
{
	mysocket* temp_socket = (mysocket*)*element;
	tcp_close(&(temp_socket->socket));
	free(*element);
	*element = NULL;
}

static void queue_element_free(element_t *element)
{
	free(*element);
	*element = NULL;
}

static void queue_element_print(element_t element)
{
	queue_data_t* data = (queue_data_t*)element;
	printf("sensorID: %u, temperature: %.2f, timestamp: %s\n",data->sensor_id,data->temperature,ctime(&(data->timestamp)));
}

FILE *fifo_fp;
Socket server;
list_ptr_t socket_list;
list_ptr_t sensor_list;
queue_t* shared_queue;
MYSQL *mySQL;
struct epoll_event *event_ptr;
struct epoll_event *events;
int num;
int epfd;
int flag;
int socket_num;
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

void sighandler(int sig)
{
	signal(SIGINT,sighandler);
	flag=0;	
}


void *data_manager(void* a)
{
	pthread_detach(pthread_self());
	while(flag)
	{
		if(queue_size(shared_queue)>0)
		{
			queue_data_t **top_elem_ptr = (queue_data_t**)queue_top(shared_queue);	
			if(pthread_mutex_lock( &data_mutex ) != 0)
				perror("pthread mutex lock failed\n");
			if(top_elem_ptr != NULL)
			{
				if((*top_elem_ptr) != NULL)
				{
					if(((*top_elem_ptr)->count)%10 != 1)
					{
						if(pthread_mutex_unlock( &data_mutex ) != 0)
							perror("pthread mutex unlock failed\n");
						queue_data_t *top_elem = *top_elem_ptr;
						read_sensor_data(top_elem, sensor_list, fifo_fp);
						top_elem->count += 1;
						if(pthread_mutex_lock( &data_mutex ) != 0)
							perror("pthread mutex lock failed\n");
						top_elem = (queue_data_t*)*queue_top(shared_queue);
						if(top_elem != NULL)
						{
							if(top_elem->count == 11)
							{
								queue_dequeue(shared_queue);
							}
						}
						if(pthread_mutex_unlock( &data_mutex ) != 0)
							perror("pthread mutex unlock failed\n");
						#ifdef DEBUG
						printf("data manager: sensor id = %d - temperature = %.2f - timestamp = %s\n", top_elem->sensor_id, top_elem->temperature, ctime(&(top_elem->timestamp)));
						#endif
					}
					else
					{
						if(pthread_mutex_unlock( &data_mutex ) != 0)
							perror("pthread mutex unlock failed\n");
					}
				}
				else
				{	
					if(pthread_mutex_unlock( &data_mutex ) != 0)
						perror("pthread mutex unlock failed\n");
				}
			}
			else
			{
				if(pthread_mutex_unlock( &data_mutex ) != 0)
					perror("pthread mutex unlock failed\n");
			}
		}
	}
	pthread_exit( NULL );
}

void *storage_manager(void* a)
{
	pthread_detach(pthread_self());
	char note[100];
	while(flag)
	{
		if(queue_size(shared_queue)>0)
		{
			queue_data_t **top_elem_ptr = (queue_data_t**)queue_top(shared_queue);	
			if(pthread_mutex_lock( &data_mutex ) != 0)
				perror("pthread mutex lock failed\n");	
			if(top_elem_ptr != NULL)
			{
				if((*top_elem_ptr) != NULL)
				{
					if(((*top_elem_ptr)->count)/10 != 1)
					{
						if(pthread_mutex_unlock( &data_mutex ) != 0)
							perror("pthread mutex unlock failed\n");
						queue_data_t *top_elem = *top_elem_ptr;
						if(insert_sensor(mySQL, top_elem->sensor_id, top_elem->temperature, top_elem->timestamp) != 0)
						{
							printf(note,"%s\n",get_error_message(mySQL));
							fifo_puts(note, fifo_fp);
							sleep(1);
							insert_sensor(mySQL, top_elem->sensor_id, top_elem->temperature, top_elem->timestamp);
						}
						top_elem->count += 10;
						if(pthread_mutex_lock( &data_mutex ) != 0)
							perror("pthread mutex lock failed\n");
						top_elem = (queue_data_t*)*queue_top(shared_queue);
						if(top_elem != NULL)
						{
							if(top_elem->count == 11)
							{
								queue_dequeue(shared_queue);
							}
						}
						if(pthread_mutex_unlock( &data_mutex ) != 0)
							perror("pthread mutex unlock failed\n");
						#ifdef	DEBUG					
						printf("storage manager: sensor id = %d - temperature = %.2f - timestamp = %s\n", top_elem->sensor_id, top_elem->temperature, ctime(&(top_elem->timestamp)));
						#endif
					}
					else
					{
						if(pthread_mutex_unlock( &data_mutex ) != 0)
							perror("pthread mutex unlock failed\n");
					}		
				}
				else
				{
					if(pthread_mutex_unlock( &data_mutex ) != 0)
						perror("pthread mutex unlock failed\n");
				}
			}
			else
			{
				if(pthread_mutex_unlock( &data_mutex ) != 0)
					perror("pthread mutex unlock failed\n");
			}
		}
	}
	pthread_exit( NULL );
}

void receive_data_handler(mysocket *client)
{
	queue_data_t* data = (queue_data_t*)malloc(sizeof(queue_data_t));

	if(data == NULL)
	{
		perror("queue data malloc failed.\n");
		return;
	}
	data->count = 0;
	char note[100];
	int bytes;
	bytes = tcp_receive(client->socket, (void *)&(data->sensor_id), sizeof(data->sensor_id));
	if(client->flag == 0)
	{
  		sprintf(note,"A sensor node with sensorID %u has opened a new connection.\n",data->sensor_id);
		fifo_puts(note, fifo_fp);
		printf("%s",note);
		printf("\n");
		client->flag = 1;
		client->ID = data->sensor_id;
	}
	if((bytes != sizeof(data->sensor_id))&&(bytes != 0))
	{
		printf("An error occurred. The received sensor_id is abnormal.\n");
	}
	bytes = tcp_receive(client->socket, (void *)&(data->temperature), sizeof(data->temperature));
	if((bytes != sizeof(data->temperature))&&(bytes != 0))
	{
		printf("An error occurred. The received temperature is abnormal.\n");
	}
	bytes = tcp_receive(client->socket, (void *)&(data->timestamp), sizeof(data->timestamp));
	if((bytes != sizeof(data->timestamp))&&(bytes != 0))
	{
		printf("An error occurred. The received timestamp is abnormal.\n");
	}
	if (bytes) 
	{
		client->last_active = data->timestamp;
		if(queue_size(shared_queue) == QUEUE_SIZE)
		{
			strcpy(note,"Circular queue is full: started to overwrite data.\n");
			fifo_puts(note, fifo_fp);
		}
		queue_overwrite_enqueue(shared_queue, (element_t)data);		
		printf("Receive data: sensor id = %d - temperature = %.2f - timestamp = %s\n", data->sensor_id, data->temperature, ctime(&(data->timestamp)));
	}
	else
		free(data);
}

void create_new_connection()
{
	mysocket* newclient = (mysocket*)malloc(sizeof(mysocket));
	if(newclient == NULL)
		perror("new client malloc failed.\n");
	newclient->socket = tcp_wait_for_connection( server );
	newclient->last_active = time(NULL);
	newclient->flag = 0;
	socket_list = list_insert_at_index(socket_list,(element_ptr_t)newclient,socket_num);
	socket_num++;
	if(socket_num > num)
	{
		num = num+UNIT_SIZE;
		struct epoll_event *temp = event_ptr;
		event_ptr = (struct epoll_event *)realloc((void*)event_ptr,sizeof(struct epoll_event)*num);
		if(event_ptr == NULL)
			free(temp);
		events = (struct epoll_event *)realloc((void*)event_ptr,sizeof(struct epoll_event)*num);
		(event_ptr+socket_num-1)->data.u64 = (uint64_t)get_socket_descriptor(newclient->socket);
		(event_ptr+socket_num-1)->data.fd = get_socket_descriptor(newclient->socket);
		(event_ptr+socket_num-1)->events = EPOLLIN|EPOLLRDHUP|EPOLLET;
		if(epoll_ctl(epfd,EPOLL_CTL_ADD,get_socket_descriptor(newclient->socket),event_ptr+socket_num-1) != 0)
		{
			perror("epoll control add failed\n");
		}
	}
	else
	{
		(event_ptr+socket_num-1)->data.u64 = (uint64_t)get_socket_descriptor(newclient->socket);
		(event_ptr+socket_num-1)->data.fd = get_socket_descriptor(newclient->socket);
		(event_ptr+socket_num-1)->events = EPOLLIN|EPOLLRDHUP|EPOLLET;
		if(epoll_ctl(epfd,EPOLL_CTL_ADD,get_socket_descriptor(newclient->socket),event_ptr+socket_num-1) != 0)
		{
			perror("epoll control add failed\n");
		}
	}
}

int main(int argc, char *argv[])
{
	char note[100];
	flag = 1;
	if (argc != 2)
  	{
    		printf("Please give the port number");
    		exit(EXIT_SUCCESS);
  	}
	int port = atoi(argv[1]);
	socket_list = list_create(NULL,&clean_client,NULL,NULL);
	shared_queue = queue_create(&queue_element_print,NULL,&queue_element_free);
	sensor_list = create_sensor_list("./room_sensor.map");
	create_fifo(FIFO_NAME, 0666);
	fifo_fp = fopen(FIFO_NAME, "w");
	if (!fifo_fp) 
	{
		perror("FIFO open failed\n");
	}
	mySQL = init_connection(1);
	
	if(mySQL == NULL)
	{
		strcpy(note,"Unable to connect to SQL server.\n");
		fifo_puts(note, fifo_fp);
	}
	else
	{
		strcpy(note,"Connection to SQL server established.\n");
		fifo_puts(note, fifo_fp);
	}
	server = tcp_passive_open( port );
	num = UNIT_SIZE;
	event_ptr = (struct epoll_event*)malloc(UNIT_SIZE*sizeof(struct epoll_event));
	events = (struct epoll_event*)malloc(UNIT_SIZE*sizeof(struct epoll_event));
	if((event_ptr == NULL) || (events == NULL))
		perror("epoll event malloc failed.\n");
	event_ptr->data.u64 = (uint64_t)get_socket_descriptor(server);
	event_ptr->data.fd = get_socket_descriptor(server);
	event_ptr->events = EPOLLIN|EPOLLET;
	epfd = epoll_create(1);
	if(epfd < 0)
	{
		perror("epoll create failed\n");
	}
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,get_socket_descriptor(server),event_ptr) != 0)
	{
		perror("epoll control add failed\n");
	}	
	
	socket_num = list_size(socket_list)+1;
	signal(SIGINT,sighandler);
	pthread_t thread1, thread2;
	if(pthread_create(&thread1,NULL,&data_manager,NULL) != 0)
		perror("pthread create failed\n");
	if(pthread_create(&thread2,NULL,&storage_manager,NULL) != 0)
		perror("pthread create failed\n");
	while(flag)
	{
		int result;
		result = epoll_wait(epfd,events,socket_num,0);
		if(result < 0)
			perror("epoll wait failed\n");
		if(result > 0)
		{
			int i;
			for ( i = 0; i < result; i++ )
   			{
				if(((events+i)->data).fd == get_socket_descriptor(server))
					create_new_connection();
      				else if(((events+i)->events) & EPOLLIN) 
      				{
					int j;
					mysocket* client;
					for(j=0;j<socket_num-1;j++)
					{
						client = (mysocket*)list_get_element_at_index(socket_list,j);
						if(get_socket_descriptor(client->socket) == ((events+i)->data).fd)
							receive_data_handler(client);
						else
						{
							if(difftime(time(NULL),client->last_active) > SET_TIMEOUT)
							{
								char note[100];
								sprintf(note,"A sensor node with sensorID %u has closed the connection.\n",client->ID); 
								fifo_puts(note, fifo_fp);
								socket_list = list_free_at_index(socket_list,j);
								socket_num--;
								j--;
							}	
						}
					}					
      				}
      				else if ((((events+i)->events) & EPOLLHUP)||(((events+i)->events) & EPOLLRDHUP)) 
      				{
					if(epoll_ctl(epfd,EPOLL_CTL_DEL,((events+i)->data).fd,event_ptr) != 0)
					{
						perror("epoll control delete failed\n");
					}
      				}
				else
					perror("other event occured\n");
    			}
		}
		
	}
	sleep(5);
	my_list_free(&socket_list);
	my_list_free(&sensor_list);
	fclose(fifo_fp);
	tcp_close(&server);
	free(event_ptr);
	free(events);
	queue_free(&shared_queue);
	disconnect(mySQL);
	if(pthread_mutex_destroy(&data_mutex) != 0)
		printf("An error ocurred to pthread_mutex_destroy.\n");	
	return 0;	
}




