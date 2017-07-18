#include "Schedule_Persist.h"
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../View/Ticket_UI.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>


static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat";

int Schedule_Perst_Insert(const schedule_t *data)
{
	assert(NULL!=data);
	FILE *fp;
	fp=fopen(SCHEDULE_DATA_FILE,"ab");
	if(fp==NULL){
		printf("Cannot open file %s!\n",SCHEDULE_DATA_FILE);
		return 0;
		}
		
	fwrite(data,sizeof(schedule_t),1,fp);
	fclose(fp);
       return 1;
}

int Schedule_Perst_Update(const schedule_t *data){
	assert(NULL!=data);
	FILE *fp=fopen(SCHEDULE_DATA_FILE,"rb+");
	if(fp==NULL){
		printf("Cannot open file %s!\n",SCHEDULE_DATA_FILE);
		return 0;
	}
	schedule_t buf;
	int found=0;
	while (!feof(fp)){
		if(fread(&buf,sizeof(schedule_t),1,fp)){
			if(buf.id==data->id){
				fseek(fp,-sizeof(schedule_t),SEEK_CUR);
				fwrite(data,sizeof(schedule_t),1,fp);
				found=1;
				break;
			}
		}
	}		
	fclose(fp);
	return found;
}

int Schedule_Perst_DeleteByID(int ID){
	if(rename(SCHEDULE_DATA_FILE, SCHEDULE_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SCHEDULE_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SCHEDULE_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", SCHEDULE_DATA_TEMP_FILE);
		return 0;
	}


	schedule_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(schedule_t), 1, fpSour)) {
			if (ID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SCHEDULE_DATA_TEMP_FILE);
	return found;
}

int Schedule_Perst_SelectByID(int ID, schedule_t *buf){
	assert(NULL!=buf);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	schedule_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
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

int Schedule_Perst_SelectAll(schedule_list_t list){
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, schedule_node_t);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
			if (!newNode) {
				printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
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

int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id){
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;
	
	List_Free(list,schedule_node_t);
	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	int found = 0;
	List_Free(list, schedule_node_t);
	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			
			
			if (play_id==data.play_id){
				newNode=(schedule_node_t*)malloc(sizeof(schedule_node_t));
				newNode->data=data;
				List_AddTail(list,newNode);
				recCount++;
				
			};

		}
	}
	fclose(fp);

	return recCount;
  
}
