/*
 * Account_Persist.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include "Account_Persist.h"
#include "../Service/Account.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>
#include <string.h>

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";

//判断账号文件是否存在
int Account_Perst_CheckAccFile() {
        if ( access(ACCOUNT_DATA_FILE,0)==0 ){
       		return 1;
       	}else{
       		return 0;
       	}
}

//根据用户名载入账号
int Account_Perst_SelByName(char usrName[], account_t *buf) {
	FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	account_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(account_t), 1, fp)) {
			if (strcmp(usrName,data.username)==0) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

       return found;
}

int Account_Perst_Insert(const account_t *data) {
	FILE *fp = fopen(ACCOUNT_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(account_t), 1, fp);

	fclose(fp);
	return rtn;
}

int Account_Perst_Update(const account_t * data) {
	
	
	FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	account_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(account_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -sizeof(account_t), SEEK_CUR);
				fwrite(data, sizeof(account_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
 
}

int Account_Perst_DeleteByID(int id) {
	
	if(rename(ACCOUNT_DATA_FILE, ACCOUNT_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(ACCOUNT_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(ACCOUNT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", ACCOUNT_DATA_TEMP_FILE);
		return 0;
	}


	account_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(account_t), 1, fpSour)) {
			if (id == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(account_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(ACCOUNT_DATA_TEMP_FILE);
	return found;
	
}

int Account_Perst_SelectByID(int id, account_t *buf) {
	
	FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	account_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(account_t), 1, fp)) {
			if (id == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
	
}

int Account_Perst_SelectAll(account_list_t list) {
	account_node_t *p;
	account_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, account_node_t);

	FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(account_t), 1, fp)) {
			p = (account_node_t*) malloc(sizeof(account_node_t));
			if (!p) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			p->data = data;
			List_AddTail(list, p);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}

