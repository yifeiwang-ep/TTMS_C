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
	
	
	printf("\t\t请输入演出计划的ID:");
			
	while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
	}
	
	if(!Schedule_Srv_FetchByID(id, &sch)){
			printf("\n\t\t未找到ID为%d的演出计划，按任意键返回 。。。",id);
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
		printf("\n\t\t=====================================================================================\n\n");
		printf("\t\t\t***************** 剧目：%10s 的演出计划 列表 ****************\n\n",pdata.name);
		printf("\t\t%5s \t %5s\t%8s \t %10s \t %10s \t %10s \n", "ID", "剧目ID", "演出厅ID",
				 "放映日期","放映时间","座位数");
		printf("\t\t-------------------------------------------------------------------------------------------\n\n");
		
		if(!List_IsEmpty(head)){
			//显示数据
			for (i = 0, p = (schedule_node_t *) (paging.curPos);p != head && i < paging.pageSize; i++){
				printf("\t\t%5d %5d %5d ", p->data.id, p->data.play_id,p->data.studio_id);
			
				printf("\t%4d-%02d-%02d ",p->data.date.year, p->data.date.month, p->data.date.day);
				printf("\t%2d:%02d:%02d ", p->data.time.hour, p->data.time.minute, p->data.time.second);
				printf("\t%5d\n", p->data.seat_count);
				p=p->next;
			}
		}else{
		
			printf("\t\t\t暂无数据！\n");
		}

		printf("\n\t\t----------------- 共:%2d条数据 -------------------------- 页码 %2d/%2d --------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t*************************************************************************************\n\n");
		printf("\t\t=========================[P]上页============================[N]下页==========[R]返回========\n\n");
		printf("\t\t=========================[S]进入售票系统====================================================\n\n");
		
		
		
		printf("\n\n\t\t=====================================================================================\n");
		printf("\t\t请选择:");
		
		choice=l_getc();
	

		switch (choice) {
		
		case 'u':
		case 'U':
			
				printf("\t\t请输入要修改演出计划的ID:");
			
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
			
				
			break;
			
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
			
		case 't':
		case 'T':
			//();
			break;
		
		case 'p':
		case 'P':
			if(1<Pageing_CurPage(paging))
                Paging_Locate_OffsetPage(head,paging,-1,schedule_node_t);
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
		printf("\t\t*********************************** 剧目 列表 **************************************\n\n");
		printf("\t\t%5s \t %20s\t%8s \t %5s \t %10s \t %10s \t %5s \n", "ID", "名称", "地区",
				"时长", "上映日期","下线日期","票价");
		printf("\t\t-------------------------------------------------------------------------------------\n\n");
		
		
		//显示数据
		for (i = 0, p = (play_node_t *) (paging.curPos);p != head && i < paging.pageSize; i++){
			printf("\t\t%5d %20s %10s %5d ", p->data.id, p->data.name,p->data.area, p->data.duration);
			printf("\t%4d-%02d-%02d ", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
			printf("\t%4d-%02d-%02d ",p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
			printf("\t%5d\n", p->data.price);
			p=p->next;
		}

		printf("\n\t\t----------------- 共:%2d条数据 -------------------------- 页码 %2d/%2d ----------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t*************************************************************************************\n\n");
		printf("\t\t======================[P]上页==============================[N]下页===================\n\n");
		
		
		printf("\t\t====[A]根据剧目ID列出演出计划=====================================[R]返回===========\n\n");
		
		
		printf("\t\t=====================================================================================\n");
		printf("\t\t请选择:");
		
		choice=l_getc();
	

		switch (choice) {
		case 'a':
		case 'A':
				
				printf("\t\t请输入要浏览演出计划的 剧目ID:");
				while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
				}
				Sale_UI_ShowScheduler(id);
			
				break;
		/*
		case 'u':
		case 'U':
			
			
			break;
			
		
		*/
		case 'p':
		case 'P':
			if(1<Pageing_CurPage(paging))
                Paging_Locate_OffsetPage(head,paging,-1,play_node_t);

			break;
		case 'n':
		case 'N':
			 system("clear");
            if(Pageing_TotalPages(paging)>Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,1,play_node_t);
            }
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, play_node_t);
}

//退票
void Sale_UI_ReturnTicket(){
	char choice;
	int id,t=0;
     while(1){
		system("clear");
       		printf("\n\n\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		printf("\t\t------------------------------------------退   票--------------------------------------\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		
       		printf("\t\t请输入票的ID:");
		
		while(1){
				if(scanf("%d",&id)==1){ cl_stdin(); break;}
				else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
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
       					printf("\n\t\t该票已过有效期，无法退票");
       					printf("\n\n\t\t\t按任意键继续！。。。\n");
					getchar();
					break;
					
       				}
       			}else{
       			
       				printf("\n\t\t该票不存在或未售出，无法退票");
       				printf("\n\n\t\t\t按任意键继续！。。。\n");
       				
				getchar();
				break;
       			}
       		}
		
		
		if(t){
			printf("\t\t请输入 Q 确认退票  输入 R 返回：");	
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
       					
       				printf("\n\t\t退票成功！");
       				printf("\n\n\t\t\t按任意键继续！。。。\n");
				cl_stdin();
				getchar();
											
				break;
       			}
       					
       		}
     			
		
	}
	
}
