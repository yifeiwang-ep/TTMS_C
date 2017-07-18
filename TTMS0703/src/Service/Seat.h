/*
 * Seat.h
 *
 * Created on: 2015年4月27日
 * Updated on: 2015年5月23日
 * Author: lc
 */
#ifndef SEAT_H_
#define SEAT_H_

typedef enum{
	SEAT_NONE=0,			//空位
	SEAT_GOOD=1,			//有座位
	SEAT_BROKEN=9			//损坏的座位
}seat_status_t;

typedef struct {
	int id;					//座位id
	int roomID;				//所在演出厅id
	int row;           		//座位行号
    int column;        		//座位列号
    seat_status_t status;	//座位在该行的状态，0表示没有座位，1表示有座位。扩展2可表示座位坏了
} seat_t;


//双向链表
typedef struct seat_node {
	seat_t data;
	struct seat_node *next, *prev;
} seat_node_t, *seat_list_t;


//根据行、列数初始化演出厅的座位
int Seat_Srv_RoomInit(seat_list_t list, int roomID,int rowsCount,int colsCount);

//对座位链表list进行排序
void Seat_Srv_SortSeatList(seat_list_t list );

//将结点node加入到已排序链表list中
inline void Seat_Srv_AddToSoftedList(seat_list_t list , seat_node_t *node);

/*单个添加座位*/
inline int Seat_Srv_Add(const seat_t *data);

/*批量添加座位*/
inline int Seat_Srv_AddBatch(seat_list_t list);

inline int Seat_Srv_Modify(const seat_t *data);

inline int Seat_Srv_DeleteByID(int ID);

inline int Seat_Srv_DeleteAllByRoomID(int roomID);



inline int Seat_Srv_FetchByID(int ID, seat_t *buf);

int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID);



/*根据放映厅ID提取有效的座位*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID);


inline seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column);

inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int seatID);


#endif //SEAT_H_





