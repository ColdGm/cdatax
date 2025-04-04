#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include "cdatax_array.h"
#include "cdatax_list.h"

struct MyStruct
{
	char name[32];
	int age;
};

int main(int argc, char** argv)
{
	CDATAX_LIST* list = cdatax_list_new(int);
	cdatax_list_append(list, int, 10);
	cdatax_list_append(list, int, 20);
	cdatax_list_append(list, int, 30);
	cdatax_list_append(list, int, 40);
	cdatax_list_append(list, int, 50);
	cdatax_list_append(list, int, 60);
	printf("%d\n", cdatax_list_at(list, int, 0));
	cdatax_list_at(list, int, 0) = 666;
	printf("%d\n", cdatax_list_at(list, int, 0));
	printf("\n");
	cdatax_list_foreach(int, it, list)
		printf("%d ", *it);
	printf("\n");
	printf("first=%d, last=%d\n", cdatax_list_first(list, int), cdatax_list_last(list, int));
	cdatax_list_delete(list);
	printf("\n\n");

	CDATAX_LIST* stist = cdatax_list_new(struct MyStruct);
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"张三", 16}));
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"李四", 18}));
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"小五", 25}));
	cdatax_list_append(stist, struct MyStruct, ((struct MyStruct){"老六", 66}));
	cdatax_list_at(stist, struct MyStruct, 0).age = 100;
	cdatax_list_foreach(struct MyStruct, it, stist)
		printf("%s %d\n", it->name, it->age);
	free(list);
	return 0;
}