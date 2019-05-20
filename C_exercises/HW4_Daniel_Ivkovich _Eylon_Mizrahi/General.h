#ifndef __PROTOTYPE__
#define __PROTOTYPE__

typedef enum
{
	EXIT,
	READ_CITY,
	SHOW_CITY,
	SHOW_GARDEN,
	WRITE_CITY,
	ADD_GARDEN,
	ADD_CHILD,
	CHILD_BIRTHDAY,
	COUNT_GRADUATE,
	LINKED_LIST_GARDENS,
	NofOptions
} MenuOptions;

typedef struct node  {
	void*  data;
	struct node* next;
}NODE;
typedef struct  {
	NODE head;
	int size;
}LIST;
void L_add(LIST* list , void* value);
int L_init ( LIST*  pList );
int	 menu();
char* getStrExactLength(char* inpStr);
int	 checkAllocation(const void* p);
void insertionSort(void** arr, int size,int typeSize, int (*compare)(void*, void*));
int compareInt(const void* num1, const void* num2);
int compareChildById(const void* child1, const void* child2);
int compareGardenByName(void* garden1, void* garden2);
int compareGardenByNumberOfChildren(void* garden1, void* garden2);
int compareChildrenByTypeAndCount(void* num1, void* num2);
void variadic_function(char* str, int n, ...);








#endif
