#include "cdatax_array.h"
#include <assert.h>

CDATAX_ARRAY *internal_cdatax_array_new(uint32_t dataLen)
{
	CDATAX_ARRAY* array = malloc(sizeof(CDATAX_ARRAY));
    memcpy((void*)&array->dataLen, &dataLen, sizeof(uint32_t));
    dataLen = 4;
    memcpy((void*)&array->reserve_size, &dataLen, sizeof(uint32_t));
    array->dataArray = malloc(dataLen * array->reserve_size);
    dataLen = 0;
    memcpy((void*)&array->count, &dataLen, sizeof(uint32_t));
    return array;
}

void internal_cdatax_array_delete(CDATAX_ARRAY *array)
{
    if(array == NULL)
        return;
    free(array->dataArray);
    free(array);
}

void internal_cdarax_array_expand(CDATAX_ARRAY *array)
{
    if(array->count == array->reserve_size)
    {
        uint32_t temp = array->reserve_size << 1;
        memcpy((void*)&array->reserve_size, &temp, sizeof(uint32_t));
        array->dataArray = realloc(array->dataArray, array->dataLen * array->reserve_size);
        assert(array->dataArray);
    }
}
void* internal_cdatax_array_append(CDATAX_ARRAY *array, uint32_t dataLen)
{
    assert(array && dataLen == array->dataLen);
    internal_cdarax_array_expand(array);
    void* data = (char*)array->dataArray + dataLen * array->count;
    dataLen = array->count + 1;
    memcpy((void*)&array->count, &dataLen, sizeof(uint32_t));
    return data; 
}

void *internal_cdatax_array_at(CDATAX_ARRAY *array, uint32_t dataLen, uint32_t index)
{
    assert(array && dataLen == array->dataLen && index < array->count);
    return (char*)array->dataArray + dataLen * index;
}
