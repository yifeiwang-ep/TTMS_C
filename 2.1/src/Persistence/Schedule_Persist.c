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

//向文件中插入新演出计划
int Schedule_Perst_Insert(const schedule_t *data)
{
	assert(NULL!=data);
	FILE *fp = fopen(SCHEDULE_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(schedule_t), 1, fp);

	fclose(fp);
	return rtn;
}

//在文件中更新演出计划
int Schedule_Perst_Update(const schedule_t *data){
	assert(NULL!=data);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	schedule_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(schedule_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -sizeof(schedule_t), SEEK_CUR);
				fwrite(data, sizeof(schedule_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

//根据ID删除在文件中删除演出计划
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

	remove(SCHEDULE_DATA_TEMP_FILE);
	return found;
}

//根据ID在文件中载入演出计划
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

//在文件中载入所有演出计划
int Schedule_Perst_SelectAll(schedule_list_t list){
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, schedule_node_t);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) { 
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
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

//根据剧目ID在文件中载入所有演出计划
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id){
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, schedule_node_t);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) { 
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			if(data.play_id == play_id)
			{
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
	}
	fclose(fp);
	return recCount;
}
