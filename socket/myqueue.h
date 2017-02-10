#ifndef MYQUEUE_
#define MYQUEUE_

#include <pthread.h>

typedef struct queue queue_t;

/*
 ** The default queue size is 5
 */
#ifndef QUEUE_SIZE
    #define QUEUE_SIZE 5
#endif

/*
 **  Make some changes here to define the type of element that will be stored in the queue
 */

typedef void* element_t;

/*
 **  Creates (memory allocation!) and initializes the queue and prepares it for usage
 **  Return a pointer to the newly created queue
 **  Returns NULL if queue creation failed
 */
queue_t* queue_create(
			void (*element_print)(element_t element),
  			void (*element_copy)(element_t *dest_element, element_t src_element),
  			void (*element_free)(element_t *element)
		     );

/*  
 **  Add an element to the queue
 **  Does nothing if queue is full
 */
void queue_enqueue(queue_t* queue, element_t element);

/*  
 **  Add an element to the queue
 **  overwrite the rear element if queue is full
 */
void queue_overwrite_enqueue(queue_t* queue, element_t element);

/*
 **  Delete the queue from memory; set queue to NULL
 **  The queue can no longer be used unless queue_create is called again
 */
void queue_free(queue_t** queue);

/*
 **  Return the number of elements in the queue
 */
int queue_size(queue_t* queue);

/*
 **  Return a pointer to the top element in the queue
 **  Returns NULL if queue is empty
 */
element_t* queue_top(queue_t* queue);

/*
 **  Remove the top element from the queue
 **  Does nothing if queue is empty
 */
void queue_dequeue(queue_t* queue);

/*
 **  Print all elements in the queue, starting from the front element
 */
void queue_print(queue_t *queue);

/*
 **index start from 0, and the element of index 0 is the front element 
 */
element_t* queue_get_element_at_index(queue_t* queue,int index);

#endif //MYQUEUE_


