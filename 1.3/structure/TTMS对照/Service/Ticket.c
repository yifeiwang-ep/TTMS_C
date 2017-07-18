#include "Ticket.h"
#include "EntityKey.h"

#include "../Common/list.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Service/Seat.h"

#include <stdio.h>
#include <stdlib.h>

int Ticket_Srv_AddBatch(int schedule_id, int studio_id){
	ticket_t data;
	ticket_list_t list=NULL;
	seat_list_t seat_head;
	ticket_node_t *newNode;
	schedule_t sch;
	play_t     play;

	long id_seed;

	int count=0;
	int recCount = 0;

	List_Init(seat_head, seat_node_t);
	count=Seat_Srv_FetchValidByRoomID(seat_head,studio_id);
	if(count==0){
		printf("not seat information,can not create tickets.\n");
		return 0;
	}

	//载入演出计划及剧目
	Schedule_Perst_SelectByID(schedule_id, &sch);
	Play_Perst_SelectByID(sch.play_id, &play);

	List_Init(list,ticket_node_t);

    seat_node_t *pos;
    id_seed=EntKey_Srv_CompNewKeys("Ticket",count);
    pos=seat_head->next;
	while(pos!=seat_head){
			data.seat_id=pos->data.id;
			data.schedule_id=schedule_id;
			data.status= TICKET_AVL;	//表示待售
			data.id=id_seed++;
			data.price=play.price;		//默认统一票价
			newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
			if (!newNode) {
				printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memmory!!!\n");
				break;
			}
			recCount++;
			newNode->data = data;
			List_AddTail(list, newNode);
		pos=pos->next;
	}
	Ticket_Perst_Insert(list);
	return recCount;
}

int Ticket_Srv_DeleteBatch(int schedule_id) {
	return Ticket_Perst_Delete(schedule_id);
}

int Ticket_Srv_Modify(const ticket_t * data){
	return Ticket_Perst_Update(data);
}

int Ticket_Srv_FetchByID(int ID, ticket_t *buf) {
	return Ticket_Perst_SelectByID(ID, buf);
}


//根据座位ID在list中找对应票
inline ticket_node_t * Ticket_Srv_FindBySeatID(ticket_list_t list, int seat_id){
	ticket_node_t *p;
	List_ForEach(list, p){
		if(p->data.seat_id==seat_id)
			return p;
	}
	return NULL;
}


//根据计划ID提取所有演出票
int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id) {

	int count=0;

	//清除原始数据
	List_Free(list, ticket_node_t);

	//提取演出票
	ticket_list_t tickList;
	List_Init(tickList, ticket_node_t);

	if(Ticket_Perst_SelectBySchID(tickList, schedule_id)<=0)	{
		List_Destroy(tickList, ticket_node_t);
		return 0;
	}

	schedule_t sch;
	Schedule_Srv_FetchByID(schedule_id, &sch);

	//对演出票按座位号排序
	seat_list_t seatList;
	seat_node_t *pSeat;
	List_Init(seatList, seat_node_t);
	Seat_Srv_FetchValidByRoomID(seatList, sch.studio_id );


	ticket_node_t *pTick;
	List_ForEach(seatList, pSeat){
		pTick=Ticket_Srv_FindBySeatID(tickList, pSeat->data.id);
		if(pTick){
			List_DelNode(pTick);
			List_AddTail(list, pTick);
			count++;
		}
	}

	List_Destroy(seatList, seat_node_t);
	List_Destroy(tickList, ticket_node_t);

	return count;
}

//根据演出计划ID，统计上座率及票房，返回票房输入
int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount, int *totalCount){
	//根据计划ID提取所有演出票
	int value=0;
	ticket_list_t list, p;
	List_Init(list, ticket_node_t);

	*soldCount=0;
	*totalCount=Ticket_Srv_FetchBySchID(list, schedule_id);
	List_ForEach(list, p){
		if(p->data.status==TICKET_SOLD){
			(*soldCount)++	;
			value+=p->data.price;
		}
	}

	List_Destroy(list, ticket_node_t);
	return value;
}


