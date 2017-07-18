#include <stdio.h>
#include <stdlib.h>

#include "Queries_Menu.h"
#include "../UI/Schedule_UI.h"
#include "../UI/Studio_UI.h"
#include "../UI/Play_UI.h"

void Queries_Menu(void){
	char choice;
	do {
		printf("\n==================================================================\n");
		printf("************************Information Queries*************************\n");
		printf("[S]tudio   Query.\n");
		printf("[P]lay     Query.\n");
		printf("[T]icket   Query.\n");
		printf("S[c]hedule Queries\n");
		printf("[R]eturn.\n");
		printf("\n==================================================================\n");
		printf("Please input your choice:");
		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's'://Studio_query;
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(1);
			break;
		case 'T':
		case 't': //Ticket_query;
			break;
		case 'C':
		case 'c':
			Schedule_UI_ListAll();
			break;
		}
	} while ('R' != choice && 'r' != choice);
	}
