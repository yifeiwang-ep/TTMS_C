/*
 * salesanalysisPersist.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include "../Persistence/EntityKey_Persist.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"
#include "../Common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//static const char PLAY_DATA_FILE[] = "play.dat";
static const char SALE_DATA_FILE[] = "sale.dat";
static const char SALESANALYSIS_DATA_FILE[] = "salesanalysis.dat";

//将一条salesanalysis记录（*data）写入salesanalysis.dat文件；成功return 1，否则return 0
int Salesanalysis_Perst_Insert(const salesanalysis_t *data) {

	return 1;

}

//遍历读salesanalysis.dat文件建立销售分析（salesanalysis）链表
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list) {

	return 1;

}

//遍历读Sale.dat文件建立list（sale_list_t） 链表，返回链表list长度
int Sale_Perst_SelectAll(sale_list_t list) {

	return 1;

}

