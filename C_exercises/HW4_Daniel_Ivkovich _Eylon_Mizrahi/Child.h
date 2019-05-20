#ifndef __CHILD__
#define __CHILD__

typedef struct {
	int id;
	int age;
} Child;

void readChildTxt(FILE* fp, Child* pChild);
void getChildFromUser(Child* pChild, int id);
void showChild(const Child* pChild);
void writeChildTxt(FILE* fp, const Child* pChild);
int findChildByid(Child** pChildList, int count, int id);
void birthday(Child* pChild);

void readChildBin(FILE* fp, Child* pChild);
void writeChildBin(FILE* fp, const Child* pChild);
unsigned char combineAgeWithStartOfID(unsigned char ageChar, int id);
int createIntFrom2Chars(unsigned char c1, unsigned char c2);
char writeByteFromChild(char byte, int start, int end, FILE* fp);

char readByteToChar(char byte, int start, int end);
void printCharAsBinary(char ch);
int findChildById(Child** pChildList, int count, int id);

#endif
