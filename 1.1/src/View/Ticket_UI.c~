#include "Ticket_UI.h"

#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/Sale.h"
#include "../Service/EntityKey.h"
#include "../Common/ComFunction.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
static const int TICKET_PAGE_SZIE = 10;

extern account_t gl_CurUser;
//根据状态返回对应表示状态符号
inline char Ticket_UI_Status2Char(ticket_status_t status) {

	
	if(status == TICKET_AVL)
	{
		return 'E';
	}
	if(status == TICKET_SOLD)
	{
		return 'F';
	}
	if(status == TICKET_RESV)
	{
           return 'G';
	}
	return '\0';
}

void Ticket_UI_Print(int ID){
	// 请补充完整
	ticket_t buf;
	seat_t     sed;
	schedule_t scd;
	studio_t   std;
	play_t     pld;
	
   	Ticket_Srv_FetchByID(ID,&buf);
   	Seat_Srv_FetchByID(buf.seat_id, &sed);
   	
   	Schedule_Srv_FetchByID(buf.schedule_id, &scd);
   	
   	Studio_Srv_FetchByID(scd.studio_id, &std);
   	Play_Srv_FetchByID( scd.play_id,  &pld);
   	
   	char ptype[10];
   	switch(pld.type){
						case PLAY_TYPE_FILE: 	strcpy(ptype,"电影");   	break;
						case PLAY_TYPE_OPEAR: 	strcpy(ptype,"戏曲");;  break;
						case PLAY_TYPE_CONCERT: strcpy(ptype,"音乐");; 	break;
	}
   	system("clear");
   	printf("\n\n\n\n");
   	
	
	printf("\t\t\t╔================================================================================╗\n");
   	printf("\t\t\t‖"); printf("%80s‖\n"," ");
   	printf("\t\t\t‖%30s %20s %30s ‖\n"," ","X X 电影院"," ");
   	printf("\t\t\t‖"); printf("%80s‖\n"," ");
	printf("\t\t\t‖ \t%5s\t%-20s\t %5s\t%3d %3s %3d %3s","影厅：", std.name ,"座位：", sed.row ,"排", sed.column,"列");  printf("\t\t\t\t ‖\n");
	printf("\t\t\t‖"); printf("%80s‖\n"," ");
	printf("\t\t\t‖\t%5s\t%-20s\t%5s\t%5s\t%5s%3d","剧名：", pld.name,"类别：",ptype,"票价：",pld.price);  printf("\t\t ‖\n");
	printf("\t\t\t‖"); printf("%80s‖\n"," ");
	printf("\t\t\t‖\t%10s\t%5d-%02d-%02d\t%5s\t%02d:%02d","放映日期：",scd.date.year,scd.date.month,scd.date.day,"时间：" ,scd.time.hour,scd.time.minute);  printf("\t\t\t\t ‖\n");
	printf("\t\t\t‖"); printf("%80s‖\n"," ");
	printf("\t\t\t‖\t%25s:%5d ","本票ID（退票时使用）",ID); printf("\t\t\t\t\t\t ‖\n");
	printf("\t\t\t‖"); printf("%80s‖\n"," ");
	printf("\t\t\t‖"); printf("%80s‖\n"," ");
	printf("\t\t\t╚================================================================================╝\n\n");
	
				
	
	

}
//根据计划ID显示所有票
void Ticket_UI_ListBySch(const schedule_t *sch,	ticket_list_t tickList, seat_list_t seatList) {
	
	int i,id;
	char choice;
	
	
	
	ticket_node_t *pos;
	Pagination_t paging;
	
	
	paging.offset = 0;
	paging.pageSize = TICKET_PAGE_SIZE;
	
	//演出计划schedule_id
	paging.totalRecords=Ticket_Srv_FetchBySchID(tickList, sch->id);
	Paging_Locate_FirstPage(tickList, paging);
	do {
		system("clear");
	        printf("\t\t\t=====================================================================================\n\n");
	        printf(
				"\t\t\t*************************************票******************************************\n\n");
		printf("\t\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s","票ID","演出计划ID","座位ID","票价","票状态");

		printf("\n\t\t\t---------------------------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(tickList, paging, ticket_node_t, pos, i){
			printf("\t\t\t%2d\t\t%5d\t\t %8d\t%10d\t\t", pos->data.id,
					pos->data.schedule_id, pos->data.seat_id, pos->data.price);
					
			switch(pos->data.status){
				case TICKET_AVL:  	printf("%5s\n","待售"); 	break;
				case TICKET_SOLD:	printf("%5s\n","已售");  	break;
				case TICKET_RESV:   	printf("%5s\n","预留"); 	break;
			}
		}
		
		printf("\n\t\t\t------- 总数:%2d ---------------------------------------------------- 页数 %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t***************************************************************************************\n");
		printf("\n\t\t\t===================================================================================\n\n");
		
		printf("\n\t\t\t=========[P]上一页====================================[N]下一页=====================\n");
		printf("\n\t\t\t=========[A]售票==============[B]预留票===============[R]返回=====================\n");
		
		printf("\n\t\t\t===================================================================================\n");
		printf("\t\t\t请选择:");
		choice=l_getc();
		switch(choice)
		{
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(tickList, paging, -1, ticket_node_t);

			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(tickList, paging, 1, ticket_node_t);
			}
			break;
		case 'a':
		case 'A':
				{
					seat_node_t *p;
					int row,column,t=0;
		        	
				    	printf("\t\t\t请输入座位的行号:");
				    	
				    	while(1){
							if(scanf("%d", &(row))==1){ cl_stdin(); break;}
							else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
						}
				    	
				    	printf("\t\t\t请输入座位的列号:");
				    	
				    	while(1){
							if(scanf("%d", &(column))==1){ cl_stdin(); break;}
							else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
						}
					
					List_ForEach(seatList, p){
					
							if(row==p->data.row && column==p->data.column){
								
								ticket_node_t *td;
								
								td= Ticket_Srv_FindBySeatID(tickList, p->data.id);
								
								
								
								if(QueryTicket(td->data.id)==1){
									if(UpdateTicket(td->data.id) ){
										sale_t sdata;
	       					
							       			sdata.id=EntKey_Srv_CompNewKey("sale");
							       			sdata.user_id=gl_CurUser.id;
							       			sdata.ticket_id=td->data.id;
							       			sdata.date=DateNow();
							       			sdata.time=TimeNow();
							       			sdata.value=td->data.price;
							       			sdata.type=SALE_SELL;
							       					
							       			Sale_Srv_Add(&sdata);
											printf("\n\t\t\t售票成功！\t系统正在出票，请稍候。。。\n");
											sleep(1);
											Ticket_UI_Print(td->data.id);
											printf("\n\n\t\t\t按任意键继续！。。。\n");
											getchar();
											t=1;
											break;
									}else{
											printf("\n\t\t\t售票失败！\t请稍候重试。\n\t\t\t按任意键返回。。。\n");
											getchar();
											t=1;
											break;
									}
									
									
								}else{
								
									printf("\n\t\t\t该票已预留或售出！\t请重新输入。\n\t\t\t按任意键继续！。。。\n");
									getchar();
									break;
								}
							}
					}
						
						
					if(!t){
								
									printf("\n\t\t\t未找到该座位！\t请重新输入。\n\t\t\t按任意键继续！。。。\n");
									getchar();
									
								
								
					}
				
				paging.totalRecords = Ticket_Srv_FetchBySchID(tickList, sch->id);
				List_Paging(tickList, paging, ticket_node_t);	
			
				}
				break;
		case 'b':
		case 'B':
				{
					seat_node_t *p;
					int row,column,t=0;
		        	
				    	printf("\t\t\t请输入座位的行号:");
				    	
				    	while(1){
							if(scanf("%d", &(row))==1){ cl_stdin(); break;}
							else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
						}
				    	
				    	printf("\t\t\t请输入座位的列号:");
				    	
				    	while(1){
							if(scanf("%d", &(column))==1){ cl_stdin(); break;}
							else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
						}
					
					List_ForEach(seatList, p){
					
							if(row==p->data.row && column==p->data.column){
							
								ticket_node_t *td;
								
								td= Ticket_Srv_FindBySeatID(tickList, p->data.id);
								
								
								
								if(QueryTicket(td->data.id)==1){
								
									ticket_t  data;
									data=td->data;
									data.status=TICKET_RESV;
									
									if(Ticket_Srv_Modify(&data) ){
											printf("\n\t\t\t预留票成功！\n");
											
											printf("\n\n\t\t\t按任意键继续！。。。\n");
											getchar();
											t=1;
											break;
									}else{
											printf("\n\t\t\t预留票失败！\t请稍候重试。\n\t\t\t按任意键返回。。。\n");
											getchar();
											t=1;
											break;
									}
								}else{
								
									printf("\n\t\t\t该票已预留或售出！\t请重新输入。\n\t\t\t按任意键继续！。。。\n");
									getchar();
									break;
								}
							}
								
					
					}
						
						
						
					if(!t){	
									printf("\n\t\t\t未找到该座位！\t请重新输入。\n\t\t\t按任意键继续！。。。\n");
									getchar();
							
					}
						
				paging.totalRecords = Ticket_Srv_FetchBySchID(tickList, sch->id);
				List_Paging(tickList, paging, ticket_node_t);		
					
			
				}
				break;
			
		
		
		}
	} while (choice != 'r' && choice != 'R');
	
	
	
}

void ListTickets(void){
	
	
			
}



int UpdateTicket(int id){
	
	ticket_t buf;
	if( Ticket_Srv_FetchByID(id,&buf) ){
			buf.status=TICKET_SOLD;
			Ticket_Srv_Modify(&buf);
        	return 1;
    }
    return 0;
}


int QueryTicket(int id){

	ticket_t buf;
	if( Ticket_Srv_FetchByID(id,&buf) ){
       			if(buf.status!=TICKET_AVL){
       				return 0;
       			
       			}
       			return 1;
       	}else{
       	
       		return -1;
       	}
}
