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
//根据剧目名字查询相关信息
int Query_PlayName(char *playName, play_t *_play)
{
	FILE *fp=fopen(PLAY_DATA_FILE,"r");
	if(fp==NULL)	{
		printf("can no file :\n");
		return 0;
	}
	while(!feof(fp))
	{
		if(fread(_play,sizeof(play_t),1,fp))  {
			if(strcmp(playName,_play->name)==0)	{
				printf("%d %s %d %s %d %d %d %d %d %d %d %d %d\n",_play->id,_play->name,_play->type,_play->area,_play->rating,_play->duration,_play->start_date.year,_play->start_date.month,_play->start_date.day,_play->end_date.year,_play->end_date.month,_play->end_date.day,_play->price);
				break;
			}
		}
	}	
	fclose(fp);
        return 1;
}
//query schedule by play id
//return 0: error the schedule is note exits
//return 1:the schedule exits and storage the information in struct
//根据剧目ID查询对应的演出计划
int Query_Schedule_By_PlayId(int playId, schedule_t *sched)
{
	FILE *fp;
	fp=fopen(SCHEDULE_DATA_FILE,"r");
	if(fp==NULL)	{
		printf("can no file :\n");
		return 0;
	}
	while(!feof(fp))
	{
		if(fread(sched,sizeof(schedule_t),1,fp))	{
			if(playId==sched->play_id)
			{
				printf("%d %d %d %d %d %d %d %d %d %d\n",sched->id,sched->play_id,sched->studio_id,sched->date.year,sched->date.month,sched->date.day,sched->time.hour,sched->time.minute,sched->time.second,sched->seat_count);
			break;
			}
		}
	}
	fclose(fp);
	
        return 1;
}
//根据剧场ID查找对应的剧场信息
int Query_Studio_By_Schedule(int id, studio_t *studio)
{
	FILE *fp=fopen(STUDIO_DATA_FILE,"r");
	if(fp==NULL)	{

		printf("can no file :\n");
		return 0;
	}
	while(!feof(fp))
	{
		if (fread(studio, sizeof(studio_t), 1, fp))	{
			if(id==studio->id)	{
				printf("%d %s %d %d\n",studio->id,studio->name,studio->rowsCount,studio->colsCount);
				break;				
			}
		}
	}
	fclose(fp);
	return 1;
}
//根据演出计划ID已经售出的票
int Sold_Ticket_Count(int id)
{
	int count=0;
	ticket_t data;
	FILE *fp=fopen(TICKET_DATA_FILE,"r");
	if(fp==NULL)	{

		printf("can no file :\n");
		return 0;
	}
	while(!feof(fp))
	{
		fread(&data,sizeof(ticket_t),1,fp);
		if(id==data.schedule_id)  {
			if(data.status==1)	{
				count++;
			}
		}
	}
	printf("All ticket num %d",count);
        return 1;
	fclose (fp);
}
//根据影厅ID查找座位数
int Seat_Number_Count(int studio_id)
{
	int count;
	seat_t data;	
	FILE *fp=fopen(SEAT_DATA_FILE,"r");
	if(fp==NULL)	{
		printf("can no file :\n");
		return 0;
	}
	while(!feof(fp))
	{
		if(studio_id==data.roomID)	
		{
			count=(data.row)*(data.column);
			break;
		}
	}
	printf("All seat %d num",count);
	fclose(fp);	
	// 请补充完整
       return 1;
}
