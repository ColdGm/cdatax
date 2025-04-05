#ifndef CDATAX_ARRAY_H
#define CDATAX_ARRAY_H 
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
    
typedef struct{
    void* dataArray;
    const uint32_t dataLen;
    const uint32_t reserve_size;
    const uint32_t count;
}CDATAX_ARRAY;

#define cdatax_array_new(_Type)\
    (CDATAX_ARRAY*)internal_cdatax_array_new(sizeof(_Type))

#define cdatax_array_delete(_Array)\
    internal_cdatax_array_delete(_Array)

#define cdatax_array_append(_Array, _Type, _Data)\
    (*(_Type*)internal_cdatax_array_append(_Array, sizeof(_Type)) = _Data)

#define cdatax_array_at(_Array, _Type, _Index)\
    (*(_Type*)internal_cdatax_array_at(_Array, sizeof(_Type), _Index))

#define cdatax_array_first(_Array, _Type)\
    (*(_Type*)internal_cdatax_array_at(_Array, sizeof(_Type), 0))

#define cdatax_array_last(_Array, _Type)\
    (*(_Type*)internal_cdatax_array_at(_Array, sizeof(_Type), _Array->count ? _Array->count - 1 : 0))

/*
�Ƽ�
for(int i = 0; i < _Array->count; i++)
{
    ((_Type*)_Array->dataArray)[i];
}
*/
#define cdatax_array_foreach(_Type, _pData, _Array)\
    if(_Array->dataLen == sizeof(_Type))\
        for(uint32_t _index_ = 0; _index_ < _Array->count; ++_index_)\
            for(_Type* _pData = (_Type*)_Array->dataArray + _index_; _pData != NULL; _pData = NULL)

#ifdef __cplusplus
extern "C"
{
#endif
    CDATAX_ARRAY* internal_cdatax_array_new(uint32_t dataLen);
    void internal_cdatax_array_delete(CDATAX_ARRAY* array);
    void* internal_cdatax_array_append(CDATAX_ARRAY* array, uint32_t dataLen);
    void* internal_cdatax_array_at(CDATAX_ARRAY* array, uint32_t dataLen, uint32_t index);
#ifdef __cplusplus
}
#endif

#endif  //CDATAX_ARRAY_H