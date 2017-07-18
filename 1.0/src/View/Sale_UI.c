#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "Ticket_UI.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Service/Sale.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//引用登陆用户的全局数据结构
extern account_t gl_CurUser;

//根据计划ID，显示演出票
void Sale_UI_ShowTicket(int schID){
	ticket_list_t list,p;
	Ticket_Srv_FetchBySchID(list,schID);
	p=list->next;
	printf("\n==================================================================\n");
	printf("********************** Projection Room List ************************\n");
	printf("%10s %10s %10s %10s %10s\n", "ID", "计划ID", "seatID","票价","状态");
	while(p != NULL){
		if (p->data.schedule_id == schID)
			printf("%10d  %10d  %10d  %10d  %10d\n",p->data.id,p->data.schedule_id,p->data.seat_id,p->data.price,p->data.status);
		p=p->next;	
	}
	getchar();
	Sale_UI_ReturnTicket();								
}
//售票  
inline int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
	int x,y;
	seat_list_t buf;
	sale_t p;
	ticket_list_t pre;
	printf("\n=======================================================\n");
	printf("****************  Update Projection Room  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("请输入要购买的演出座位行号:\n");
	scanf("%d",&x);
	printf("请输入要购买的演出座位列号:\n");
	scanf("%d",&y);
	buf=Seat_Srv_FindByRowCol(seatList,x,y);
	pre=Ticket_Srv_FindBySeatID(tickList,buf->data.id);
	pre->data.status=1;
	p.id=EntKey_Srv_CompNewKey("sale");
	p.ticket_id=EntKey_Srv_CompNewKey("ticket");
	printf("value:");
	scanf("%d",&p.value);
	Sale_Perst_Insert(p);
	Sale_UI_MgtEntry();
}



//根据剧目ID显示演出计划
void Sale_UI_ShowScheduler(int playID) {
	int i;
	char choice;

	schedule_list_t head;
	schedule_node_t *pos;
	Pagination_t paging;

	List_Init(head, schedule_node_t);
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		/*system("cls");*/
		printf("\n==================================================================\n");
		printf(
				"********************** Projection Room List **********************\n");
		printf("%10s %10s %15s %15s %15s %15s \n", "计划ID", "剧目ID", "演出厅ID","放映日期","放映时间","座位数");
		printf(
				"------------------------------------------------------------------\n");
		//显示数据
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
			printf("%-10d  %10d  %10d    %d%d%d    %d%d%d %10d\n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,pos->data.date.month,pos->data.date.month,pos->data.date.day,pos->data.time.hour,pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
		}

		printf("------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("******************************************************************\n");
		printf("[P]revPage            |       [N]extPage            |      [R]eturn");
		printf("\n==================================================================\n");
		printf("Your Choice:");
		choice = getchar();
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

//售票管理的总界面
void Sale_UI_MgtEntry() {
	int ID,roomID;
	char choice;
	
	ticket_list_t phead;
	ticket_node_t *poss;

	seat_list_t hhead;
	seat_node_t *ppos;

	List_Init(phead, ticket_node_t);
	List_Init(poss, ticket_node_t);

	List_Init(hhead,seat_node_t);
	List_Init(ppos,seat_node_t);


	//载入数据
	do {
		/*system("cls");*/
		printf("\n==================================================================\n");
		printf("********************** Projection Room List **********************\n");
		printf("[B]uy\n[A]xiansh\n[Z]teat\n[T]tui\n[R]eturn");
		printf("\n==================================================================\n");
		printf("Your Choice:");
		choice = getchar();
		switch (choice) {
		case 'a':
		case 'A':
		{
			Sale_UI_ShowScheduler(ID);
			break;
		}
		case 'b':
		case 'B':
		{
			printf("请输入计划ID:");
			scanf("%d",&ID);
			printf("请输入演出厅ID:");
			scanf("%d",&roomID);

			Seat_Srv_FetchByRoomID(hhead,roomID);
			Ticket_Srv_FetchBySchID(phead,ID);
			Sale_UI_SellTicket(phead,hhead);
			break;
		}
		case 'z':
		case 'Z':
		{
			printf("请输入剧目ID:\n");
			scanf("%d",&ID);
			Sale_UI_ShowTicket(ID);
			break;
		}
		case 't':
		case 'T':
		{
			Sale_UI_ReturnTicket();
			break;
		}
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(phead, ticket_node_t);
	List_Destroy(hhead, seat_node_t);
}

//退票
void Sale_UI_ReturnTicket(){
	int ID;
	ticket_t *buf;
	sale_t *date;
	printf("\n=======================================================\n");
	printf("****************  Update Projection Room  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("请输入要退票的ID:\n");
	scanf("%d",&ID);
	Ticket_Srv_FetchByID(ID,buf);
	Ticket_Perst_Update(buf);
	Sale_Srv_Add(date);
}
