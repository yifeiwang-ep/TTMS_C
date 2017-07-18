/*
 *  Seat.c
 *
 *  Created on: 2015年6月12日
 *  Author: lc
 */
#include <stdlib.h>
#include "../Common/list.h"
#include "Seat.h"
#include "../Persistence/Seat_Persist.h"
#include "./EntityKey.h"

inline int Seat_Srv_Add(const seat_t *data){
	return Seat_Perst_Insert(data);
}

inline int Seat_Srv_AddBatch(seat_list_t list){
	return Seat_Perst_InsertBatch(list);
}

inline int Seat_Srv_Modify(const seat_t *data){
	return Seat_Perst_Update(data);
}

inline int Seat_Srv_DeleteByID(int ID){
	return Seat_Perst_DeleteByID(ID);
}

inline int Seat_Srv_FetchByID(int ID, seat_t *buf){
	return Seat_Perst_SelectByID(ID, buf);
}

inline int Seat_Srv_DeleteAllByRoomID(int roomID){
	return Seat_Perst_DeleteAllByRoomID(roomID);
}

//根据演出厅ID载入座位
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID){

	//根据演出厅ID载入座位
	int SeatCount=Seat_Perst_SelectByRoomID(list, roomID);

	//对座位链表排序
	Seat_Srv_SortSeatList(list);
	return SeatCount;
}

/*根据放映厅ID提取有效的座位*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
	//根据演出厅ID载入座位
	int SeatCount=Seat_Perst_SelectByRoomID(list, roomID);

	seat_node_t *p;
	//去除无效座位
	List_ForEach(list, p){
		if(p->data.status!=SEAT_GOOD){
			List_FreeNode(p);
			SeatCount--;
		}
	}

	//对座位链表排序
	Seat_Srv_SortSeatList(list);
	return SeatCount;
}


//根据行、列数初始化演出厅的座位
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,
		int colsCount) {
	int i, j;

	seat_node_t *p;

	//批量获取主键
	long seatID=EntKey_Srv_CompNewKeys("Seat", rowsCount*colsCount);

	//先按行列数生成默认座位，形成链表
	for (i = 1; i <= rowsCount; i++){
		for (j = 1; j <= colsCount; j++) {
			p = (seat_node_t *) malloc(sizeof(seat_node_t));
			p->data.id = seatID;
			p->data.roomID = roomID;
			p->data.row = i;
			p->data.column = j;
			p->data.status = SEAT_GOOD;
			seatID++;
			List_AddTail(list, p);
		}
	}

	return Seat_Perst_InsertBatch(list);
}

//对座位链表list进行按座位行号和列号排序
void Seat_Srv_SortSeatList(seat_list_t list) {
	seat_node_t *p, *listLeft;
	assert(list!=NULL);

	if(List_IsEmpty(list))
		return ;

	//将next指针构成的循环链表从最后一个结点断开
	list->prev->next = NULL;

	//listLeft指向第一个数据节点
	listLeft = list->next;

	//将list链表置为空
	list->next = list->prev = list;

	while (listLeft != NULL ) {
		//取出第一个结点
		p = listLeft;
		listLeft = listLeft->next;

		//将结点p加入到已排序链表list中
		Seat_Srv_AddToSoftedList(list, p);
	}
}

//将结点node加入到已排序链表list中
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {

	seat_node_t *p;

	assert(list!=NULL && node!=NULL);

	if(List_IsEmpty(list))	{
		List_AddTail(list, node);
	}else{
		//寻找插入位置
		p=list->next;

		while(p!=list && (p->data.row<node->data.row ||
				(p->data.row==node->data.row && p->data.column<node->data.column))){
			p=p->next;
		}

		//将结点node加入到p之前
		List_InsertBefore(p, node);
	}
}

inline seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {

	assert(NULL!=list);
	seat_node_t *p;

	List_ForEach(list,p)
		if (p->data.row == row && p->data.column == column)
			return p;
	return NULL ;
}


inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {

	assert(NULL!=list);
	seat_node_t *p;

	List_ForEach(list,p)
		if (p->data.id==rowID)
			return p;

	return NULL ;
}
