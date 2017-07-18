#include "Schedule_UI.h"
#include "Play_UI.h"
#include "../Service/Ticket.h"
#include "../Common/list.h"
#include "../Common/ComFunction.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Persistence/Query_Persist.h"
#include "../Persistence/Schedule_Persist.h"
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
		printf("\n\n\n\t		==================================================================");
        printf("\n\t		**************************放映计划表******************************");
          printf("\n\t		==================================================================");
		printf("\n\t\t\t    %-5s%-10s   %-12s   %-12s      %-12s   %-5s", "ID", "剧目", "演出厅",
		 "上映日期","上映时间","票价");
		printf("\n\t		-----------------------------------------------------------------");
		
		
		//显示数据
		for (i = 0, p= (schedule_node_t *) (paging.curPos);
				p != head && i < paging.pageSize; i++){
			printf("\n\t\t\t    %-3d 『%d』 \t   『%d』 ", p->data.id, p->data.play_id,p->data.studio_id);
			printf("\t%4d-%02d-%02d\t",p->data.date.year, p->data.date.month, p->data.date.day);
			printf("%2d:%02d:00", p->data.time.hour, p->data.time.minute);
			printf("    %-5d", p->data.price);
			p=p->next;
		}
		

		printf("\n\t		==================================================================");
        printf("\n\t		|-----------总数%2d-------------------------------%2d/%2d页----------|",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
        printf("\n\t		==================================================================");
        printf("\n\t		|        [P]revPage            |             [N]extPage          |");
       	printf("\n\t		------------------------------------------------------------------");
		printf("\n\t		                         [R]eturn    ");
		printf("\n\t		==================================================================");
		printf("\n\t		Iput Your choice:");	
		choice=l_getc();
		switch (choice) {
		
		
		case 'p' :
        case 'P':
	     if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n' :
        case 'N':
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
    cl_stdin();
	Play_Srv_FetchByID(play_id, &pdata);
		do { 

				system("clear");
				printf("\n\n\n\t		=================================================================");
        			printf("\n\t		***************************添加演出计划**************************");
          			printf("\n\t		=================================================================");
				data.id = EntKey_Srv_CompNewKey("schedule");
				data.play_id=play_id;
				while(1){
				printf("\n\t		|请输入演出厅ID：");
					if(scanf("%d",&sid)==1){
					 cl_stdin(); 
					 
					 if(!Studio_Srv_FetchByID(sid, &sdata)){
					 	printf("\n\t\t\t                    **没有演出厅信息！请重新输入**        ");
					 	continue;
					 }
					 
					data.studio_id=sdata.id;
                    data.price=pdata.price;
    				data.seat=Seat_Number_Count(data.studio_id);
                   
					 break;
					}
					else{ cl_stdin(); printf("\n\t\t\t您的输入有误！请重新输入**  "); }
				}
				while(1){
				printf("\n\t		|请输入演出日期：");
					if(scanf("%d %d %d",&(data.date.year), &(data.date.month), &(data.date.day))==3){
						 cl_stdin();
						 if(data.date.month>12 || data.date.day>31){
						 	printf("\n\t		                      **您输入的日期有误!请重新输入**     ");
						 	continue;
						 }
						 if(DateCmp(data.date, DateNow())==-1){
						 	printf("\n\t		                      **您输入的日期太早!请重新输入**     ");
						 	continue;
						 
						 }
						 
						 break;
					}
					else{ cl_stdin();printf("\n		                        **您的输入有误!请重新输入**     "); }
				}
				
				

				while(1){ 
				printf("\n\t		| 请输入演出时间(h min)：");
					if(scanf("%d %d",&(data.time.hour), &(data.time.minute))==2){
						data.time.second=0;
						cl_stdin();
						if(data.time.hour>24 || data.time.minute>60){
						 	printf("\n\t		                        **您的输入有误!请重新输入**     "); 
						 	continue;
						 }
						
						 break;
					}
					else{ cl_stdin(); printf("\n		                        **您的输入有误!请重新输入**     ");  }
				}
				
				
				printf("\n\t		==================================================================");		

				if(Schedule_Srv_Add(&data)){
					Ticket_Srv_AddBatch(data.id, data.studio_id);
					newRecCount++;
					printf("\n\t		-------------------------添加计划成功！---------------------------");
				}else{
					
				}
				printf("\n\t		==================================================================");
       				printf("\n\t		|         [A]dd More               |             [R]eturn        |");
        			printf("\n\t		******************************************************************");
        			printf("\n\t		Iput Your choice:");
		
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
				printf("\n\n\n\t		=================================================================");
        			printf("\n\t		*************************修改演出计划****************************");
          			printf("\n\t		=================================================================");
       				printf("\n\t\t\t    %-5s%-10s   %-12s   %-12s      %-12s   %-5s", "ID", "剧目", "演出厅",
		 "上映日期","上映时间","票价");
				printf("\n\t		-----------------------------------------------------------------");
			printf("\n\t\t\t    %-3d 『%d』 \t   『%d』 ", data.id, data.play_id,data.studio_id);
			printf("\t%4d-%02d-%02d\t",data.date.year,data.date.month,data.date.day);
			printf("%2d:%02d:00", data.time.hour, data.time.minute);
			printf("    %-5d", data.price);
		
				printf("\n\t		==================================================================");
       				printf("\n\t		|      [S]tudio       |       [T]ime        |       [R]eturn     |");
        			printf("\n\t		******************************************************************");
				printf("\n\t		Iput Your choice:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				switch(choice){
					
					case 's':
					case 'S':
						while(1){
						printf("\t\t\t|请输入演出厅ID：");
							if(scanf("%d",&sid)==1){
							 cl_stdin(); 
							 
							 if(!Studio_Srv_FetchByID(sid, &sdata)){
							 	printf("\n\t\t\t\t\t\t**没有演出厅信息！请重新输入**  \n");
							 	continue;
							 }
							 
							data.studio_id=sdata.id;
							data.seat=Seat_Number_Count(data.studio_id);
							 
							 break;
							}
							else{ cl_stdin(); printf("\n\t\t\t		                        **您的输入有误!请重新输入**     \n");  }
						}
						break;
		
					case 't':
					case 'T':
				
						while(1){
						printf("\t\t	|请输入上映日期( 年 月 日)：   ");
							if(scanf("%d %d %d",&(data.date.year), &(data.date.month), &(data.date.day))==3){
								 cl_stdin();
								 if(data.date.month>12 || data.date.day>31){
								 	printf("\n\t		                      **您输入的日期有误!请重新输入**     \n");
								 	continue;
								 }
								 if(DateCmp(data.date, DateNow())==-1){
								 	printf("\n\t		                    **您输入的时间早于今天！请重新输入！**   \n");
								 	continue;
								 
								 }
								 
								 break;
							}
							else{ cl_stdin(); printf("\n\t		                        **您的输入有误!请重新输入**     \n");}
						}
						
				
				
						printf("\t		|请输入上映时间(h min)：");
						while(1){ 
							if(scanf("%d %d",&(data.time.hour), &(data.time.minute))==2){
								data.time.second=0;
								cl_stdin();
								if(data.time.hour>24 || data.time.minute>60){
								 	 printf("\n\t		                        **您的输入有误!请重新输入**  \n"); 
								 	continue;
								 }
						
								 break;
							}
							else{ cl_stdin();printf("\n\t		                        **您的输入有误!请重新输入**  \n");  }
						}
						
						break;
				
				
				}//switch
				printf("\n\t		==================================================================");		

				if(Schedule_Srv_Modify(&data)){
					
					printf("\n\t		--------------------------修改计划成功！----------------------------");
					ret=1;
				}else{
					printf("\n\t		--------------------------修改计划失败！----------------------------");
				}
			sleep(1);
		}//while
	}else{
	    printf("\n\t                         **没有演出厅信息！** ");
		sleep(1);
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
				printf("\n\n\n\t		=================================================================");
        			printf("\n\t		*************************删除演出计划****************************");
          			printf("\n\t		=================================================================");
       				printf("\n\t\t\t    %-5s%-10s   %-12s   %-12s      %-12s   %-5s", "ID", "剧目", "演出厅",
		 "上映日期","上映时间","票价");
				printf("\n\t		-----------------------------------------------------------------");
					printf("\n\t\t\t    %-3d 『%d』 \t   『%d』 ",data.id,data.play_id,data.studio_id);
			printf("\t%4d-%02d-%02d\t",data.date.year, data.date.month,data.date.day);
			printf("%2d:%02d:00", data.time.hour, data.time.minute);
			printf("    %-5d", data.price);
                		printf("\n\t		=================================================================");     	
       				printf("\n\t		|          [D]elete               |            [R]eturn         |");
       				printf("\n\t		=================================================================");
       				printf("\n\t		Iput Your choice:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				
				if('d'==choice || 'D'==choice){
					
					if(Schedule_Srv_DeleteByID(id)){
					
						printf("\n\t\t		--------------------------删除计划成功！----------------------------");
						printf("\n\t\t		******************************************************************");
						ret=1;
					}else{
						printf("\n\t\t		--------------------------删除计划失败！----------------------------");
						printf("\n\t\t		******************************************************************");
					}
				sleep(1);
				}
	
		}//while
	}else{
		printf("\n\t\t                                **没有演出计划**");
		sleep(1);
        return 0;
	}
       return ret;
}
int Schedule_UI_Query(int id){
	int ret=0;
	schedule_t data;
	if(id==-1){
		while(1){
		printf("\n\t\t		|请输入计划ID：");
			if(scanf("%d",&id)==1){ cl_stdin(); break;}
			else{ cl_stdin();printf("\n\t\t		                        **您的输入有误!请重新输入**     "); }
		}
	}
	
	if(Schedule_Srv_FetchByID(id, &data)){
		//while(1){ 

				system("clear");
				printf("\n\n\n\t\t		=================================================================");
        			printf("\n\t\t		*************************根据ID查询演出计划*************************");
          			printf("\n\t\t		=================================================================");
       				printf("\n\t\t\t    %-5s%-10s   %-12s   %-12s      %-12s   %-5s", "ID", "剧目", "演出厅",
		 "上映日期","上映时间","票价");
				printf("\n\t\t		-----------------------------------------------------------------");
				printf("\n\t\t\t    %-3d 『%d』 \t   『%d』 ",data.id,data.play_id,data.studio_id);
			printf("\t%4d-%02d-%02d\t",data.date.year,data.date.month,data.date.day);
			printf("%2d:%02d:00", data.time.hour, data.time.minute);
			printf("    %-5d\n",data.price);
				
				printf("\n\t\t		=================================================================");
       				
		
	}else{
				printf("\n\t\t		                       **未找到ID『%d』!请重新输入**",id);
	}
    sleep(1);
       return ret;
}

/*以列表模式显示给定剧目的演出计划信息*/
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging){

        Schedule_UI_MgtEntry(play->id);
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
		printf("\n\n\n\t		=================================================================");
        	printf("\n\t		**************************剧目%d的演出计划************************",play_id);
          	printf("\n\t		=================================================================");
		printf("\n\t\t\t    %-5s%-10s   %-12s   %-12s      %-12s   %-5s", "ID", "剧目", "演出厅",
		 "上映日期","上映时间","票价");
		    printf("\n\t		-----------------------------------------------------------------");
		//显示数据
		for (i = 0, p = (schedule_node_t *) (paging.curPos);p != head && i < paging.pageSize; i++){
			printf("\n\t\t\t    %-3d 『%d』 \t   『%d』 ", p->data.id, p->data.play_id,p->data.studio_id);
			printf("\t%4d-%02d-%02d\t",p->data.date.year, p->data.date.month, p->data.date.day);
			printf("%2d:%02d:00", p->data.time.hour, p->data.time.minute);
			printf("    %-5d\n", p->data.price);
			p=p->next;
		}
		printf("\n\t		=================================================================");
        printf("\n\t		|-------------总数%2d---------------------------%2d/%2d页-----------|",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
        printf("\n\t		|       [P]revPage            |              [N]extPage          |");
		printf("\n\t		|     [A]dd   |   [D]elete    |     [U]pdate     |   [V]iew All  |");         
		printf("\n\t		------------------------[R]eturn----------------------------------");	
  		printf("\n\t		==================================================================");
        	printf("\n\t		Iput Your choice:");
		
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
						printf("\n		               **没有计划信息，无法添加计划!**  /n");
						sleep(0.5);
					}
				}
			}
			break;
		case 'd':
		case 'D':
			printf("\t		|请输入计划ID：");
			while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin();printf("\n\t		                        **您的输入有误!请重新输入**     ");}
				}
			
			if (Schedule_UI_Delete(id)) {	//从新载入数据
					paging.totalRecords = Schedule_Srv_FetchByPlay(head,play_id);
					List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 'u':
		case 'U':
				printf("\t		|请输入计划ID：");
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin();printf("\n\t		                        **您的输入有误!请重新输入**     "); }
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
