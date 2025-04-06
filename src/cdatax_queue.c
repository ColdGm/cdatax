#include "cdatax_queue.h"
#include <assert.h>

CDATAX_QUEUE *internal_cdatax_queue_new(const size_t dataLen, const uint32_t reserveSize)
{
	CDATAX_QUEUE* queue = malloc(sizeof(CDATAX_QUEUE));
    *(size_t*)&queue->dataLen = dataLen;
    *(uint32_t*)&queue->reserveSize = reserveSize;
    *(void**)&queue->dataArray = malloc(dataLen * queue->reserveSize);
    assert(queue->dataArray);
    *(uint32_t*)&queue->count = 0;
    *(uint32_t*)&queue->head = 0;
    *(uint32_t*)&queue->tail = 0;
    return queue;
}

void internal_cdatax_queue_delete(const CDATAX_QUEUE *queue)
{ 
    if(queue == NULL)
        return;
    free(queue->dataArray);
    free((void*)queue);
}

void internal_cdatax_queue_expand(CDATAX_QUEUE *queue)
{
    if(queue->count == queue->reserveSize)
    {
        void* databack = malloc(queue->dataLen * queue->count);
        memcpy(databack, queue->dataArray, queue->dataLen * queue->count);
        *(uint32_t*)&queue->reserveSize = queue->reserveSize << 1;
        void* data = realloc(queue->dataArray, queue->dataLen * queue->reserveSize);
        assert(data);
        *(void**)&queue->dataArray = data;
        for(uint32_t i=0; i < queue->count; ++i)
            memcpy((char*)queue->dataArray + queue->dataLen * i
                , (char*)databack + queue->dataLen * ((queue->head + i) % queue->count)
                , queue->dataLen);
        *(uint32_t*)&queue->head = 0;
        *(uint32_t*)&queue->tail = queue->count;
        free(databack);
    }
}
void *internal_cdatax_queue_enqueue(CDATAX_QUEUE *queue, const size_t dataLen)
{
    assert(queue && dataLen == queue->dataLen);
    internal_cdatax_queue_expand(queue);
    void* data = (char*)queue->dataArray + dataLen * queue->tail;
    *(uint32_t*)&queue->tail = (queue->tail + 1) % queue->reserveSize;
    ++*(uint32_t*)&queue->count;
    return data; 
}

void *internal_cdatax_queue_dequeue(CDATAX_QUEUE *queue, const size_t dataLen)
{
    assert(queue && dataLen == queue->dataLen && queue->count > 0);
    void* data = internal_cdatax_queue_at(queue, dataLen, 1);
    *(uint32_t*)&queue->head = (queue->head + 1) % queue->reserveSize;
    --*(uint32_t*)&queue->count;
    return data;
}

void *internal_cdatax_queue_at(const CDATAX_QUEUE *queue, const size_t dataLen, const char isFont)
{
    assert(queue && dataLen == queue->dataLen && queue->count > 0);
    if(isFont)
        return (char*)queue->dataArray + queue->dataLen * queue->head;    
    else
        return (char*)queue->dataArray + queue->dataLen * (queue->tail ? queue->tail - 1 : queue->reserveSize - 1);
}
