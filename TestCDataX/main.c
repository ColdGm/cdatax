#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include "cdatax_array.h"
#include "cdatax_list.h"
#include "cdatax_stack.h"
#include "cdatax_queue.h"

struct MyStruct
{
	char name[32];
	int age;
};

void testArray();
void testList();
void testStack();
void testQueue();

int main(int argc, char** argv)
{
	//testArray();
	//testList();
	testStack();
	testQueue();
	return 0;
}

void testArray()
{
	//////////////////////////// À≥–Ú±Ì≤‚ ‘
	printf("//////////////////////////// À≥–Ú±Ì≤‚ ‘\n");
	CDATAX_ARRAY* array = cdatax_array_new(double);
	double* dlarr[100]; 
	for(int i = 0; i < 100; ++i)
	{
		cdatax_array_append(array, double, i * 10 + i / 100.0);
		dlarr[i] = &(((double*)array->dataArray)[i]);
	}
	printf("%lf\n", cdatax_array_at(array, double, 0));
	cdatax_array_at(array, double, 0) = 666.6;
	printf("%lf\n", cdatax_array_at(array, double, 0));
	printf("\n");
	cdatax_array_foreach(double, it, array)
		printf("%lf ", *it);
	printf("\n");
	printf("count=%d, first=%lf, last=%lf\n", array->count
		, cdatax_array_first(array, double)
		, cdatax_array_last(array, double));
	printf("\n");
	cdatax_array_delete(array);
}

void testList()
{
	//////////////////////////// ¡¥±Ì≤‚ ‘
	printf("//////////////////////////// ¡¥±Ì≤‚ ‘\n");
	CDATAX_LIST* stist = cdatax_list_new(struct MyStruct);
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"’≈»˝", 16}));
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"¿ÓÀƒ", 18}));
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"–°ŒÂ", 25}));
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"¿œ¡˘", 66}));
	cdatax_list_at(stist, struct MyStruct, 0).age = 100;
	cdatax_list_foreach(struct MyStruct, it, stist)
		printf("%s %d\n", it->name, it->age);
	cdatax_list_delete(stist);
	printf("\n");
}

void testStack()
{
	//////////////////////////// ’ª≤‚ ‘
	printf("//////////////////////////// ’ª≤‚ ‘\n");
	typedef struct {
		char str[128];
	}CString;
	CDATAX_STACK* stack = cdatax_stack_new(CString);
	cdatax_stack_push(stack, CString, (CString){"hello"});
	cdatax_stack_push(stack, CString, (CString){"World"});
	cdatax_stack_push(stack, CString, (CString){"Test"});
	cdatax_stack_push(stack, CString, (CString){"Case"});
	cdatax_stack_push(stack, CString, (CString){"CString"});
	while(stack->count)
	{
		CString val = cdatax_stack_pop(stack, CString);
		printf("%s\n", val.str);
	}
	printf("stack count: %d\n", stack->count);
	cdatax_stack_delete(stack);
}

void testQueue()
{
	//////////////////////////// ∂”¡–≤‚ ‘
	printf("//////////////////////////// ∂”¡–≤‚ ‘\n");
	CDATAX_QUEUE* queue = cdatax_queue_new(float);
	for(int i=0; i<50; ++i)
	{
		cdatax_queue_enqueue(queue, float, i / 1.0f);
		if(i && i % 10 == 0)
		{
			for(int j=0; j<5; ++j)
			{
				printf("%f ", cdatax_queue_dequeue(queue, float));
			}
			printf("\n\tqueue count: %d\tfont:%f\tback:%f\n", queue->count
				, cdatax_queue_font(queue, float), cdatax_queue_back(queue, float));
		}
	}
	printf("\n\nqueue count: %d, queue font:%f\tqueue back:%f\n", queue->count
		, cdatax_queue_font(queue, float), cdatax_queue_back(queue, float));
	cdatax_queue_delete(queue);
}