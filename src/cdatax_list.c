#include "cdatax_list.h"
#include <assert.h>

CDATAX_LIST *internal_cdatax_list_new(const size_t dataLen)
{
	assert(dataLen > 0);
    CDATAX_LIST* list = calloc(1, sizeof(CDATAX_LIST));
	*(size_t*)&list->dataLen = dataLen;
    return list;
}

void internal_cdatax_list_delete(const CDATAX_LIST *list)
{
	if(list == NULL)
		return;
	const struct _CDARAX_LIST_NODE_* node = list->head;
	const struct _CDARAX_LIST_NODE_* current = NULL;
	while(node)
	{
		current = node;
		node = node->next;
		free(current->data);
		free((void*)current);
	}
	free((void*)list);
}

void *internal_cdatax_list_at(const CDATAX_LIST *list, const size_t dataLen, const uint32_t index)
{
	assert(list && dataLen == list->dataLen && index < list->count);
	struct _CDARAX_LIST_NODE_* node = NULL;
	if(index < ((list->count - 1)/2))
	{
		int i = 0;
		node = list->head;
		while(node && i++ != index)
			node = node->next;
	}
	else
	{
		int i = list->count - 1;
		node = list->tail;
		while(node && i-- != index)
			node = node->previous;
	}
    return node->data;
}

void* internal_cdatax_list_insert(CDATAX_LIST *list, const size_t dataLen, uint32_t index)
{
    assert(list && dataLen == list->dataLen && index <= list->count);
	struct _CDARAX_LIST_NODE_** node = NULL;
	if(index < (list->count/2) || index == 0)
	{
		int i = 0;
		node = (struct _CDARAX_LIST_NODE_**)&list->head;
		while(*node && i++ != index)
			node = &(*node)->next;
	}
	else
	{
		int i = list->count;
		node = (struct _CDARAX_LIST_NODE_**)&list->tail;
		while(*node && i-- != index)
			node = &(*node)->previous;
	}
	struct _CDARAX_LIST_NODE_* newNode = malloc(sizeof(struct _CDARAX_LIST_NODE_));
	*(void**)&newNode->data = malloc(dataLen);
	if(list->count > 0)
	{
		if(index == 0)
		{
			newNode->previous = NULL;
			newNode->next = (*node);
			(*node)->previous = newNode;
			*node = newNode;
		}
		else if(index == list->count)
		{
			(*node)->next = newNode;
			newNode->previous = (*node);
			newNode->next = NULL;
			*(struct _CDARAX_LIST_NODE_**)&list->tail = newNode;
		}
		else
		{
			(*node)->previous->next = newNode;
			newNode->previous = (*node)->previous;
			newNode->next = *node;
		}
	}
	else
	{
		newNode->previous = NULL;
		newNode->next = NULL;
		*node = newNode;
		*(struct _CDARAX_LIST_NODE_**)&list->tail = newNode;
	}
	++*(uint32_t*)&list->count;
    return newNode->data;
}
