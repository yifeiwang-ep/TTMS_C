/*
 *  Seat.c
 *
 *  Created on: 2015年6月12日
 *  Author: lc
 */
 #include <stdio.h>
#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"
#include "../Persistence/Seat_Persist.h"
#include "EntityKey.h"

inline int Seat_Srv_Add(const seat_t *data){
	// 请补充完整
       return Seat_Perst_Insert(data);
}

inline int Seat_Srv_AddBatch(seat_list_t list){
	// 请补充完整
       return Seat_Perst_InsertBatch(list);
}

inline int Seat_Srv_Modify(const seat_t *data){
	// 请补充完整
       return Seat_Perst_Update(data);
}

inline int Seat_Srv_DeleteByID(int ID){
	// 请补充完整
       return Seat_Perst_DeleteByID(ID);
}

inline int Seat_Srv_FetchByID(int ID, seat_t *buf){
	// 请补充完整
       return Seat_Perst_SelectByID(ID,buf);
}

inline int Seat_Srv_DeleteAllByRoomID(int roomID){
	// 请补充完整
       return Seat_Perst_DeleteAllByRoomID(roomID);
}

//根据演出厅ID载入座位
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID){
       // 请补充完整
       return Seat_Perst_SelectByRoomID(list,roomID);
}
/*根据放映厅ID提取有效的座位*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       // 请补充完整
       int rtn;
       seat_node_t  *p;
       rtn = Seat_Perst_SelectByRoomID(list,roomID);
       List_ForEach(list,p)
       {
       		if(p->data.roomID == roomID)
       		{
       			if(p->data.status != SEAT_GOOD)
			{
				rtn--;
				 List_FreeNode(p);
			}
		}
	}       			
       return rtn;
}


//根据行、列数初始化演出厅的座位
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,int colsCount) {
	// 请补充完整
	seat_node_t *p;
	int i,j,x,y,key;
	x=rowsCount;
	y=colsCount;
	key=EntKey_Srv_CompNewKeys("seat",x*y);
	if(list==NULL){
		List_Init(list, seat_node_t);
	}
	for(i=1;i<=x;i++)
	{
	    for(j=1;j<=y;j++)
	    {
	    	
	    	p=(seat_node_t *)malloc(sizeof(seat_node_t));
	    	
	    	p->data.id=key;
	    	p->data.roomID=roomID;
	    	p->data.row=i;
	    	p->data.column=j;
	    	p->data.status=SEAT_GOOD;
	    	
	    	
	    	List_AddTail(list,p);
	    	
	    	key++;
	    	
	    }
	}	
	
	  Seat_Perst_InsertBatch(list);  	
	
       return 1;
}

//对座位链表list进行按座位行号和列号排序
void Seat_Srv_SortSeatList(seat_list_t list) {
       // 请补充完整
       seat_node_t *listLeft,*p;
       if(List_IsEmpty(list))
       {
       		//return 0;
       }else{
	       list->prev->next = NULL;
	       listLeft=list->next;
	       list->next=list->prev=list;
	       while(listLeft!=NULL)
	       {
	       	    p=listLeft;
	       	    listLeft=listLeft->next;
	       	    Seat_Srv_AddToSoftedList(list,p);
	       	} 
	}    
}

//将结点node加入到已排序链表list中
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       // 请补充完整
       if(List_IsEmpty(list))
       {
       		List_AddTail(list,node);
       }
       seat_node_t *p;
       p=list->next;
       while(!(p!=list && (p->data.row<node->data.row || p->data.row == node->data.row) && (p->data.column < node->data.column)))
       {
       			p=p->next;
       }
       List_InsertBefore(node,p);
}

inline seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
       // 请补充完整
       seat_node_t *p;
       int t=0;
       List_ForEach(list,p)
       {
       		if(p->data.row==row && p->data.column == column)
       		{
       				t=1;
       				return p;
       		}
       	}
       	if(t==0)
       	{
       		printf("查询的座位不存在！\n");
                return NULL;
        }
}


inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
       // 请补充完整
       seat_node_t *p;
       int t=0;
       List_ForEach(list,p)
       {
       		if(p->data.id == rowID)
       		{
       			t=1;
       			return p;
       		}
       	}
       	if(t==0)
       	{
       		printf("查询的座位不存在!\n");
               return NULL;
         }
}
