#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Common/List.h"
#include "../Common/ComFunction.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Persistence/Query_Persist.h"

#include <stdio.h>
#include <stdlib.h>

void Schedule_UI_ListAll(void) {
	int i, id;
	char choice;

	schedule_list_t head;
	schedule_node_t *p;
	Pagination_t paging;

	List_Init(head, schedule_node_t);
	
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n\t\t=====================================================================================\n\n");
		printf("\t\t************************************ 演出计划 列表 ***********************************\n\n");
		printf("\t\t%5s\t%5s\t%8s\t%10s\t%10s\t%10s\n", "ID", "剧目ID", "演出厅ID",
				 "放映日期","放映时间","座位数");
		printf("\t\t---------------------------------------------------------------------------------------\n\n");
		
		
		//显示数据
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, p, i){
			printf("\t\t%5d %5d %5d ", p->data.id, p->data.play_id,p->data.studio_id);
			
			printf("\t\t%4d-%02d-%02d ",p->data.date.year, p->data.date.month, p->data.date.day);
			printf("\t%2d:%02d:%02d ", p->data.time.hour, p->data.time.minute, p->data.time.second);
			printf("\t%5d\n", p->data.seat_count);
		}
		

		printf("\n\t\t----------------- 共:%2d条数据 ------------------------------- 页码 %2d/%2d --------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t**************************************************************************************\n\n");
		printf("\t\t=============[P]上页=========================[N]下页=================[R]返回==========\n\n");
		
		
		
		printf("\t\t=====================================================================================\n");
		printf("\t\t请选择:");
		
		choice=l_getc();
	

		switch (choice) {
		
		
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}

int Schedule_UI_Add(int play_id) {
	int er=0,sid,newRecCount=0;
       	char choice;
	schedule_t data;
	studio_t sdata;	
	play_t pdata;
		do { 

				system("clear");
				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t\t------------------------------------新添 演出计划--------------------------------------\n\n");
       				printf("\t\t=======================================================================================\n\n");
       				
				data.id = EntKey_Srv_CompNewKey("schedule");
				
				
				data.play_id=play_id;
				
				
				printf("\t\t请输入演播厅的ID：");
				
				while(1){
					if(scanf("%d",&sid)==1){
					 cl_stdin(); 
					 
					 if(!Studio_Srv_FetchByID(sid, &sdata)){
					 	printf("\n\t\tID为%d的演出厅不存在，请重新输入：",sid);
					 	continue;
					 }
					 
					data.studio_id=sdata.id;
					data.seat_count=Seat_Number_Count(data.studio_id);
					 
					 break;
					}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
		
		
				
				
				printf("\t\t请输入放映日期:(年 月 日) ");
				while(1){
					if(scanf("%d%d%d",&(data.date.year), &(data.date.month), &(data.date.day))==3){
						 cl_stdin();
						 if(data.date.month>12 || data.date.day>31){
						 	printf("\t\t您输入的 月 或 日 有误！请重新输入: ");
						 	continue;
						 }
						 if(DateCmp(data.date, DateNow())==-1){
						 	printf("\t\t您输入的日期早于今日！请重新输入: ");
						 	continue;
						 
						 }
						 
						 break;
					}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入: "); }
				}
				
				
				printf("\t\t请输入放映时间:(时 分) ");
				while(1){ 
					if(scanf("%d%d",&(data.time.hour), &(data.time.minute))==2){
						data.time.second=0;
						cl_stdin();
						if(data.time.hour>24 || data.time.minute>60){
						 	printf("\t\t您输入的 时 或 分 有误！请重新输入:");
						 	continue;
						 }
						
						 break;
					}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
				
				
				

				if(Schedule_Srv_Add(&data)){
					Ticket_Srv_AddBatch(data.id, data.studio_id);
					newRecCount++;
					printf("\t\t添加成功！\n");
				}else{
					
				}
				printf("\t\t===== [A]继续添加 ==== [R]返回=====:");
		
				choice=l_getc();
		} while ('a' == choice || 'A' == choice);
	return newRecCount;
			
     
}

int Schedule_UI_Modify(int id){
	int ret=0,sid;
       	char choice;
	schedule_t data;
	studio_t sdata;	
	
	if(Schedule_Perst_SelectByID(id, &data)){
		
		while(1){ 

				system("clear");
				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t\t------------------------------------修改 演出计划--------------------------------------\n\n");
       				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t%5s \t %5s\t%8s \t %10s \t %10s \t %10s \n", "ID", "剧目ID", "演出厅ID",
				 "放映日期","放映时间","座位数");
				printf("\t\t-------------------------------------------------------------------------------------------\n\n");
		
		
		
				printf("\t\t%5d %5d %5d ", data.id, data.play_id,data.studio_id);
			
				printf("\t%4d-%02d-%02d ",data.date.year, data.date.month, data.date.day);
				printf("\t%2d:%02d:%02d ", data.time.hour, data.time.minute, data.time.second);
				printf("\t%5d\n", data.seat_count);
				
				printf("\n\t\t=======================================================================================\n\n");
				printf("\t\t==========[A]修改演出厅================[B]修改放映时间================[R]返回============\n");
				printf("\n\t\t=======================================================================================\n\n");
				printf("\t\t请选择:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				switch(choice){
					
					case 'a':
					case 'A':
				
						printf("\t\t请输入演播厅的ID：");
				
						while(1){
							if(scanf("%d",&sid)==1){
							 cl_stdin(); 
							 
							 if(!Studio_Srv_FetchByID(sid, &sdata)){
							 	printf("\n\t\tID为%d的演出厅不存在，请重新输入：",sid);
							 	continue;
							 }
							 
							data.studio_id=sdata.id;
							data.seat_count=Seat_Number_Count(data.studio_id);
							 
							 break;
							}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
						}
						break;
		
					case 'b':
					case 'B':
				
						printf("\t\t请输入放映日期:(年 月 日) ");
						while(1){
							if(scanf("%d%d%d",&(data.date.year), &(data.date.month), &(data.date.day))==3){
								 cl_stdin();
								 if(data.date.month>12 || data.date.day>31){
								 	printf("\t\t您输入的 月 或 日 有误！请重新输入: ");
								 	continue;
								 }
								 if(DateCmp(data.date, DateNow())==-1){
								 	printf("\t\t您输入的日期早于今日！请重新输入: ");
								 	continue;
								 
								 }
								 
								 break;
							}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入: "); }
						}
						
				
				
						printf("\t\t请输入放映时间:(时 分) ");
						while(1){ 
							if(scanf("%d%d",&(data.time.hour), &(data.time.minute))==2){
								data.time.second=0;
								cl_stdin();
								if(data.time.hour>24 || data.time.minute>60){
								 	printf("\t\t您输入的 时 或 分 有误！请重新输入:");
								 	continue;
								 }
						
								 break;
							}
							else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
						}
						
						break;
				
				
				}//switch

				if(Schedule_Srv_Modify(&data)){
					
					printf("\t\t修改成功！\n");
					ret=1;
				}else{
					printf("\t\t修改失败！\n");
				}
				
				printf("\t\t按任意键继续修改。");
		
				getchar();
		
		}//while
	}else{
		printf("\t\t未找到ID为%d的演出计划！\n",id);
		printf("\t\t按任意键返回！\n");
		//cl_stdin();
		getchar();
		return 0;
	}
       return ret;
}

int Schedule_UI_Delete(int id){

	int ret=0,sid;
       	char choice;
	schedule_t data;
	studio_t sdata;	
	
	if(Schedule_Srv_FetchByID(id, &data)){
		
		while(1){ 

				system("clear");
				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t\t------------------------------------删除 演出计划--------------------------------------\n\n");
       				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t%5s \t %5s\t%8s \t %10s \t %10s \t %10s \n", "ID", "剧目ID", "演出厅ID",
				 "放映日期","放映时间","座位数");
				printf("\t\t-------------------------------------------------------------------------------------------\n\n");
		
		
		
				printf("\t\t%5d %5d %5d ", data.id, data.play_id,data.studio_id);
			
				printf("\t%4d-%02d-%02d ",data.date.year, data.date.month, data.date.day);
				printf("\t%2d:%02d:%02d ", data.time.hour, data.time.minute, data.time.second);
				printf("\t%5d\n", data.seat_count);
				
				printf("\n\t\t=======================================================================================\n\n");
       				printf("\t\t===================[Q]确认删除 ===================[R]返回 ==============================\n");
       				printf("\t\t=======================================================================================\n\n");
				printf("\t\t请选择:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				
				if('q'==choice || 'Q'==choice){
					
					if(Schedule_Srv_DeleteByID(id)){
					
						printf("\t\t删除成功！\n");
						ret=1;
					}else{
						printf("\t\t删除失败！\n");
					}
				
					printf("\t\t按任意键继续删除。");
					cl_stdin();
					getchar();
				
					
				}
	
		}//while
	}else{
		printf("\t\t未找到ID为%d的演出计划！\n",id);
		printf("\t\t按任意键返回！\n");
		
		getchar();
		return 0;
	}
       return ret;
}
int Schedule_UI_Query(int id){

	
	int ret=0;
	
	schedule_t data;
	if(id==-1){
		printf("\t\t请输入要查询演出计划的ID:");
			
		while(1){
			if(scanf("%d",&id)==1){ cl_stdin(); break;}
			else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
		}
	}
	
	if(Schedule_Srv_FetchByID(id, &data)){
		//while(1){ 

				system("clear");
				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t\t-----------------------------根据ID查询 演出计划-------------------------------------\n\n");
       				printf("\t\t=======================================================================================\n\n");
       				printf("\t\t%5s \t %5s\t%8s \t %10s \t %10s \t %10s \n", "ID", "剧目ID", "演出厅ID",
				 "放映日期","放映时间","座位数");
				printf("\t\t-------------------------------------------------------------------------------------------\n\n");
		
		
				
				printf("\t\t%5d %5d %5d ", data.id, data.play_id,data.studio_id);
			
				printf("\t%4d-%02d-%02d ",data.date.year, data.date.month, data.date.day);
				printf("\t%2d:%02d:%02d ", data.time.hour, data.time.minute, data.time.second);
				printf("\t%5d\n", data.seat_count);
				
				
				printf("\n\t\t=======================================================================================\n\n");
       				
		
	}else{
				printf("\t\t未找到ID为%d的演出计划！\n",id);
				
	}	
	printf("\n\t\t按任意键返回！");
	getchar();	
       return ret;
}

/*以列表模式显示给定剧目的演出计划信息*/
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging){

	//Schedule_UI_MgtEntry(play->play_id)
}

void Schedule_UI_MgtEntry(int play_id){
     int i, id;
	char choice;
	
	
	play_t pdata;
	
	
	schedule_list_t head;
	schedule_node_t *p;
	Pagination_t paging;
	
	Play_Srv_FetchByID(play_id, &pdata);
	
	List_Init(head, schedule_node_t);
	
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Schedule_Srv_FetchByPlay(head,play_id);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n\t\t=====================================================================================\n\n");
		printf("\t\t********************************** 剧目:%s的演出计划列表 **************************************\n\n",pdata.name);
		printf("\t\t%5s\t%5s\t%8s\t%10s\t%10s\t%10s \n", "ID", "剧目ID", "演出厅ID",
				 "放映日期","放映时间","座位数");
		printf("\t\t-------------------------------------------------------------------------------------------\n\n");
		
		
		//显示数据
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, p, i){
			printf("\t\t%5d %5d %5d ", p->data.id, p->data.play_id,p->data.studio_id);
			
			printf("\t\t%4d-%02d-%02d ",p->data.date.year, p->data.date.month, p->data.date.day);
			printf("\t%2d:%02d:%02d ", p->data.time.hour, p->data.time.minute, p->data.time.second);
			printf("\t%5d\n", p->data.seat_count);
		}
		

		printf("\n\t\t----------------- 共:%2d条数据 -------------------------- 页码 %2d/%2d --------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t*************************************************************************************\n\n");
		printf("\t\t=========================[P]上页============================[N]下页==================\n\n");
		
		
		printf("\t\t====[A]新增演出计划======[D]删除演出计划 ======[U]修改演出计划==========================\n\n");
		printf("\t\t====[S] 浏览所有演出计划=======================[R]返回=================================\n");
		
		printf("\n\n\t\t=====================================================================================\n");
		printf("\t\t请选择:");
		
		choice=l_getc();
	

		switch (choice) {
		case 'a':
		case 'A':
			{
				
				studio_list_t slist;
				
				
				List_Init(slist, studio_node_t);
				
				
				Studio_Srv_FetchAll(slist);
				
				
				
				
				if(!List_IsEmpty(slist) ){
					if (Schedule_UI_Add(pdata.id)) //新添加成功，跳到最后一页显示
					{
						paging.totalRecords =Schedule_Srv_FetchByPlay(head,play_id);
						Paging_Locate_LastPage(head, paging, schedule_node_t);
					}
				}else{
					if(List_IsEmpty(slist)){
						printf("\n\t\t还未添加演出厅，不能添加演出计划");
					}
					
					printf("\n\t\t按任意键返回！");
					getchar();
				}
				
			}
			break;
		case 'd':
		case 'D':
			
			printf("\t\t请输入要删除演出计划的ID:");
			while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
			
			if (Schedule_UI_Delete(id)) {	//从新载入数据
					paging.totalRecords = Schedule_Srv_FetchByPlay(head,play_id);
					List_Paging(head, paging, schedule_node_t);
			}
			
			break;
		case 'u':
		case 'U':
			
				printf("\t\t请输入要修改演出计划的ID:");
			
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
			
				if (Schedule_UI_Modify(id)) {	//从新载入数据
					paging.totalRecords = Schedule_Srv_FetchByPlay(head,play_id);
					List_Paging(head, paging, schedule_node_t);
				}
			
			break;
			
		case 's':
		case 'S':
			Schedule_UI_ListAll();
			break;
			
		case 't':
		case 'T':
			//();
			break;
		
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}
