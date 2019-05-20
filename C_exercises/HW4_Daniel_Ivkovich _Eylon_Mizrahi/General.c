#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "General.h"
#include "Kindergarten.h"
#include "Child.h"

const char* optionStr[NofOptions] = { "Exit", "Read City information from file",
		"Show all Kindergartens", "Show a specific Kindergarten",
		"Save City information to file", "Add a Kindergarten", "Add a Child",
		"Birthday to a Child", "Count Hova childres", "Move to list" };

void L_add(LIST* list, void* value) {
	NODE* node = (NODE*) malloc(sizeof(NODE));
	node->data = value;
	node->next = &(list->head);
	list->head = *node;
	list->size++;
}

int L_init(LIST* pList) {
	if (pList == NULL)
		return 0;

	pList->head.next = NULL;
	pList->size = 0;
	return 1;
}

int compareInt(const void* num1, const void* num2) {
	int n1 = *((int*) num1);
	int n2 = *((int*) num2);
	if (n1 < n2) {
		return -1;
	} else if (n1 > n2) {
		return 1;
	}
	return 0;
}
int compareChildrenByTypeAndCount(void* garden1, void* garden2) {
	Garden* g1 = (Garden*) garden1;
	Garden* g2 = (Garden*) garden2;
	GardenType t1 = g1->type;
	GardenType t2 = g2->type;
	int count1 = g1->childCount;
	int count2 = g2->childCount;

	if (t1 < t2) {
		return -1;
	} else if (t1 > t2) {
		return 1;
	}
	return compareInt(&count1, &count2);

}
int compareGardenByNumberOfChildren(void* garden1, void* garden2) {
	Garden* g1 = (Garden*) garden1;
	Garden* g2 = (Garden*) garden1;
	int n1 = g1->childCount;
	int n2 = g2->childCount;
	if (n1 < n2) {
		return -1;
	} else if (n1 > n2) {
		return 1;
	}
	return 0;
}

int compareChildById(const void* child1, const void* child2) {
	Child* c1 = (Child*) child1;
	Child* c2 = (Child*) child2;
	if (c1->id > c2->id) {
		return 1;
	} else if (c1->id < c2->id) {
		return -1;
	}
	return 0;
}

int compareGardenByName(void* garden1, void* garden2) {
	Garden* g1 = (Garden*) garden1;
	Garden* g2 = (Garden*) garden2;
	return strcmp(g1->name, g2->name);
}

void insertionSort(void** arr, int size, int typeSize,
		int (*compare)(void*, void*)) {
	int i, j;
	void* key;
	for (i = 1; i < size; i++) {
		key = arr[i];
		for (j = i - 1; j >= 0 && (compare(arr[j], key) > 0); j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

void variadic_function(char* str, int n, ...) {
	printf("\nstr = %s  n = %d", str, n);

	va_list list;
	va_start(list, str);
	int vali;
	char* vals;
	vals = va_arg(list, char*);

	while (vals) {
		printf("\nstr = %s", vals);
		vali = va_arg(list, int);
		printf("  n = %d", vali);
		vals = va_arg(list, char*);
	}
	va_end(list);
}

/**************************************************/
int menu()
/**************************************************/
/**************************************************/
{
	int option, i;

	printf("\n==========================");
	printf("\nSelect:\n");
	for (i = 0; i < NofOptions; i++)
		printf("\n\t%d. %s.", i, optionStr[i]);
	printf("\n");
	scanf("%d", &option);
	return option;
}

char* getStrExactLength(char* inpStr) {
	char* theStr = NULL;
	size_t len;

	len = strlen(inpStr) + 1;
	//allocate a place for the string in the right location in the array 
	theStr = (char*) malloc(len * sizeof(char));
	//Copy the string to the right location in the array 
	if (theStr != NULL)
		strcpy(theStr, inpStr);

	return theStr;
}

int checkAllocation(const void* p) {
	if (!p) {
		printf("ERROR! Not enough memory!");
		return 0;
	}
	return 1;
}
