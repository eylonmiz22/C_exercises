#include <stdio.h>
#include "General.h"
#include "City.h"
#include "Kindergarten.h"

void KinderGardenLinkedList(City* city, LIST* list) {

	int type = -1;
	printf("\nPlease enter type of KinderGarden from {0,1,2}:");
	scanf(" %d", &type);
	createLinkedListForKindergardenType(city, (GardenType) type, list);
	printf("\nPrinting the Linked list of Gardens:\n");
	displayKindergardensFromList(list);

}

void displayKindergardensFromList(LIST* list) {

	NODE* p;
	int i;
	p = &(list->head);
	for (i = 0; i < list->size; i++) {
		printf("\nPrinting the Garden number %d:\n", i + 1);
		showGarden((Garden*) p->data);
		printf("\n");
		p = p->next;
	}

}

void createLinkedListForKindergardenType(City* city, GardenType type,
		LIST* list) {
	int i;
	for (i = 0; i < city->count; i++) {
		if (city->pGardenList[i]->type == type) {
			L_add(list, city->pGardenList[i]);
		}
	}
}

void readCityBin(City* pCity) {
	if (pCity->pGardenList != NULL) {
		releaseCity(pCity);
		pCity->count = 0;
	}
	pCity->pGardenList = readAllGardensFromFileBin(BIN_FILE, &pCity->count);

	if (pCity->pGardenList == NULL)
		printf("Error reading city information\n");
}

void readCityTxt(City* pCity) {
	if (pCity->pGardenList != NULL) {
		releaseCity(pCity);
		pCity->count = 0;
	}
	pCity->pGardenList = readAllGardensFromFileTxt(TEXT_FILE, &pCity->count);

	if (pCity->pGardenList == NULL)
		printf("Error reading city information\n");
}

void showCityGardens(City* pCity) {
	showAllGardens(pCity->pGardenList, pCity->count);
}

void showSpecificGardenInCity(City* pCity) {
	showGardenMenu(pCity->pGardenList, pCity->count);
}

void saveCityTxt(City* pCity) {
	writeGardensToFileTxt(pCity->pGardenList, pCity->count, TEXT_FILE);
}

void saveCityBin(City* pCity) {
	writeGardensToFileBin(pCity->pGardenList, pCity->count, BIN_FILE);
}

void cityAddGarden(City* pCity) {

	pCity->pGardenList = addGarden(pCity->pGardenList, &pCity->count);
	if (pCity->pGardenList == NULL) //Allocation error
		printf("Error adding kindergarten\n");
}

void addChildToSpecificGardenInCity(City* pCity) {
	addChildToGarden(pCity->pGardenList, pCity->count);
}

void birthdayToChild(City* pCity) {
	handleBirthdayToChild(pCity->pGardenList, pCity->count);
}

int countChova(City* pCity) {
	int i;
	int count = 0;
	for (i = 0; i < pCity->count; i++) {
		if (pCity->pGardenList[i]->type == Chova)
			count += pCity->pGardenList[i]->childCount;
	}
	return count;
}

void releaseCity(City* pCity) {
	release(pCity->pGardenList, pCity->count);
}
