#include "cdatax_list.h"

CDATAX_LIST *__cdatax_list_new__(uint32_t dataLen)
{
	assert(dataLen > 0);
    CDATAX_LIST* list = calloc(1, sizeof(CDATAX_LIST));
	memcpy((void*)&list->dataLen, &dataLen, sizeof(uint32_t));
    return list;
}

void __cdatax_list_delete__(CDATAX_LIST *list)
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
	free(list);
}

void *__cdatax_list_at__(CDATAX_LIST *list, uint32_t dataLen, uint32_t index)
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

void* __cdatax_list_insert__(CDATAX_LIST *list, uint32_t dataLen, uint32_t index)
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
	newNode->data = malloc(dataLen);
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
			memcpy((void*)&list->tail, &newNode, sizeof(void*));
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
		memcpy((void*)&list->tail, &newNode, sizeof(void*));
	}
	dataLen = list->count + 1;
	memcpy((void*)&list->count, &dataLen, sizeof(uint32_t));
    return newNode->data;
}
