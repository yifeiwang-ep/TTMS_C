#include "Schedule.h"
#include "../Common/List.h"
#include "../Persistence/Schedule_Persist.h"
#include "Ticket.h"
#include <stdio.h>

//新增演出计划服务
inline int Schedule_Srv_Add(const schedule_t *data) {
	return Schedule_Perst_Insert(data);
	/*ticket_srv_addbatch*/
}

//修改演出计划服务
inline int Schedule_Srv_Modify(const schedule_t *data) {
	return Schedule_Perst_Update(data);
}

//根据id删除演出计划服务
inline int Schedule_Srv_DeleteByID(int ID) {
	return Schedule_Perst_DeleteByID(ID);
}

//根据id获取演出计划服务
inline int Schedule_Srv_FetchByID(int ID, schedule_t *buf) {
	return Schedule_Perst_SelectByID(ID, buf);

}

//获取所有演出计划服务
inline int Schedule_Srv_FetchAll(schedule_list_t list) {
	return Schedule_Perst_SelectAll(list);
}

//根据剧目id获取演出计划服务
inline int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id) {
	return Schedule_Perst_SelectByPlay(list,play_id);
}

//根据playID，统计上座率及票房，返回票房数收入
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount, int *totalCount) {
	schedule_list_t list,curPos;	
	int sum=0 , sold_temp, total_temp;

	*soldCount = *totalCount = 0;

	Schedule_Perst_SelectByPlay(list, play_id);
	
	List_ForEach(list, curPos)
	{
		sum+=Ticket_Srv_StatRevBySchID(curPos->data.id, &sold_temp, &total_temp);
		(*soldCount) += sold_temp;
		(*totalCount)+= total_temp;
	}
	return sum;
}

