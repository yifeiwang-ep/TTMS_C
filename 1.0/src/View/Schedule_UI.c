#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"

#include <stdio.h>
#include <stdlib.h>
//显示所有演出计划界面
void Schedule_UI_ListAll(void) {
	schedule_list_t list;
	Schedule_Srv_FetchAll(list);
	schedule_node_t *rec=list->next;
	while (rec != NULL){
		printf("\n=======================================================\n");
		printf("****************  Update Projection Room  ****************\n");
		printf("-------------------------------------------------------\n");
		printf("\n演出计划ID:%d\n", rec->data.id);
		printf("演出厅ID%d\n:", rec->data.studio_id);
		printf("放映日期:%d%d%d\n:",rec->data.date.year,rec->data.date.month,rec->data.date.day);
		printf("放映时间:%d\n:",rec->data.time.hour,rec->data.time.minute,rec->data.time.second);
		printf("座位数:%d\n", rec->data.seat_count);
		rec=rec->next;
	}
}
//添加剧目ID的新演出计划界面
int Schedule_UI_Add(int play_id) {
	schedule_t rec;
	int newRecCount = 0;
	char choice;

	do {
		/*system("cls");*/
		printf("\n=======================================================\n");
		printf("****************  Add New Projection Room  ****************\n");
		printf("-------------------------------------------------------\n");
		fflush(stdin);
		rec.id = EntKey_Srv_CompNewKey("schedule");
		printf("演出厅ID:");
		scanf("%d", &(rec.studio_id));
		printf("放映日期:");
		scanf("%d%d%d", &(rec.date.year),&(rec.date.month),&(rec.date.day));
		printf("放映时间:");
		getchar();
		scanf("%d%d%d",&(rec.time.hour),&(rec.time.minute),&(rec.time.second));
		rec.seat_count = 0;
		printf("=======================================================\n");

		if (Schedule_Srv_Add(&rec)) {
			rec.seat_count += 1;
			newRecCount += 1;
			printf("The new room added successfully!\n");
		} else
			printf("The new room added failed!\n");
		printf("-------------------------------------------------------\n");
		printf("[A]dd more, [R]eturn:");
		fflush(stdin);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}
//根据ID修改演出计划界面
int Schedule_UI_Modify(int id){
	schedule_t rec;
	int rtn = 0,seatcount;

	/*Load record*/
	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("The room does not exist!\nPress [Enter] key to return!\n");
		getchar();
		return 0;
	}

	printf("\n=======================================================\n");
	printf("****************  Update Projection Room  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("演出计划ID:%d\n", rec.id);
	printf("演出厅ID%d\n:", rec.studio_id);
	printf("放映日期:%d%d%d\n:",rec.date.year,rec.date.month,rec.date.day);
	printf("放映时间:%d\n:",rec.time.hour,rec.time.minute,rec.time.second);
	printf("座位数:%d\n", rec.seat_count);
	fflush(stdin);
	seatcount =Schedule_Perst_SelectByID(rec);
	if (!seatcount) {
		printf("演出厅ID:");
		scanf("%d", &(rec.studio_id));
		printf("放映日期:");
		scanf("%d%d%d", &(rec.date.year),&(rec.date.month),&(rec.date.day));
		printf("放映时间:");
		scanf("%d%d%d",&(rec.time.hour),&(rec.time.minute),&(rec.time.second));
	}

	printf("-------------------------------------------------------\n");
	Schedule_Perst_DeleteByID(id);
	Schedule_Perst_Insert(&rec);

	if (Schedule_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
				"The room data updated successfully!\nPress [Enter] key to return!\n");
	} else
		printf("The room data updated failed!\nPress [Enter] key to return!\n");

	getchar();
	return rtn;
}
//根据ID删除演出计划界面
int Schedule_UI_Delete(int id){

	int rtn = 0;

	if (Schedule_Srv_DeleteByID(id)) {
		if (Ticket_Perst_Delete(id))
			printf("The seats of the room deleted successfully!\n");
		printf(
				"The room deleted successfully!\nPress [Enter] key to return!\n");
		rtn = 1;
	} else {
		printf("The room does not exist!\nPress [Enter] key to return!\n");
	}

	getchar();
	return rtn;
}
//根据ID查询演出计划界面
int Schedule_UI_Query(int id){
	
	schedule_t rec;
	int rtn = 0,seatcount;

	/*Load record*/
	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("The room does not exist!\nPress [Enter] key to return!\n");
		getchar();
		return 0;
	}

	printf("\n=======================================================\n");
	printf("****************  Update Projection Room  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("演出计划ID:%d\n", rec.id);
	printf("演出厅ID%d\n:", rec.studio_id);
	printf("放映日期:%d%d%d\n:",rec.date.year,rec.date.month,rec.date.day);
	printf("放映时间:%d\n:",rec.time.hour,rec.time.minute,rec.time.second);
	printf("座位数:%d\n", rec.seat_count);
	return 0;
	
}

/*以列表模式显示给定剧目的演出计划信息*/
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging){

	Schedule_Srv_FetchAll(list);
	schedule_node_t *rec=list->next;
	while (rec != NULL){
		printf("\n=======================================================\n");
		printf("****************  Update Projection Room  ****************\n");
		printf("-------------------------------------------------------\n");
		printf("演出厅ID%d\n:", rec->data.studio_id);
		printf("放映日期:%d%d%d\n:",rec->data.date.year,rec->data.date.month,rec->data.date.day);
		printf("放映时间:%d\n:",rec->data.time.hour,rec->data.time.minute,rec->data.time.second);
		printf("座位数:%d\n", rec->data.seat_count);
		rec=rec->next;
	}

	
}
//根据剧目ID管理演出计划界面
void Schedule_UI_MgtEntry(int play_id){
        int i,ID;
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
		printf("[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate  [R]eturn");
		printf("\n==================================================================\n");
		printf("Your Choice:");
		fflush(stdin);
		scanf("%c", &choice);

		switch (choice) {
		case 'a':
		case 'A':
			if (Schedule_UI_Add(play_id)) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
			break;
		case 'd':
		case 'D':
		{
			printf("\n=======================================================\n");
			printf("****************  Update Projection Room  ****************\n");
			printf("-------------------------------------------------------\n");
			printf("请输入要删除的演出计划ID:\n");
			scanf("%d",&ID);
			if (Schedule_UI_Delete(ID)) {	//从新载入数据
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		}
		case 'u':
		case 'U':
		{
			printf("\n=======================================================\n");
			printf("****************  Update Projection Room  ****************\n");
			printf("-------------------------------------------------------\n");
			printf("请输入要修改的演出计划ID:\n");
			scanf("%d",&ID);
			if (Schedule_UI_Modify(ID)) {	//从新载入数据
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		}
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
