#ifndef CDATAX_LIST_H
#define CDATAX_LIST_H 
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#define cdatax_list_new(_DataType)\
	(CDATAX_LIST*)internal_cdatax_list_new(sizeof(_DataType))

#define cdatax_list_delete(_List)\
	internal_cdatax_list_delete(_List)

#define cdatax_list_insert(_List, _Type, _Data, _Index)\
	*((_Type*)internal_cdatax_list_insert(_List, sizeof(_Type), _Index)) = _Data

#define cdatax_list_append(_List, _Type, _Data)\
	*((_Type*)internal_cdatax_list_insert(_List, sizeof(_Type), _List->count)) = _Data

#define cdatax_list_at(_List, _Type, _Index)\
	(*((_Type*)internal_cdatax_list_at(_List, sizeof(_Type), _Index)))

#define cdatax_list_first(_List, _Type)\
	(*((_Type*)internal_cdatax_list_at(_List, sizeof(_Type), 0)))

#define cdatax_list_last(_List, _Type)\
	(*((_Type*)internal_cdatax_list_at(_List, sizeof(_Type), _List->count - 1)))

#define cdatax_list_foreach(_Type, _pData, _List)\
	if(_List->dataLen == sizeof(_Type))\
		for(struct _CDARAX_LIST_NODE_* _node_ = _List->head; _node_ != NULL; _node_ = _node_->next)\
			for(_Type* _pData = (_Type*)_node_->data; _pData != NULL; _pData = NULL)

struct _CDARAX_LIST_NODE_{
	void* data; 
	struct _CDARAX_LIST_NODE_* previous;
	struct _CDARAX_LIST_NODE_* next;
};
typedef struct{
	struct _CDARAX_LIST_NODE_* const head;
	struct _CDARAX_LIST_NODE_* const tail;
    const uint32_t dataLen;
	const uint32_t count;
}CDATAX_LIST;

#ifdef __cplusplus
extern "C"
{
#endif

	CDATAX_LIST* internal_cdatax_list_new(uint32_t dataLen);
	void internal_cdatax_list_delete(CDATAX_LIST* list);
	void* internal_cdatax_list_insert(CDATAX_LIST* list, uint32_t dataLen, uint32_t index);
	void* internal_cdatax_list_at(CDATAX_LIST* list, uint32_t dataLen, uint32_t index);

#ifdef __cplusplus
}
#endif
#endif //CDATAX_LIST_H