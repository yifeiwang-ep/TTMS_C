#ifndef SLAEINGPERSIST_H
#define SALEINGPERSIST_H

#include "../Service/Sale.h"
#include "../Common/common.h"

int Sale_Perst_Insert(const sale_t *data);
int Sale_Perst_DeleteByID(int saleID);


//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID,
		user_date_t stDate, user_date_t endDate);

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByDate(sale_list_t list,
		user_date_t stDate, user_date_t endDate);

/*
int Sale_Infor_By_Time(char queryTime[][30], sale_list_t head);

//根据票的id获得票的基本信息 这个函数可以在ticket里面调用，但是可能你那个文件名字不一样，所以重新写了一份，你那边可以直接调用api，这个函数主要是获得票票的价格,
int Select_Price_By_Playid(int id, ticket_t *buf);
*/
#endif
