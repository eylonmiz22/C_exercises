#include <stdio.h>
#include <stdlib.h>
#include "General.h"
#include "Kindergarten.h"
#include "Child.h"
#include "City.h"
typedef enum {
	TXT, BIN
} TypeOfFile;
				//Written by: Daniel Ivkovich, Eylon Mizrahi

int main(int argc, char* argv[]) {

	int type;
	TypeOfFile Ftype;
	sscanf(argv[1], "%d", &type);
	Ftype = type;
	City utz = { NULL, 0 };
	int uReq;

	if (argc != 2) {
		//checks if there are two arguments passed to the main()
		return -1;
	}

	if (Ftype == TXT) {
		//first time read
		readCityTxt(&utz);
		do {
			uReq = menu();
			switch (uReq) {
			case READ_CITY:
				readCityTxt(&utz);
				break;

			case SHOW_CITY:
				showCityGardens(&utz);
				break;

			case SHOW_GARDEN:
				showSpecificGardenInCity(&utz);
				break;

			case WRITE_CITY:
				saveCityTxt(&utz);
				break;

			case ADD_GARDEN:
				cityAddGarden(&utz);
				break;

			case ADD_CHILD:
				addChildToSpecificGardenInCity(&utz);
				break;

			case CHILD_BIRTHDAY:
				birthdayToChild(&utz);
				break;

			case COUNT_GRADUATE:
				printf("There are %d children going to school next year\n",
						countChova(&utz));
				break;

			}
		} while (uReq != EXIT);
	} else if (Ftype == BIN) {
		//first time read
		readCityBin(&utz);
		do {
			uReq = menu();
			switch (uReq) {
			case READ_CITY:
				readCityBin(&utz);
				break;

			case SHOW_CITY:
				showCityGardens(&utz);
				if (utz.count >= 3) {
					Garden** g = utz.pGardenList;
					variadic_function(g[0]->name, g[0]->childCount, g[1]->name,
							g[1]->childCount, g[2]->name, g[2]->childCount,
							NULL, 9);
				}
				break;

			case SHOW_GARDEN:
				showSpecificGardenInCity(&utz);
				break;

			case WRITE_CITY:
				saveCityBin(&utz);
				break;

			case ADD_GARDEN:
				cityAddGarden(&utz);
				break;

			case ADD_CHILD:
				addChildToSpecificGardenInCity(&utz);
				break;

			case CHILD_BIRTHDAY:
				birthdayToChild(&utz);
				break;

			case COUNT_GRADUATE:
				printf("There are %d children going to school next year\n",
						countChova(&utz));
				break;
			case LINKED_LIST_GARDENS: {
				LIST list;

				if (L_init(&list) == 1) {
					KinderGardenLinkedList(&utz, &list);

				}
				break;
			}

			}
		} while (uReq != EXIT);
	}

	releaseCity(&utz); //free all allocations

	return EXIT_SUCCESS;

}

