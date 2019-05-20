/*
 ============================================================================
 Name        : HW3_EylonMizrahi.c
 Author      : Eylon
 Version     :
 Copyright   : 
 Description : HW3_EylonMizrahi, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HW3_EylonMizrahi.h"

int main(void)
{
	City utz = {NULL,0};
	int uReq;

	//first time read
	readCity(&utz);
	do
	{
		printf("==========================");
		printMenu();
		scanf("%d", &uReq);
		switch (uReq)
		{
		case  READ_CITY:
			readCity(&utz);
			break;

		case  SHOW_CITY:
			showCityGardens(&utz);
			break;

		case  SHOW_GARDEN:
			showSpecificGardenInCity(&utz);
			break;

		case  WRITE_CITY:
			saveCity(&utz);
			break;

		case  ADD_GARDEN:
			cityAddGarden(&utz);
			break;

		case  ADD_CHILD:
			addChildToSpecificGardenInCity(&utz);
			break;

		case  CHILD_BIRTHDAY:
			birthdayToChild(&utz);
			break;

		case COUNT_GRADUATE:
			printf("There are %d children going to school next year\n",countChova(&utz));
			break;
		}
	}
	while (uReq!=EXIT);

	ReleaseCity(&utz);//free all allocations
	printf("\n==========================");

	return 1;
}

void printMenu()
{
	printf("\n\n");
	printf("Select:\n");
	printf("	%d. Read City information from file.\n", READ_CITY);
	printf("	%d. Show all kindergartens.\n", SHOW_CITY);
	printf("	%d. Show a specific Kindergarten.\n", SHOW_GARDEN);
	printf("	%d. Save City information to file.\n", WRITE_CITY);
	printf("	%d. Add a Kindergarten.\n", ADD_GARDEN);
	printf("	%d. Add a Child.\n", ADD_CHILD);
	printf("	%d. Birthday to a Child.\n", CHILD_BIRTHDAY);
	printf("	%d. Count Hova childres.\n", COUNT_GRADUATE);
	printf("	%d. Exit.\n", EXIT);
}

void printChild(const Child* child)
{//Prints a given child to screen
	printf("\nID: %d, Age: %d", child->id, child->age);
}

void addChildToFile(const Child* child, FILE* file)
{//Adds a given child to a given text file
	fprintf(file, "\n%d %d", child->id, child->age);
}

Child readChildFromFile(FILE* file)
{//Reads and returns a child from a given text file
	Child child;
	fscanf(file, "\n%d %d", &child.id, &child.age);
	return child;
}

void printGarden(const Garden* garden)
{//Prints a given garden to screen
	int i;
	const char* types[] = {"Chova", "Trom Chova", "Trom Trom Chova"};
	printf("\nName: %s		Type: %s		%d Children:", garden->name, types[garden->type], garden->childrenNumber);
	for(i = 0; i < garden->childrenNumber; i++)
	{
		printChild((garden->childrenP)[i]);
	}
	printf("\n");
}

void addGardenToFile(const Garden* garden, FILE* file)
{//Adds a given garden to a given text file
	int i;
	fprintf(file, "%s  %d %d", garden->name, garden->type, garden->childrenNumber);
	for(i = 0; i < garden->childrenNumber; i++)
	{
		addChildToFile((garden->childrenP)[i] ,file);
	}
}

Garden readGardenFromFile(FILE* file)
{//Reads and returns a garden from a given text file
	int i, t, nameLength = 0;
	char c;
	long size = ftell(file);
	Garden garden;
	while(c != ' ')
	{
		fscanf(file, "%c", &c);
		nameLength++;
	}
	if(fseek(file, size, SEEK_SET) != 0)
	{
		printf("\nCouldn't read from file.");
		exit(0);
	}
	garden.name = (char*)malloc(nameLength * sizeof(char));
	exitIfAllocDidntSucceed(garden.name);
	fscanf(file, "\n%s  %d %d", garden.name, &t, &garden.childrenNumber);
	garden.name[nameLength - 1] = 0;
	garden.type = t;
	garden.childrenP = (Child**)malloc(garden.childrenNumber * sizeof(Child*));
	exitIfAllocDidntSucceed(garden.childrenP);
	for(i = 0; i < garden.childrenNumber; i++)
	{
		(garden.childrenP)[i] = (Child*)malloc(sizeof(Child));
		exitIfAllocDidntSucceed((garden.childrenP)[i]);
		*(garden.childrenP)[i] = readChildFromFile(file);
	}
	return garden;
}

void readCity(City* city)
{//Reads a city from a text file to a given city
	int i;
	FILE* file = fopen("DataFile.txt", "r");
	if(file == NULL)
	{
		printf("Failed opening the file!");
		return;
	}
	fscanf(file, "%d", &city->gardensNumber);
	city->gardens = (Garden*)malloc(city->gardensNumber * sizeof(Garden));
	exitIfAllocDidntSucceed(city->gardens);
	for(i = 0; i < city->gardensNumber; i++)
	{
		fscanf(file, "\n");
		*(city->gardens + i) = readGardenFromFile(file);
	}
	fclose(file);
}

void showCityGardens(const City* city)
{//Prints a given city to screen
	int i;
	for(i = 0; i < city->gardensNumber; i++)
	{
		printf("\nKindergarten %d:", (i + 1));
		printGarden(city->gardens + i);
	}
	printf("\n\n");
}

void showSpecificGardenInCity(const City* city)
{//Shows specific garden in a given city by a given garden's name
	char* gardenName = 0;
	int gardenIndex = isGardenExist(city, &gardenName);
	if(gardenIndex != -1)
	{
		printf("\n\nKindergarten %d:", (gardenIndex + 1));
		printGarden(city->gardens + gardenIndex);
	}
	else
	{
		printf("\n\nThere's no such Kindergarten");
	}
	free(gardenName);
}

int isGardenExist(const City* city, char** gardenName)
{//Checks if a garden exists in a given city by name, and returns it's index
	int i;
	*gardenName = (char*)calloc(10, sizeof(char));
	exitIfAllocDidntSucceed(*gardenName);
	printf("\nKindergarten Name:\n");
	scanf("%s", *gardenName);
	for(i = 0; i < city->gardensNumber; i++)
	{
		if(strcmp((city->gardens)[i].name, *gardenName) == 0)
		{
			return i;
		}
	}
	return -1;
}

int isChildExist(const Garden* garden, int givenId)
{//Checks if a child exists in a given garden by ID, and returns it's index
	int i;
	for(i = 0; i < garden->childrenNumber; i++)
	{
		if((garden->childrenP)[i]->id == givenId)
		{
			return i;
		}
	}
	return -1;
}

void saveCity(const City* city)
{//Saves a given city to a txt file
	int i;
	FILE* file = fopen("DataFile2.txt", "w");
	if(file == NULL)
	{
		printf("Failed opening the file!");
		return;
	}
	fprintf(file, "%d", city->gardensNumber);
	for(i = 0; i < city->gardensNumber; i++)
	{
		fprintf(file, "\n");
		addGardenToFile((city->gardens + i), file);
	}
	fclose(file);
}

void cityAddGarden(City* city)
{//Adds a garden to a given city
	char* gardenName = 0;
	int newType, i;
	Garden newGarden;
	if(isGardenExist(city, &gardenName) == -1)
	{
		newGarden.name = (char*)malloc(strlen(gardenName));
		exitIfAllocDidntSucceed(newGarden.name);
		strcpy(newGarden.name, gardenName);
		free(gardenName);
		printf("Garden type:\nEnter 0 for Chova\nEnter 1 for Trom Chova\nEnter 2 for Trom Trom Chova\n");
		scanf("%d", &newType);
		newGarden.type = newType;
		printf("Enter children Details:\n\nChildren count:\n");
		scanf("%d", &(newGarden.childrenNumber));
		newGarden.childrenP = (Child**)malloc(newGarden.childrenNumber * sizeof(Child*));
		exitIfAllocDidntSucceed(newGarden.childrenP);
		for(i = 0; i < newGarden.childrenNumber; i++)
		{
			*(newGarden.childrenP + i) = (Child*)malloc(newGarden.childrenNumber * sizeof(Child));
			exitIfAllocDidntSucceed(*(newGarden.childrenP + i));
			gardenAddChild(&newGarden, i);
		}
		city->gardensNumber++;
		city->gardens = (Garden*)realloc(city->gardens, city->gardensNumber * sizeof(Garden));
		exitIfAllocDidntSucceed(city->gardens);
		(city->gardens)[city->gardensNumber - 1] = newGarden;
	}
	else
	{
		printf("\nGarden is already exist\n");
	}
}

void gardenAddChild(Garden* garden, int index)
{//Adds a child to a given garden by index
	Child newChild;
	printf("\n\nID No.:\n");
	scanf("%d", &newChild.id);
	printf("\n\nAge:\n");
	scanf("%d", &newChild.age);
	*(garden->childrenP[index]) = newChild;
}

void addChildToSpecificGardenInCity(City* city)
{//Adds a specific child to a specific garden, in a given city
	Child newChild;
	char* gardenName = 0;
	int i = isGardenExist(city, &gardenName);
	free(gardenName);
	if(i != -1)
	{
		printf("\n\nID No.:\n");
		scanf("%d", &newChild.id);
		printf("\n\nAge:\n");
		scanf("%d", &newChild.age);
		if(isChildExist((city->gardens + i), newChild.id) == -1)
		{
			(city->gardens)[i].childrenNumber++;
			(city->gardens)[i].childrenP = (Child**)realloc((city->gardens)[i].childrenP, (city->gardens)[i].childrenNumber * sizeof(Child*));
			exitIfAllocDidntSucceed((city->gardens)[i].childrenP);
			((city->gardens)[i].childrenP)[(city->gardens + i)->childrenNumber - 1] = (Child*)malloc(sizeof(Child));
			exitIfAllocDidntSucceed(((city->gardens)[i].childrenP)[(city->gardens + i)->childrenNumber - 1]);
			*((city->gardens)[i].childrenP)[(city->gardens + i)->childrenNumber - 1] = newChild;
		}
		else
		{
			printf("\n\nChild is already exist");
		}
	}
	else
	{
		printf("\n\nThere's no such a garden");
	}
}

void birthdayToChild(City* city)
{//Adds a year to an age of specific child in a specific garden, in a given city
	int childIndex, gardenIndex, id;
	char* gardenName = 0;
	gardenIndex = isGardenExist(city, &gardenName);
	free(gardenName);
	if(gardenIndex != -1)
	{
		printf("Child's id to add a year: ");
		scanf("%d", &id);
		childIndex = isChildExist((city->gardens + gardenIndex), id);
		if(childIndex != -1)
		{
			((city->gardens)[gardenIndex].childrenP)[childIndex]->age++;
		}
		else
		{
			printf("\n\nThere's no such a child");
		}
	}
	else
	{
		printf("\n\nThere's no such a garden");
	}
}

int countChova(City* city)
{//Counts the number of 'Chova' kids in a given city
	int i, counter = 0;
	for(i = 0; i < city->gardensNumber; i++)
	{
		if((city->gardens)[i].type == CNS)
		{
			counter += (city->gardens)[i].childrenNumber;
		}
	}
	return counter;
}

void ReleaseCity(City* city)
{//Releases all dynamic allocations of a given city
	int i;
	for(i = 0; i < city->gardensNumber; i++)
	{
		ReleaseGarden(city->gardens + i);
	}
	free(city->gardens);
}

void ReleaseGarden(Garden* garden)
{//Releases all dynamic allocations of a given garden
	int j;
	free(garden->name);
	for(j = 0; j < garden->childrenNumber; j++)
	{
		free((garden->childrenP)[j]);
	}
	free(garden->childrenP);
}

void exitIfAllocDidntSucceed(void* arg)
{//Exits program if a dynamic allocation of a given argument did not succeed
	if(!arg)
	{
		printf("\nERROR! out of memory.");
		exit(0);
	}
}

