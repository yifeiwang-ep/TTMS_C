#include "../Service/Play.h"
#include "../Common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

static const char PLAY_DATA_FILE[] = "Play.dat";//保存剧目信息
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat";//删除或更新时，暂时保存剧目信息

/*
 * Function:    Play_Perst_Insert
 * Function ID:    TTMS_SCU_Play_Perst_Insert
 * Description: 在剧目信息文件末尾写入一条剧目信息
 * Input:       待加入文件的剧目信息数据
 * Output:      打开文件失败的信息
 * Return:      写入文件的记录数
 */

//添加新剧目信息函数
int Play_Perst_Insert(const play_t *data) {
    FILE *fp;
    fp = fopen(PLAY_DATA_FILE, "ab");               /*追加打开一个二进制文件*/
    int rtn = 0;                             //记录数字
        if (NULL == fp) {
            printf("Cannot open file %s!\n", PLAY_DATA_FILE);
            return 0;
        }
        rtn = fwrite(data,sizeof(play_t),1,fp);            /*将待加入文件的剧目信息数据写入文件*/
        fclose(fp);
    return rtn;                                            /*return返回写入文件的记录数*/
}

/*
 * Function:    Play_Perst_Update
 * Function ID:    TTMS_SCU_Play_Perst_Mod
 * Description: 按照剧目ID号更新文件中的剧目信息
 * Input:       待在文件中更新的剧目信息数据
 * Output:      打开文件失败的信息
 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
 */

//按照ID更新文件中的剧目信息
int Play_Perst_Update(const play_t *data) {
    FILE *fp;
    fp = fopen(PLAY_DATA_FILE,"rb+");
    if(NULL == fp){
        printf("Cannot open file %s!\n",PLAY_DATA_FILE);
        return 0;
    }
    play_t buf;
    int found = 0;
    while(!feof(fp))    //判断文本指针是否处于文件结束部分
    {
        if(fread(&buf,sizeof(play_t),1,fp)){
            if(buf.id == data->id){
                fseek(fp,-sizeof(play_t),SEEK_CUR);
                fwrite(data,sizeof(play_t),1,fp);
                found = 1;
                break;
            }

        }
    }
    fclose(fp);

   return found;
}

/*
 * Function:    Play_Perst_DeleteByID
 * Function ID:    TTMS_SCU_Play_Perst_DelByID
 * Description: 按照剧目ID号删除剧目的信息
 * Input:       待删除的剧目ID号
 * Output:      打开文件失败的信息
 * Return:      0表示删除失败，1表示删除成功
 */

 int Play_Perst_DeleteByID(int ID) {
 if(rename(PLAY_DATA_FILE, PLAY_DATA_TEMP_FILE)<0){
            printf("Cannot open file %s!\n", PLAY_DATA_FILE);
            return 0;                                                   ;
        
 }
    FILE *fp1;
        fp1 = fopen(PLAY_DATA_FILE, "rb");
        if (fp1 == NULL ){
                    printf("Cannot open file %s!\n", PLAY_DATA_FILE);
                    return 0;       
        }
     FILE *fp2;
        fp2 = fopen(PLAY_DATA_TEMP_FILE, "wb");
            if (fp2 == NULL) {
                printf("Cannot open file %s!\n", PLAY_DATA_TEMP_FILE);
                        return 0;
            }
               play_t buf;
                int found = 0;
                while (!feof(fp1)) {
                    if (fread(&buf, sizeof(play_t), 1, fp1)) {
                        if (ID == buf.id) {
                                found = 1;
                                continue;
                                        
                        }
             fwrite(&buf, sizeof(play_t), 1, fp2);
                                
                    }
                        
                }
                fclose(fp1);
                fclose(fp2);
             remove(PLAY_DATA_TEMP_FILE);   //删除临时文件 
             return found;
}

/*
 * Function:    Play_Perst_SelectByID
 * Function ID:    TTMS_SCU_Play_Perst_SelByID
 * Description: 按照剧目ID号查找剧目的信息
 * Input:       待查找的剧目ID号，保存查找结果的内存的地址
 * Output:      无
 * Return:      0表示未找到，1表示找到了
 */

int Play_Perst_SelectByID(int ID, play_t *buf) {
    FILE *fp;
    fp = fopen(PLAY_DATA_FILE,"rb");
    if(NULL == fp){
        return 0;
    }
        play_t data;
        int found= 0;
        while(!(feof)){
            if(fread(&data,sizeof(play_t),1,fp)){
                if(ID == data.id){
                    *buf = data;
                    return found= 1;
                    break;
                }
            }
        }
    fclose(fp);
    return found;
    }
/*
 * Function:    Play_Perst_SelectAll
 * Function ID:    TTMS_SCU_Play_Perst_SelAll
 * Description: 将所有剧目信息建立成一条链表
 * Input:       list剧目信息链表的头指针
 * Output:      提示建立链表时，申请空间失败
 * Return:      返回查找到的记录数目
 */

int Play_Perst_SelectAll(play_list_t list) {
    int recCount = 0;
    play_node_t *newNode;
    play_t data;
    assert(list != NULL);   //链表建立不为空
    List_Free(list,play_node_t);              
    FILE *fp;
    fp = fopen(PLAY_DATA_FILE,"rb");
    List_Init(newNode,play_node_t);
    if(fp == NULL)
        return 0;
    while(!feof(fp)){
        if(fread(&data,sizeof(play_t),1,fp)){
            newNode->data = data;
            List_AddTail(list,newNode);
            recCount++;
        }
    }
    fclose(fp);
    return recCount;
}


/*
 * Function:    Play_Perst_SelectByName
 * Function ID:    TTMS_SCU_Play_Perst_SelByName
 * Description: 按照剧目名称查找剧目的信息
 * Input:       list为查找到的剧目信息链表，condt为模糊查询的关键字
 * Output:      提示建立链表时，申请空间失败
 * Return:      返回查找到的记录数目
 */

int Play_Perst_SelectByName(play_list_t list, char condt[]) {
        play_node_t *n;
        play_t data;
        int recCount = 0;
        List_Free(list, play_node_t);
        FILE *fp = fopen(PLAY_DATA_FILE, "rb");
        if (fp == NULL)
                  return 0;
        while (!feof(fp)) {
        if (fread(&data, sizeof(play_t), 1, fp)) {
             n = (play_node_t*) malloc(sizeof(play_node_t));  //动态分配内存
            }


             
            if(memcmp((void*)condt,(void*) data.name,strlen(condt))==0){
                                n->data = data;
                                List_AddTail(list, n);
                                recCount++;              
            }
                    
        }
        fclose(fp);
        return recCount;
}

