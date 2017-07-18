#include <stdio.h>
#include <stdlib.h>

#include "Queries_Menu.h"
#include "../UI/Schedule_UI.h"
#include "../UI/Studio_UI.h"
#include "../UI/Play_UI.h"

void Queries_Menu(int flag){
	char choice;
	do {
        system("clear");
		printf("\n\n\n\t\t\t==================================================================\n");
		printf("\t\t\t************************Information Queries*************************\n");
		printf("\t\t\t\t\t\t[S]tudio   Query.\n");
		printf("\t\t\t\t\t\t[P]lay     Query.\n");
		printf("\t\t\t\t\t\tS[c]hedule Queries\n");
		printf("\t\t\t\t\t\t[R]eturn.\n");
		printf("\t\t\t==================================================================\n");
		printf("\t\t\tPlease input your choice:");
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's':Studio_UI_MgtEntry(1);
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(1);
			break;
		case 'C':
		case 'c':
			Schedule_UI_ListAll();
			break;
		}
	} while ('R' != choice && 'r' != choice);
	}
