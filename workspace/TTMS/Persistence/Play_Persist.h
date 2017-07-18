/*
* File name:  Play_Persist.h
* File ID:	  TTMS_SSF_Play_Perst_Head
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/

#ifndef PLAYPERSIST_H_
#define PLAYPERSIST_H_

	#include "../Service/Play.h"

	/*
	 * Function:    Play_Perst_Insert
	 * Function ID:	TTMS_SCU_Play_Perst_Insert
	 * Description: 在剧目信息文件末尾写入一条剧目信息
	 * Input:       待加入文件的剧目信息数据
	 * Output:      打开文件失败的信息
	 * Return:      写入文件的记录数
	 */
	int Play_Perst_Insert(const play_t *data);

	/*
	 * Function:    Play_Perst_Update
	 * Function ID:	TTMS_SCU_Play_Perst_Mod
	 * Description: 按照剧目ID号更新文件中的剧目信息
	 * Input:       待在文件中更新的剧目信息数据
	 * Output:      打开文件失败的信息
	 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
	 */
	int Play_Perst_Update(const play_t *data);

	/*
	 * Function:    Play_Perst_DeleteByID
	 * Function ID:	TTMS_SCU_Play_Perst_DelByID
	 * Description: 按照剧目ID号删除剧目的信息
	 * Input:       待删除的剧目ID号
	 * Output:      打开文件失败的信息
	 * Return:      0表示删除失败，1表示删除成功
	 */
	int Play_Perst_DeleteByID(int ID);

	/*
	 * Function:    Play_Perst_SelectByID
	 * Function ID:	TTMS_SCU_Play_Perst_SelByID
	 * Description: 按照剧目ID号查找剧目的信息
	 * Input:       待查找的剧目ID号，保存查找结果的内存的地址
	 * Output:      无
	 * Return:      0表示未找到，1表示找到了
	 */
	int Play_Perst_SelectByID(int ID, play_t *buf);

	/*
	 * Function:    Play_Perst_SelectByName
	 * Function ID:	TTMS_SCU_Play_Perst_SelByName
	 * Description: 按照剧目名称查找剧目的信息
	 * Input:       list为查找到的剧目信息链表的头指针，condt为模糊查询的关键字
	 * Output:      提示建立链表时，申请空间失败
	 * Return:      返回查找到的记录数目
	 */
	int Play_Perst_SelectByName(play_list_t list, char condt[]);

	/*
	 * Function:    Play_Perst_SelectAll
	 * Function ID:	TTMS_SCU_Play_Perst_SelAll
	 * Description: 将所有剧目信息建立成一条链表
	 * Input:       list剧目信息链表的头指针
	 * Output:      提示建立链表时，申请空间失败
	 * Return:      返回查找到的记录数目
	 */
	int Play_Perst_SelectAll(play_list_t list);

#endif /* PLAYPERSIST_H_ */
