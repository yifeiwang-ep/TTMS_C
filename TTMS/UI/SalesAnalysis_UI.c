/*
 * SalesAnalysis_UI.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
//#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
void SalesAnalysis_UI_BoxOffice() {

}

//显示售票员在给定日期区间的售票情况
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){

}

//销售分析入口函数，显示菜单，菜单包含"降序显示截止目前剧院电影票房排行榜"，“显示或查询当日售票员售票情况”，
//“查询给定日期区间某售票员售票情况”
void SalesAanalysis_UI_MgtEntry() {

}



