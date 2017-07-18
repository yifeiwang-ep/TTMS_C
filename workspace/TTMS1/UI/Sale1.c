/*************************************************************************
	> File Name: Sale_UI.c
	> Author:wyf 
	> Mail: catherine199787@outlook.com
	> Created Time: Sat 18 Jun 2016 22:18:59 CST
 ************************************************************************/
#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "Ticket_UI.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Service/Sale.h"
#include "../Common/ComFunction.h"
#include "../Common/common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//引用登陆用户的全局数据结构
extern account_t gl_CurUser;

//根据计划ID，显示演出票
void Sale_UI_ShowTicket(int schID){
	// 请补充完整
	
}

inline int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
	
	int id;
	ticket_list_t head;
	schedule_t sch;
	
	
    printf("\n		|     请输入演出计划ID:");
			
	while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin();printf("\n		                        **您的输入有误!请重新输入**     ");}
	}
	
	if(!Schedule_Srv_FetchByID(id, &sch)){
			printf("\n		                        **未找到ID『%d』!按任意键返回**     ",id);
			getchar();
			return 0;
	}
	
	Ticket_Srv_FetchBySchID(tickList, sch.id);
			
	Seat_Srv_FetchValidByRoomID(seatList, sch.studio_id);
	
	
	Ticket_UI_ListBySch(&sch,tickList,seatList);
	
	
    return 1;
}



//根据剧目ID显示演出计划
void Sale_UI_ShowScheduler(int playID) {
	int i, id;
	char choice;
	
	play_t pdata;
	ticket_list_t tickList;
	seat_list_t   seatList;
	
	schedule_list_t head;
	schedule_node_t *p;
	Pagination_t paging;
	
	Play_Srv_FetchByID(playID, &pdata);
	
	List_Init(head, schedule_node_t);
	
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Schedule_Srv_FetchByPlay(head,playID);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n		=================================================================");
        	printf("\n		**************************剧目%s的演出计划*************************");
          	printf("\n		=================================================================");
		printf("\t\t%5s\t%5s\t%8s\t%10s\t%10s\t%10s\n", "ID", "剧目编号", "演出厅编号",
		 "上映日期","上映时间","票价");
		printf("\n		-----------------------------------------------------------------");
		
		if(!List_IsEmpty(head)){
			//显示数据
			for (i = 0, p = (schedule_node_t *) (paging.curPos);p != head && i < paging.pageSize; i++){
				printf("%5d  『%d』%20s  『%d』%2s ", p->data.id, p->data.play_id, p->data.play_name,p->data.studio_id, p->data.studio_name);
				printf("  %4d-%02d-%02d",p->data.date.year, p->data.date.month, p->data.date.day);
				printf("\t%2d:%02d:%02d ", p->data.time.hour, p->data.time.minute, p->data.time.second);
				printf("\t%5d\n", p->data.price);
			}
		}else{
		
			printf("\n		                    **没有演出厅信息！**");
			printf("\n		==================================================================");
		}
		printf("\n		==================================================================");
        	printf("\n		|----------总数%2d------------------------------%2d/%2d页---------|",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\n		******************************************************************");
        	printf("\n		|       [P]revPage          |              [N]extPage          |");
		printf("\n		-----------------------------------------------------------------");
		printf("\n		|         [S]ale       	  |             [R]eturn              |");
		printf("\n		******************************************************************");
		printf("\n		==================================================================");
		printf("\n		Iput Your choice:");
		choice=l_getc();
	

		switch (choice) {
			
		case 's':
		case 'S':
			{
				
				
				
				List_Init(tickList, ticket_node_t);
				List_Init(seatList,   seat_node_t);
				
				
			
			
				Sale_UI_SellTicket(tickList,seatList);
				
				List_Destroy(tickList, ticket_node_t);
				List_Destroy(seatList,   seat_node_t);
			}
			break;
		case 'p':
        case 'P':
			system("clear");
            if(Pageing_TotalPages(paging)>Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,1,schedule_node_t);
            }
			break;
		case 'n':
        case 'N':
			 system("clear");
            if(Pageing_TotalPages(paging)>Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,1,schedule_node_t);
            }
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}


void Sale_UI_MgtEntry() {
	int i, id;
	char choice;

	schedule_list_t head;
	//schedule_node_t *p;
	schedule_node_t *p;
	Pagination_t paging;

	List_Init(head, schedule_node_t);
	//List_Init(head,schedule_node_t);
	
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	
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
		
			for (i = 0, p = (schedule_node_t *) (paging.curPos);p != head && i < paging.pageSize; i++){
				printf("%5d  『%d』%20s  『%d』%2s ", p->data.id, p->data.play_id, p->data.play_name,p->data.studio_id, p->data.studio_name);
				printf("  %4d-%02d-%02d",p->data.date.year, p->data.date.month, p->data.date.day);
				printf("\t%2d:%02d:%02d ", p->data.time.hour, p->data.time.minute, p->data.time.second);
				printf("\t%5d\n", p->data.price);
				p=p->next;
		}

		printf("\n		==================================================================");
        	printf("\n		|----------总数%2d------------------------------%2d/%2d页---------|",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\n		******************************************************************");
        	printf("\n		|        [P]revPage          |              [N]extPage          |");
		printf("\n		-----------------------------------------------------------------");
		printf("\n		|         [I]D List    	  |             [R]eturn              |");
		printf("\n		******************************************************************");
		printf("\n		==================================================================");
		printf("\n		Iput Your choice:");
		choice=l_getc();
	

		switch (choice) {
		case 'i':
		case 'D':
				
				printf("\n		|     请输入演出计划ID：");
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\n		                    **您的输入有误！**");}
				}
				Sale_UI_ShowScheduler(id);
			
				break;
		case 'p':
        case 'P':
			system("clear");
	        if(1<Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,-1,schedule_node_t);
            }
			break;
		case 'n':
        case 'N':
		system("clear");
            if(Pageing_TotalPages(paging)>Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,1,schedule_node_t);
            }
		}

	
} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}

//退票
void Sale_UI_ReturnTicket(){
	char choice;
	int id,t=0;
     while(1){
		system("clear");
       		printf("\n		=================================================================");
        		printf("\n		**************************剧目%s的演出计划************************");
          		printf("\n		=================================================================");
            printf("\n		|     请输入演出计划ID:");
		
		while(1){
				if(scanf("%d",&id)==1){ cl_stdin(); break;}
				else{ cl_stdin();printf("\n		                    **您的输入有误！**");}
		}
		
		
		ticket_t buf;
		schedule_t scd;
			
	   	Schedule_Srv_FetchByID(buf.schedule_id, &scd);
		if( Ticket_Srv_FetchByID(id,&buf) ){
			if(buf.status==TICKET_SOLD){
       				Ticket_UI_Print(id);
       				user_time_t nowtime=TimeNow();
       				if(DateCmp(DateNow(), scd.date)==-1 || (DateCmp(DateNow(), scd.date)==0 && scd.time.hour<nowtime.hour && scd.time.minute<nowtime.minute ) ){
       				t=1;
       				Ticket_UI_Print(id);
       				}else{
       					printf("\n		                **您的输入有误！按任意键继续**");
					getchar();
					break;
					
       				}
       			}else{
       			
       				printf("\n		                    **信息不存在！按任意键返回**");
       				
				getchar();
				break;
       			}
       		}
		
		
		if(t){
			printf("\n		-----------------------------------------------------------------");
			printf("\n		|         [Q]uik    	       |             [R]eturn              |");
			printf("\n		******************************************************************");
			printf("\n		==================================================================");
			printf("\n		Iput Your choice:");
			choice=l_getc();
			if('r'==choice || 'R'==choice) break;	
			if('q'==choice || 'Q'==choice) {
			
				
	       			buf.status=TICKET_AVL;
	       			sale_t data;
	       					
	       			data.id=EntKey_Srv_CompNewKey("sale");
	       			data.user_id=gl_CurUser.id;
	       			data.ticket_id=id;
	       			data.date=DateNow();
	       			data.time=TimeNow();
	       			data.value=buf.price;
	       			data.type=SALE_RETURN;
	       					
	       			Sale_Srv_Add(&data);
	       					
	       			Ticket_Srv_Modify(&buf);
       				printf("\n		----------------------------**退票成功! **---------------------------------");
					printf("\n		==================================================================");
				cl_stdin();
				getchar();
											
				break;
       			}
       					
       		}
     			
		
	}
	
}

