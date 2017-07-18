#ifndef SCHEDPERSIST_H_
#define SCHEDPERSIST_H_

#include "../Service/Schedule.h"



int Schedule_Perst_Insert(const schedule_t *data);

int Schedule_Perst_Update(const schedule_t *data);

int Schedule_Perst_DeleteByID(int ID);

int Schedule_Perst_SelectByID(int ID, schedule_t *buf);

int Schedule_Perst_SelectAll(schedule_list_t list);

int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id);

#endif // SCHEDPERSIST_H_
