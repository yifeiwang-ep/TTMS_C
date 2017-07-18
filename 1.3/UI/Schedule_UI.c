#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Common/list.h"
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
		printf("\n		==================================================================");
        	printf("\n		**************************放映计划表********************************");
          	printf("\n		==================================================================");
		printf("\t\t%5s\t%5s\t%8s\t%10s\t%10s\t%10s\n", "ID", "剧目编号","演出厅编号" , "上映日期","上映时间","票价");
		printf("\n		-----------------------------------------------------------------");
		
		
		//显示数据
		for (i = 0, p= (schedule_node_t *) (paging.curPos);
				p != head && i < paging.pageSize; i++){
			printf("%5d  『%d』%20s  『%d』%2s ", p->data.id, p->data.play_id, p->data.play_name,p->data.studio_id, p->data.studio_name);
			
			printf("  %4d-%02d-%02d",p->data.date.year, p->data.date.month, p->data.date.day);
			printf("\t%2d:%02d:%02d ", p->data.time.hour, p->data.time.minute, p->data.time.second);
			printf("\t%5d\n", p->data.price);
			p=p->next;
		}
		

		printf("\n		==================================================================");
        	printf("\n		|----------总数%2d------------------------------%2d/%2d页---------|\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
        	printf("\n		==================================================================");
		printf("\n		******************************************************************");
        	printf("\n		|      [P]revPage             |             [N]extPage          |");
       		printf("\n		-----------------------------------------------------------------");
		printf("\n		                         [R]eturn    ");
		printf("\n		******************************************************************");
		printf("\n		==================================================================");
		printf("		Iput Your choice:");	
		choice=l_getc();
		switch (choice) {
		
		
		case 24 :
	     if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 25 :
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
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
				printf("\n		=================================================================");
        			printf("\n		***************************添加演出计划*******************************");
          			printf("\n		=================================================================");
       				
				data.id = EntKey_Srv_CompNewKey("schedule");
				
				
				data.play_id=play_id;
				
				
				printf("\n		|     请输入名称：");
				
				while(1){
					if(scanf("%d",&sid)==1){
					 cl_stdin(); 
					 
					 if(!Studio_Srv_FetchByID(sid, &sdata)){
					 	printf("                    **没有演出厅信息！请重新输入**                          ");
					 	continue;
					 }
					 
					data.studio_id=sdata.id;
					data.seat_count=Seat_Number_Count(data.studio_id);
					 
					 break;
					}
					else{ cl_stdin(); printf("                    **您的输入有误！请重新输入**                            "); }
				}
		
		
				
				
				printf("\n		|     请输入演出日期：");
				while(1){
					if(scanf("%d%d%d",&(data.date.year), &(data.date.month), &(data.date.day))==3){
						 cl_stdin();
						 if(data.date.month>12 || data.date.day>31){
						 	printf("\n		                      **您输入的日期有误!请重新输入**     ");
						 	continue;
						 }
						 if(DateCmp(data.date, DateNow())==-1){
						 	printf("\n		                      **您输入的日期太早!请重新输入**     ");
						 	continue;
						 
						 }
						 
						 break;
					}
					else{ cl_stdin();printf("\n		                        **您的输入有误!请重新输入**     "); }
				}
				
				
				printf("\n		|     请输入演出时间(h min)：");

				while(1){ 
					if(scanf("%d%d",&(data.time.hour), &(data.time.minute))==2){
						data.time.second=0;
						cl_stdin();
						if(data.time.hour>24 || data.time.minute>60){
						 	printf("\n		                        **您的输入有误!请重新输入**     "); 
						 	continue;
						 }
						
						 break;
					}
					else{ cl_stdin(); printf("\n		                        **您的输入有误!请重新输入**     ");  }
				}
				
				
				printf("\n		==================================================================");		

				if(Schedule_Srv_Add(&data)){
					//Ticket_Srv_AddBatch(data.id, data.studio_id);
					newRecCount++;
					printf("\n		------------------------添加计划成功！--------------------------");
					printf("\n		******************************************************************");
				}else{
					
				}
				printf("\n		==================================================================");
       				printf("\n		|         [A]dd More               |             [R]eturn        |");
        			printf("\n		******************************************************************");
        			printf("		Iput Your choice:");
		
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
				printf("\n		=================================================================");
        			printf("\n		***************************修改演出计划*******************************");
          			printf("\n		=================================================================");
       				printf("\t\t%5s \t %5s\t%8s \t %10s \t %10s \t %10s \n", "ID", "剧目ID", "演出厅ID",
				 "放映日期","放映时间","座位数");
				printf("\n		-----------------------------------------------------------------");
				printf("%5d  『%d』%20s  『%d』%2s ", data.id,data.play_id, data.play_name,data.studio_id, data.studio_name);
				printf("  %4d-%02d-%02d",data.date.year, data.date.month,data.date.day);
				printf("\t%2d:%02d:%02d ", data.time.hour, data.time.minute, data.time.second);
				printf("\t%5d\n", data.price);
		
				printf("\n		==================================================================");
       				printf("\n		|      [S]tudio       |       [T]ime        |       [R]eturn     |");
        			printf("\n		******************************************************************");
				printf("		Iput Your choice:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				switch(choice){
					
					case 's':
					case 'S':
						printf("\n		|     请输入演出厅ID：                                                          |");
				
						while(1){
							if(scanf("%d",&sid)==1){
							 cl_stdin(); 
							 
							 if(!Studio_Srv_FetchByID(sid, &sdata)){
							 	printf("                    **没有演出厅信息！请重新输入**                          ");
							 	continue;
							 }
							 
							data.studio_id=sdata.id;
							data.seat_count=Seat_Number_Count(data.studio_id);
							 
							 break;
							}
							else{ cl_stdin(); printf("\n		                        **您的输入有误!请重新输入**     ");  }
						}
						break;
		
					case 't':
					case 'T':
				
						printf("\n		|     请输入上映日期( 年 月 日)：                                                |");
						while(1){
							if(scanf("%d%d%d",&(data.date.year), &(data.date.month), &(data.date.day))==3){
								 cl_stdin();
								 if(data.date.month>12 || data.date.day>31){
								 	printf("\n		                      **您输入的日期有误!请重新输入**     ");
								 	continue;
								 }
								 if(DateCmp(data.date, DateNow())==-1){
								 	printf("\n		                    **您输入的时间早于今天！请重新输入！**   ");
								 	continue;
								 
								 }
								 
								 break;
							}
							else{ cl_stdin(); printf("\n		                        **您的输入有误!请重新输入**     ");}
						}
						
				
				
						printf("\n		|     请输入上映时间(h min)：                                                |");
						while(1){ 
							if(scanf("%d%d",&(data.time.hour), &(data.time.minute))==2){
								data.time.second=0;
								cl_stdin();
								if(data.time.hour>24 || data.time.minute>60){
								 	 printf("\n		                        **您的输入有误!请重新输入**     "); 
								 	continue;
								 }
						
								 break;
							}
							else{ cl_stdin();printf("\n		                        **您的输入有误!请重新输入**     ");  }
						}
						
						break;
				
				
				}//switch
				printf("\n		==================================================================");		

				if(Schedule_Srv_Modify(&data)){
					
					printf("\n		--------------------------修改计划成功！----------------------------");
					printf("\n		******************************************************************");
					ret=1;
				}else{
					printf("\n		--------------------------修改计划成功！----------------------------");
					printf("\n		******************************************************************");
				}
				
				printf("\n		按任意键继续修改");       //想改SLEEP
		
				getchar();
		
		}//while
	}else{
		printf("                         **没有演出厅信息！按任意键继续修改**                          ");
		//printf("\n		按任意键继续修改");       //想改SLEEP
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
				printf("\n		=================================================================");
        			printf("\n		***************************删除演出计划****************************");
          			printf("\n		=================================================================");
       				printf("\t\t%5s\t%5s\t%8s\t%10s\t%10s\t%10s\n", "ID", "剧目编号", "演出厅编号",
				 "上映日期","上映时间","票价");
				printf("\n		-----------------------------------------------------------------");
					printf("%5d  『%d』%20s  『%d』%2s ", data.id, data.play_id,data.play_name,data.studio_id,data.studio_name);
					printf("  %4d-%02d-%02d",data.date.year,data.date.month, data.date.day);
					printf("\t%2d:%02d:%02d ", data.time.hour, data.time.minute, data.time.second);
					printf("\t%5d\n", data.price);
                		printf("\n		=================================================================");     	
       				printf("\n		|          [D]elete              |            [R]eturn=         |");
       				printf("\n		================================================================");
       				printf("		Iput Your choice:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				
				if('q'==choice || 'Q'==choice){
					
					if(Schedule_Srv_DeleteByID(id)){
					
						printf("\n		--------------------------删除计划成功！----------------------------");
						printf("\n		******************************************************************");
						ret=1;
					}else{
						printf("\n		--------------------------删除计划失败！----------------------------");
						printf("\n		******************************************************************");
					}
				
					printf("\n		按任意键继续删除");       //想改SLEEP
					cl_stdin();
					getchar();
				
					
				}
	
		}//while
	}else{
		printf("                      **没有演出计划！按任意键继续修改**                          ");
		//printf("\n		按任意键继续修改");       //想改SLEEP
		
		getchar();
		return 0;
	}
       return ret;
}
int Schedule_UI_Query(int id){

	
	int ret=0;
	
	schedule_t data;
	if(id==-1){
		printf("\n		|     请输入计划ID：                                                            |");
		while(1){
			if(scanf("%d",&id)==1){ cl_stdin(); break;}
			else{ cl_stdin();printf("\n		                        **您的输入有误!请重新输入**     "); }
		}
	}
	
	if(Schedule_Srv_FetchByID(id, &data)){
		//while(1){ 

				system("clear");
				printf("\n		=================================================================");
        			printf("\n		*************************根据ID查询演出计划*************************");
          			printf("\n		=================================================================");
       				printf("\t\t%5s\t%5s\t%8s\t%10s\t%10s\t%10s\n", "ID", "剧目编号", "演出厅编号",
				 "上映日期","上映时间","票价");
				printf("\n		-----------------------------------------------------------------");
				printf("%5d  『%d』%20s  『%d』%2s ",data.id, data.play_id, data.play_name,data.studio_id, data.studio_name);
				printf("  %4d-%02d-%02d",data.date.year, data.date.month,data.date.day);
				printf("\t%2d:%02d:%02d ", data.time.hour, data.time.minute, data.time.second);
				printf("\t%5d\n", data.price);
				
				printf("\n		=================================================================");
       				
		
	}else{
				printf("\n		                       **未找到ID『%d』!请重新输入**                          \n",id);
		//printf("\n		按任意键继续修改");       
				
	}	
	printf("\n		按任意键继续修改");
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
		printf("\n		=================================================================");
        	printf("\n		**************************剧目%s的演出计划*************************");
          	printf("\n		=================================================================");
		printf("\t\t%5s\t%5s\t%8s\t%10s\t%10s\t%10s\n", "ID", "剧目编号", "演出厅编号",
		 "上映日期","上映时间","票价");
		printf("\n		-----------------------------------------------------------------");
		//显示数据
		for (i = 0, p = (schedule_node_t *) (paging.curPos);
				p != head && i < paging.pageSize; i++){
			printf("%5d  『%d』%20s  『%d』%2s ", p->data.id, p->data.play_id, p->data.play_name,p->data.studio_id, p->data.studio_name);
			printf("  %4d-%02d-%02d",p->data.date.year, p->data.date.month, p->data.date.day);
			printf("\t%2d:%02d:%02d ", p->data.time.hour, p->data.time.minute, p->data.time.second);
			printf("\t%5d\n", p->data.price);
			p=p->next;
		}
		printf("\n		==================================================================");
        	printf("\n		|----------总数%2d------------------------------%2d/%2d页---------|\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\n		******************************************************************");
        	printf("\n		|      [%c]PrevPage          |             [%c]NextPage          |\n",24,25);
		printf("\n		|    [A]dd   |   [D]elete    |     [U]udate      |   [V]iew All  |");         
		printf("\n		------------------------[R]eturn----------------------------------");	
  		printf("\n		==================================================================");
        	printf("		Iput Your choice:");
		
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
						printf("\n		               **没有演出厅信息，无法添加计划!**  /n");
					}
					printf("\n		-------------------------------按任意键返回-------------------------");
					getchar();
				}
				
			}
			break;
		case 'd':
		case 'D':
			printf("\n		|     请输入计划ID：                                                            |");
			while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin();printf("\n		                        **您的输入有误!请重新输入**     ");}
				}
			
			if (Schedule_UI_Delete(id)) {	//从新载入数据
					paging.totalRecords = Schedule_Srv_FetchByPlay(head,play_id);
					List_Paging(head, paging, schedule_node_t);
			}
			
			break;
		case 'u':
		case 'U':
				printf("\n		|     请输入计划ID：                                                            |");
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin();printf("\n		                        **您的输入有误!请重新输入**     "); }
				}
			
				if (Schedule_UI_Modify(id)) {	//从新载入数据
					paging.totalRecords = Schedule_Srv_FetchByPlay(head,play_id);
					List_Paging(head, paging, schedule_node_t);
				}
			
			break;
			
		case 'v':
		case 'V':
			Schedule_UI_ListAll();
			break;
			
		case 't':
		case 'T':
			//();
			break;
		
		case 24 :
	     if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 25 :
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;

		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}
