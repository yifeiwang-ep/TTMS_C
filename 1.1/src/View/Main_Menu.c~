#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Common/ComFunction.h"
#include "Main_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "Queries_Menu.h"
#include "Account_UI.h"
#include "Sale_UI.h"
#include "SalesAnalysis_UI.h"

extern account_t gl_CurUser;

void Main_Menu(void) {
	char choice;
	while(1) {
		system("clear");
		printf("\t\t\t==========================================================================================\n\n");
		printf("\t\t\t*************************************欢迎使用影片管理系统**********************************\n\n");
		printf("\t\t\t\t[S]演出厅管理\t\t\t\t\t[U]修改密码\n\n");
		printf("\t\t\t\t[P]剧目管理  \t\t\t\t\t[X]注销当前用户\n\n");
		printf("\t\t\t\t[T]售票管理  \t\t\t\t\t[M]销售数据分析\n\n");
		printf("\t\t\t\t[R]退票管理  \t\t\t\t\t[A]系统用户管理\n\n");				
		printf("\t\t\t\t[Q]查询      \t\t\t\t\t[E]退出系统\n");
		/*printf("\t\t\t\t[A]系统用户管理\n\n");
		printf("\t\t\t\t[E]退出系统\n");*/
		printf("\n\t\t\t==========================================================================================\n");
		printf("\t\t\t\t请选择:");
		
		choice = l_getc();
		if('x'==choice || 'X'==choice){
			if( SysLogout() ) main();
		
		}
		
		if('e'==choice || 'E'==choice){
			printf("\t\t\t=======================================================================================\n\n");
       		
       		
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
			}
			
			
		}
		
		switch (choice) {
		case 'S':
		case 's':
			switch(gl_CurUser.type){
				case USR_CLERK:  
				case USR_MANG:  
						printf("\n\t\t\t\t您的权限不足，无法进入该菜单！\n\t\t\t\t请按任意键返回！");
						cl_stdin();
						getchar();
						break;
						
				case USR_ADMIN:  
						Studio_UI_MgtEntry();
						break;
			}
			
			break;
		case 'P':
		case 'p':
			switch(gl_CurUser.type){
				case USR_CLERK:  
				  
						Play_UI_MgtEntry(1);
						break;
				case USR_MANG:	
				case USR_ADMIN:  
						Play_UI_MgtEntry(0);
						break;
			}
			
			break;
		case 'Q':
		case 'q':
			Queries_Menu();
			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
		//case 'N':
		//case 'n':
		//	SalesAanalysis_UI_MgtEntry();
		//	break;
		case 'A':
		case 'a':
			switch(gl_CurUser.type){
				case USR_CLERK:  
				case USR_MANG:  
						printf("\n\t\t\t\t您的权限不足，无法进入该菜单！\n\t\t\t\t请按任意键返回！");
						cl_stdin();
						getchar();
						break;
						
				case USR_ADMIN:  
						Account_UI_MgtEntry();
						break;
			}
			break;
			
		case 'u':
		case 'U':
			Change_Passwd();
			break;
			
		case 'm':
		case  'M':
			SalesAanalysis_UI_MgtEntry();
			break;
		
		
		}
	} 
}

