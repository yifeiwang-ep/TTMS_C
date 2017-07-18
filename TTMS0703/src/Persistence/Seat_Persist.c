/*
 *  Seat_Persist.c
 *
 *  Created on: 2015年5月23日
 *  Author: lc
 */

#include "Seat_Persist.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";

int Seat_Perst_Insert(const seat_t *data) {
	// 请补充完整
	assert(data != NULL);
	FILE *fp = fopen(SEAT_DATA_FILE,"ab");
	int  rtn = 0;
	if(fp == NULL)
	{
		printf("打开文件失败!\n");
		 return 0;
	}
	rtn = fwrite(data,sizeof(seat_t),1,fp);
	
	fclose(fp);
	return rtn;
}

int Seat_Perst_InsertBatch(seat_list_t list) {
	// 请补充完整
	FILE *fp = fopen(SEAT_DATA_FILE,"ab");
	seat_node_t *p;
	seat_t  data;
	int rtn = 0;
	if(fp == NULL)
	{
		printf("文件打开失败!\n");
			return 0;
	}
	List_ForEach(list,p)
	{
		data=p->data;
	       	fwrite(&data,sizeof(seat_t),1,fp);
	       	rtn++;
	}
	fclose(fp);
	         
	
       return rtn;
}
int Seat_Perst_Update(const seat_t *seatdata) {
	// 请补充完整
	assert(NULL !=seatdata);
	
	FILE  *fp = fopen(SEAT_DATA_FILE,"rb+");
	if(fp == NULL)
	{
		printf("文件打开失败！\n");
		return 0;
	}
	seat_t buf;
	int found = 0;
	
	while(!feof(fp)) {
		if(fread(&buf,sizeof(seat_t),1,fp)){
			if(buf.id == seatdata->id){
				fseek(fp,-sizeof(seat_t),SEEK_CUR);
				fwrite(seatdata,sizeof(seat_t),1,fp);
				found=1;
			 }
		}
	}
	fclose(fp);
	
       return found; 
}

int Seat_Perst_DeleteByID(int ID) {
	// 请补充完整
	if(rename(SEAT_DATA_FILE,SEAT_DATA_TEMP_FILE)<0){
		printf("打开文件失败!\n");
		return 0;
	}
	FILE *fpSour,*fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE,"rb");
	if(fpSour == NULL){
		printf("打开文件失败!\n");
		return 0;
	}
	fpTarg = fopen(SEAT_DATA_FILE,"wb");
	if(fpTarg == NULL){
	        printf("文件打开失败!\n");
	        return 0;
	 }
	 
	 
	seat_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) {
			if (ID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SEAT_DATA_TEMP_FILE);
	return found;
}
    


int Seat_Perst_DeleteAllByRoomID(int roomID) {
	// 请补充完整
	if(rename(SEAT_DATA_FILE,SEAT_DATA_TEMP_FILE)<0){
		printf("打开文件失败!\n");
		return 0;
	}
	FILE *fpSour,*fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE,"rb");
	if(fpSour == NULL){
		printf("打开文件失败!\n");
		return 0;
	}
	fpTarg = fopen(SEAT_DATA_FILE,"wb");
	if(fpTarg == NULL){
	        printf("文件打开失败!\n");
	        return 0;
	 }
	 
	 
	seat_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) {
			if (roomID == buf.roomID) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SEAT_DATA_TEMP_FILE);
	return found;
}

int Seat_Perst_SelectByID(int ID, seat_t *buf) {
	// 请补充完整
	assert(NULL!=buf);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	seat_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp)) {
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

int Seat_Perst_SelectAll(seat_list_t list) {
	// 请补充完整
	seat_node_t *newNode;
	seat_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, seat_node_t);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			newNode = (seat_node_t*) malloc(sizeof(seat_node_t));
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

int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID) {
	// 请补充完整
	seat_node_t *newNode;
	seat_t data;
	int recCount = 0;

	assert(NULL!=list);
	
	List_Free(list,seat_node_t);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}
	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			newNode = (seat_node_t *) malloc(sizeof(seat_node_t));
			if (!newNode) {
				printf("内存已满!!!!\n不能存储更多数据!!!\n");
				break;
			}
			if(data.roomID == roomID){
			 newNode->data = data;
			 List_AddTail(list, newNode);
			 recCount++;
			}
		}
	}
	fclose(fp);
	return recCount;
}
