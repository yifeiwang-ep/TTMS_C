#include <stdio.h>

#include "./Main_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "Queries_Menu.h"
#include "Account_UI.h"
#include "../Service/Account.h"
#include "Sale_UI.h"
#include "SalesAnalysis_UI.h"
#include "../Common/ComFunction.h"

void Main_Menu(void) {
	char choice;
    account_t gl_CurUser;
    int flag;
    switch(gl_CurUser.type){
        case 1:flag=1;break;
        case 2:flag=2;break;
        case 9:flag=3;break;
    }
	do {
        system("clear");
		 printf("\n\n\n	\t\t==================================================================");
        printf("\n	\t\t***************************主菜单*********************************");
        printf("\n	\t\t==================================================================");
	    printf("\n\t\t\t|                   \033[31mS\033[0mtudio Management.                           |");
        printf("\n\t\t\t|                   \033[31mP\033[0mlay Management.                             |");
		printf("\n\t\t\t|                   \033[31mT\033[0micket Sale.                                 |");
		printf("\n	\t\t|                   \033[31mR\033[0meturn Ticket.                               |");
		printf("\n	\t\t|                   \033[31mQ\033[0mueries                                      |");
		printf("\n	\t\t|                   Sale \033[31mA\033[0mnalysisi.                              |");
		printf("\n	\t\t|                   Account \033[31mM\033[0management.                          |");
		printf("\n\n\t\t\t==================================================================");
        printf("\n	\t\t|         [L]og Off           |               [E]xit             |");
        printf("\n	\t\t******************************************************************");
		printf("\n	\t\t==================================================================");
		printf("\n	\t\tInput Your Choice:");
		choice =l_getc();
		switch (choice) {
		case 'S':
		case 's':
			Studio_UI_MgtEntry(flag);
			break;
		case 'P':
		case 'p':  
			Play_UI_MgtEntry(flag);
			break;
		case 'Q':
		case 'q':
			Queries_Menu(flag);
			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry(flag);
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket(flag);
			break;
		case 'A':
		case 'a':
			SalesAanalysis_UI_MgtEntry(flag);
			break;
		case 'M':
		case 'm':
			Account_UI_MgtEntry(flag);
			break;
		case 'l':
		case 'L':
				if(!SysLogout()) break;
        }
} while ('E' != choice && 'e' != choice);
	printf("\t\t\t\t当前用户为:%s\n",gl_CurUser.username);
       			choice=prom("\t\t\t\t真的要退出吗？",'y','n');
        		if(1==choice){
			       	
			       	system("clear");
			       	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
			       	printf("\t\t\t\t\t\t\t\033[31m 正在退出 ");
			       	sleep(1);
			       	printf("。");
			       	sleep(1);
			       	printf("。");
			       	sleep(1);
			       	printf("。\033[0m");
			       	printf("\n\n\t\t\t\t\t\t\t欢迎再次使用！\n");
			       	sleep(2);
			       	system("clear");
			       	exit(0);


}}

