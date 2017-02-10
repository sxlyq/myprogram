#include<stdio.h>
#include<stdlib.h>
#include"list.h"

struct list
{
	list_node_ptr_t head_ptr;
	int list_size;
	void (*copy)(element_ptr_t *dest_element, element_ptr_t src_element);
	void (*free)(element_ptr_t *element);
	int (*compare)(element_ptr_t x, element_ptr_t y);
	void (*print)(element_ptr_t element);
};

struct list_node
{
	element_ptr_t element;
	list_node_ptr_t previous;
	list_node_ptr_t next;
};

list_ptr_t list_create 	( 
			  void (*element_copy)(element_ptr_t *dest_element, element_ptr_t src_element),
			  void (*element_free)(element_ptr_t *element),
			  int (*element_compare)(element_ptr_t x, element_ptr_t y),
			  void (*element_print)(element_ptr_t element)
			)
{
	list_ptr_t list_ptr = (list_ptr_t)malloc(sizeof(list_t));
	if(list_ptr == NULL)
	{
		list_errno = LIST_MEMORY_ERROR;
		return NULL;
	}
	else
		list_errno = LIST_NO_ERROR;
	list_ptr->head_ptr = NULL;
	list_ptr->list_size = 0;
	list_ptr->copy = element_copy;
	list_ptr->free = element_free;
	list_ptr->compare = element_compare;
	list_ptr->print = element_print;
	return list_ptr;	
}

void my_list_free( list_ptr_t* list )
{
	if((*list) == NULL)
	{
		list_errno = LIST_NO_ERROR;
		return;
	}
	while((*list)->list_size>0)
	{
		list_free_at_index(*list, 0);
	}
	free(*list);
	*list = NULL;
	list_errno = LIST_NO_ERROR;
}

int list_size( list_ptr_t list )
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return -1;
	}
	return list->list_size;
}

list_ptr_t list_insert_at_index( list_ptr_t list, element_ptr_t element, int index)
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return NULL;
	}
	if(list->head_ptr == NULL)
	{
		list->head_ptr = (list_node_ptr_t)malloc(sizeof(list_node_t));
		if(list->head_ptr == NULL)
		{
			list_errno = LIST_MEMORY_ERROR; 
			return NULL;
		}
		else
			list_errno = LIST_NO_ERROR;
		(list->head_ptr)->element = element;
		(list->head_ptr)->next = (list->head_ptr);
		(list->head_ptr)->previous = (list->head_ptr);
	}
	else if(index >= list->list_size || index <= 0)
	{
		list_node_ptr_t temp = (list->head_ptr)->previous;
		(list->head_ptr)->previous = (list_node_ptr_t)malloc(sizeof(list_node_t));
		if((list->head_ptr)->previous == NULL)
		{
			list_errno = LIST_MEMORY_ERROR; 
			return NULL;
		}
		else
			list_errno = LIST_NO_ERROR;
		((list->head_ptr)->previous)->element = element;
		((list->head_ptr)->previous)->next = list->head_ptr;
		((list->head_ptr)->previous)->previous = temp;
		temp->next = (list->head_ptr)->previous;
		if(index <= 0)
			list->head_ptr = (list->head_ptr)->previous;
	}
	else
	{
		int i;
		list_node_ptr_t track_ptr = list->head_ptr;
		for(i=0;i<index-1;i++)
		{
			track_ptr = track_ptr->next;
		}
		list_node_ptr_t temp = track_ptr->next;
		track_ptr->next = (list_node_ptr_t)malloc(sizeof(list_node_t));
		if(track_ptr->next == NULL)
		{
			list_errno = LIST_MEMORY_ERROR; 
			return NULL;			
		}
		else
			list_errno = LIST_NO_ERROR;
		(track_ptr->next)->element = element;
		(track_ptr->next)->next = temp;
		(track_ptr->next)->previous = track_ptr;
		temp->previous = track_ptr->next;
	}
	(list->list_size)++;	
	return list;
}

list_ptr_t list_remove_at_index( list_ptr_t list, int index)
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return NULL;
	}
	if(list->head_ptr == NULL)
	{
		list_errno = LIST_EMPTY_ERROR;		
		return list;
	}
	else
		list_errno = LIST_NO_ERROR;
	if(index <= 0)
	{
		list_node_ptr_t temp = list->head_ptr;
		list->head_ptr = (list->head_ptr)->next;
		(list->head_ptr)->previous = temp->previous;
		(temp->previous)->next = list->head_ptr;
		if(list->head_ptr == temp)
			list->head_ptr = NULL;
		free(temp);
	
	}
	else if(index >= list->list_size)
	{
		list_node_ptr_t temp = (list->head_ptr)->previous;
		(list->head_ptr)->previous = temp->previous;
		(temp->previous)->next = list->head_ptr;
		if(list->head_ptr == temp)
			list->head_ptr = NULL;
		free(temp);
	}
	else
	{
		int i;
		list_node_ptr_t track_ptr = list->head_ptr;
		for(i=0;i<index-1;i++)
		{
			track_ptr = track_ptr->next;
		}
		list_node_ptr_t temp = track_ptr->next;
		track_ptr->next = (track_ptr->next)->next;
		(track_ptr->next)->previous = track_ptr;
		if(list->head_ptr == temp)
			list->head_ptr = NULL;
		free(temp);
	}
	(list->list_size)--;
	return list;	
}

list_ptr_t list_free_at_index( list_ptr_t list, int index)
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return NULL;
	}
	if(list->head_ptr == NULL)
	{
		list_errno = LIST_EMPTY_ERROR;		
		return list;
	}
	else
		list_errno = LIST_NO_ERROR;
	if(index <= 0)
	{
		list_node_ptr_t temp = list->head_ptr;
		list->head_ptr = (list->head_ptr)->next;
		(list->head_ptr)->previous = temp->previous;
		(temp->previous)->next = list->head_ptr;
		if(temp->element != NULL)
			(list->free)(&(temp->element));
		if(list->head_ptr == temp)
			list->head_ptr = NULL;
		free(temp);
	}
	else if(index >= list->list_size)
	{
		list_node_ptr_t temp = (list->head_ptr)->previous;
		(list->head_ptr)->previous = temp->previous;
		(temp->previous)->next = list->head_ptr;
		if(temp->element != NULL)
			(list->free)(&(temp->element));
		if(list->head_ptr == temp)
			list->head_ptr = NULL;
		free(temp);
	}
	else
	{
		int i;
		list_node_ptr_t track_ptr = list->head_ptr;
		for(i=0;i<index-1;i++)
		{
			track_ptr = track_ptr->next;
		}
		list_node_ptr_t temp = track_ptr->next;
		track_ptr->next = (track_ptr->next)->next;
		(track_ptr->next)->previous = track_ptr;
		if(temp->element != NULL)
			(list->free)(&(temp->element));
		if(list->head_ptr == temp)
			list->head_ptr = NULL;
		free(temp);
	}
	(list->list_size)--;
	return list;
}

list_node_ptr_t list_get_reference_at_index( list_ptr_t list, int index )
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return NULL;
	}
	if(list->head_ptr == NULL)
	{	
		return NULL;
	}
	else if(index <= 0)
	{
		return list->head_ptr;
	}
	else if(index >= list->list_size)
	{
		return (list->head_ptr)->previous;
	}
	else
	{
		int i;
		list_node_ptr_t track_ptr = list->head_ptr;
		for(i=0;i<index;i++)
		{
			track_ptr = track_ptr->next;
		}
		return track_ptr;
	}
}


element_ptr_t list_get_element_at_index( list_ptr_t list, int index )
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return NULL;
	}
	if(list->head_ptr == NULL)
	{	
		return NULL;
	}
	else if(index <= 0)
	{
		return (list->head_ptr)->element;
	}
	else if(index >= list->list_size)
	{
		return ((list->head_ptr)->previous)->element;
	}
	else
	{
		int i;
		list_node_ptr_t track_ptr = list->head_ptr;
		for(i=0;i<index;i++)
		{
			track_ptr = track_ptr->next;
		}
		return track_ptr->element;
	}
}

int list_get_index_of_element( list_ptr_t list, element_ptr_t element )
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return -1;
	}
	int i;
	for(i=0;i<list->list_size;i++)
	{
		if(list_get_element_at_index(list,i) == element)
			return i;
	}
	return -1;
}

void list_print( list_ptr_t list )
{
	if(list == NULL)
	{
		list_errno = LIST_INVALID_ERROR;
		return;
	}
	int i;
	for(i=0;i<list->list_size;i++)
	{
		(list->print)(list_get_element_at_index(list,i));
	}
}

list_ptr_t list_insert_sorted( list_ptr_t list, element_ptr_t element )
{
	if((list == NULL)||(list->head_ptr == NULL))
		return list_insert_at_index(list, element, 0);
	if((list->compare)(element, (list->head_ptr)->element)<0)
		return list_insert_at_index(list, element, 0);
	if((list->compare)(element, ((list->head_ptr)->previous)->element)>0)
		return list_insert_at_index(list, element, list->list_size);
	int upper_limit = (list->list_size)-1;
	int lower_limit = 0;
	while(upper_limit - lower_limit > 1)
	{
		if((list->compare)(element,list_get_element_at_index(list, (upper_limit + lower_limit)/2)) > 0)
			lower_limit = (upper_limit + lower_limit)/2;
		else
			upper_limit = (upper_limit + lower_limit)/2;
	}
	return list_insert_at_index(list, element, upper_limit);	
}






















