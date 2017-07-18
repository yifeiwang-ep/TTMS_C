/*
 *  Seat_UI.h
 *
 *  Created on: 2015年5月23日
 *  Author: lc
 */

#ifndef SEAT_UI_H_
#define SEAT_UI_H_
#include "../Common/List.h"
#include "../Service/Seat.h"
int Seat_UI_MgtEntry(int roomID);


//根据状态返回对应表示状态符号
inline char Seat_UI_Status2Char(seat_status_t status);

//根据状态符号返回桌位状态
inline seat_status_t Seat_UI_Char2Status(char statusChar);


int Seat_UI_Add(seat_list_t list, int roomID, int rowsCount,int colsCount);

int Seat_UI_Modify(seat_list_t list, int row, int column);

int Seat_UI_Delete(seat_list_t list, int rowsCount, int colsCount);



#endif /* SEAT_UI_H_ */
