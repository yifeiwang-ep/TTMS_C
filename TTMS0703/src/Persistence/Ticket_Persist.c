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

int Ticket_Perst_Insert(ticket_list_t list){

	FILE *fp = fopen(TICKET_DATA_FILE,"ab");
	ticket_node_t *p;
	ticket_t data;
	int rtn = 0;
	if(fp == NULL)
	{
		printf("文件打开失败!\n");
		return 0;
	}
	List_ForEach(list,p)
	{
		data=p->data;
		fwrite(&data,sizeof(ticket_t),1,fp);
		rtn++;
	}
	fclose(fp);
	
	return rtn;
}
int Ticket_Perst_Delete(int schedule_id){
	if(rename(TICKET_DATA_FILE,TICKET_DATA_TEMP_FILE)<0){
		printf("打开文件失败!\n");
		return 0;
	}
	FILE *fpSour,*fpTarg;
	fpSour = fopen(TICKET_DATA_TEMP_FILE,"rb");
	if(fpSour == NULL){
		printf("打开文件失败!\n");
		return 0;
	}
	fpTarg = fopen(TICKET_DATA_FILE,"wb");
	if(fpTarg == NULL){
	        printf("文件打开失败!\n");
	        return 0;
	 }
	 
	 
	ticket_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(ticket_t), 1, fpSour)) {
			if (schedule_id == buf.schedule_id) {
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

int Ticket_Perst_Update(const ticket_t * data) {
	assert(NULL !=data);
	
	FILE  *fp = fopen(TICKET_DATA_FILE,"rb+");
	if(fp == NULL)
	{
		printf("文件打开失败！\n");
		return 0;
	}
	ticket_t buf;
	int found = 0;
	
	while(!feof(fp)) {
		if(fread(&buf,sizeof(ticket_t),1,fp)){
			if(buf.id == data->id){
				fseek(fp,-sizeof(ticket_t),SEEK_CUR);
				fwrite(data,sizeof(ticket_t),1,fp);
				found=1;
			 }
		}
	}
	fclose(fp);
	
       return found; 
}


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
						"内存已满!!!!\n不能存储更多数据!!!\n");
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


int Ticket_Perst_SelectBySchID(ticket_list_t list, int schedule_id) {
	
       ticket_node_t *newNode;
	ticket_t data;
	int recCount = 0;

	assert(NULL!=list);
	
	List_Free(list,ticket_node_t);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}
	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)) {
			newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
			if (!newNode) {
				printf(
						"内存已满!!!!\n不能存储更多数据!!!\n");
				break;
			}
			if(data.schedule_id == schedule_id){
			 newNode->data = data;
			 List_AddTail(list, newNode);
			 recCount++;
			}
		}
	}
	fclose(fp);
	return recCount;
}
int TICKET_SOLD_SeleBySchedule(int schedule_id)
{
	int rtn=0;
	ticket_t data;
	FILE *fp=fopen(TICKET_DATA_FILE,"rb");
	if(fp==NULL)
	{
		printf("文件打开失败!\n");
		return 0;
	}
	while (!feof(fp)) {
		if (fread(&data, sizeof(ticket_t), 1, fp)){
			if(data.status==TICKET_SOLD && data.schedule_id==schedule_id)
			{
				rtn++;
			}
			else
			{
				continue;
			}
		}
	}
	
return rtn;
}			
//根据票主键列表载入票
/*int Ticket_Perst_SelectByKeyList(ticket_list_t list, entkey_list_t keyList) {
	
	assert(NULL !=list);
	assert(NULL != keyList);
	
       return 1;
}*/

