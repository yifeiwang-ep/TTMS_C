#include "Sale_Persist.h"
#include "../Common/List.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

//将订单信息插入到文件中
int Sale_Perst_Insert(const sale_t *data) {
	assert(NULL!=data);
	FILE *fp = fopen(SALE_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(sale_t), 1, fp);

	fclose(fp);
	return rtn;
}

//将订单信息删除
int Sale_Perst_DeleteByID(int saleID) {
	if(rename(SALE_DATA_FILE, SALE_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SALE_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SALE_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", SALE_DATA_TEMP_FILE);
		return 0;
	}


	sale_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(sale_t), 1, fpSour)) {
			if (saleID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(sale_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SALE_DATA_TEMP_FILE);
	return found;
}

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate,
		user_date_t endDate) {
	sale_node_t *p=list->next;
	int found = 0;
	while (p != NULL)
	{
		if(p->data.user_id==usrID && stDate.year<=p->data.date.year && stDate.month<=p->data.date.month && stDate.day<=p->data.date.day && endDate.year>=p->data.date.year && endDate.month>=p->data.date.month && endDate.day>=p->data.date.day )
		{
			found=1;
			break;
		}
		p=p->next;
	}
	return found;
	
}


//根据给定时间区间内的销售记录
int Sale_Perst_SelectByDate(sale_list_t list, user_date_t stDate,
		user_date_t endDate) {
	sale_node_t *p=list->next;
	int found = 0;
	while (p != NULL)
	{
		if(stDate.year<=p->data.date.year && stDate.month<=p->data.date.month && stDate.day<=p->data.date.day && endDate.year>=p->data.date.year && endDate.month>=p->data.date.month && endDate.day>=p->data.date.day )
		{
			found=1;
			break;
		}
		p=p->next;
	}
	return found;
	
}

/*

//queryUid = null,query all the uid Sale information return the all uid Sale information number
//queryUid =  uid, query the uid Sale information return the uid Sale  number
 *
int  Sale_Infor_By_Uid(char * queryUid, Sale_list_t head)
{
       // 请补充完整
       return 1;
}

int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head)
{
// 请补充完整
       return 1;
}

//根据票的id获得票的基本信息 
int Select_Price_By_Playid(int id, ticket_t *buf)
{
// 请补充完整
       return 1;
}
*/

