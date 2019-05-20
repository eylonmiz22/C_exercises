/*
 * HW3_EylonMizrahi.h
 *
 *  Created on: Dec 17, 2018
 *      Author: eylon
 */

#ifndef HW3_EYLONMIZRAHI_H_
#define HW3_EYLONMIZRAHI_H_

//Enums
typedef enum {CNS, PRECNS, PREPRECNS} Type;

//Structs
typedef struct
{
	int id;
	int age;
} Child;

typedef struct
{
	char* name;
	Type type;
	Child** childrenP;
	int childrenNumber;
} Garden;

typedef struct
{
	Garden* gardens;
	int gardensNumber;
} City;

//CONSTS
#define READ_CITY 1
#define SHOW_CITY 2
#define SHOW_GARDEN 3
#define WRITE_CITY 4
#define ADD_GARDEN 5
#define ADD_CHILD 6
#define CHILD_BIRTHDAY 7
#define COUNT_GRADUATE 8
#define EXIT 0

//Prototypes
void printMenu();
void printChild(const Child* child);
void addChildToFile(const Child* child, FILE* file);
Child readChildFromFile(FILE* file);
void printGarden(const Garden* garden);
void addGardenToFile(const Garden* garden, FILE* file);
Garden readGardenFromFile(FILE* file);
void readCity(City* city);
void showCityGardens(const City* city);
void ReleaseCity(City* city);
int isGardenExist(const City* city, char** gardenName);
int isChildExist(const Garden* garden, int givenId);
void showSpecificGardenInCity(const City* city);
void saveCity(const City* city);
void cityAddGarden(City* city);
void gardenAddChild(Garden* garden, int index);
void ReleaseGarden(Garden* garden);
void addChildToSpecificGardenInCity(City* city);
void birthdayToChild(City* city);
int countChova(City* city);
void exitIfAllocDidntSucceed(void* arg);

#endif /* HW3_EYLONMIZRAHI_H_ */
