#ifndef __CITY__
#define __CITY__

#include "Kindergarten.h"

#define TEXT_FILE "DataFile.txt"
#define BIN_FILE "DataFile.bin"

typedef struct {
	Garden** pGardenList;
	int count;
} City;
void KinderGardenLinkedList(City* city, LIST* list);
void createLinkedListForKindergardenType(City* city, GardenType type,
		LIST* list);
void displayKindergardensFromList(LIST* list);
void readCityTxt(City* pCity);
void readCityBin(City* pCity);
void showCityGardens(City* pCity);
void showSpecificGardenInCity(City* pCity);
void saveCityTxt(City* pCity);
void saveCityBin(City* pCity);
void cityAddGarden(City* pCity);
void addChildToSpecificGardenInCity(City* pCity);
void birthdayToChild(City* pCity);
int countChova(City* pCity);
void releaseCity(City* pCity);

#endif
