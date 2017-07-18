#include "Schedule.h"
#include "../Common/List.h"
#include "../Persistence/Schedule_Persist.h"
#include "Ticket.h"
#include <stdio.h>

inline int Schedule_Srv_Add(const schedule_t *data) {
	return Schedule_Perst_Insert(data);
}

inline int Schedule_Srv_Modify(const schedule_t *data) {
	return Schedule_Perst_Update(data);
}

inline int Schedule_Srv_DeleteByID(int ID) {
	return Schedule_Perst_DeleteByID(ID);
}

inline int Schedule_Srv_FetchByID(int ID, schedule_t *buf) {
	return Schedule_Perst_SelectByID(ID,buf);

}

inline int Schedule_Srv_FetchAll(schedule_list_t list) {
	return Schedule_Perst_SelectAll(list);
}

inline int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id) {
	return Schedule_Perst_SelectByPlay(list,play_id);
}

//根据演出ID，统计上座率及票房，返回票房数收入
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount, int *totalCount) {
	// 请补充完整
       return 1;
}

