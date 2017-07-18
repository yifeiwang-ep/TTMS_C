/*
 *salesanalysis.h
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */
#ifndef SALESANALYSIS_H_
#define SALESANALYSIS_H_
#include "../Common/Common.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"
typedef struct {
	int play_id; 	//剧目编号
	char name[31]; 	//剧目名称
	char area[9]; 	//剧目区域
	int duration; 	//以分钟为单位
	long totaltickets; //电影票房
	long sales; 	//剧目票销售数量
	int price; 		//剧目票价
	user_date_t start_date; 	//剧目上映日期
	user_date_t end_date; 	//剧目下映日期
} salesanalysis_t;

//双向链表
typedef struct salesanalysis_node {
	salesanalysis_t data;
	struct salesanalysis_node *next, *prev;
} salesanalysis_node_t, *salesanalysis_list_t;



//计算员工usrID在给定时间区间的销售额
inline int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate);

//统计销售数据
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list);

//根据票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list);



inline int Salesanalysis_Srv_Insert(const salesanalysis_t *data);

inline int SalesAnalysis_Srv_FetchAll(salesanalysis_list_t list);

int SalesAnalysis_Srv_Analysis(play_list_t  plist, sale_list_t salist,salesanalysis_list_t slist );

void SalesAnalysis_Srv_Sort(salesanalysis_list_t slist,int sanalysisrec);

long SalesAnalysis_Srv_CountTicketByID(sale_list_t list,int playID) ;


#endif //SALESANALYSIS_H_
