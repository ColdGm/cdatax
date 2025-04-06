#include "cdatax_stack.h"
#include <assert.h>

CDATAX_STACK *internal_cdatax_stack_new(const size_t dataLen, const uint32_t reserveSize)
{
	CDATAX_STACK* stack = malloc(sizeof(CDATAX_STACK));
    *(size_t*)&stack->dataLen = dataLen;
    *(uint32_t*)&stack->reserveSize = reserveSize;
    *(void**)&stack->dataArray = malloc(dataLen * stack->reserveSize);
    assert(stack->dataArray);
    *(uint32_t*)&stack->count = 0;
    return stack;
}

void internal_cdatax_stack_delete(const CDATAX_STACK *stack)
{
    if(stack == NULL)
        return;
    free(stack->dataArray);
    free((void*)stack);
}

void internal_cdatax_stack_expand(CDATAX_STACK *stack)
{
    if(stack->count == stack->reserveSize)
    {
        *(uint32_t*)&stack->reserveSize = stack->reserveSize << 1;
        void* data = realloc(stack->dataArray, stack->dataLen * stack->reserveSize);
        assert(data);
        *(void**)&stack->dataArray = data;
    }
}
void *internal_cdatax_stack_push(CDATAX_STACK *stack, const size_t dataLen)
{
    assert(stack && dataLen == stack->dataLen);
    internal_cdatax_stack_expand(stack);
    void* data = (char*)stack->dataArray + dataLen * stack->count;
    ++*(uint32_t*)&stack->count;
    return data; 
}

void *internal_cdatax_stack_pop(CDATAX_STACK *stack, const size_t dataLen)
{
    void* data = internal_cdatax_stack_top(stack, dataLen);
    --*(uint32_t*)&stack->count;
    return data;
}

void *internal_cdatax_stack_top(const CDATAX_STACK *stack, const size_t dataLen)
{
    assert(stack && dataLen == stack->dataLen && stack->count > 0);
    return (char*)stack->dataArray + (stack->count - 1) * stack->dataLen;
}
