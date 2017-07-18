/*
* File name:  Schedule_Persist.h
* File ID:	  TTMS_SSF_Schedule_Perst_Head
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/

#ifndef SCHEDPERSIST_H_
#define SCHEDPERSIST_H_

	#include "../Service/Schedule.h"



	/*
	 * Function:    Schedule_Perst_Insert
	 * Function ID:	TTMS_SCU_Schedule_Perst_Insert
	 * Description: 在演出计划信息文件末尾写入一条演出计划信息
	 * Input:       待加入文件的演出计划信息数据
	 * Output:      打开文件失败的信息
	 * Return:      写入文件的记录数
	 */
	int Schedule_Perst_Insert(const schedule_t *data);

	/*
	 * Function:    Schedule_Perst_Update
	 * Function ID:	TTMS_SCU_Schedule_Perst_Mod
	 * Description: 按照演出计划ID号更新文件中的演出计划信息
	 * Input:       待在文件中更新的演出计划信息数据
	 * Output:      打开文件失败的信息
	 * Return:      更新的演出计划信息数，0表示未找到，1表示找到并更新
	 */
	int Schedule_Perst_Update(const schedule_t *data);

	/*
	 * Function:    Schedule_Perst_DeleteByID
	 * Function ID:	TTMS_SCU_Schedule_Perst_DelByID
	 * Description: 按照演出计划ID号删除演出计划的信息
	 * Input:       待删除的演出计划ID号
	 * Output:      打开文件失败的信息
	 * Return:      0表示删除失败，1表示删除成功
	 */
	int Schedule_Perst_DeleteByID(int ID);

	/*
	 * Function:    Schedule_Perst_SelectByID
	 * Function ID:	TTMS_SCU_Schedule_Perst_SelByID
	 * Description: 按照演出计划ID号删除演出计划的信息
	 * Input:       待查找的演出计划ID号，保存查找结果的内存的地址
	 * Output:      无
	 * Return:      0表示未找到，1表示找到了
	 */
	int Schedule_Perst_SelectByID(int ID, schedule_t *buf);

	/*
	 * Function:    Schedule_Perst_SelectAll
	 * Function ID:	TTMS_SCU_Schedule_Perst_SelAll
	 * Description: 将所有演出计划信息建立成一条链表
	 * Input:       list为演出计划信息链表的头指针
	 * Output:      提示建立链表时，申请空间失败
	 * Return:      返回查找到的记录数目
	 */
	int Schedule_Perst_SelectAll(schedule_list_t list);

	/*
	 * Function:    Schedule_Perst_SelectByPlay
	 * Function ID:	TTMS_SCU_Schedule_Perst_SelByPlay
	 * Description: 将同意剧目的演出计划信息搜索出来，建立一条链表
	 * Input:       list为满足条件的演出计划信息链表的头指针，剧目的ID号
	 * Output:      提示建立链表时，申请空间失败
	 * Return:      返回查找到的记录数目
	 */
	int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id);

#endif // SCHEDPERSIST_H_
