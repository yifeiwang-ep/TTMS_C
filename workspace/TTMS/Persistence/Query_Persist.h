#ifndef QUERYPERSIST_H
#define QUERYPERSIST_H

#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Studio.h"

//Query play by name
//0: error, the play is not exits
//1: the play exits and storage the information in the struct
int Query_PlayName(char *playName, play_t *_play);

//query schedule by play id
//0:error: the schedule is not exits
//1 :the play exits and storage the information int the struct
int Query_Schedule_By_PlayId(int playId, schedule_t *sched);

//query studio by schedule id
void Query_Studio_By_Schedule(int id, studio_t* name);

//query the ticket count by schedlue id
int Sold_Ticket_Count(int id);

int Seat_Number_Count(int studio_id);

#endif
