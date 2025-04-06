#ifndef CDATAX_QUEUE_H
#define CDATAX_QUEUE_H 
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

#define cdatax_queue_new(_Type)\
    (CDATAX_QUEUE*)internal_cdatax_queue_new(sizeof(_Type), (uint32_t)4)

#define cdatax_queue_newex(_Type, _ReserveSize)\
    (CDATAX_QUEUE*)internal_cdatax_queue_new(sizeof(_Type), (uint32_t)_ReserveSize)

#define cdatax_queue_delete(_Queue)\
    internal_cdatax_queue_delete(_Queue)

#define cdatax_queue_enqueue(_Queue, _Type, _Data)\
    *(_Type*)internal_cdatax_queue_enqueue(_Queue, sizeof(_Type)) = _Data

#define cdatax_queue_dequeue(_Queue, _Type)\
    (*(_Type*)internal_cdatax_queue_dequeue(_Queue, sizeof(_Type)))

#define cdatax_queue_font(_Queue, _Type)\
    (*(_Type*)internal_cdatax_queue_at(_Queue, sizeof(_Type), 1))

#define cdatax_queue_back(_Queue, _Type)\
    (*(_Type*)internal_cdatax_queue_at(_Queue, sizeof(_Type), 0))

typedef struct{
    void* const dataArray;
    const uint32_t dataLen;
    const uint32_t reserveSize;
    const uint32_t count;
    const uint32_t head;
    const uint32_t tail;
}CDATAX_QUEUE;

#ifdef __cplusplus
extern "C"
{
#endif
    CDATAX_QUEUE* internal_cdatax_queue_new(const size_t dataLen, const uint32_t reserveSize);
    void internal_cdatax_queue_delete(const CDATAX_QUEUE* queue);
    void* internal_cdatax_queue_enqueue(CDATAX_QUEUE* queue, const size_t dataLen);
    void* internal_cdatax_queue_dequeue(CDATAX_QUEUE* queue, const size_t dataLen);
    void* internal_cdatax_queue_at(const CDATAX_QUEUE* queue, const size_t dataLen, const char isFont);
#ifdef __cplusplus
}
#endif
#endif //CDATAX_QUEUE_H