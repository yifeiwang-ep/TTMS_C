/*
 * salesanalysis.c
 *
 *  Created on: 2015年6月12日
 *      Author: Administrator
 */
#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h"
#include "Sale.h"
#include "Ticket.h"
#include "../Persistence/Ticket_Persist.h"
#include "Play.h"
#include "Schedule.h"
#include <string.h>

#include "../Common/List.h"

//计算员工usrID在给定时间区间的销售额
/*inline int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate){
	// 请补充完整
       return 1;
}

//统计销售数据
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list) {

	// 请补充完整
       return 1;
}

//根据票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list){
	// 请补充完整
}



//实现销售数据分析，获取分析好的销售数据，写入销售分析（salesanalysis_list_t slist）链表中
int SalesAnalysis_Srv_Analysis(play_list_t plist, sale_list_t salist,
		salesanalysis_list_t slist) {
	// 请补充完整
       return 1;
}

//销售分析链表（slist）结点数据，按剧目票销售数量（sales）字段降序排序
*///sanalysisrec ：销售分析链表（slist）结点数量
/*void SalesAnalysis_Srv_Sort(salesanalysis_list_t slist, int sanalysisrec) {
	// 请补充完整
	
}*/

//根据剧目（play）的id号找到Sale.dat中匹配的记录,返回记录总数，即售票数
long SalesAnalysis_Srv_CountTicketByID(sale_list_t list, int playID) {
	// 请补充完整
	
       return 1;
}

/*inline int Salesanalysis_Srv_Insert(const salesanalysis_t *data) {
	// 请补充完整
       return 1;
}*/
inline int SalesAnalysis_Srv_FetchAll(salesanalysis_list_t list) {
	// 请补充完整
	int rtn=0;
	play_list_t plist;
	schedule_list_t mlist;
	
	play_node_t *p;
	schedule_node_t *q;
	salesanalysis_node_t *n;
	
	List_Free(list,salesanalysis_node_t);
	
	List_Init(plist,play_node_t);
	List_Init(mlist,schedule_node_t);
	
	Play_Perst_SelectAll(plist);
	Schedule_Perst_SelectAll(mlist);
	
	//p=plist->next;
	//q=mlist->next;
		List_ForEach(plist,p)
		{
			List_ForEach(mlist,q)
			{
				if(p->data.id==q->data.play_id)
				{
					//rtn++;
					//printf("%d\n",rtn);
					n=(salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));
					n->data.play_id=p->data.id;
					strcpy(n->data.name,p->data.name);
					//printf("%s",p->data.name);
					strcpy(n->data.area,p->data.area);
					n->data.totaltickets=TICKET_SOLD_SeleBySchedule(q->data.id);
					n->data.price=p->data.price;
					n->data.sales=(n->data.totaltickets)*(p->data.price);
					n->data.start_date.year=p->data.start_date.year;
					n->data.start_date.month=p->data.start_date.month;
					n->data.start_date.day=p->data.start_date.day;
					n->data.end_date.year=p->data.end_date.year;
					n->data.end_date.month=p->data.end_date.month;
					n->data.end_date.day=p->data.end_date.day;
					n->data.duration=p->data.duration;
					List_AddTail(list,n);
					
				}
			}
		}
       return rtn;
}


/*inline int Sale_Srv_FetchAll(sale_list_t list) {
	// 请补充完整
       return 1;
}*/

