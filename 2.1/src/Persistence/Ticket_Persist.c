#include "Ticket_Persist.h"
//#include "../Persistence/Common_Persist.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>

static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char TICKET_DATA_TEMP_FILE[]="TicketTemp.dat";

//在文件中批量插入新票
int Ticket_Perst_Insert(ticket_list_t list){
	assert(NULL!=list);

	FILE *fp = fopen(TICKET_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", TICKET_DATA_FILE);
		return 0;
	}
	ticket_list_t curPos;
	List_ForEach(list, curPos)
	{
		rtn = fwrite(&(curPos->data), sizeof(ticket_t), 1, fp);
	}
	fclose(fp);
	return rtn;
}

//根据演出计划ID删除票
int Ticket_Perst_Delete(int schedule_id){

	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。

	//对原始数据文件重命名
	if(rename(TICKET_DATA_FILE, TICKET_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(TICKET_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(TICKET_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", TICKET_DATA_TEMP_FILE);
		return 0;
	}


	ticket_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(ticket_t), 1, fpSour)) {
			if (schedule_id == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(ticket_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(TICKET_DATA_TEMP_FILE);
	return found;
}

//在文件中修改票信息
int Ticket_Perst_Update(const ticket_t * data) {
	assert(NULL!=data);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	ticket_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(ticket_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -sizeof(ticket_t), SEEK_CUR);
				fwrite(data, sizeof(ticket_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

//根据票ID从文件中载入票
int Ticket_Perst_SelectByID(int ID, ticket_t *buf) {
	assert(NULL!=buf);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	ticket_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)) {
			if (ID == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}

//从文件中载入所有票
int Ticket_Perst_SelectAll(ticket_list_t list) {
	ticket_node_t *newNode;
	ticket_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, ticket_node_t);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)) {
			newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}

//根据演出计划ID查找票
int Ticket_Perst_SelectBySchID(ticket_list_t list, int schedule_id) {
	ticket_node_t *newNode;
	ticket_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, ticket_node_t);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)) {
			if(data.schedule_id == schedule_id)			
			{
				newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
				if (!newNode) {
					printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
					break;
				}
				newNode->data = data;
				List_AddTail(list, newNode);
				recCount++;
			}		
		}
	}
	fclose(fp);
	return recCount;
}

//根据票主键列表载入票
/*int Ticket_Perst_SelectByKeyList(ticket_list_t list, entkey_list_t keyList) {
	assert(NULL!=list);
	ticket_node_t *p=list->next;
	int found = 0;

	while (p != NULL)
	{
			if(p->data.)
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}*/
