/*************************************************************************
	> File Name: test.c
	> Author:wyf 
	> Mail: catherine199787@outlook.com
	> Created Time: Fri 17 Jun 2016 00:28:21 CST
 ************************************************************************/

#include<stdio.h>
#include "Seat_UI.h"
#include<ctype.h>
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include "../Common/ComFunction.h"

inline char Seat_UI_Status2Char(seat_status_t status) {

	char statusChar;
	switch (status) {
	case SEAT_GOOD:		
		statusChar = 'G';
		break;
	case SEAT_BROKEN:	
		statusChar = 'B';
		break;
	case SEAT_NONE:
		statusChar = 'N';
		break;
	}
	return statusChar;
}

inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	seat_status_t status;
	switch (statusChar) {
	case 'G':		
		status = SEAT_GOOD;
		break;
	case 'B':	
		status = SEAT_BROKEN;
		break;
	case 'N':
		status = SEAT_NONE;
		break;
	}
	return status;
}

void Seat_UI_MgtEntry(int roomID) {
	int i, j;
	char choice;
	int seatCount;
	int changedCount = 0;
	studio_t studioRec;

	if (!Studio_Srv_FetchByID(roomID, &studioRec)) {
		printf("\n\n\n			=================================================================");
       	        printf("\n			-----------------------------------------------------------------");
				printf("\n	                 		      **演出厅不存在！**                             ");
       	        printf("\n			-----------------------------------------------------------------");
		printf("\n			=================================================================");
		getchar();
		return;
	}

	seat_list_t list;
	seat_node_t *p;

	List_Init(list, seat_node_t);
	seatCount = Seat_Srv_FetchByRoomID(list, roomID);

	if (!seatCount) {		
		seatCount = Seat_Srv_RoomInit(list, roomID, studioRec.rowsCount,
				studioRec.colsCount);
		studioRec.seatsCount = seatCount;
		Studio_Srv_Modify(&studioRec);
	}
	do {
        system("clear");
		printf("\n\n\n			=================================================================");
		printf("\n			---------------------%d号演出厅座位表------------------------------",roomID);
		printf("\n\t\t\t|        \033[32m♡ \033[0m[N]one       |    \033[35m❤\033[0m[G]et        |     \033[31m✘\033[0m[B]roken        |");
		printf("\n			*****************************************************************");
		printf("\n	\t\t   列：%c", ' ');
		for (i = 1; i <= studioRec.colsCount; i++) {
			printf("%3d", i);
		}
		printf("\n	\t\t=================================================================");

		for (i = 1; i <= studioRec.rowsCount; i++) {
			j = 1;
			printf("\n	\t\t%3d行：%3c", i, ' ');

			List_ForEach(list,p)
			{
				if (p->data.row == i) {
					while (p->data.column != j) {
						printf("%3c", ' ');
						j++;
					}
					Seat_UI_Status2Char(p->data.status);
					if(p->data.status == SEAT_NONE)
					{
						printf("\033[32m♡\033[0m  ");
					}
					if(p->data.status == SEAT_GOOD)
					{
						printf("\033[35m❤\033[0m  ");
					}
					if(p->data.status == SEAT_BROKEN)
					{
						printf("\033[31m✘\033[0m  ");
					}
						j++;
				}
			}
		}
		printf("\n			******************************************************************");
       		printf("\n	\t\t|     [A]dd     |    [D]elete    |   [U]pdate   |     [R]eturn   |");
        	printf("\n			******************************************************************");
		printf("\n	\t\tYour choice:");
        scanf("%c", &choice);
		switch (choice) {
		case 'a':
		case 'A':
			changedCount = Seat_UI_Add(list, roomID, studioRec.rowsCount,
					studioRec.colsCount);
			if (changedCount > 0) {
				seatCount += changedCount;
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'd':
		case 'D':
			changedCount = Seat_UI_Delete(list, studioRec.rowsCount,
					studioRec.colsCount);
			if (changedCount > 0) {
				seatCount -= changedCount;
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'u':
		case 'U':
		{
            system("clear");
			int row,column;
			char choice;
			printf("\n			=================================================================");
				printf("\n\t\t\t|        \033[32m♡ \033[0m[N]one      |        \033[35m❤\033[0m[G]et       |     \033[31m✘\033[0m[B]roken     |");
			printf("\n			*****************************更新座位****************************");
            printf("\n	\t\t|      [1]按行更新     |      [2]按列更新     |    [3]单座更新   |");
            printf("\n	\t\t|\tInput Your Choice:");
			choice=l_getc();
			switch(choice)
			{
			case '3':
			printf("\t\t\t|\t请输入座位行号:");
			while(1){
				if(scanf("%d", &(row))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\n	                 		     **输入有误！清重新输入**  ");}
				}
			printf("\t\t\t|\t请输入座位列号:");
			while(1){
				if(scanf("%d", &(column))==1){ cl_stdin(); break;}
				else {cl_stdin();printf("\n	                 		     **输入有误！清重新输入**  ");}
				}
			Seat_UI_Modify(list,row,column);
			break;
			case '2':
				printf("\t\t\t|\t请输入座位的列号:");
				while(1){
				if(scanf("%d", &(column))==1){ cl_stdin(); break;}
				else {cl_stdin();printf("\n	                 		     **输入有误！清重新输入**  ");}
				}
				Seat_UI_Modify(list,0,column);
				break;
			case '1':
				printf("\t\t\t|\t请输入座位的行号:");
			while(1){
				if(scanf("%d", &(row))==1){ cl_stdin(); break;}
				else {cl_stdin();printf("\n	                 		     **输入有误！清重新输入**  ");}
				}
				Seat_UI_Modify(list,row,0);
				break;
			}
			break;
			}
		}
	} while (choice != 'r' && choice != 'R');

	List_Destroy(list, seat_node_t);
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) { 
	seat_t rec;
	seat_node_t *p;
	int newRecCount = 0;
	char choice;
	do {
        system("clear");
		printf("\n\n\n			=================================================================");
		printf("\n			---------------------------添加座位-------------------------------");
		printf("\n			*****************************************************************");

		do {
		printf("\n			 |\t目前座位行数为：[%d]",row);
         printf("\n\t\t\t\t请输入添加的座位行号：");
			scanf("%d",&(row));
		printf("\n			 |\t目前座位列数为：[%d]",column);
         printf("\n\t\t\t\t请输入添加的座位列号：");
			scanf("%d", &(column));
         if((rec.row )<row || (rec.column <column)){
                	printf("\n			**请输入小于当前座位行（列）数的数**");
               	printf("\n			-----------------------------------------------------------------");
         		}
		} while (rec.row >row && rec.column >column);

		p = Seat_Srv_FindByRowCol(list, rec.row, rec.column);
		if (p) {
	printf("\n			----------------------------------------------------------------");					
			printf("\n	\t\t                       **座位已存在！**  ");
       	       		printf("\n			-----------------------------------------------------------------");
		printf("\n			=================================================================");
            sleep(1);
			continue;
		}

		rec.id = EntKey_Srv_CompNewKey("Seat");		
		rec.roomID = roomID;
		rec.status = SEAT_GOOD;    
		printf("\n			=================================================================");
		if (Seat_Srv_Add(&rec)) {
			newRecCount++;
			printf("\n			------------------------添加座位成功！--------------------------");
			p = (seat_node_t*) malloc(sizeof(seat_node_t));
			p->data = rec;
			Seat_Srv_AddToSoftedList(list, p);
		} else
			printf("\n			------------------------添加座位失败！--------------------------"); 
		 printf("\n			==================================================================");
       		 printf("\n			|         [A]dd More               |             [R]eturn        |");
        	 printf("\n			******************************************************************");
        	 printf("\n			Iput Your choice:");
		fflush(stdin);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Seat_UI_Modify(seat_list_t list, int row, int column) {
	int rtn = 0;
	char choice;
	seat_node_t *p;
	seat_status_t status;
    List_Init(p,seat_node_t);
	studio_t studioRec;
	seat_t rec;
    int i;
	if(row==0)
	{
	  p=Seat_Srv_FindByRowCol(list,1,column);
	  Studio_Srv_FetchByID(p->data.roomID,&studioRec);
	  if(!p)
          {
           printf("\n\n\n	\t\t                       **座位不存在！**  ");
		      printf("\n			-----------------------------------------------------------------");
		printf("\n			=================================================================");
          return 0;
          }
            printf("	\t\t|\t请输入座位状态:");
           choice=l_getc();
           printf("%d",p->data.row);
          for(i=1;i<=studioRec.rowsCount;i++)
          {
           p=Seat_Srv_FindByRowCol(list,i,column);
           status=Seat_UI_Char2Status(toupper(choice));
           p->data.status=status;
	   rec=p->data;
	   Seat_Srv_Modify(&rec);
	   }
	   return 1;
	 }
          if(column==0)
          {
              p=Seat_Srv_FindByRowCol(list,row,1);
               Studio_Srv_FetchByID(p->data.roomID,&studioRec);
	    if(!p)
            {
              printf("	\t\t                       **座位不存在！**  ");
		      printf("\n			-----------------------------------------------------------------");
            return 0;
            }
            printf("	\t\t|\t请输入座位状态:");
            choice=l_getc();
           for(i=1;i<=studioRec.colsCount;i++)
           {
           p=Seat_Srv_FindByRowCol(list,row,i);
          status=Seat_UI_Char2Status(toupper(choice));
           p->data.status=status;
	   rec=p->data;
	   Seat_Srv_Modify(&rec);
	   }
	   return 1;
	}     
		p = Seat_Srv_FindByRowCol(list,row,column);    
            printf("	\t\t|\t请输入座位状态:");
        choice=l_getc();
		status=Seat_UI_Char2Status(toupper(choice));
		 p->data.status=status;
	 	rec=p->data;
		if(Seat_Srv_Modify(&rec))
		{
			rtn++;
			printf("		------------------------修改座位成功！--------------------------");
		}
		else
		{
			printf("\n			------------------------修改座位失败！--------------------------");
		}
		 printf("\n			==================================================================");
		fflush(stdin);
	return rtn;
}

int Seat_UI_Delete(seat_list_t list, int row, int column) {

	int delSeatCount = 0;
	int newrow, newcolumn;
	seat_node_t *p;
	char choice;

	do {
        system("clear");
		printf("\n\n\n			=================================================================");
		printf("\n			*****************************删除座位**************************");
    		printf("\n			=================================================================");
		do {
			fflush(stdin);
			printf("\n			|\t目前座位行数为：[%d]",row);
            		printf("\n\t\t\t\t请输入要删除的座位行号：");
			scanf("%d", &(newrow));
			printf("\n			|\t目前座位列数为：[%d]",column);
            		printf("\n\t\t\t\t请输入要删除的座位列号：");
			scanf("%d", &(newcolumn));
            		if(newrow < row || newcolumn < column){
                	printf("\n			        **请输入小于当前座位行（列）数的数**");
               		printf("\n			-----------------------------------------------------------------");	
            		}
			fflush(stdin);
		} while (newrow > row || newcolumn > column);
		printf("\n			=================================================================");       
		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p) {
			if (Seat_Srv_DeleteByID(p->data.id)) {
				printf("\n			-----------------------------------------------------------------");
				printf("                       ** 删除完毕**                             ");
       	        		printf("\n			-----------------------------------------------------------------");
				delSeatCount++;
				List_FreeNode(p);	
			}
		} else {
			printf("\n			-----------------------------------------------------------------");
			printf("                       **座位不存在！**                             ");
       	        	printf("\n			-----------------------------------------------------------------");
		}

		 printf("\n			==================================================================");
       		 printf("\n			|        [D]elet More            |              [R]eturn        |");
        	 printf("\n			******************************************************************");
        	 printf("\n			Iput Your choice:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
	} while ('d' == choice || 'D' == choice);
	return delSeatCount;
}


