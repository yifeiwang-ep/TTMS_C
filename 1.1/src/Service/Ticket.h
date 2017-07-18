#ifndef TICKET_H_
#define TICKET_H_

typedef enum{
	TICKET_AVL=0,		//待售
	TICKET_SOLD=1,		//已售
	TICKET_RESV=9		//预留
}ticket_status_t;

typedef struct {
	int id;
	int schedule_id;
	int seat_id;
	int price;
	ticket_status_t status;
} ticket_t;

//双向链表
typedef struct ticket_node {
	ticket_t data;
	struct ticket_node *next, *prev;
} ticket_node_t, *ticket_list_t;

int Ticket_Srv_AddBatch(int schedule_id, int studio_id);

int Ticket_Srv_DeleteBatch(int schedule_id);

int Ticket_Srv_Modify(const ticket_t * data);

int Ticket_Srv_FetchByID(int ID, ticket_t *buf) ;

//根据计划ID提取所有演出票
int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id);

//根据演出计划ID，统计上座率及票房，返回票房数收入
int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount, int *totalCount);

//根据座位ID在list中找对应票
inline ticket_node_t * Ticket_Srv_FindBySeatID(ticket_list_t list, int seat_id);


#endif //TICKET_H_
