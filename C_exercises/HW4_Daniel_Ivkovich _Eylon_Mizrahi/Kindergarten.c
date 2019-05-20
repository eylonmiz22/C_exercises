#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kindergarten.h"
#include "Child.h"
#include "General.h"

const char* GardenTypeName[NofTypes] = { "Chova", "Trom Chova",
		"Trom Trom Chova" };

//**************************************************
// Read data off all Kinder gardens from Bin file
//**************************************************
Garden** readAllGardensFromFileBin(char* fileName, int* pGardenCount) {
	int i;
	unsigned char count;
	FILE *fp;
	Garden** gardens;

	if ((fp = fopen(fileName, "rb")) == NULL) {
		printf("Cannot Open File '%s'", fileName);
		return NULL;
	}
	//opened successfully.
	fread(&count, sizeof(unsigned char), 1, fp);
	gardens = (Garden**) malloc(count * sizeof(Garden*));

	if (!checkAllocation(gardens)) {
		return NULL;
	}
	unsigned char nameLen, countAndType;
	long int currentPosition;
	for (i = 0; i < count; i++) {
		currentPosition = ftell(fp);
		fread(&nameLen, sizeof(unsigned char), 1, fp);
		fseek(fp, (nameLen - 1) * sizeof(unsigned char), SEEK_CUR);
		fread(&countAndType, sizeof(unsigned char), 1, fp);
		fseek(fp, (currentPosition), SEEK_SET);
		gardens[i] = (Garden*) malloc(sizeof(Garden));
		if (!checkAllocation(gardens[i])) {
			return NULL;
		}
		readGardenBin(fp, gardens[i]);
	}
	fclose(fp);
	*pGardenCount = count;
	return gardens;
}

//**************************************************
// Read data off all Kinder gardens from Text file
//**************************************************
Garden** readAllGardensFromFileTxt(char* fileName, int* pGardenCount) {
	int count, i;
	FILE *fp;
	Garden** gardens;

	*pGardenCount = 0;

	if ((fp = fopen(fileName, "rt")) == NULL) {
		printf("Cannot Open File '%s'", fileName);
		return NULL;
	}

	fscanf(fp, "%d", &count);

	//Would like to do the allocation even if count ==0
	//so will not return NULL as error
	gardens = (Garden**) malloc(count * sizeof(Garden*));

	if (!checkAllocation(gardens))
		return NULL;

	for (i = 0; i < count; i++) {
		gardens[i] = (Garden*) malloc(sizeof(Garden));
		if (!checkAllocation(gardens[i]))
			return NULL;
		readGardenTxt(fp, gardens[i]);
	}

	fclose(fp);

	*pGardenCount = count;
	return gardens;

}

/**************************************************/
/*             Read a Kindergarten from a BIN file           */
/**************************************************/
void readGardenBin(FILE* fp, Garden* pGarden) {
	int i;
	unsigned char nameLen, countAndType;
	fread(&nameLen, sizeof(unsigned char), 1, fp);
	pGarden->name = (char*) malloc(sizeof(char) * (int) nameLen);
	if (!checkAllocation(pGarden->name))
		return;
	for (i = 0; i < nameLen; i++) {
		fread(&pGarden->name[i], sizeof(unsigned char), 1, fp); // each char of the name.
	}
	fread(&countAndType, sizeof(unsigned char), 1, fp);
	pGarden->childCount = (int) (countAndType >> 2);
	pGarden->childPtrArr = (Child**) malloc(
			sizeof(Child*) * pGarden->childCount);
	if (!checkAllocation(pGarden->childPtrArr)) {
		pGarden->childCount = 0;
		*pGarden->childPtrArr = 0;
		return;
	}
	countAndType = countAndType << 6;
	pGarden->type = (int) (countAndType >> 6);
	for (i = 0; i < pGarden->childCount; i++) {
		Child* aChild = (Child*) malloc(sizeof(Child));
		if (!checkAllocation(aChild)) {
			aChild = 0;
			return;
		}
		aChild->age = 0;
		aChild->id = 0;
		readChildBin(fp, aChild); // read children and insert to child array.
		pGarden->childPtrArr[i] = aChild;
	}
	//done

}

/**************************************************/
/*             Read a Kindergarten from a TXT file           */
/**************************************************/
void readGardenTxt(FILE* fp, Garden* pGarden) {
	int i, type;
	char sTemp[100];

	//Kindergarten Name
	//Get it to a temp string and then create the pointer to save
	//in the struct in exact length.
	fscanf(fp, "%s", sTemp);
	pGarden->name = getStrExactLength(sTemp);

	//Kindergarten type
	fscanf(fp, "%d", &type);
	pGarden->type = (GardenType) type;

	//Child count
	fscanf(fp, "%d", &pGarden->childCount);
	if (pGarden->childCount == 0) {
		pGarden->childPtrArr = NULL;
		return;
	}

	pGarden->childPtrArr = (Child**) malloc(
			pGarden->childCount * sizeof(Child*));
	if (!checkAllocation(pGarden->childPtrArr))
		return;

	//Read each child
	for (i = 0; i < pGarden->childCount; i++) {
		pGarden->childPtrArr[i] = (Child*) malloc(sizeof(Child));
		if (!checkAllocation(pGarden->childPtrArr[i]))
			return;
		readChildTxt(fp, pGarden->childPtrArr[i]);
	}

}

/**************************************************/
/*            show all Kindergartens		      */
/**************************************************/
void showAllGardens(Garden** pGardenList, int count) {
	int i;
	printf("There are %d kindergarten in the city\n", count);
	for (i = 0; i < count; i++) {
		printf("\nKindergarten %d:\n", i + 1);
		showGarden(pGardenList[i]);
		printf("\n");
	}
	printf("\n");
}

/**************************************************/
/*            show a Kindergarten		           */
/**************************************************/
void showGarden(const Garden* pGarden) {
	int i;

	// Kindergarten name
	printf("Name:%s", pGarden->name);
	printf("\tType:%s", GardenTypeName[pGarden->type]);
	printf("\t%d Children:", pGarden->childCount);
	//all Children
	for (i = 0; i < pGarden->childCount; i++)
		showChild(pGarden->childPtrArr[i]);
}

/**************************************************/
/*  write Kindergartens to a TXT file					   */

/**************************************************/

void writeGardensToFileTxt(Garden** pGardenList, int gardenCount,
		char* fileName) {
	int i;
	FILE *fp;
	if ((fp = fopen(fileName, "wt")) == NULL) {
		printf("Cannot Open File '%s'", fileName);
		return;
	}
	fprintf(fp, "%d\n", gardenCount);
	for (i = 0; i < gardenCount; i++)
		writeGardenTxt(fp, pGardenList[i]);

	fclose(fp);
}

/**************************************************/
/*  write Kindergartens to a BIN file					   */

/**************************************************/

void writeGardensToFileBin(Garden** pGardenList, int gardenCount,
		char* fileName) {
	int i;
	FILE *fp;
	unsigned char countChar;

	if ((fp = fopen(fileName, "wb")) == NULL) {
		printf("Cannot Open File '%s'", fileName);
		return;
	}
	//open successful.
	countChar = (unsigned char) gardenCount;
	fwrite(&countChar, sizeof(unsigned char), 1, fp);

	for (i = 0; i < gardenCount; i++) {
		writeGardenBin(fp, pGardenList[i]);
	}
	fclose(fp);

}

/**************************************************/
/*Write a Kindergarten to the open BIN file						*/
/**************************************************/
void writeGardenBin(FILE* fp, const Garden* pGarden) {
	int i, nameLen;
	int count = pGarden->childCount;
	int type = pGarden->type;
	unsigned char result;

	nameLen = sizeof(pGarden->name);
	if (nameLen < 256) {
		result = (unsigned char) nameLen;
	}
	fwrite(&result, sizeof(unsigned char), 1, fp); //write length of the name.
	for (i = 0; i < nameLen; i++) {
		result = pGarden->name[i];
		fwrite(&result, sizeof(unsigned char), 1, fp); //write each char of the name.
	}
	result = count << 2;
	result = result | type;

	fwrite(&result, sizeof(unsigned char), 1, fp); // write child count combined with type

	for (i = 0; i < count; i++) {
		writeChildBin(fp, pGarden->childPtrArr[i]); // write each child in from the child array to the bin file.
	}
}

/**************************************************/
/*Write a Kindergarten to the open TXT file						*/
/**************************************************/
void writeGardenTxt(FILE* fp, const Garden* pGarden) {
	int i;
	//Kindergarten Name
	fprintf(fp, "%s", pGarden->name);
	fprintf(fp, "  %d", pGarden->type);
	//Children
	fprintf(fp, " %d\n", pGarden->childCount);
	for (i = 0; i < pGarden->childCount; i++)
		writeChildTxt(fp, pGarden->childPtrArr[i]);
}

//*************************************************
// menu option to add Child to a Kindergarten
//*************************************************
void addChildToGarden(Garden** pGardenList, int gardenCount) {
	Garden* pGarden;
	if (pGardenList == NULL) {
		printf("There are no Kindergartens yet\n");
		return;
	}

	pGarden = getGardenAskForName(pGardenList, gardenCount);
	if (pGarden == NULL) {
		printf("no such Kindergarten\n");
		return;
	}

	pGarden->childPtrArr = (Child**) realloc(pGarden->childPtrArr,
			(pGarden->childCount + 1) * sizeof(Child*));
	if (!checkAllocation(pGarden->childPtrArr)) {
		pGarden->childCount = 0;
		return;
	}

	pGarden->childPtrArr[pGarden->childCount] = (Child*) malloc(sizeof(Child));
	getChildCheckIdFromUser(pGarden->childPtrArr[pGarden->childCount], pGarden);
	pGarden->childCount++;
}

/**************************************************/
/* Add a Kindergarten  - we need to allocate more space   */
/* in the list.									*/
/**************************************************/
Garden** addGarden(Garden** pGardenList, int* pGardenCount) {

	pGardenList = (Garden**) realloc(pGardenList,
			(*pGardenCount + 1) * sizeof(Garden*));
	if (!checkAllocation(pGardenList)) {
		printf("addGarden didnt work!");
		*pGardenCount = 0;
		return NULL;
	}

	Garden* temp = (Garden*) malloc(sizeof(Garden));
	getGardenFromUser(temp, pGardenList, *pGardenCount);
	pGardenList[*pGardenCount] = temp;
	(*pGardenCount)++;

	return pGardenList;

}

void showGardenMenu(Garden** pGardenList, int count) {
	Garden* pGarden;

	pGarden = getGardenAskForName(pGardenList, count);

	if (pGarden != NULL)
		showGarden(pGarden);
	else
		printf("No such Kindergarten\n");

}

Garden* getGardenAskForName(Garden** pGardenList, int count) {
	char sTemp[100];
	Garden* pGarden;

	//Kindergarten name
	puts("\nGive me the Kindergarten Name:\t");
	scanf("%s", sTemp);
	getchar(); //remove \n

	//In this exe the find will not be efficient
	pGarden = findGardenByName(pGardenList, count, sTemp);

	return pGarden;
}

Garden* findGardenByName(Garden** pGardenList, int count, const char* name) {
	//linear search
	int i;

	for (i = 0; i < count; i++) {
		if (strcmp(pGardenList[i]->name, name) == 0)
			return pGardenList[i];
	}

	return NULL;
}

Child* getChildAskForId(Garden* pGarden) {
	int id;
	int index;

	printf("Enter child id\n");
	scanf("%d", &id);

	//The search will be inefficient - so sort
	index = findChildById(pGarden->childPtrArr, pGarden->childCount, id);
	if (index == -1)
		return NULL;

	return pGarden->childPtrArr[index];
}

void getGardenFromUser(Garden* pGarden, Garden** pGardenList, int count) {
	int i;
	char sTemp[100];
	int bOK = 0;
	int countC;

	do {
		//Kindergarten name
		puts("\nName:\t");
		scanf("%s", sTemp);
		getchar(); //remove second word if exsist
		if (findGardenByName(pGardenList, count, sTemp) != NULL)
			printf("This Kindergarten already in list\n");
		else
			bOK = 1;
	} while (!bOK);

	pGarden->name = getStrExactLength(sTemp);

	pGarden->type = getTypeOption();

	//Children
	puts("\nEnter children Details:\t");

	puts("\nChildren count:");
	scanf("%d", &countC);
	if (countC == 0) {
		pGarden->childCount = 0;
		pGarden->childPtrArr = NULL;
		return;
	}

	//create the list of children in the correct size
	pGarden->childPtrArr = (Child**) malloc(countC * sizeof(Child*));
	if (!checkAllocation(pGarden->childPtrArr)) {
		pGarden->childPtrArr = NULL;
		return;
	}

	pGarden->childCount = 0;
	for (i = 0; i < countC; i++) {
		pGarden->childPtrArr[i] = (Child*) malloc(sizeof(Child));
		getChildCheckIdFromUser(pGarden->childPtrArr[i], pGarden);
		pGarden->childCount++;
	}

}

/**************************************************/
/* Init a child from use. Ask for Id, check it is */
/* new and after call the function to ask for all other */
/* information										*/
/**************************************************/
void getChildCheckIdFromUser(Child* pChild, const Garden* pGarden) {
	int id, bOK = 0;
	do {
		puts("\nID No.:\t");
		scanf("%d", &id);
		if (findChildById(pGarden->childPtrArr, pGarden->childCount, id) != -1)
			printf("This child is in the Kindergarten\n");
		else
			bOK = 1;
	} while (!bOK);

	getChildFromUser(pChild, id);
}

void handleBirthdayToChild(Garden** pGardenList, int count) {
	Garden* pGarden;
	Child* pChild;

	pGarden = getGardenAskForName(pGardenList, count);
	if (pGarden == NULL) {
		printf("No such Kindergarten\n");
		return;
	}

	pChild = getChildAskForId(pGarden);
	if (pChild == NULL) {
		printf("No such child\n");
		return;
	}
	birthday(pChild);
}

GardenType getTypeOption() {
	int i, type;
	printf("Garden type:\n");
	do {
		for (i = 0; i < NofTypes; i++)
			printf("Enter %d for %s\n", i, GardenTypeName[i]);
		scanf("%d", &type);
	} while (type < 0 || type >= NofTypes);
	return (GardenType) type;
}
// release the Children list
//release the name ptr of each Kindergarten
//release the Kindergarten list
void release(Garden** pGardenList, int count) {
	int i;
	for (i = 0; i < count; i++) {
		free(pGardenList[i]->childPtrArr);
		free(pGardenList[i]);
	}

	free(pGardenList);

}

