/*
 * Account_Persist.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include "Account_Persist.h"
#include "../Service/Account.h"
#include "../Common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include <string.h>

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";

 
//判断账号文件是否存在，返回1存在，返回0不存在 
int Account_Perst_CheckAccFile() { 
     if ( access(ACCOUNT_DATA_FILE,0)==0  ){ 
        return 1; 
    } 
    else 
        return 0; 
} 
 
 
 
//根据用户名载入账号,载入成功 return 1；否则 return 0 
int Account_Perst_SelByName(char usrName[], account_t *buf) { 
    int found = 0; 
    FILE *fp = fopen(ACCOUNT_DATA_FILE,"rb"); 
    if(fp == NULL){ 
        return 0; 
    }  
    account_t data; 
    while(!feof(fp)){ 
        if(fread(&data,sizeof(account_t),1,fp)){ 
            if(strcmp(usrName,data.username) == 0){ 
                *buf = data; 
                found =1; 
            } 
        } 
    } 
 
    fclose(fp); 
    return found; 
 
} 
 
 
 
//新账号写入账号文件中，返回实际写入的数据块数目 
int Account_Perst_Insert(const account_t *data) { 
    FILE *fp = fopen(ACCOUNT_DATA_FILE,"ab"); 
    if(fp == NULL){ 
        printf("cannot open file %s!\n",ACCOUNT_DATA_FILE); 
        return 0; 
    } 
    int rtn = 0; 
    rtn = fwrite(data,sizeof(account_t),1,fp); 
    fclose(fp); 
    return rtn; 
} 
 
 
//在账号文件中查找与参数账号匹配的账号，找到 return 1；否则 return 0；并进行覆盖重写 
int Account_Perst_Update(const account_t * data) { 
    FILE *fp = fopen(ACCOUNT_DATA_FILE,"rb+"); 
    if(fp == NULL){ 
        printf("cannot open file %s!\n",ACCOUNT_DATA_FILE); 
        return 0; 
    } 
    account_t buf;     //结构体 
    int found = 0; 
    while(!feof(fp)){ 
        if(fread(&buf,sizeof(account_t),1,fp)){ 
            if(buf.id == data->id) 
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
 
 
 
 
//在账号文件中删除与参数id匹配的账号，删除成功 return 1；否则 return 0； 
int Account_Perst_DeleteByID(int id) { 
    if(rename(ACCOUNT_DATA_FILE, ACCOUNT_DATA_TEMP_FILE)<0){ 
      printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE); 
      return 0;  
    } 
 
    FILE *fp1; 
    fp1= fopen(ACCOUNT_DATA_TEMP_FILE, "rb"); 
    if (fp1 == NULL){ 
        printf("Cannot open file %s!\n", ACCOUNT_DATA_FILE); 
        return 0;    
    } 
    FILE *fp2; 
    fp2 = fopen(ACCOUNT_DATA_FILE, "wb"); 
    if (fp2 == NULL) { 
        printf("Cannot open file %s!\n", ACCOUNT_DATA_TEMP_FILE); 
        return 0;    
    } 
    account_t buf; 
    int found = 0; 
    while (!feof(fp1)) { 
        if (fread(&buf, sizeof(account_t), 1, fp1)) { 
            if (id == buf.id) { 
              found = 1; 
              continue; 
            } 
    fwrite(&buf, sizeof(account_t), 1, fp2);  
        }   
    } 
    fclose(fp1); 
    fclose(fp2); 
    remove(ACCOUNT_DATA_TEMP_FILE);     //删除临时文件 
    return found; 
} 
 
 
 
//在账号文件中查找与参数id匹配的账号，并通过指针buf传出；匹配成功 return 1；否则 return 0； 
int Account_Perst_SelectByID(int id, account_t *buf) { 
 
    FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb"); 
    if (fp == NULL) { 
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
            }    
        } 
    } 
        fclose(fp); 
        return found; 
} 
 
 
 
 
//遍历读ACCOUNT_DATA_FILE文件，动态构建用户账号list链表,list 为链表头指针，返回list长度 
int Account_Perst_SelectAll(account_list_t list) { 
        int recCount = 0; 
 
        assert(list != NULL); 
        List_Free(list, account_node_t); 
 
        FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb"); 
        if (fp == NULL) { 
           return 0; 
      } 
        account_node_t *p; 
        account_t data; 
        while (!feof(fp)) { 
        if (fread(&data, sizeof(account_t), 1, fp)) { 
              p = (account_node_t*) malloc(sizeof(account_node_t)); 
             if (!p) { 
                printf("Cannot Load more Data into memory!!!\n"); 
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
 


