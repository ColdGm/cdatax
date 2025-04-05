#ifndef CDATAX_STACK_H
#define CDATAX_STACK_H
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

typedef struct{
    void* const dataArray;
    const uint32_t dataLen;
    const uint32_t reserveSize;
    const uint32_t count;
    const uint32_t current;
}CDATAX_STACK;

#define cdatax_stack_new(_Type)\
    (CDATAX_STACK*)internal_cdatax_stack_new(sizeof(_Type), (uint32_t)4)

#define cdatax_stack_newex(_Type, _ReserveSize)\
    (CDATAX_STACK*)internal_cdatax_stack_new(sizeof(_Type), (uint32_t)_ReserveSize)

#define cdatax_stack_delete(_Stack)\
    internal_cdatax_stack_delete(_Stack)

#define cdatax_stack_push(_Stack, _Type, _Data)\
    *(_Type*)internal_cdatax_stack_push(_Stack, sizeof(_Type)) = _Data

#define cdatax_stack_pop(_Stack, _Type)\
    (*(_Type*)internal_cdatax_stack_pop(_Stack, sizeof(_Type)))

#define cdatax_stack_top(_Stack, _Type)\
    (*(_Type*)internal_cdatax_stack_top(_Stack, sizeof(_Type)))

#ifdef __cplusplus
extern "C"
{
#endif
    CDATAX_STACK* internal_cdatax_stack_new(const size_t dataLen, const uint32_t reserveSize);
    void internal_cdatax_stack_delete(const CDATAX_STACK* stack);
    void* internal_cdatax_stack_push(CDATAX_STACK* stack, const size_t dataLen);
    void* internal_cdatax_stack_pop(CDATAX_STACK* stack, const size_t dataLen);
    void* internal_cdatax_stack_top(const CDATAX_STACK* stack, const size_t dataLen);
#ifdef __cplusplus
}
#endif
#endif //CDATAX_STACK_H