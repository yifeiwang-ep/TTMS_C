#include "Play_UI.h"
#include "Schedule_UI.h"

#include "../Common/List.h"
#include "../Common/Common.h"
#include "../Common/ComFunction.h"
#include "../Service/Play.h"
#include "../Service/EntityKey.h"

#include <stdio.h>
#include <stdlib.h>

/*void Play_UI_ShowList(play_list_t list, Pagination_t paging) {

	// 请补充完整
}
*/
void Play_UI_MgtEntry(int flag){
	int i, id;
	char choice;

	play_list_t head;
	play_node_t *p;
	Pagination_t paging;

	List_Init(head, play_node_t);
	
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Play_Srv_FetchAll(head);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n\t\t=====================================================================================\n\n");
		printf("\t\t*************************************** 剧目 列表 ************************************\n\n");
		printf("\t\t%5s \t %20s\t%8s \t %5s \t %10s \t %10s \t %5s \n", "ID", "名称", "地区",
				"时长", "上映日期","下线日期","票价");
		printf("\t\t-------------------------------------------------------------------------------------\n\n");
		
		
		//显示数据
		Paging_ViewPage_ForEach(head, paging, play_node_t, p, i){
			printf("\t\t%5d %20s %10s %5d ", p->data.id, p->data.name,p->data.area, p->data.duration);
			printf("\t%4d-%02d-%02d ", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
			printf("\t%4d-%02d-%02d ",p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
			printf("\t%5d\n", p->data.price);
		}

		printf("\n\t\t----------------- 共:%2d条数据 -------------------------- 页码 %2d/%2d --------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t*************************************************************************************\n\n");
		printf("\t\t================[P]上页======================================[N]下页==================\n\n");
		
		if(flag==0){
			printf("\t\t====[A]新增======[D]删除======[U]修改 ======[S]演出计划管理=============[R]返回=======\n\n");
		}
		
		printf("\t\t========================================================================================\n");
		printf("\t\t请选择:");
		
		choice=l_getc();
	

		switch (choice) {
		case 'a':
		case 'A':
			if (flag==0 && Play_UI_Add()) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Play_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, play_node_t);
			}
			break;
		case 'd':
		case 'D':
			if(flag==0){
				printf("\t\t请输入要删除剧目的ID:");
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
			
				if (Play_UI_Delete(id)) {	//从新载入数据
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
			}
			break;
		case 'u':
		case 'U':
			if(flag==0){
				printf("\t\t请输入要修改剧目的ID:");
			
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
			
				if (Play_UI_Modify(id)) {	//从新载入数据
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
			}
			break;
			
		
		
		case 's':
		case 'S':
			if(flag==0){
				printf("\n\t\t请输入要计划演出的剧目ID:");
			
				while(1){
						if(scanf("%d",&id)==1){ cl_stdin(); break;}
						else{ cl_stdin(); printf("\n\t\t您的输入有误！请重新输入:"); }
				}
				play_t data;
				if(Play_Srv_FetchByID(id, &data)){
					Schedule_UI_MgtEntry(id);
				}else{
					printf("\n\t\t未找到ID为%d的剧目！\n",id);
					printf("\n\t\t按任意键返回！\n");
					cl_stdin();
					getchar();
				
				}
			}
			break;
		
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, play_node_t);
}



int Play_UI_Add(void)
{
       		int er=0,newRecCount=0;
       		char choice;
		play_t data;	
		do { 

				system("clear");
				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t--------------------------------------新添 剧目------------------------------------------\n\n");
       				printf("\t\t=======================================================================================\n\n");
       				
				data.id = EntKey_Srv_CompNewKey("play");
				
				printf("\t\t请输入剧目名称：");
				scanf("%s",data.name);
				//cl_stdin();
				//fgets(data.name,30,stdin);
				//getchar();
		
				printf("\t\t请输入出品地区：");
				scanf("%s",data.area);
				
				printf("\t\t请选择剧目类型：\n\t\t==[1].电影====[2].戏曲====[3].音乐==\n\t\t");
				while(1){
					er=0;
					choice=l_getc();
					switch(choice){
						case '1': data.type= PLAY_TYPE_FILE;   break;
						case '2': data.type=PLAY_TYPE_OPEAR;   break;
						case '3': data.type=PLAY_TYPE_CONCERT; break;
						default : er=1; printf("\t\t您的选择有误！请重新选择。\n");
					}
					if(er!=1) break;
				}
			
				printf("\t\t请选择剧目等级：\n\t\t==[1].儿童====[2].少年====[3].成人==\n\t\t");
				while(1){
					er=0;
					choice=l_getc();
					switch(choice){
						case '1': data.rating= PLAY_RATE_CHILD;   break;
						case '2': data.rating= PLAY_RATE_TEENAGE; break;
						case '3': data.rating= PLAY_RATE_ADULT;   break;
						default : er=1; printf("\t\t您的选择有误！请重新选择。\n");
					}
					if(er!=1) break;
				}
				
				printf("\t\t请输入剧目时长:(单位：分钟) ");
				while(1){
					if(scanf("%d",&(data.duration))==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
				
				printf("\t\t请输入开始放映日期:(年 月 日) ");
				while(1){
					if(scanf("%d%d%d",&(data.start_date.year), &(data.start_date.month), &(data.start_date.day))==3){
						 cl_stdin();
						 if(data.start_date.month>12 || data.start_date.day>31){
						 	printf("\t\t您输入的 月 或 日 有误！请重新输入: ");
						 	continue;
						 }
						 if(DateCmp(data.start_date, DateNow())==-1){
						 	printf("\t\t您输入的日期早于今日！请重新输入: ");
						 	continue;
						 
						 }
						 
						 break;
					}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入: "); }
				}
				
				
				printf("\t\t请输入结束放映日期:(年 月 日) ");
				while(1){
					if(scanf("%d%d%d",&(data.end_date.year), &(data.end_date.month), &(data.end_date.day))==3){
						 cl_stdin();
						 if(data.end_date.month>12 || data.end_date.day>31){
						 	printf("\t\t您输入的 月 或 日 有误！请重新输入:");
						 	continue;
						 }
						 if(DateCmp(data.end_date,data.start_date)==-1){
						 	printf("\t\t您输入的 结束放映日期 早于 开始放映日期！请重新输入: ");
						 	continue;
						 
						 }
						 
						 break;
					}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
				
				printf("\t\t请输入票价:");
				while(1){
					if(scanf("%d",&(data.price))==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
				

				if(Play_Srv_Add(&data)){
					newRecCount++;
					printf("\t\t添加成功！\n");
				}else{
					
				}
				printf("\t\t===== [A]继续添加 ==== [R]返回=====:");
		
				choice=l_getc();
		} while ('a' == choice || 'A' == choice);
		return newRecCount;
}

int Play_UI_Modify(int id){


	int er=0,ret=0;
       	char choice;
	play_t data;
	
	if(Play_Srv_FetchByID(id, &data)){
		while(1){ 

			system("clear");
			printf("\t\t=======================================================================================\n\n");
       			printf("\t\t------------------------------------修改 剧目--------------------------------------\n\n");
       			printf("\t\t=======================================================================================\n\n");
       				
			
       			printf("\t\t该剧目信息如下：\n");
       			printf("\t\t%5s \t %20s\t%8s \t %5s \t %10s \t %10s \t %5s \n", "ID", "名称", "地区",
				"时长", "上映日期","下线日期","票价");
			printf("\n\t\t=========================================================================================\n\n");	
       			printf("\t\t%5d %20s %10s %5d ",data.id,data.name,data.area,data.duration);
			printf("\t%4d-%02d-%02d ",data.start_date.year,data.start_date.month,data.start_date.day);
			printf("\t%4d-%02d-%02d ",data.end_date.year,data.end_date.month,data.end_date.day);
			printf("\t%5d\n", data.price);
       			printf("\n\t\t===========================================================================================\n\n");
			printf("\t\t============[A]修改名称 =============[B]修改出品地区 =========[C]修改类型=====================\n");	
			printf("\t\t============[D]修改等级 =============[E]修改时长 =============[F]修改开始放映日期=============\n");	
			printf("\t\t============[G]修改结束放映日期======[H]修改票价==============================================\n");
       			printf("\t\t====================================[R]返回==================================================\n\n");
       		
       			printf("\t\t请选择:");
			
			choice=l_getc();
			if('r'==choice || 'R'==choice) break;	
			switch(choice){
					
					case 'a':
					case 'A':
						printf("\t\t请输入剧目名称：");
						scanf("%s",data.name);
						cl_stdin();
						//fgets(data.name,30,stdin);
						//getchar();
						break;
						
					case 'b':
					case 'B':
						printf("\t\t请输入出品地区：");
						scanf("%s",data.area);
						break;
					case 'c':
					case 'C':
				
						printf("\t\t请选择剧目类型：\n\t\t==[1].电影====[2].戏曲====[3].音乐==\n\t\t");
						while(1){
							er=0;
							choice=l_getc();
							switch(choice){
								case '1': data.type= PLAY_TYPE_FILE;   break;
								case '2': data.type=PLAY_TYPE_OPEAR;   break;
								case '3': data.type=PLAY_TYPE_CONCERT; break;
								default : er=1; printf("\t\t您的选择有误！请重新选择。\n");
							}
							if(er!=1) break;
						}
						
						break;
					case 'd':
					case 'D':
			
						printf("\t\t请选择剧目等级：\n\t\t==[1].儿童====[2].少年====[3].成人==\n\t\t");
						while(1){
							er=0;
							choice=l_getc();
							switch(choice){
								case '1': data.rating= PLAY_RATE_CHILD;   break;
								case '2': data.rating= PLAY_RATE_TEENAGE; break;
								case '3': data.rating= PLAY_RATE_ADULT;   break;
								default : er=1; printf("\t\t您的选择有误！请重新选择。\n");
							}
							if(er!=1) break;
						}
						
						break;
					case 'e':
					case 'E':
				
						printf("\t\t请输入剧目时长:(单位：分钟) ");
						while(1){
							if(scanf("%d",&(data.duration))==1){ cl_stdin(); break;}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
						}
						
						break;
						
					case 'f':
					case 'F':
				
						printf("\t\t请输入开始放映日期:(年 月 日) ");
						while(1){
							if(scanf("%d%d%d",&(data.start_date.year), &(data.start_date.month), &(data.start_date.day))==3){
								 cl_stdin();
								 if(data.start_date.month>12 || data.start_date.day>31){
								 	printf("\t\t您输入的 月 或 日 有误！请重新输入: ");
								 	continue;
								 }
								 if(DateCmp(data.start_date, DateNow())==-1){
								 	printf("\t\t您输入的日期早于今日！请重新输入: ");
								 	continue;
								 
								 }
								 
								 break;
							}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入: "); }
						}
						
						break;
						
					case 'g':
					case 'G':
				
				
						printf("\t\t请输入结束放映日期:(年 月 日) ");
						while(1){
							if(scanf("%d%d%d",&(data.end_date.year), &(data.end_date.month), &(data.end_date.day))==3){
								 cl_stdin();
								 if(data.end_date.month>12 || data.end_date.day>31){
								 	printf("\t\t您输入的 月 或 日 有误！请重新输入:");
								 	continue;
								 }
								 if(DateCmp(data.end_date,data.start_date)==-1){
								 	printf("\t\t您输入的 结束放映日期 早于 开始放映日期！请重新输入: ");
								 	continue;
								 
								 }
								 
								 break;
							}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
						}
						
						break;
						
					case 'h':
					case 'H':
				
						printf("\t\t请输入票价:");
						while(1){
							if(scanf("%d",&(data.price))==1){ cl_stdin(); break;}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
						}
						
						break;
			}//switch
				
				if(Play_Srv_Modify(&data)){
					printf("\t\t修改成功！\n");
					ret=1;
				}else{
					printf("\t\t修改失败！\n");
				}
				printf("\t\t按任意键继续修改。");
		
				getchar();
		}//while
		
	}else{
		
		printf("\t\t未找到ID为%d的剧目！\n",id);
		printf("\t\t按任意键返回！\n");
		cl_stdin();
		getchar();
		return 0;
	}
	
	
       return ret;
}

int Play_UI_Delete(int id){
	play_t data;
	char choice;
	int ret=0;
       if(Play_Srv_FetchByID(id, &data)){
       		system("clear");
       		
       		printf("\t\t=======================================================================================\n\n");
       		printf("\t\t------------------------------------删除 剧目--------------------------------------\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		printf("\t\t该剧目信息如下：\n");
       		printf("\t\t%5s \t %20s\t%8s \t %5s \t %10s \t %10s \t %5s \n", "ID", "名称", "地区",
				"时长", "上映日期","下线日期","票价");
		printf("\n\t\t=======================================================================================\n\n");	
       		printf("\t\t%5d %20s %10s %5d ",data.id,data.name,data.area,data.duration);
			printf("\t%4d-%02d-%02d ",data.start_date.year,data.start_date.month,data.start_date.day);
			printf("\t%4d-%02d-%02d ",data.end_date.year,data.end_date.month,data.end_date.day);
			printf("\t%5d\n", data.price);
       		printf("\n\t\t=======================================================================================\n\n");
       		printf("\t\t===================[Q]确认删除 ===================[R]返回 ==============================\n");
       		printf("\t\t=======================================================================================\n\n");
       		
       		printf("\t\t请选择:");
		while(1){
			choice=l_getc();
	
			if('r'==choice || 'R'==choice) break;
			else if('q'==choice || 'Q'==choice){
			
					if(Play_Srv_DeleteByID(id)){
						printf("\t\t删除成功!\n");
						ret=1;
					}else{
						printf("\t\t删除失败!\n");
					}
					getchar();
			}else{
				printf("\t\t无效的操作！\n");
			}
		}
	}else{
		printf("\t\t未找到ID为%d的剧目！\n",id);
		printf("\t\t按任意键返回！\n");
		getchar();
		return 0;
	}
				
			
       		
       		
       return ret;
}




