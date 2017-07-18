#include "Sale_Persist.h" 
#include "../Common/list.h" 
#include "../Service/Sale.h" 
#include <stdio.h> 
#include<unistd.h> 
#include <stdlib.h> 
#include <string.h> 
 
 
static const char SALE_DATA_FILE[] = "Sale.dat"; 
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat"; 
 
 
//将售票信息写入文件 
int Sale_Perst_Insert(const sale_t *data) { 
    FILE *fp; 
    fp = fopen(SALE_DATA_FILE,"ab"); 
    if(fp == NULL){ 
        printf("cannot open file %s!\n",SALE_DATA_FILE); 
        return 0; 
    } 
    int rtn; 
    rtn = fwrite(&data,sizeof(sale_t),1,fp); 
    fclose(fp); 
    return rtn; 
} 
 
 
 
 
//从文件中删除售票信息 
int Sale_Perst_DeleteByID(int saleID) { 
    if(rename(SALE_DATA_FILE,SALE_DATA_TEMP_FILE) < 0){ 
        printf("cannot open file %s!\n",SALE_DATA_FILE); 
        return 0; 
    } 
    FILE *fp1,*fp2; 
    fp1 = fopen(SALE_DATA_FILE,"rb"); 
    if(fp1 == NULL){ 
        printf("cannot open file %s!\n",SALE_DATA_FILE); 
        return 0; 
    } 
    fp2 = fopen(SALE_DATA_TEMP_FILE,"wb"); 
    if(fp2 == NULL){ 
        printf("cannot open file %s!\n",SALE_DATA_TEMP_FILE); 
        return 0; 
    } 
    int found = 0; 
    sale_t data; 
    sale_t buf; 
    while(!feof(fp1)){ 
        if(fread(&buf,sizeof(sale_t),1,fp1)){ 
            if(saleID == buf.id){ 
                found = 1; 
                continue; 
            }             
            fwrite(&buf,sizeof(sale_t),1,fp2); 
        } 
    } 
    fclose(fp1); 
    fclose(fp2); 
    remove(SALE_DATA_TEMP_FILE);                            //删除临时文件 
    return found; 
} 
 
 
 
//根据用户ID载入给定时间区间内的销售记录 
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate, 
        user_date_t endDate) { 
            int recCount = 0; 
            FILE *fp; 
            fp = fopen(SALE_DATA_FILE,"rb"); 
            if(fp == NULL){ 
                printf("cannot open file %s!\n",SALE_DATA_FILE); 
                return 0; 
            } 
            sale_t data; 
            sale_node_t *p; 
            while(!feof(fp)){ 
                if(fread(&data,sizeof(sale_t),1,fp)){ 
                  if(usrID == data.user_id){ 
 
 
 
                    if(DateCmp(data.date,stDate) != -1 && DateCmp(endDate,data.date) != -1){ 
                        p = (sale_node_t*) malloc( sizeof(sale_node_t)); 
                        if(!p){ 
                            printf("cannot load more data into memory\n"); 
                            break; 
                        } 
                        p->data = data; 
                        List_AddTail(list,p); 
                        recCount++; 
                    } 
 
                } 
            } 
            return recCount; 
} 
 
 
 
//根据给定时间区间内的销售记录 
int Sale_Perst_SelectByDate(sale_list_t list, user_date_t stDate,user_date_t endDate) { 
            FILE *fp; 
            fp == fopen(SALE_DATA_FILE,"rb"); 
             if(fp == NULL){ 
                printf("cannot open file %s!\n",SALE_DATA_FILE); 
                return 0; 
            } 
            int recCount = 0; 
            sale_t data; 
            sale_node_t *p; 
            while(!feof(fp)){ 
                if(fread(&data,sizeof(sale_t),1,fp)){ 
 
 
 
 
                    if(DateCmp(data.date,stDate) != 0 && DateCmp(endDate,data.date) != -1){ 
                        p = (sale_node_t*) malloc (sizeof(sale_node_t)); 
                        if(!p){ 
                            printf("cannot load more data into memory\n"); 
                            break; 
                        } 
                        p->data = data; 
                        List_AddTail(list,p); 
                        recCount++; 
                    } 
                } 
            } 
} 
            return recCount; 
} 
 
/* 
 
//queryUid = null,query all the uid Sale information return the all uid Sale information number 
//queryUid =  uid, query the uid Sale information return the uid Sale  number 
 * 
int  Sale_Infor_By_Uid(char * queryUid, Sale_list_t head) 
{ 
 
    return 0; 
} 
 
int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head) 
{ 
 
     
    return 0; 
} 
 
//根据票的id获得票的基本信息  
int Select_Price_By_Playid(int id, ticket_t *buf) 
{ 
     
        return 0; 
} 
*/
