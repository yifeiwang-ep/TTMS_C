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
	
}

inline int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
	
	return 0;

}



//根据剧目ID显示演出计划
void Sale_UI_ShowScheduler(int playID) {
	

}

void Sale_UI_MgtEntry() {
	
}

//退票
void Sale_UI_ReturnTicket(){
	
}
