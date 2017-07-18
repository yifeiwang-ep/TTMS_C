#include "Schedule_Persist.h" 
#include "../Service/Schedule.h" 
#include "../Common/list.h" 
#include "../Service/Ticket.h" 
#include "../UI/Ticket_UI.h" 
#include <stdlib.h> 
#include <stdio.h> 
#include<unistd.h> 
#include <assert.h> 
 
 
static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";//保存演出计划信息 
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat"; //删除或更新时，暂时保存演出计划 
/* 
 * Function:    Schedule_Perst_Insert 
 * Function ID:    TTMS_SCU_Schedule_Perst_Insert 
 * Description: 在演出计划信息文件末尾写入一条演出计划信息 
 * Input:       待加入文件的演出计划信息数据 
 * Output:      打开文件失败的信息 
 * Return:      写入文件的记录数 
 */ 
 
 
 
int Schedule_Perst_Insert(const schedule_t *data) 
{ 
    FILE *fp; 
    fp = fopen(SCHEDULE_DATA_FILE,"ab"); 
    if(fp == NULL){ 
        printf("cannot open file %s!\n",SCHEDULE_DATA_FILE); 
        return 0; 
    } 
    fwrite(data,sizeof(schedule_t),1,fp); 
    fclose(fp); 
    return 1; 
} 
 
 
 
/* 
 * Function:    Schedule_Perst_Update 
 * Function ID:    TTMS_SCU_Schedule_Perst_Mod 
 * Description: 按照演出计划ID号更新文件中的演出计划信息 
 * Input:       待在文件中更新的演出计划信息数据 
 * Output:      打开文件失败的信息 
 * Return:      更新的演出计划信息数，0表示未找到，1表示找到并更新 
 */ 
 
 
int Schedule_Perst_Update(const schedule_t *data){ 
    assert(data != NULL); 
    int found = 0; 
    FILE *fp; 
    fp = fopen(SCHEDULE_DATA_FILE,"rb+"); 
    if(fp == NULL){ 
        printf("cannot open file %s!\n",SCHEDULE_DATA_FILE); 
        return 0; 
    } 
    schedule_t buf; 
    while(!feof(fp)){ 
           if(fread(&buf,sizeof(schedule_t),1,fp)){ 
            if(buf.id == data->id){ 
                fseek(fp,-sizeof(schedule_t),SEEK_CUR); 
                fwrite(data,sizeof(schedule_t),1,fp); 
                found = 1; 
                break; 
            } 
        } 
    } 
    fclose(fp); 
    return found; 
} 
 
 
 
/* 
 * Function:    Schedule_Perst_DeleteByID 
 * Function ID:    TTMS_SCU_Schedule_Perst_DelByID 
 * Description: 按照演出计划ID删除演出计划信息 
 * Input:       待删除的演出计划ID号 
 * Output:      打开文件失败的信息 
 * Return:      0表示删除失败，1表示删除成功 
 */ 
int Schedule_Perst_DeleteByID(int ID){ 
    if(rename(SCHEDULE_DATA_FILE,SCHEDULE_DATA_TEMP_FILE) < 0){ 
        printf("cannot open file %s!\n",SCHEDULE_DATA_FILE); 
        return 0; 
    } 
    FILE *fp1; 
    fp1 = fopen(SCHEDULE_DATA_FILE,"rb"); 
    if(fp1 == NULL){ 
        printf("Cannot open file %s!\n",SCHEDULE_DATA_FILE); 
        return 0; 
    } 
    FILE *fp2; 
    fp2 = fopen(SCHEDULE_DATA_TEMP_FILE,"wb"); 
    if(fp2 == NULL){ 
        printf("cannot open file %s!\n",SCHEDULE_DATA_TEMP_FILE); 
    } 
    schedule_t buf; 
    int found = 0; 
    while(!feof(fp1)){ 
         if(fread(&buf,sizeof(schedule_t),1,fp1)){ 
            if(ID == buf.id){ 
                found = 1; 
                continue; 
            } 
            fwrite(&buf,sizeof(schedule_t),1,fp2); 
        } 
    } 
    fclose(fp1); 
    fclose(fp2); 
 
    remove(SCHEDULE_DATA_TEMP_FILE); 
    return found; 
} 
 
 
 
 
 
/* 
 * Function:    Schedule_Perst_SelectByID 
 * Function ID:    TTMS_SCU_Schedule_Perst_SelByID 
 * Description: 按照演出计划ID查询演出计划的信息 
 * Input:       待查找的演出计划ID号，保存查找结果的内存的地址 
 * Output:      无 
 * Return:      0表示未找到，1表示找到了 
 */ 
 
int Schedule_Perst_SelectByID(int ID, schedule_t *buf){ 
    int found = 0; 
 
    FILE *fp = fopen(SCHEDULE_DATA_FILE,"rb"); 
    if(fp == NULL) 
    { 
        printf("cannot open file %s!\n",SCHEDULE_DATA_FILE); 
        return 0; 
    } 
 
    schedule_t data; 
    while(!feof(fp)){ 
        if(fread(&data,sizeof(schedule_t),1,fp)){ 
            if(ID == data.id){ 
                *buf = data; 
                found = 1; 
                break; 
            } 
        } 
    } 
    fclose(fp); 
   return found; 
} 
 
 
/* 
 * Function:    Schedule_Perst_SelectAll 
 * Function ID:    TTMS_SCU_Schedule_Perst_SelAll 
 * Description: 将所有演出计划信息建立成一条链表 
 * Input:       list为演出计划信息链表的头指针 
 * Output:      提示建立链表时，申请空间失败 
 * Return:      返回查找到的记录数目 
 */ 
 
int Schedule_Perst_SelectAll(schedule_list_t list){ 
    int recCount = 0; 
    FILE *fp; 
    fp = fopen(SCHEDULE_DATA_FILE,"rb"); 
    if(fp == NULL){ 
        return 0; 
    } 
    schedule_node_t *newNode; 
    schedule_t data; 
    while(!feof(fp)){ 
        if(fread(&data,sizeof(schedule_t),1,fp)){ 
            newNode = (schedule_node_t*) malloc (sizeof(schedule_node_t)); 
            if(!newNode){ 
                printf("cannot load data into memory!\n"); 
                break; 
            } 
        newNode->data = data; 
            List_AddTail(list,newNode); 
            recCount++; 
        } 
    } 
    fclose(fp); 
    return recCount; 
} 
 
 
 
 
/* 
 * Function:    Schedule_Perst_SelectByPlay 
 * Function ID:    TTMS_SCU_Schedule_Perst_SelByPlay 
 * Description: 将同意剧目的演出计划信息搜索出来，建立一条链表 
 * Input:       list为满足条件的演出计划信息链表的头指针，剧目的ID号 
 * Output:      提示建立链表时，申请空间失败 
 * Return:      返回查找到的记录数目 
 */ 
 
 
 
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id){ 
    int recCount = 0; 
    FILE *fp = fopen(SCHEDULE_DATA_FILE,"rb"); 
    if(fp == NULL){ 
        printf("cannot open file %s!\n",SCHEDULE_DATA_FILE); 
        return 0; 
    } 
    schedule_t data; 
    schedule_node_t *newNode; 
    while(!feof(fp)){ 
        if(fread(&data,sizeof(schedule_t),1,fp)){ 
            if(play_id == data.play_id){ 
                newNode=(schedule_node_t*)malloc(sizeof(schedule_node_t)); 
                newNode->data = data; 
                List_AddTail(list,newNode); 
                recCount++; 
            } 
        } 
    } 
    fclose(fp); 
}
