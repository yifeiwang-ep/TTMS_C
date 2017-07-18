#include "Query_Persist.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include "../Service/Studio.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>
#include <string.h>

static const char PLAY_DATA_FILE[] = "Play.dat";
static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";
static const char STUDIO_DATA_FILE[] = "Studio.dat";
static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char SEAT_DATA_FILE[] = "Seat.dat";
//Query play by name
//0: error, the play is not exits
//1: the play exits and storage the information in the struct
int Query_PlayName(char *playName, play_t *_play)
{
	
	play_t data;
	int found = 0;

	
	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			
			if(strcmp(playName , data.name)==0){
				*_play = data;
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
       return found;
}
//query schedule by play id
//return 0: error the schedule is note exits
//return 1:the schedule exits and storage the information in struct
int Query_Schedule_By_PlayId(int playId, schedule_t *sched)
{
	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	schedule_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			if (playId == data.play_id) {
				*sched = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}
void Query_Studio_By_Schedule(int id, studio_t *studio)
{
	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	schedule_t data;
	

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			if (id == data.id) {
				//*sched = data;

				FILE *fp1 = fopen(STUDIO_DATA_FILE, "rb");
				if (NULL == fp1) {
					
				}

				studio_t sdata;
				

				while (!feof(fp1)) {
					if (fread(&sdata, sizeof(studio_t), 1, fp1)) {
						if (sdata.id == data.studio_id) {
							*studio = sdata;
							
							break;
						};

					}
				}
				fclose(fp1);
				break;
			};

		}
	}
	fclose(fp);


}
//已经售出的票
int Sold_Ticket_Count(int id)
{
	ticket_t data;
	int rtn=0;
	FILE  *fp=fopen(TICKET_DATA_FILE,"rb");
	if(NULL == fp)
	{
		return 0;
	}
	while(!feof(fp)){
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			if(id==data.schedule_id && data.status==TICKET_SOLD)
			{
				rtn++;
			}
		}
	}
	
       return rtn;
}

int Seat_Number_Count(int studio_id)
{
	seat_t data;
	int rtn=0;
	FILE  *fp=fopen(SEAT_DATA_FILE,"rb");
	if(NULL == fp)
	{
		return 0;
	}
	while(!feof(fp)){
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			if(studio_id==data.roomID && data.status==SEAT_GOOD)
			{
				rtn++;
			}
		}
	}
	
       return rtn;
}
