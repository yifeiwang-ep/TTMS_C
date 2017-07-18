#ifndef TICKET_UI_H_
#define TICKET_UI_H_
#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Schedule.h"

static const int TICKET_PAGE_SIZE=8;

int UpdateTicket(int id);

int QueryTicket(int id);

void ListTickets(void);

//状态转换为字符
inline char Ticket_UI_Status2Char(ticket_status_t status);

//根据票ID打印票
void Ticket_UI_Print(int ID);

//根据计划ID显示所有票
void Ticket_UI_ListBySch(const schedule_t *sch,	ticket_list_t tickList, seat_list_t seatList);

#endif /* TICKET_UI_H_ */
