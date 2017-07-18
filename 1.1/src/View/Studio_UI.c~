/*
 * Studio_UI.c
 *
 *  Created on: 2015年4月24日
 *      Author: Administrator
 */
#include "Studio_UI.h"

#include "../Common/List.h"
#include "../Common/ComFunction.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"
#include "../Service/EntityKey.h"
#include "Seat_UI.h"

static const int STUDIO_PAGE_SIZE = 2;

#include <stdio.h>

void Studio_UI_MgtEntry(void) {
	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
				printf("\t\t\t=========================================================================================\n\n");
		printf(
				"\t\t\t***********************************演出厅管理界面*****************************************\n\n");
		printf("\t\t\t\t%5s \t %20s \t %10s \t %10s \t %10s\n", "演出厅ID", "演出厅名称", "座位行数",
				"座位列数", "座位总数");
		printf(
				"\t\t\t--------------------------------------------------------------------------------------------\n");
		//显示数据
		Paging_ViewPage_ForEach(head, paging, studio_node_t, pos, i){
			printf("\t\t\t\t%5d  %22s  %13d \t %13d \t  %10d\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
		}

		printf("\t\t\t------- 总数:%2d ---------------------------------------------------- 页数 %2d/%2d ------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t********************************************************************************************\n");
		printf("\t\t\t[P]上一页 | [N]下一页 | [A]添加 | [D]删除 | [Y]确认删除｜[U]修改 | [S]座位管理 | [R]返回");
		printf("\n\t\t\t==========================================================================================\n");
		printf("\t\t\t请选择:");

		choice=l_getc();

		switch (choice) {
		case 'a':
		case 'A':
			if (Studio_UI_Add()) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
			}
			break;
		case 'd':
		case 'D':
			{char ch;
			printf("\t\t\t请输入ID:");
			while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
			}
			printf("\t\t\t确认删除[y/n]:");
			ch=l_getc();
			if(ch=='Y' || ch== 'y')
			{
			  
			  if (Studio_UI_Delete(id)) {	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			}
			break;
			}
		case 'u':
		case 'U':
			printf("\t\t\t请输入ID:");
			while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
			}
			if (Studio_UI_Modify(id)) {	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 's':
		case 'S':
			printf("\t\t\t请输入ID:");
			while(1){
					if(scanf("%d",&id)==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\t\t您的输入有误！请重新输入:"); }
			}
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, studio_node_t);
}

int Studio_UI_Add(void) {
	studio_t rec;
	int newRecCount = 0,er;
	char choice;

	do {
		system("clear");
		printf("\n\t\t\t===========================================================================\n\n");
		printf("\t\t\t******************************演出厅添加界面**********************************\n\n");
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		printf("\t\t\t请输入演出厅名称:");
		//cl_stdin();
		scanf("%s",rec.name);
		
		printf("\t\t\t请输入座位行数:");
		while(1){
			if(scanf("%d", &(rec.rowsCount))==1){ cl_stdin(); break;}
			else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
			}
		
		
		printf("\t\t\t请输入座位列数:");
		while(1){
			if(scanf("%d", &(rec.colsCount))==1){ cl_stdin(); break;}
			else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
			}
		rec.seatsCount = rec.rowsCount * rec.colsCount;
		printf("\t\t\t================================================================================\n");

		//获取主键
		rec.id = EntKey_Srv_CompNewKey("Studio");

		if (Studio_Srv_Add(&rec)) {
			seat_list_t list=NULL;
			Seat_Srv_RoomInit(list,rec.id,rec.rowsCount,rec.colsCount);
			newRecCount += 1;
			printf("\t\t\t演出厅添加成功!\n");
		} else
			printf("\t\t\t演出厅添加失败\n");
		printf("\t\t\t-------------------------------------------------------------------------------\n");
		printf("\t\t\t[A]继续添加 | [R]返回\n");
		printf("\t\t\t请选择:");
		
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;
	char choice;
	int t;

	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t演出厅不存在!\n\t\t\t按任意键退出!\n");
		getchar();
		return 0;
	}
	system("clear");
	printf("\n\t\t\t==================================================================================\n\n");
	printf("\t\t\t**********************************演出厅修改界面***********************************\n\n");
	printf("\t\t\t----------------------------------------------------------------------------------\n");
	printf("\t\t\t\t%5s \t %20s \t %10s \t %10s\n", "演出厅ID", "演出厅名称", "座位行数","座位列数");
	printf("\t\t\t\t%5d  %22s  %13d \t %13d\n", rec.id,rec.name, rec.rowsCount, rec.colsCount);
	printf("\t\t\t----------------------------------------------------------------------------------\n");
	printf("\t\t\t[1]修改演出厅名称                  [2]修改座位行数                      [3]修改座位列\n");
	printf("\t\t\t----------------------------------------------------------------------------------\n");
	//printf("\t\t\t演出厅ID:%d\n", rec.id);
	printf("\t\t\t请选择:");
	choice=l_getc();
	switch(choice)
	{
	case '1':
		printf("\t\t\t演出厅名称:");
		fflush(stdin);
		scanf("%s",rec.name);
		break;
	case '2':
	   t=2;
	   break;
	case '3':
	   t=3;
	  break;
	 }
	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if (seatcount) {
		//do {	
				//如果座位文件中已有座位信息，则更新的行列必须比以前大，否则不允许更改
		while(t==2)
		{
			printf("\t\t\t座位的行数必须大于[%d]:", rec.rowsCount);
			//scanf("%d", &(newrow));
			while(1){
			if(scanf("%d", &(newrow))==1){ cl_stdin(); break;}
			else {cl_stdin(); printf("\t\t\t座位的行数必须大于[%d]:", rec.rowsCount);}
			}
			if(newrow > rec.rowsCount)
			{
				rec.rowsCount = newrow;
				break;
			}
		}
		while(t==3)
		{
			printf("\t\t\t座位的列数必须大于[%d]:", rec.colsCount);
			//scanf("%d", &(newcolumn));
			while(1){
			if(scanf("%d", &(newcolumn))==1){ cl_stdin(); break;}
			else {cl_stdin(); printf("\t\t\t座位的列数数必须大于[%d]:", rec.colsCount);}
			}
			if(newcolumn > rec.colsCount)
			{
				rec.colsCount = newcolumn;
				break;
			}
		}
		//} while (newrow < rec.rowsCount || newcolumn < rec.colsCount);
		
		
		rec.seatsCount = seatcount;
	} else {
		if(t==2)
		{
		 printf("\t\t\t请输入新的座位行数:");
		 //scanf("%d", &rec.rowsCount);
		 while(1){
			if(scanf("%d", &(rec.rowsCount))==1){ cl_stdin(); break;}
			else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
			}
		}
		if(t==3)
		{
		printf("\t\t\t请输入新的座位列数:");
		//scanf("%d", &rec.colsCount);
		while(1){
			if(scanf("%d", &(rec.colsCount))==1){ cl_stdin(); break;}
			else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
			}
		}
		rec.seatsCount = 0;
	}

	printf("\t\t\t-------------------------------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
				"\t\t\t演出厅修改成功!\n\t\t\t按任意键返回!\n");
	} else
		printf("\t\t\t演出厅修改失败!\n\t\t\t按任意键返回!\n");

	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		//在删除放映厅时，同时根据放映厅id删除座位文件中的座位
		if (Seat_Srv_DeleteAllByRoomID(id))
			printf("\t\t\t演出厅座位删除成功!\n");
		printf(
				"\t\t\t演出厅删除成功\n\t\t\t按任意键退出!\n");
		rtn = 1;
	} else {
		printf("演出厅不存在\n\t\t\t按任意键退出!\n");
	}

	getchar();
	return rtn;
}

