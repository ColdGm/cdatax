#include "cdatax_array.h"
#include <assert.h>

CDATAX_ARRAY *internal_cdatax_array_new(const size_t dataLen, const uint32_t reserveSize)
{
	CDATAX_ARRAY* array = malloc(sizeof(CDATAX_ARRAY));
    assert(array);
    memcpy((void*)&array->dataLen, &dataLen, sizeof(size_t));
    *(uint32_t*)&array->reserveSize = reserveSize;
    *(void**)&array->dataArray = malloc(dataLen * array->reserveSize);
	assert(array->dataArray);
    *(uint32_t*)&array->count = 0;
    return array;
}

void internal_cdatax_array_delete(const CDATAX_ARRAY *array)
{
    if(array == NULL)
        return;
    free(array->dataArray);
    free((void*)array);
}

void internal_cdarax_array_expand(CDATAX_ARRAY *array)
{
    if(array->count == array->reserveSize)
    {
        *(uint32_t*)&array->reserveSize <<= 1;
        void* data = realloc(array->dataArray, array->dataLen * array->reserveSize);
        assert(data);
        *(void**)&array->dataArray = data;
    }
}
void* internal_cdatax_array_append(CDATAX_ARRAY *array, const size_t dataLen)
{
    assert(array && dataLen == array->dataLen);
    internal_cdarax_array_expand(array);
    void* data = (char*)array->dataArray + dataLen * array->count;
    ++*(uint32_t*)&array->count;
    return data; 
}

void *internal_cdatax_array_at(const CDATAX_ARRAY *array, const size_t dataLen, const uint32_t index)
{
    assert(array && dataLen == array->dataLen && index < array->count);
    return (char*)array->dataArray + dataLen * index;
}
