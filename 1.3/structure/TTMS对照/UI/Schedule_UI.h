/*
* File name:  Schedule_UI.h
* File ID:	  TTMS_SSF_Schedule_UI_Head
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#ifndef SCHEDULE_UI_H_
	#define SCHEDULE_UI_H_
	#include "../Common/list.h"
	#include "../Service/Schedule.h"
	#include "../Service/Play.h"

	static const int SCHEDULE_PAGE_SIZE=5;

	/*
	 * Function:    Schedule_UI_Add
	 * Function ID:	TTMS_SCU_Schedule_UI_Add
	 * Description: 添加一条演出计划信息
	 * Input:       相关剧目的ID号
	 * Output:      输入信息时的各种提示
	 * Return:      添加的记录数
	 */
	int Schedule_UI_Add(int play_id);

	/*
	 * Function:    Schedule_UI_Modify
	 * Function ID:	TTMS_SCU_Schedule_UI_Mod
	 * Description: 按照ID号更新演出计划信息
	 * Input:       待更新的剧目ID号
	 * Output:      输入信息时的各种提示
	 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
	 */
	int Schedule_UI_Modify(int id);

	/*
	 * Function:    Schedule_UI_Delete
	 * Function ID:	TTMS_SCU_Schedule_UI_Del
	 * Description: 按照ID号删除演出计划信息
	 * Input:       待删除的剧目ID号
	 * Output:      提示删除是否成功
	 * Return:      0表示删除失败，1表示删除成功
	 */
	int Schedule_UI_Delete(int id);

	/*
	 * Function:    Schedule_UI_Query
	 * Function ID:	TTMS_SCU_Schedule_UI_Qry
	 * Description: 按照ID号查询演出计划信息
	 * Input:       待查找的剧目ID号
	 * Output:      查找到的剧目信息
	 * Return:      0表示未找到，1表示找到了
	 */
	int Schedule_UI_Query(int id);

	/*
	 * Function:    Schedule_UI_MgtEntry
	 * Function ID:	TTMS_SCU_Schedule_UI_MgtEnt
	 * Description: 演出计划管理界面，演出计划按照剧目进行管理，以剧目ID号为输入
	 * Input:       相关剧目ID号
	 * Output:      演出计划信息
	 * Return:      无
	 */
	void Schedule_UI_MgtEntry(int play_id);

	/*
	 * Function:    Schedule_UI_ListByPlay
	 * Function ID:	TTMS_SCU_Schedule_UI_ListByPlay
	 * Description: 以列表模式显示给定剧目的演出计划信息
	 * Input:       list为查找到的演出计划信息链表的头指针，play为剧目信息，paging为显示分页设置参数
	 * Output:      无
	 * Return:      返回查找到的记录数目
	 */
	void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging);

	/*
	 * Function:    Schedule_UI_ListAll
	 * Function ID:	TTMS_SCU_Schedule_UI_List
	 * Description: 显示所有的演出计划信息
	 * Input:       无
	 * Output:      所有剧目的信息
	 * Return:      无
	 */
	void Schedule_UI_ListAll(void);

#endif // SCHEDULES_UI_H_
