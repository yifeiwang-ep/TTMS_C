/*
* File name:  Play.c
* File ID:	  TTMS_SSF_Play_Srv_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/

#include "Play.h"
#include "../Common/list.h"
#include "../Persistence/Play_Persist.h"
#include <string.h>

/*
 * Function:    Play_Srv_Add
 * Function ID:	TTMS_SCU_Play_Srv_Add
 * Description: 添加一条剧目信息
 * Input:       待添加的剧目信息数据
 * Output:      无
 * Return:      添加的记录数
 */
inline int Play_Srv_Add(const play_t *data) {
	return Play_Perst_Insert(data);
}

/*
 * Function:    Play_Srv_Modify
 * Function ID:	TTMS_SCU_Play_ Srv _Mod
 * Description: 更新一条剧目信息
 * Input:       待更新的剧目信息数据
 * Output:      无
 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
 */
inline int Play_Srv_Modify(const play_t *data) {
	return Play_Perst_Update(data);
}

/*
 * Function:    Play_Srv_DeleteByID
 * Function ID:	TTMS_SCU_Play_Srv_DelByID
 * Description: 按照ID号删除剧目信息
 * Input:       待删除的剧目ID号
 * Output:      无
 * Return:      0表示删除失败，1表示删除成功
 */
inline int Play_Srv_DeleteByID(int ID) {
	return Play_Perst_DeleteByID(ID);
}

/*
 * Function:    Play_Srv_FetchByID
 * Function ID:	TTMS_SCU_Play_Srv_FetchByID
 * Description: 按照ID号查找一条剧目信息，存入buf所指单元
 * Input:       待查找的剧目ID号，将查找到的信息保存到buf中
 * Output:      无
 * Return:      0表示未找到，1表示找到了
 */
inline int Play_Srv_FetchByID(int ID, play_t *buf) {
	return Play_Perst_SelectByID(ID, buf);

}

/*
 * Function:    Play_Srv_FetchAll
 * Function ID:	TTMS_SCU_Play_Srv_FetchAll
 * Description: 将所有剧目信息建立成一条链表
 * Input:       list剧目信息链表的头指针
 * Output:      无
 * Return:      返回查找到的记录数目
 */
inline int Play_Srv_FetchAll(play_list_t list) {
	return Play_Perst_SelectAll(list);
}

/*
 * Function:    Play_Srv_FetchByName
 * Function ID:	TTMS_SCU_Play_Srv_FetchByName
 * Description: 根据剧目名称查找剧目，返回载入的剧目数量
 * Input:       list为查找到的剧目信息链表的头指针，condt为模糊查询的关键字
 * Output:      无
 * Return:      返回查找到的记录数目
 */
int Play_Srv_FetchByName(play_list_t list, char condt[]){
	return Play_Perst_SelectByName(list,condt);
}



/*
 * Function:    Play_Srv_FilterByName
 * Function ID:	TTMS_SCU_Play_Srv_FilterByName
 * Description: 根据剧目名称查找剧目，返回载入的剧目数量
 * Input:       list为查找到的剧目信息链表的头指针，filter为过滤词
 * Output:      无
 * Return:      返回查找到的记录数目
 */
/*
int Play_Srv_FilterByName(play_list_t list, char filter[]){
	int cnt=0;//累加计数器 
	play_node_t *p;
	if(NULL==list)
		return 0;
	else{
	
		
		if( (strstr(filter,list)-filter+1)!=0 ){//检测相同的部分是从哪一位开始的，不等于0则说明模糊查找找到 
			cnt++;
			list=list->next;
		}
		else {
			p->next=list->next;
			free(list);
		}
	}

	return cnt;
}
*/

int Play_Srv_FilterByName(play_list_t list, char filter[])
{
	play_list_t buf;
	int i,j,found=0;
	buf=list->next;
	while(buf!=list)
	{
		found++;
		for(i=0;i<strlen(buf->data.name);i++)
		{
			if(buf->data.name[i]==filter[0])
			{
				for(j=0;j<strlen(filter);j++)
				{
					if(buf->data.name[i+j]!=filter[j])
					{
						break;
					}
				}				
				if(j==strlen(filter))
				{
					found--;
					break;
				}
			}
		}
		buf=buf->next;	
	}
	return found;
}

