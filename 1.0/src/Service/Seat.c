/*
 *  Seat.c
 *
 *  Created on: 2015年6月12日
 *  Author: lc
 */
#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"
#include "../Persistence/Seat_Persist.h"
#include "EntityKey.h"

//单个添加座位服务
inline int Seat_Srv_Add(const seat_t *data){
	return Seat_Perst_Insert(data);
}

//批量添加座位服务
inline int Seat_Srv_AddBatch(seat_list_t list){
	return Seat_Perst_InsertBatch(list);
}

//修改座位服务
inline int Seat_Srv_Modify(const seat_t *data){
	return Seat_Perst_Update(data);
}

//根据id删除座位服务
inline int Seat_Srv_DeleteByID(int ID){
	return Seat_Perst_DeleteByID(ID);
}

//根据id获取座位服务
inline int Seat_Srv_FetchByID(int ID, seat_t *buf){
	return Seat_Perst_SelectByID(ID, buf);
}

//根据演出厅id删除其所有座位服务
inline int Seat_Srv_DeleteAllByRoomID(int roomID){
	return Seat_Perst_DeleteAllByRoomID(roomID);
}

//根据演出厅ID获取其所有座位服务
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID){
       return Seat_Perst_SelectByRoomID(list, roomID);
}

//根据演出厅ID获取其有效座位服务
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
      	int count=Seat_Perst_SelectByRoomID(list, roomID);
	return count;
}


//演出厅座位初始化服务
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,int colsCount) {
	int i,j,count=0;
	seat_list_t newNode;
	for(i=1;i<=rowsCount;i++)
	{
		for(j=1;j<=colsCount;j++)
		{
			newNode = (seat_node_t*)malloc(sizeof(seat_node_t));
			newNode->data.id = EntKey_Srv_CompNewKey("seat");
			newNode->data.roomID = roomID;
			newNode->data.row = i;
			newNode->data.column = j;
			newNode->data.status = 0;
			List_AddTail(list, newNode);
			count++;
		}
	}
       return count;
}

//对座位链表list进行按座位行号和列号排序
void Seat_Srv_SortSeatList(seat_list_t list) {
	seat_list_t temp=NULL , buf = list->next ,flag;       
	List_Init(temp, seat_node_t);
	while(buf!=list)
	{
		if(temp->next==temp)
		{
			List_AddHead(temp, buf);
			flag=temp->next;
		}
		else
		{
			while((flag->data.row < buf->data.row || (flag->data.row == buf->data.row && flag->data.column < buf->data.column)) && flag->next!=temp)
			{
				flag=flag->next;
			}
			List_InsertBefore(flag, buf);
		}
		buf=list->next;
	}
	list->next = temp->next;
	temp->next->prev = list;
}

//将新结点node加入到已排序链表list中 直接加到list尾
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       List_AddTail(list, node);
}

//根据行列号在已知链表上查找座位
inline seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
       seat_list_t buf = list->next;
	while(buf!=list)
	{
		if(buf->data.row == row && buf->data.column == column)
		{
			return buf;
		}
		buf=buf->next;
	}
       return NULL;
}

//根据座位id在已知链表上查找座位
inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int seatID) {
	seat_list_t buf = list->next;
	while(buf!=list)
	{
		if(buf->data.id == seatID)
		{
			return buf;
		}
		buf=buf->next;
	}
       return NULL;
}
