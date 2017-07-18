/*
* File name:  Play_UI.h
* File ID:	  TTMS_SSF_Play_UI_Head
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#ifndef PLAY_UI_H_
	#define PLAY_UI_H_
	#include "../Common/list.h"
	#include "../Service/Play.h"

	static const int PLAY_PAGE_SIZE=6;

	/*
	 * Function:    Play_UI_Add
	 * Function ID:	TTMS_SCU_Play_UI_Add
	 * Description: 添加一条剧目信息
	 * Input:       无
	 * Output:      输入信息时的各种提示
	 * Return:      添加的记录数
	 */
	int Play_UI_Add(void);

	/*
	 * Function:    Play_UI_Modify
	 * Function ID:	TTMS_SCU_Play_UI_Mod
	 * Description: 更新剧目信息
	 * Input:       待更新的剧目ID号
	 * Output:      输入信息时的各种提示
	 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
	 */
	int Play_UI_Modify(int id);

	/*
	 * Function:    Play_UI_Delete
	 * Function ID:	TTMS_SCU_Play_UI_Del
	 * Description: 按照ID号删除剧目信息
	 * Input:       待删除的剧目ID号
	 * Output:      提示删除是否成功
	 * Return:      0表示删除失败，1表示删除成功
	 */
	int Play_UI_Delete(int id);

	/*
	 * Function:    Play_UI_Query
	 * Function ID:	TTMS_SCU_Play_UI_Qry
	 * Description: 按照ID号查询剧目信息
	 * Input:       待查找的剧目ID号
	 * Output:      查找到的剧目信息
	 * Return:      0表示未找到，1表示找到了
	 */
	int Play_UI_Query(int id);

	/*
	 * Function:    Play_UI_ShowList
	 * Function ID:	TTMS_SCU_Play_UI_Show
	 * Description: 以列表模式显示剧目信息
	 * Input:       list剧目信息链表的头指针，paging分页设置参数
	 * Output:      所有剧目的信息
	 * Return:      返回查找到的记录数目
	 */
	void Play_UI_ShowList(play_list_t list, Pagination_t paging);

	/*
	 * Function:    Play_UI_MgtEntry
	 * Function ID:	TTMS_SCU_Play_UI_MgtEnt
	 * Description: 剧目信息管理界面
	 * Input:       flag为0，进入管理页面，flag为1进入查询界面
	 * Output:      剧目管理界面
	 * Return:      无
	 */
	void Play_UI_MgtEntry(int flag);

#endif /* PLAY_UI_H_ */
