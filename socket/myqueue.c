#include <stdio.h>
#include "myqueue.h"
#include <stdlib.h>
#include <assert.h>

/*
 * The real definition of 'struct queue'
 */
struct queue {
  element_t *arr; // dynamic array containing data elements
  int current_size; // Counts number of elements in the queue
  int front, rear;
  pthread_mutex_t *queue_mutex;// Remark for later: extra fields need to be added here to make it a thread-safe queue as needed
  void (*element_print)(element_t element);
  void (*element_copy)(element_t *dest_element, element_t src_element);
  void (*element_free)(element_t *element);
};


queue_t* queue_create(
			void (*element_print)(element_t element),
  			void (*element_copy)(element_t *dest_element, element_t src_element),
  			void (*element_free)(element_t *element)
		     )
{
	queue_t *queue_ptr = (queue_t*)malloc(sizeof(queue_t));
	if(queue_ptr == NULL)
		return NULL;
	queue_ptr->arr = (element_t*)malloc(QUEUE_SIZE*sizeof(element_t));
	assert(queue_ptr->arr);
	queue_ptr->current_size = 0;
	queue_ptr->front = 0;
	queue_ptr->rear = 0;
	queue_ptr->queue_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(queue_ptr->queue_mutex,NULL);
	queue_ptr->element_print = element_print;
	queue_ptr->element_copy = element_copy;
	queue_ptr->element_free = element_free;
	return queue_ptr;
}

void queue_free(queue_t** queue)
{
	if(pthread_mutex_lock( (*queue)->queue_mutex ) != 0)
		perror("pthread mutex lock failed\n");
	int i;
	for(i=(*queue)->front;i<((*queue)->front+(*queue)->current_size);i++)
		((*queue)->element_free)((*queue)->arr+i%QUEUE_SIZE);
	pthread_mutex_t *temp_mutex = (*queue)->queue_mutex;
	free((*queue)->arr);
	free(*queue);
	*queue = NULL;
	if(pthread_mutex_unlock( temp_mutex ) != 0)
		perror("pthread mutex unlock failed\n");
	if(pthread_mutex_destroy(temp_mutex) != 0)
		perror("An error occurred to pthread_mutex_destroy.\n");
	free(temp_mutex);
}

void queue_enqueue(queue_t* queue, element_t element)
{
	if(pthread_mutex_lock( queue->queue_mutex ) != 0)
		perror("pthread mutex lock failed\n");
	if(queue->current_size < QUEUE_SIZE)
	{
		*(queue->arr+queue->rear) = element;
		queue->rear++;
		queue->current_size++;
	}
	else
		printf("The queue is already full, no more element can be added\n");
	if(queue->rear >= QUEUE_SIZE)
		queue->rear = queue->rear%QUEUE_SIZE;	
	#ifdef  DEBUG_PRINTF
		printf("The size of queue is %d\n",queue_size(queue));
		queue_print(queue);
	#endif
	if(pthread_mutex_unlock( queue->queue_mutex ) != 0)
		perror("pthread mutex unlock failed\n");
}

void queue_overwrite_enqueue(queue_t* queue, element_t element)
{
	if(pthread_mutex_lock( queue->queue_mutex ) != 0)
		perror("pthread mutex lock failed\n");
	if(queue->current_size < QUEUE_SIZE)
	{
		*(queue->arr+queue->rear) = element;
		queue->rear++;
		queue->current_size++;
	}
	else
	{
		(queue->element_free)(queue->arr+(queue->rear-1));
		*(queue->arr+(queue->rear-1)) = element;		
	}
	if(queue->rear >= QUEUE_SIZE)
		queue->rear = queue->rear%QUEUE_SIZE;	
	#ifdef  DEBUG_PRINTF
		printf("The size of queue is %d\n",queue_size(queue));
		queue_print(queue);
	#endif
	if(pthread_mutex_unlock( queue->queue_mutex ) != 0)
		perror("pthread mutex unlock failed\n");
}

int queue_size(queue_t* queue)
{
	return queue->current_size;
}

element_t* queue_top(queue_t* queue)
{
	if(queue->current_size>0)
		return queue->arr+queue->front;
	else
		return NULL;
}

element_t* queue_get_element_at_index(queue_t* queue,int index)
{
	if(queue->current_size > index)
	{
		if((queue->front+index) >= QUEUE_SIZE)
			return queue->arr+((queue->front+index)%QUEUE_SIZE);
		else
			return queue->arr+(queue->front+index);
	}

	else
		return NULL;
}

void queue_dequeue(queue_t* queue)
{
	if(pthread_mutex_lock( queue->queue_mutex ) != 0)
		perror("pthread mutex lock failed\n");
	if(queue->current_size > 0)
	{
		(queue->element_free)(queue->arr+queue->front);
		queue->front++;
		queue->current_size--;
	}
	else
		printf("There is no element in the queue\n");
	if(queue->front >= QUEUE_SIZE)
		queue->front = queue->front%QUEUE_SIZE;	
	#ifdef  DEBUG_PRINTF
		printf("The size of queue is %d\n",queue_size(queue));
		queue_print(queue);
	#endif
	if(pthread_mutex_unlock( queue->queue_mutex ) != 0)
		perror("pthread mutex unlock failed\n");
}

void queue_print(queue_t *queue)
{
	int i;
	if(queue->rear > queue->front)
	{
		for(i=queue->front;i<queue->rear;i++)
			(queue->element_print)(*(queue->arr+i));	
	}
	if((queue->rear == queue->front) && (queue->current_size > 0))
	{
		for(i=queue->front;i<queue->front+QUEUE_SIZE;i++)
			(queue->element_print)(*(queue->arr+(i%QUEUE_SIZE)));
	}
	if(queue->rear < queue->front)
	{
		for(i=queue->front;i<queue->rear+QUEUE_SIZE;i++)
			(queue->element_print)(*(queue->arr+(i%QUEUE_SIZE)));
	}

}



