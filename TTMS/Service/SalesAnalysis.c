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
#include "../Persistence/SalesAnalysis_Persist.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/list.h"

//计算员工usrID在给定时间区间的销售额，返回销售额
inline int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate){
	int amount=0;
	sale_list_t saleList;
	sale_list_t pSale;
	List_Init(saleList,sale_node_t);//初始化链表
	Sale_Perst_SelectByUsrID(saleList,usrID,stDate,endDate); //调用销售信息，构建链表
	List_ForEach(saleList,pSale){	//遍历链表 
		amount+=pSale->data.value;	//累加售票额 
	} 
	List_Destroy(saleList,sale_node_t);
	return amount;
}


//结合剧目Play.dat,统计销售数据，构建销售分析salesanalysis_list_t list链表，返回list链表长度
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list) {
	int count=0;
	assert(NULL!=list);
	play_list_t playList;
	play_list_t pos;
	salesanalysis_node_t *newNode;
	int sold;	//已售票数 
	int total;	//总票数 
	List_Free(list,salesanalysis_node_t);	//释放所有数据结点 
	List_Init(playList,play_node_t);	//初始化 
	Play_Srv_FetchAll(playList);	//载入剧目信息，构建链表
	List_ForEach(playList,pos)
	{
		printf("play_id:%s",pos->data.name);
		newNode=(salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));
		if(!newNode)
		{		
			break;
		}
			
		newNode->data.play_id=pos->data.id;	//编号 
		strcpy(newNode->data.name,pos->data.name);	//名称 
		strcpy(newNode->data.area,pos->data.area);	//区域 
		newNode->data.duration=pos->data.duration;	//时长 
		newNode->data.sales=Schedule_Srv_StatRevByPlay(pos->data.id,&sold,&total);//销售数量
		newNode->data.totaltickets=sold;//票房 
		newNode->data.price=pos->data.price;	//票价 
		newNode->data.start_date=pos->data.start_date;	//上映日期 
		newNode->data.end_date=pos->data.end_date;	//下映日期 
		
		List_AddTail(list,newNode);	//将newNode尾插到list中 
		count++;
	}
	List_Destroy(playList,play_node_t);
	return count;

}


//对剧院电影票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list){
	salesanalysis_node_t *p, *listLeft;
	assert(list!=NULL);
	if(List_IsEmpty(list))
		return ;
	list->prev->next = NULL;	//将next指针构成的循环链表从最后一个结点断开
	listLeft = list->next;	//listLeft指向第一个数据节点
	list->next = list->prev = list;	//将list链表置为空
	while (listLeft != NULL ) {
		p = list;	//取出第一个结点
		listLeft = listLeft->next;	
		
		//将结点p加入到已排序的链表list  
		salesanalysis_node_t *node;
		assert(list!=NULL && p!=NULL);
		if(List_IsEmpty(list))	{
			List_AddTail(list, p);
		}	
		else{	//寻找插入位置
			node=list->next;
			while(node!=list && (node->data.sales<p->data.sales ||(node->data.sales==p->data.sales && node->data.sales<p->data.sales))){
				node=node->next;
			}
			List_InsertBefore(node, p);//将结点node加入到p之前
		}
	}

}
