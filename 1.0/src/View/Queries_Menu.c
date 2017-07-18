#include <stdio.h>
#include <stdlib.h>

#include "Queries_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"

//查询菜单界面
void Queries_Menu(void){
	char choice;     
	int id;	
	
	do {
		/*system("cls");*/
		printf	("\n==================================================================\n");
		printf("******************************************************************\n");
		printf(" [F]查询剧目信息    |    [S]查询演出计划信息    |    [R]返回");
		printf("\n==================================================================\n");
		
		printf("Your Choice:");
		fflush(stdin);
		scanf("%c", &choice);
		getchar();

		switch (choice) {
		case 'f':
		case 'F':
			printf("请输入要查询剧目的id：");
			scanf("%d",&id);
			getchar();
			break;
		case 'S':
		case 's':
			printf("请输入要查询演出计划的id：");
			scanf("%d",&id);
			getchar();
			break;
		}
	}while (choice != 'r' && choice != 'R');
}
