/*
 * SalesAnalysis_UI.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */
#include "SalesAnalysis_UI.h"
#include "../Common/ComFunction.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Common/list.h"
/*#include <conio.h>*/
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

extern account_t gl_CurUser;

static const int SALESANALYSIS_PAGE_SIZE = 5;

/*//销售分析模块入口函数,显示分析好的销售数据
void SalesAanalysis_UI_BoxOffice() {
	// 请补充完整
	
}


void SalesAanalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){
	// 请补充完整
}
*/
void SalesAanalysis_UI_MgtEntry(int flag) {
	// 请补充完整
	
	
	int i;
	char choice;
	
	schedule_list_t head;
	salesanalysis_node_t *p;
	salesanalysis_list_t list;
	
	Pagination_t paging;
	
	List_Init(head, schedule_node_t);
	List_Init(list,salesanalysis_node_t);
	
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
	
	paging.totalRecords = Schedule_Perst_SelectAll(head);
	//printf("%d",SalesAnalysis_Srv_FetchAll(list));
	SalesAnalysis_Srv_FetchAll(list);
	
	Paging_Locate_FirstPage(list, paging);
	
	do {
		system("clear");
		//SalesAnalysis_Srv_FetchAll(list);
	
		//Paging_Locate_FirstPage(list, paging);
	
		system("clear");
		printf("\t\t=====================================================================================\n\n");
		printf(
				"\t\t***********************************销售数据分析*************************************\n\n");
		printf("\t%15s%15s%15s%15s%10s%17s%16s%8s%15s\n", "剧目ID", "剧目名称", "剧目地区",
				"剧目时长", "上座数","上映日期","下线日期","票价","票房收入");
		printf(
				"\t\t------------------------------------------------------------------------------------------\n");
		for (i = 0, p = (salesanalysis_node_t *) (paging.curPos);p!= head && i < paging.pageSize; i++){
		printf("\t\t%d%12s%13s%8d%8ld", p->data.play_id, p->data.name,p->data.area, p->data.duration,p->data.totaltickets);
		printf("\t%4d-%02d-%02d ", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
		printf(" %4d-%02d-%02d ",p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
		printf("%5d\t%5ld\n",p->data.price,p->data.sales);
		p=p->next;
		}
		
		printf("\t\t------- 总数:%2d ---------------------------------------------------- 页数 %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t***************************************************************************************\n");
		printf("\t\t[P]上一页　|   [N]下一页  |   [R]返回");
		
		printf("\n\t\t===================================================================================\n");
		printf("\t\t请选择:");

		choice=l_getc();

		switch (choice) {
		
				case 'p':
				case 'P':
					 system("clear");
	        if(1<Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,-1,salesanalysis_node_t);
            }
					break;
				case 'n':
				case 'N':
				system("clear");
            if(Pageing_TotalPages(paging)>Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,1,salesanalysis_node_t);
            }break;
				}
	} while (choice != 'r' && choice != 'R');
}



