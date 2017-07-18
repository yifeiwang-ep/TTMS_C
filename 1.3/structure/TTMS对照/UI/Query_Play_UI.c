#include "Query_Play_UI.h"
#include "../Service/Play.h"
#include "../Persistence/Query_Persist.h"
#include "../Service/Schedule.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Service/Studio.h"
#include "../Persistence/Ticket_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void DisplayQueryPlay(void)
{
	fflush(stdin);
	char fileName[30];
	play_t play;

	char choice;
	do {
		fflush(stdin);
		memset(fileName, 0, sizeof(fileName));
		printf("Please input the play name:");
		scanf("%s",fileName);
		printf("\n=======================================================\n");
		printf("\n****************  Play Information List  ***********\n");
		if (Query_PlayName(fileName,&play)) {
			printf("ID\t\tName\t\tArea\t Rating\t\tStart date\t End date\tPrice\n");
			printf("-------------------------------------------------------\n");
			printf("%d\t\t%s\t\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%d\n", play.id,
								play.name,	play.area,
								(play.rating==1?"child   ":(play.rating==2?"teenager":"adult   ")),
								play.start_date.year,play.start_date.month,
								play.start_date.day,play.end_date.year,
								play.end_date.month,play.end_date.day,play.price);
			schedule_t  sched;
			studio_t studio = {0};
	//		seat_list_t list, int studio_id
			if (Query_Schedule_By_PlayId(play.id, &sched)) {
				Query_Studio_By_Schedule(sched.studio_id, &studio);
				printf("the play will be show at %d:%d:%d %d:%d on %s studio\n", sched.date.year, sched.date.month,
																			sched.date.day,sched.time.hour,
																			sched.time.minute, studio.name);
				printf("have the seat %d , have sold %d, have %d is selling\n", Seat_Number_Count(sched.studio_id), Sold_Ticket_Count(sched.id),
																			Seat_Number_Count(sched.studio_id)-Sold_Ticket_Count(sched.id));
			} else {
				printf("sorry, the play is not show!\n");
			}
			printf("[R]eturn, [B]ooking, [A]gain:");
			fflush(stdin);
			scanf("%c", &choice);
			switch(choice) {
			case 'a':
			case 'A':
				break;
			case 'B':
			case 'b':
				//Sale the ticket
				break;
			}
		} else {
			printf("the play name is not exit!\n");
			printf("[R]eturn, [B]ooking, [A]gain:");
			fflush(stdin);
			scanf("%c", &choice);
			switch(choice) {
			case 'a':
			case 'A':
				break;
			case 'B':
			case 'b':
				//Sale the ticke
				break;
			}
		}
	} while (choice != 'r' && choice != 'R');
}


