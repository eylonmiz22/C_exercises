#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Child.h"
#include "General.h"
#include "Kindergarten.h"

char readByteToChar(char byte, int start, int end) { //Reads number of bits from in a given range of bits and returns a new char
	if (!(end < start)) {
		int i;
		unsigned char bit, targetChar;
		targetChar = targetChar & 0;
		for (i = start; i < end; i++) {
			bit = byte << i;
			bit = bit >> 7;
			targetChar = targetChar | bit;
			if (i <= end - 2) {
				targetChar = targetChar << 1;
			}
		}
		return targetChar;
	}
	return byte;
}

void printCharAsBinary(char ch) {
	int i;
	unsigned char temp;
	for (i = 0; i < 8; i++) {
		temp = ch << i;
		temp = temp >> 7;
		printf("%d", temp);
	}
}

int createIntFrom2Chars(unsigned char c1, unsigned char c2) {
	int id = 0;
	id = id | c1;
	id = id << 8;
	id = id | c2;
	return id;
}

/**************************************************/
/*             Read a Child from a BIN file           */
/**************************************************/
void readChildBin(FILE* fp, Child* pChild) { //01100000 00011111
	unsigned char currentRead, bitAge, ID5, ID8;
	fread(&currentRead, sizeof(unsigned char), 1, fp);
	bitAge = currentRead >> 5;
	ID5 = currentRead & 31;
	fread(&currentRead, sizeof(unsigned char), 1, fp);
	ID8 = currentRead;
	pChild->age = (int) bitAge;
	pChild->id = createIntFrom2Chars(ID5, ID8);
}

/**************************************************/
/*Write a Child to the open BIN file				*/
/**************************************************/

void writeChildBin(FILE* fp, const Child* theChild) { //writes number of bits from in a given range of bits to IO file
	int age, id;
	unsigned char idChar1, idChar2, ageChar, secondInsert, firstInsert;
	age = theChild->age;
	id = theChild->id;

	ageChar = (unsigned char) age; //good example bin : 00000011 = 3 age , id = 31: 000000000 00011111
	ageChar = ageChar << 5; // example : 01100000
	idChar1 = (unsigned char) (id >> 8); // 00000000
	firstInsert = ageChar | idChar1; // 01100000
	idChar2 = (unsigned char) id; // 00011111
	secondInsert = idChar2; // 00011111

	fwrite(&firstInsert, sizeof(unsigned char), 1, fp);
	fwrite(&secondInsert, sizeof(unsigned char), 1, fp);

}

/**************************************************/
/*             Read a Child from a TXT file           */
/**************************************************/
void readChildTxt(FILE* fp, Child* pChild) {
	//Child ID
	fscanf(fp, "%d", &pChild->id);
	fscanf(fp, "%d", &pChild->age);
}

/**************************************************/
/*            show a Child				           */
/**************************************************/
void showChild(const Child* pChild) {
	printf("\nID:%d  ", pChild->id);
	printf("Age:%d  ", pChild->age);
}
int findChildById(Child** pChildList, int count, int id) {
	int i;
	for (i = 0; i < count; i++) {
		if (pChildList[i]->id == id) {
			return i;
		}
	}
	return -1;
}

/**************************************************/
void getChildFromUser(Child* pChild, int id)
/**************************************************/
/**************************************************/
{
	pChild->id = id;

	puts("\nAge:\t");
	scanf("%d", &pChild->age);
}

/**************************************************/
/*Write a Child to the open TXT file				*/
/**************************************************/
void writeChildTxt(FILE* fp, const Child* pChild) {
	fprintf(fp, "%d %d\n", pChild->id, pChild->age);
}

//binary search
int findChildByid(Child** pChildList, int count, int id) {
	Child c = { id, 0 };
	Child* cp = &c;
	qsort(pChildList, count, sizeof(Child*), compareChildById);
	Child** found;
	found = bsearch(&cp, pChildList, count, sizeof(Child*), compareChildById);
	return (found - pChildList);
}

void birthday(Child* pChild) {
	pChild->age++;
}

//void	releaseChild(Child* pChild)
//{
//	//nothing to release
//}
