/*
 *  Seat_UI.c
 *
 *  Created on: 2015年5月23日
 *  Author: lc
 */
#include "Seat_UI.h"

#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/List.h"
#include <stdio.h>

//演出厅座位管理页面
void Seat_UI_MgtEntry(int roomID) {
	int row, column , i,j,type;
	char userName[30];
	char choice;

	studio_t temp;
	seat_list_t head;
	seat_node_t *pos;



	List_Init(head, seat_node_t);
	List_Init(pos, seat_node_t);

	//载入数据
	Seat_Srv_FetchByRoomID( head, roomID);
	//Seat_Srv_SortSeatList(head);

	do {
		/*system("cls");*/

		if(!Studio_Srv_FetchByID(roomID, &temp))	
		{
			printf("该演出厅不存在\n");
			return;
		}

		printf("\n==================================================================\n");
		printf(
				"********************** Projection Seat List **********************\n");
		printf(
				"------------------------------------------------------------------\n");
	
		//显示数据
		printf(" %3s","~");
		for(i=1;i<=temp.colsCount;i++)
			printf(" %3d",i);
		printf("\n");
		for(i=1;i<=temp.rowsCount;i++)
		{
			printf(" %3d",i);
			for(j=1;j<=temp.colsCount;j++)
			{
				pos = Seat_Srv_FindByRowCol(head,i, j);
				if(pos!=NULL)				
					printf(" %3c",Seat_UI_Status2Char(pos->data.status));
				else
					printf(" %3s"," ");
			}
			printf("\n");
		}


		printf("******************************************************************\n");
		printf("[A]dd|[D]elete|[U]pdate |  [R]eturn");
		printf("\n==================================================================\n");
		printf("Your Choice:");
		fflush(stdin);
		scanf("%c", &choice);
		getchar();
 		//scanf("%*c");
		//fflush(stdin);

		switch (choice) {
		case 'a':
		case 'A':
			printf("请输入添加座位的行号：");
			scanf("%d",&row);
			getchar();
			printf("请输入添加座位的列号：");
			scanf("%d",&column);
			getchar();
			Seat_UI_Add(head, roomID, row, column);
			if(row>temp.rowsCount)
			{
				temp.rowsCount = row;
			}
			if(column>temp.colsCount)
			{
				temp.colsCount = column;
			}
			Studio_Srv_Modify(&temp);
			break;
		case 'u':
		case 'U':
			printf("请输入要修改的座位所在行：");
			scanf("%d",&row);
			getchar();
			printf("请输入要修改的座位所在列：");
			scanf("%d",&column);
			getchar();
					
			Seat_UI_Modify(head, row, column);
			break;
		case 'd':
		case 'D':
			printf("请输入要修改的座位所在行：");
			scanf("%d",&row);
			getchar();
			printf("请输入要修改的座位所在列：");
			scanf("%d",&column);
			getchar();

			Seat_UI_Delete(head, row, column);
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, seat_node_t);

}

//根据状态返回对应表示状态符号
inline char Seat_UI_Status2Char(seat_status_t status) {

	if(status == 0)
	{
		return 'O';
	}
	if(status == 1)
	{
		return 'H';
	}
	if(status == 9)
	{
       		return 'x';
	}
}

//根据状态符号返回桌位状态
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	// 请补充完整
        seat_status_t tmp;
       return tmp;
}

//添加演出厅新座位界面
int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //输入一个座位
	seat_list_t data=(seat_list_t)malloc(sizeof(seat_node_t));
	data->data.id = EntKey_Srv_CompNewKeys("seat", 1);
	data->data.roomID = roomID;
	data->data.row = row;
	data->data.column = column;
	data->data.status = 0;
	Seat_Srv_AddToSoftedList(list, data);
	if(Seat_Srv_Add(&(data->data)))
	{
		printf("添加成功\n");
		return 1;
	}
	printf("添加失败\n");
       return 0;
}

int Seat_UI_Modify(seat_list_t list, int row, int column) {
	seat_node_t *data;
	int type;
	data = Seat_Srv_FindByRowCol( list, row, column);
	do {
		printf("\n=======================================================\n");
		printf("****************  Updata Seat  ****************\n");
		printf("-------------------------------------------------------\n");
		fflush(stdin);
		printf("请重新设定座位的状态： [0]空\t[1]完好\t[9]损坏\n");
		printf("=======================================================\n");
		scanf("%d",&type);
		getchar();
	}
	while(type!=0 && type!=1 && type!=9);
	data->data.status = type;
	if(Seat_Srv_Modify(&(data->data)))
	{
		printf("修改成功\n");
		return 1;
	}
	printf("修改失败\n");
       return 0;	
}

int Seat_UI_Delete(seat_list_t list, int row, int column) {
	seat_node_t *data;
	data = Seat_Srv_FindByRowCol( list, row, column);

	if(Seat_Srv_DeleteByID(data->data.id))
	{
		printf("删除成功\n");
		List_FreeNode(data); 
		return 1;
	}
	printf("删除失败\n");	
	List_FreeNode(data); 
	return 0;
}


