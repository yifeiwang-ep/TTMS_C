#include "../Common/ComFunction.h"
#include "../Common/common.h"
#include "../Common/list.h"
#include  "Query_Play_UI.h"
#include "../Service/Play.h"
#include "../Persistence/Query_Persist.h"
#include "../Service/Schedule.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Service/Studio.h"
#include "../Persistence/Ticket_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void DisplayQueryPlay(int flag)
{
       play_t data;
	play_node_t *p;
	play_list_t list;
	char choice,str[30]="\0";
	int id,type=2; //查询类型 0 id  1 name
	
	List_Init(list, play_node_t);
	
	while(1){
		system("clear");
       		
       		printf("\t\t=======================================================================================\n\n");
       		printf("\t\t------------------------------------查询 剧目-------------------------------------------\n\n");
       		printf("\t\t=======================================================================================\n\n");
		
		if(type==1){
			
			if(Play_Srv_FetchByName(list,str)){
				printf("\t\t该剧目信息如下：\n");
		       		printf("\t\t%5s \t %20s\t%8s \t %5s \t %10s \t %10s \t %5s \n", "ID", "名称", "地区",
						"时长", "上映日期","下线日期","票价");
				printf("\n\t\t=======================================================================================\n\n");
				List_ForEach(list, p){	
			       		printf("\t\t%5d %20s %10s %5d ",p->data.id,p->data.name,p->data.area,p->data.duration);
					printf("\t%4d-%02d-%02d ",p->data.start_date.year,p->data.start_date.month,p->data.start_date.day);
					printf("\t%4d-%02d-%02d ",p->data.end_date.year,p->data.end_date.month,p->data.end_date.day);
					printf("\t%5d\n", p->data.price);
				
				}
		       		printf("\n\t\t=======================================================================================\n\n");
       		
	       		}else{
	       		
	       		printf("\t\t未找到！\n\t\t按任意键返回！");
	       		getchar();
	       		
	       		}
	       	}
       		
       		if(type==0 ){
       			if( Play_Srv_FetchByID(id, &data)){
	       			printf("\t\t该剧目信息如下：\n");
	       			printf("\t\t%5s \t %20s\t%8s \t %5s \t %10s \t %10s \t %5s \n", "ID", "名称", "地区",
					"时长", "上映日期","下线日期","票价");
				printf("\n\t\t=======================================================================================\n\n");	
	       			printf("\t\t%5d %20s %10s %5d ",data.id,data.name,data.area,data.duration);
				printf("\t%4d-%02d-%02d ",data.start_date.year,data.start_date.month,data.start_date.day);
				printf("\t%4d-%02d-%02d ",data.end_date.year,data.end_date.month,data.end_date.day);
				printf("\t%5d\n", data.price);
	       			printf("\n\t\t=======================================================================================\n\n");
	       		
	       		}else{
	       		
	       		printf("\t\t未找到！\n\t\t按任意键返回！\n");
	       		getchar();
	       		
	       		}
	       	}
       		
       		printf("\n\t\t===========[A]根据ID查询===================[B]根据名称查询=================[R]返回=================\n");
       		printf("\t\t=================================================================================================\n\n");
		printf("\t\t请选择:");
			
		choice=l_getc();
		if('r'==choice || 'R'==choice) break;	
		switch(choice){
					
					case 'a':
					case 'A':
						printf("\t\t请输入要查询的ID：");
						while(1){
							if(scanf("%d",&id)==1){ cl_stdin(); break;}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
						}
						type=0;
						break;
						
					case 'b':
					case 'B':
						
						printf("\t\t请输入要查询的剧目名称：");
						scanf("%s",str);
						type=1;
						break;
					
		}
	}
}


