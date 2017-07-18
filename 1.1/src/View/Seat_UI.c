/*
 *  Seat_UI.c
 *
 *  Created on: 2015年5月23日
 *  Author: lc
 */
#include "Seat_UI.h"

#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/List.h"
#include "../Common/ComFunction.h"
#include <stdio.h>
#include <ctype.h>
//根据状态返回对应表示状态符号
inline char Seat_UI_Status2Char(seat_status_t status) {

	// 请补充完整
	if(status == SEAT_GOOD)
	{
		return 'E';
	}
	if(status == SEAT_BROKEN)
	{
		return 'F';
	}
	if(status == SEAT_NONE)
	{
           return 'G';
	}
}

//根据状态符号返回桌位状态
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	// 请补充完整
        seat_status_t tmp;
       	if(statusChar == 'E')
       	{
       		tmp = SEAT_GOOD;
       	}
       	if(statusChar == 'F')
       	{
       		tmp = SEAT_BROKEN;
       	}
       	if(statusChar == 'G')
       	{
       		tmp = SEAT_NONE;
       	}
       return tmp;
}

int  Seat_UI_MgtEntry(int roomID) {

	// 请补充完整
	int i,j;
	
	studio_t buf;
	seat_list_t list;
	List_Init(list, seat_node_t);
	
	seat_node_t *q;
	char choice;
	if(!(Studio_Srv_FetchByID(roomID,&buf)))
	{
		printf("\t\t\t演出厅不存在!\n\t\t\t按任意键退出!\n");
		getchar();
		return 0;
	}
	if(!(Seat_Srv_FetchByRoomID(list,roomID)))
	{
	  Seat_Srv_RoomInit(list,roomID,buf.rowsCount,buf.colsCount);
	}
	Seat_Srv_FetchByRoomID(list,roomID);
	do {
		system("clear");
		printf("\t\t\t=====================================================================================\n\n");
		printf(
				"\t\t\t*************************************座位管理****************************************\n\n\n");
		for(i=1;i<=buf.rowsCount;i++)
		{printf("\t\t\t");
		   for(j=1;j<=buf.colsCount;j++)
		   {
			
			q=Seat_Srv_FindByRowCol(list,i,j);
			
			if(q->data.status == SEAT_NONE)
			{
				printf("\033[32m♡\033[0m\t");
			}
			if(q->data.status == SEAT_GOOD)
			{
				printf("\033[35m❤\033[0m\t");
			}
			if(q->data.status == SEAT_BROKEN)
			{
				printf("\033[31m✘\033[0m\t");
			}
		   }
		 
		printf("\n");
	      }
	      
		printf("\n\t\t\t**************************************************************************************\n\n");
		printf("\t\t\t[A]添加 | [D]删除 | [U]修改 | [R]返回 | \033[32m♡ :空位[G/g]\033[0m |  \033[35m❤ ::有位[E/e]\033[0m | \033[31m✘ :损坏[F/f]\033[0m\n");
		printf("\t\t\t=====================================================================================\n\n");
	        printf("\t\t\t请选择:");

		choice=l_getc();

		switch (choice) {
		case 'a':
		case 'A':
		        {
		        	
		        	int row,column;
		        	printf("\t\t\t请输入座位的行号:");
		        	//scanf("%d",&row);
		        	while(1){
				if(scanf("%d", &(row))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
		        	printf("\t\t\t请输入座位的列号:");
		        	//scanf("%d",&column);
		        	while(1){
				if(scanf("%d", &(column))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
		        	Seat_UI_Add(list,roomID,row,column);
		        	break;
		        }
		case 'd':
		case 'D':
			{
			int row,column;
			printf("\n\t\t\t==================================================================================\n\n");
	                printf("\t\t\t**********************************座位删除***********************************\n\n");
	                printf("\t\t\t----------------------------------------------------------------------------------\n");
			printf("\t\t\t请输入座位的行号:");
			//scanf("%d",&row);
			while(1){
				if(scanf("%d", &(row))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
			printf("\t\t\t请输入座位的列号:");
			//scanf("%d",&column);
			while(1){
				if(scanf("%d", &(column))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
			Seat_UI_Delete(list,row,column);
			break;
			}
		case 'U':
		case 'u':
			{
			int row,column;
			char ch;
			printf("\n\t\t\t==================================================================================\n\n");
			printf("\t\t\t**********************************座位修改******************************************\n\n");
			printf("\t\t\t1.按行修改　　　　　　　　　　　　　　2.按列修改　　　　　　　　　　　　　　　 3.单座修改\n");
			printf("\t\t\t-------------------------------------------------------------------------------------\n");
			printf("\t\t\t请选择:");
			ch=l_getc();
			switch(ch)
			{
			case '3':
			printf("\t\t\t请输入座位的行号:");
			//scanf("%d",&row);
			while(1){
				if(scanf("%d", &(row))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
			printf("\t\t\t请输入座位的列号:");
			//scanf("%d",&column);
			while(1){
				if(scanf("%d", &(column))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
			Seat_UI_Modify(list,row,column);
			break;
			case '2':
				printf("\t\t\t请输入座位的列号:");
				while(1){
				if(scanf("%d", &(column))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
				Seat_UI_Modify(list,0,column);
				break;
			case '1':
				printf("\t\t\t请输入座位的行号:");
			//scanf("%d",&row);
			while(1){
				if(scanf("%d", &(row))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
				Seat_UI_Modify(list,row,0);
				break;
			}
			break;
			}
		}	
	}while (choice != 'r' && choice != 'R');
					
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //输入一个座位
	// 请补充完整
	seat_t rec;
	studio_t buf;
	seat_node_t *p;
	//char ch;
	char choice;
	if (!Studio_Srv_FetchByID(roomID, &buf)) {
		printf("\t\t\t演出厅不存在!\n\t\t\t按任意键退出!\n");
		getchar();
		return 0;
	}
        Seat_Srv_FetchByRoomID(list,roomID);
        p=Seat_Srv_FindByRowCol(list,row,column);
    	if(!p)
        {
        		printf("\t\t\t座位不存在!\n");
        		return 0;
        }
        system("clear");
	while(1)
	 {
	  	
	  	printf("\n\t\t\t===========================================================================\n\n");
		printf("\t\t\t******************************座位添加**********************************\n\n");
		printf("\t\t\t-----------------------------------------------------------------------------\n");
		if(p->data.status==SEAT_GOOD)
		{
			printf("座位已存在!\n");
			return 0;
		}
		p->data.status=SEAT_GOOD;
		rec=p->data;
		if(Seat_Srv_Modify(&rec)){
			printf("\t\t\t座位添加成功!\n");
		}else
		        printf("\t\t\t座位添加失败!\n");
		 printf("\t\t\t[A]继续添加　｜　[R]返回\n");
		 printf("\t\t\t===========================================================================\n\n");
		 //fflush(stdin);
		 printf("\t\t\t请选择:");
		 choice=l_getc();
		 if(choice =='a' || choice=='A')
		 {
		 	printf("\t\t\t请输入座位的行号:");
			//scanf("%d",&row);
			while(1){
				if(scanf("%d", &(row))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
			printf("\t\t\t请输入座位的列号:");
			//scanf("%d",&column);
			while(1){
				if(scanf("%d", &(column))==1){ cl_stdin(); break;}
				else {cl_stdin(); printf("\t\t\t输入有误,请重新输入:");}
				}
		  }
		  else
		  {
		  	break;
		  }	
	 	 }      
		
       return 1;
}

int Seat_UI_Modify(seat_list_t list, int row, int column) {
	// 请补充完整
	seat_t rec;
	seat_node_t *p;
	seat_status_t tmp;
	studio_t buf;
	int rtn=0,i;
	char ch;
	
	if(row==0)
	{
	  p=Seat_Srv_FindByRowCol(list,1,column);
	  Studio_Srv_FetchByID(p->data.roomID,&buf);
	  if(!p)
          {
           printf("\t\t\t座位不存在!");
          return 0;
          }
           printf("\t\t\t请输入座位符号状态:");
           ch=l_getc();
           printf("%d",p->data.row);
          for(i=1;i<=buf.rowsCount;i++)
          {
           p=Seat_Srv_FindByRowCol(list,i,column);
           tmp=Seat_UI_Char2Status(toupper(ch));
           p->data.status=tmp;
	   rec=p->data;
	   Seat_Srv_Modify(&rec);
	   }
	   return 1;
	 }
          if(column==0)
          {
              p=Seat_Srv_FindByRowCol(list,row,1);
               Studio_Srv_FetchByID(p->data.roomID,&buf);
	    if(!p)
            {
             printf("\t\t\t座位不存在!");
            return 0;
            }
            printf("\t\t\t请输入座位符号状态:");
            ch=l_getc();
           for(i=1;i<=buf.colsCount;i++)
           {
           p=Seat_Srv_FindByRowCol(list,row,i);
          tmp=Seat_UI_Char2Status(toupper(ch));
           p->data.status=tmp;
	   rec=p->data;
	   Seat_Srv_Modify(&rec);
	   }
	   return 1;
	 }
          	
	//system("clear");
	 p=Seat_Srv_FindByRowCol(list,row,column);
	
	 printf("\t\t\t请输入座位符号状态:");
	 ch=l_getc();
	 tmp=Seat_UI_Char2Status(toupper(ch));
	 p->data.status=tmp;
	 rec=p->data;
	if(Seat_Srv_Modify(&rec))
	{
		rtn++;
		printf("\t\t\t座位修改成功!\n按任意键退出!\n");
	}
	else
	{
		printf("\t\t\t座位修改失败!\n");
	}
		
       return rtn;
}

  int Seat_UI_Delete(seat_list_t list, int row, int column) {
       // 请补充完整
       seat_node_t *p;
       seat_t rec;
       p=Seat_Srv_FindByRowCol(list,row,column);
       if(!p)
        {
        		printf("\t\t\t座位不存在!");
        		return 0;
        }
        //system("clear");
	
	//Seat_Srv_DeleteByID(p->data.id);
	p->data.status=SEAT_NONE;
	rec=p->data;
	Seat_Srv_Modify(&rec);
       return 1;
}


