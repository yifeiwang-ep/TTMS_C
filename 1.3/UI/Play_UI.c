/*************************************************************************
	> File Name: Playtest.c
	> Author:wyf 
	> Mail: catherine199787@outlook.com
	> Created Time: Fri 17 Jun 2016 15:03:13 CST
 ************************************************************************/
#include "Schedule_UI.h"
#include "../Common/list.h"
#include "../Service/Play.h"
#include "../Service/EntityKey.h"
#include"Play_UI.h"
#include"../Common/ComFunction.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/*void Play_UI_ShowList(play_list_t list, Pagination_t paging) {

//整合在了list里

}*/
void Play_UI_MgtEntry(int flag){
	int i, id;
	char choice;

	play_list_t head;
	play_node_t *p;
	Pagination_t paging;

	List_Init(head, play_node_t);
	
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Play_Srv_FetchAll(head);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n\n\n			==================================================================");
        	printf("\n			*************************剧目列表*******************************");
          	printf("\n			==================================================================");
		printf("\n	\t\t  %-7s% -13s %-8s %-5s %-15s %-15s %-5s", "ID", "名称", "地区","时长", "上映日期","下线日期","票价");
		printf("\n			-----------------------------------------------------------------\n");
			//显示数据
		for (i = 0, p = (play_node_t *) (paging.curPos);
						p != head && i < paging.pageSize; i++){
			printf("\n\t\t\t  %-6d %-12s%-7s% -5d ", p->data.id, p->data.name,p->data.area, p->data.duration);
			printf("%-4d-%-02d-%-02d ", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
			printf("%-4d-%-02d-%-02d ",p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
			printf(" %-5d\n", p->data.price);
			p=p->next;
		}
		printf("\n			==================================================================");
        	printf("\n			|---------总数%2d------------------------------%2d/%2d页---------",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
        	printf("\n			==================================================================");
		printf("\n			******************************************************************");
        	printf("\n			|      [P]revPage           |             [N]extPage          ");
       		printf("\n			-----------------------------------------------------------------");
			printf("\n			|   [A]dd   |   [D]elete  |   [U]pdate |  [S]chedule |  [R]eturn |");
			printf("\n			******************************************************************");
			printf("\n			==================================================================");
			printf("\n			Iput Your choice:");
		
			choice=l_getc();
	

		switch (choice) {
            getchar();
		case 'a':
		case 'A':
			system("clear");
			if (Play_UI_Add()) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Play_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, play_node_t);
			}
			break;
		case 'd':
		case 'D':
				printf("\t\t\tInput the Play ID:");
				scanf("%d",&id);
				if (Play_UI_Delete(id)) {	//从新载入数据
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
			break;
		case 'u':
		case 'U':
				printf("\t\t\tInput the Play ID:");
				scanf("%d",&id);
				if (Play_UI_Modify(id)) {	//从新载入数据

				printf("\nddfddd\n");
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
			break;
		case 's':
		case 'S':
				printf("\t\t\tInput the Play ID:");
				scanf("%d",&id);
				play_t data;
				if(Play_Srv_FetchByID(id, &data)){
					Schedule_UI_MgtEntry(id);
				}else{
					printf("\t\t\t                       **没有剧目信息！**                             ");
       	       		printf("\n			-----------------------------------------------------------------");
        	printf("\n			=================================================================");    	
					cl_stdin();
                    sleep(1);
			}
			break;
		
		case 'p':
		case 'P':
		system("clear");
	     if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
			system("clear");
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;

		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, play_node_t);
}



int Play_UI_Add(void)
{
       		int er=0,newRecCount=0;
       		char choice;
		play_t data;	
		do { 

				system("clear");
				printf("\n\n\n			=================================================================");
        			printf("\n			***************************添加剧目*******************************");
          		printf("\n			=================================================================");
            getchar();
            data.id = EntKey_Srv_CompNewKey("play");
                printf("\n			|     请输入名称:");
				gets(data.name);
				printf("\n			|     请输入地区：");
				gets(data.area);
				printf("\n			-------[1].电影------------[2].戏曲-------------[3].话剧---------");
				printf("\n			|     请选择剧目类型：");
				while(1){
					er=0;
					choice=l_getc();
					switch(choice){
						case '1': data.type= PLAY_TYPE_FILE;   break;
						case '2': data.type=PLAY_TYPE_OPEAR;   break;
						case '3': data.type=PLAY_TYPE_DRAMA; break;
						default : er=1; 
							printf("\n			                      **您的选择有误！请重新选择!**     ");
					}
					if(er!=1) break;
				}
				printf("\n			-------[1].文艺------------[2].轻松------------[3].重口-----------");
				printf("\n			|     请选择剧目风格：");
				while(1){
					er=0;
					choice=l_getc();
					switch(choice){
						case '1': data.rating= PLAY_RATE_ART;   break;
						case '2': data.rating= PLAY_RATE_ACUTE; break;
						case '3': data.rating= PLAY_RATE_HARD;break;
						default : er=1; 
							printf("\n			                      **您的选择有误！请重新选择!**     ");
					}
					if(er!=1) break;
				}
				printf("\n			|     请输入剧目时长(min)：");
				while(1){
					if(scanf("%d",&(data.duration))==1){ cl_stdin(); break;}
					else{ cl_stdin(); 
						printf("\n			                      **您的输入有误！请重新选择!**     ");}
				}
				
				printf("\n			|     请输入上映时间( 年 月 日)：");
				while(1){
					if(scanf("%d %d %d",&(data.start_date.year), &(data.start_date.month), &(data.start_date.day))==3){            //格式限制
						 cl_stdin();
						 if(data.start_date.month>12 || data.start_date.day>31||DateCmp(data.start_date, DateNow())==-1){
							printf("\n			                      **您输入的日期有误!请重新输入**     ");
						 	continue;
						 }
                                                                                                        break;
					}
					else{ cl_stdin(); printf("\n			                        **您的输入有误!请重新输入**     "); }
				}
				
				
				printf("\n			|     请输入下线时间( 年 月 日)：");
				while(1){
					if(scanf("%d %d %d",&(data.end_date.year), &(data.end_date.month), &(data.end_date.day))==3){
						 cl_stdin();
						 if(data.end_date.month>12 || data.end_date.day>31){
						 	printf("\n			                      **您输入的日期有误!请重新输入**     ");
						 	continue;
						 }
						 if(DateCmp(data.end_date,data.start_date)==-1){
						 	printf("\n			               **您输入的『下线』时间早于『上映』时间！请重新输入！**   ");
						 	continue;
						 
						 }
						 
						 break;
					}
					else{ cl_stdin(); printf("\n			                        **您的输入有误!请重新输入**     "); }
				}
				
				printf("\n			|     请输入票价：");
				while(1){
					if(scanf("%d",&(data.price))==1){ cl_stdin(); break;}
					else{ cl_stdin(); printf("\n			                        **您的输入有误!请重新输入**     "); }
				}
				
				printf("\n			==================================================================");
				if(Play_Srv_Add(&data)){
					newRecCount++;
					printf("\n			------------------------添加剧目成功！--------------------------");
				}else{
					printf("\n			------------------------添加剧目失败！--------------------------");   
				}
				printf("\n			==================================================================");
       				printf("\n			|         [A]dd More               |             [R]eturn        |");
        			printf("\n			******************************************************************");
        			printf("\n			Iput Your choice:");
				choice=l_getc();
		} while ('a' == choice || 'A' == choice);
		return newRecCount;
}

int Play_UI_Modify(int id){


	int er=0,ret=0;
       	char choice;
	play_t data;
    cl_stdin;	
	if(Play_Srv_FetchByID(id, &data)){
		while(1){ 

			system("clear");
			printf("\n			==================================================================");
        		printf("\n			***************************修改剧目*******************************");
          		printf("\n			==================================================================");
			printf("\n			|     ID：  %-5d                                                ",data.id);
			printf("\n			|     名称：%-20s                                 ",data.name);
          switch(data.type){
                case PLAY_TYPE_FILE:
			printf("\n			|     类型：电影                                                ");
                case PLAY_TYPE_OPEAR:
			printf("\n			|     类型：戏剧                                                     ");
                case PLAY_TYPE_DRAMA:
			printf("\n			|     类型：舞台剧                                           ");
            }
            switch(data.rating){
                case PLAY_RATE_ART:
			printf("\n			|     风格：文艺                                             ");
                case PLAY_RATE_ACUTE:
			printf("\n			|     风格：轻松                                                    ");
                case PLAY_RATE_HARD:
			printf("\n			|     文艺：重口                                                    ");
            }
			printf("\n			|     地区：%-8s                                                    ",data.area);
			printf("\n			|     时长：%-5d                                                    ",data.duration);
			printf("\n			|     上映日期：%4d-%02d-%02d                                       ",data.start_date.year,data.start_date.month,data.start_date.day);
			printf("\n			|     下映日期：%4d-%02d-%02d                                       ",data.end_date.year,data.end_date.month,data.end_date.day);
			printf("\n			|     票价：%-5d                                                    ",data.price);			
       			printf("\n			===================================================================");
			printf("\n			-[A]修改名称--[B]修改出品地区--[C]修改类型--[D]修改风格--[E]修改时长-");         
			printf("\n			--[F]修改上映日期-----[G]修改下映时间-----[H]修改票价-----[R]返回---");	
  			printf("\n			********************************************************************");
        		printf("\n			Iput Your choice:");
			choice=l_getc();
			if('r'==choice || 'R'==choice) break;	
			switch(choice){
					
					case 'a':
					case 'A':
						printf("\n			|     请输入名称：");
						scanf("%s",data.name);
						cl_stdin();
						//fgets(data.name,30,stdin);
						//getchar();
						break;
						
					case 'b':
					case 'B':
						printf("\n			|     请输入地区：");
						scanf("%s",data.area);
						break;
					case 'c':
					case 'C':
						printf("\n			|     请选择剧目类型：");
						printf("\n			-------[1].电影------------[2].戏曲-------------[3].话剧---------");
						while(1){
							er=0;
							printf("\n			Iput Your choice:");
							choice=l_getc();
							switch(choice){
								case '1': data.type= PLAY_TYPE_FILE;   break;
								case '2': data.type=PLAY_TYPE_OPEAR;   break;
								case '3': data.type=PLAY_TYPE_DRAMA; break;
								default : er=1; 
									printf("\n			                      **您的选择有误！请重新选择!**     ");
							}
							if(er!=1) break;
						}
					case 'd':
					case 'D':
						printf("\n			|     请选择剧目风格:");
						printf("\n			-------[1].文艺------------[2].激烈------------[3].重口-----------");
						while(1){
							er=0;
							choice=l_getc();
							switch(choice){
								case '1': data.rating= PLAY_RATE_ART;   break;
								case '2': data.rating= PLAY_RATE_ACUTE; break;
								case '3': data.rating= PLAY_RATE_HARD;break;
								default : er=1; 
									printf("\n			                      **您的选择有误！请重新选择!**     ");
							}
							if(er!=1) break;
						}
				
					case 'e':
					case 'E':
						printf("\n			|     请输入剧目时长(min)：");
						while(1){
							if(scanf("%d",&(data.duration))==1){ cl_stdin(); break;}
							else{ cl_stdin(); 
								printf("\n			                      **您的选择有误！请重新选择!**     ");}
						}
					case 'f':
					case 'F':
						printf("\n			|     请输入上映时间( 年 月 日)：");
						while(1){
							if(scanf("%d%d%d",&(data.start_date.year), &(data.start_date.month), &(data.start_date.day))==3){            
								 cl_stdin();
								 if(data.start_date.month>12 || data.start_date.day>31||DateCmp(data.start_date, DateNow())==-1){
									printf("\n			                      **您输入的日期有误!请重新输入**     ");
						 			continue;
								 }
								 break;
							}
							else{ cl_stdin(); printf("\n			                        **您的输入有误!请重新输入**     "); }
						}
		
						break;
						
					case 'g':
					case 'G':
						printf("\n			|     请输入下线时间( 年  月日)：");
						while(1){
							if(scanf("%d%d%d",&(data.end_date.year), &(data.end_date.month), &(data.end_date.day))==3){
						 		cl_stdin();
						 		if(data.end_date.month>12 || data.end_date.day>31){
						 			printf("\n			                      **您输入的日期有误!请重新输入**     ");
						 			continue;
						 		}
								 if(DateCmp(data.end_date,data.start_date)==-1){
						 			printf("\n			               **您输入的『下线』时间早于『上映』时间！请重新输入！**   ");
						 			continue;	 
						 		}
						 		break;
							}
							else{ cl_stdin(); printf("\n			                        **您的输入有误!请重新输入**     "); }
						}
						break;
						
					case 'h':
					case 'H':
						printf("\n			|     请输入票价：");
						while(1){
							if(scanf("%d",&(data.price))==1){ cl_stdin(); break;}
							else{ cl_stdin(); printf("\n			                        **您的输入有误!请重新输入**     "); }
						}	
						break;
				}
				printf("\n			==================================================================");				
				if(Play_Srv_Modify(&data)){
					printf("\n			------------------------修改剧目成功！--------------------------");
					ret=1;
				}else{
					printf("\n			------------------------修改剧目失败！--------------------------");
				}
				printf("\n			==================================================================");
		}
		
	}//最开始的if  
    else{
		
		printf("\t\t\t                       **没有剧目信息！**                             ");
       	        printf("\n			-----------------------------------------------------------------");
                printf("\n			=================================================================");
		cl_stdin();
        sleep(1);
		return 0;
	}
	
	
       return ret;
}

int Play_UI_Delete(int id){
	play_t data;
	char choice;
	int ret=0;
       if(Play_Srv_FetchByID(id, &data)){
           cl_stdin;
       		system("clear");
       		
       		printf("\n			==================================================================");
        	printf("\n			***************************删除剧目*******************************");
          	printf("\n			==================================================================");
       		printf("\n			|     ID：  %-5d                                                  ",data.id);
	     	printf("\n			|     名称：%-20s                                                 ",data.name);
		 switch(data.type){
                case PLAY_TYPE_FILE:
			printf("\n			|     类型：电影                                                  ");
                case PLAY_TYPE_OPEAR:
			printf("\n			|     类型：戏剧                                                  ");
                case PLAY_TYPE_DRAMA:
			printf("\n			|     类型：舞台剧                                                ");
            }
            switch(data.rating){
                case PLAY_RATE_ART:
			printf("\n			|     风格：文艺                                                  ");
                case PLAY_RATE_ACUTE:
			printf("\n			|     风格：轻松                                                  ");
                case PLAY_RATE_HARD:
		    printf("\n			|     文艺：重口                                                  ");
            }
            printf("\n			|     地区：%-8s                                                   ",data.area);
		printf("\n			|     时长：%5d                                                    ",data.duration);
		printf("\n			|     上映日期：%4d-%02d-%02d                                      ",data.start_date.year,data.start_date.month,data.start_date.day);
		printf("\n			|     下映日期：%4d-%02d-%02d                                      ",data.end_date.year,data.end_date.month,data.end_date.day);
		printf("\n			|     票价：%-5d                                                   ",data.price);			
       		printf("\n			==================================================================");
       		printf("\n			|            [D]elete            |             [R]eturn           |");
        	printf("\n			******************************************************************");
        	printf("\n			Iput Your choice:");
		while(1){
			choice=l_getc();
	
			if('r'==choice || 'R'==choice) break;
			else if('d'==choice || 'D'==choice){
			
					if(Play_Srv_DeleteByID(id)){
						printf("\n			------------------------删除剧目成功！--------------------------");
						ret=1;
					}else{
						printf("\n			------------------------删除剧目失败！--------------------------");
					}
			
			getchar();
			}else{
				printf("\n			                      **您的输入有误！请重新输入!**     ");
			}
			printf("\n			==================================================================");
		}
	}// 最开始的if
    else{
		printf("\t\t\t                       **没有剧目信息！**                             ");
       	printf("\n			-----------------------------------------------------------------");
	    sleep(1);
        return 0;
    }
				
			
       		
       		
       return ret;
}
