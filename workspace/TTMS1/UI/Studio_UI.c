/*************************************************************************
	> File Name: test.c
	> Author:wyf 
	> Mail: catherine199787@outlook.com
	> Created Time: Thu 16 Jun 2016 13:58:27 CST
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include"Studio_UI.h"
#include"../Common/ComFunction.h"
#include"../Service/Studio.h"
#include"../Common/list.h"
#include"../Service/Seat.h"
#include"../Service/EntityKey.h"
#include"Seat_UI.h"

static const int  STUDIO_PAGE_SIZE=5;

void Studio_UI_MgtEntry(int flag){
    int i,id;
    char choice;
    studio_list_t head;
    head = (studio_list_t)malloc(sizeof(studio_node_t));
    head->prev = head->next = head;
    studio_node_t *pos;
    Pagination_t paging;
    paging.offset=0;
    paging.pageSize=STUDIO_PAGE_SIZE;
    paging.totalRecords=Studio_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head,paging);
    do{
        system("clear");
        printf("\n\n\n\t\t\t==================================================================");
        printf("\n\t\t\t*************************演出厅列表*******************************");
        printf("\n\t\t\t==================================================================");
        printf("\n\t\t\t%s\t%s\t\t%s\t\t%s\t\t%s","ID","ROOM","SIZE","MODE","SEAT");
        printf("\n\t\t\t-----------------------------------------------------------------");
        //改变了数据类型，注意！汉字的输入会导致格式问题
		for (i = 0, pos = (studio_node_t *) (paging.curPos);pos != head && i < paging.pageSize; i++){
           // printf("\n%d--%d\n",strlen(pos->data.MOD),strlen(pos->data.SEAT));
            printf("\n\t\t\t%-8d%-16s%-16s%-16s%-10s\n",pos->data.id,pos->data.ROOM,pos->data.SIZE,pos->data.MOD,pos->data.SEAT);
            pos= pos->next;
        		}
   
        printf("\n		\t==================================================================");
        printf("\n		\t|----------总数%2d------------------------------%2d/%2d页-----------|",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
        printf("\n		\t==================================================================");
        printf("\n		\t******************************************************************");
        printf("\n\t\t\t[P]revPage|[N]extPage |[A]dd |[D]elete |[U]pdate |[S]eat |[R]eturn");
        printf("\n		\t******************************************************************");
        printf("\n\t\t\tYour choice:");
        scanf("%c",&choice);
        switch(choice){            
	        case 'p':
            case 'P':
            system("clear");
	        if(1<Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,-1,studio_node_t);
            }
            break;
            case 'n':
            case 'N':
            system("clear");
            if(Pageing_TotalPages(paging)>Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,1,studio_node_t);
            }
            break;
            case 'A':
            case 'a':
            system("clear");
            if(Studio_UI_Add()){
                paging.totalRecords=Studio_Srv_FetchAll(head);
                Paging_Locate_LastPage(head,paging,studio_node_t);
            }
            break;
            case 'd':
            case 'D':
            getchar();
            printf("\t\t\tInput the Room ID:");
            
        scanf("%d",&id);
            if(Studio_UI_Delete(id)){
                paging.totalRecords=Studio_Srv_FetchAll(head);
                List_Paging(head,paging,studio_node_t);
            }
            break;
            case 'u':
            case 'U':
            getchar();
            printf("\t\t\tInput the Room ID:");
            scanf("%d",&id);
            system("clear");
            if(Studio_UI_Modify(id)){
                paging.totalRecords=Studio_Srv_FetchAll(head);
                List_Paging(head,paging,studio_node_t);
            }
            break;
            case 's':
            case 'S':
            getchar();
            printf("\t\t\tInput the Room ID:");
            scanf("%d",&id);
            system("clear");
            Seat_UI_MgtEntry(id,flag);
            paging.totalRecords=Studio_Srv_FetchAll(head);
            List_Paging(head,paging,studio_node_t);
            break;  
        }
    }while(choice !='r'&& choice !='R');     //必须&&
    List_Destroy(head,studio_node_t);
}

int Studio_UI_Add(void){
    studio_t rec;
    int newRecCount =0;
    char choice;
    getchar();
    do{
        printf("\n\n\n		\t==================================================================");
        printf("\n		\t*************************添加演出厅*******************************");
        printf("\n		\t==================================================================");
        printf("\n		\t|     姓名：");
        gets(rec.ROOM);
        printf("\n		\t|     规模：");
        gets(rec.SIZE);
        printf("\n		\t|     类型：");
        gets(rec.MOD);
        printf("\n		\t|     座椅类型：");
        gets(rec.SEAT);
        printf("\n		\t|     座位行数:");
        scanf("%d",&rec.rowsCount);
        printf("\n\t		|     座位列数：");
        scanf("%d",&rec.colsCount);
        getchar();        
        rec.seatsCount = rec.rowsCount*rec.colsCount;
     //   printf("\n%d\n",rec.seatsCount);     检测
        printf("\n\t		==================================================================");
		rec.id = EntKey_Srv_CompNewKey("Studio");
        if(Studio_Srv_Add(&rec)){
            newRecCount+=1;
            printf("\n\t		------------------------添加演出厅成功！--------------------------");
        }
        else{
            printf("\n\t		------------------------添加演出厅失败！--------------------------");   
        }
        printf("\n\t		==================================================================");
        printf("\n\t		|         [A]dd More               |             [R]eturn        |");
        printf("\n\t		******************************************************************");
        printf("\n\t		Input Your choice:");
        scanf("%c",&choice);
        system("clear");
        getchar();
    }while('a'==choice||'A'==choice);
    return newRecCount;
}

int Studio_UI_Modify(int id){
    studio_t rec;  int rtn=0;
    char size;
    int newrow,newcolumn;
    seat_list_t list;
    int seatcount=1;
    getchar();
    if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t                         **没有演出厅信息！**          ");
       	printf("\n\t		-----------------------------------------------------------------");
        printf("\n\t		=================================================================");     	
		sleep(1);
        system("clear");
		return 0;
	}
    printf("\n\n\n\t		=================================================================");
	printf("\n\t		*****************************更新演出厅**************************");
    printf("\n\t		=================================================================");
	printf("\n\t		|演出厅ID:%-5d                                                  |", rec.id);
    printf("\n\t		|演出厅名:%-20s                                 |", rec.ROOM);
	printf("\n\t		|演出厅规模:%-10s                                         |", rec.SIZE);
    printf("\n\t		-----------------------------------------------------------------");
	//List_Init(list, seat_node_t);
         printf("\n\t\t\t|目前座位行数为：[%d]                                            |", rec.rowsCount);
            printf("\n\t\t\t请输入更新的座位行数：");
			scanf("%d", &(newrow));
			printf("\t\t\t|目前座位列数为：[%d]                                           |", rec.colsCount);
            printf("\n\t\t\t请输入更新的座位列数：");
			scanf("%d", &(newcolumn));
        
		rec.rowsCount=newrow;
		rec.colsCount=newcolumn;
		rec.seatsCount=seatcount;
    printf("\n\t		=================================================================");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
	        printf("\n\t\t\t                         ** 更新完毕!** ");
       	        printf("\n\t		-----------------------------------------------------------------");
                printf("\n\t		=================================================================");       
	} else{
	        printf("\n\t\t\t                         ** 更新失败!** ");
       	        printf("\n\t		-----------------------------------------------------------------");
                printf("\n\t		=================================================================");       
		}
	sleep(1);
	return rtn;
}

int Studio_UI_Delete(int id) {
	int rtn = 0;
	if (Studio_Srv_DeleteByID(id)) {
		          printf("\t\t\t                     **演出厅删除完毕！**  ");
       	        printf("\n\t		-----------------------------------------------------------------");
                printf("\n\t		=================================================================");     	
		
		rtn = 1;
	} else {
		          printf("\n\n\t\t\t                      **演出厅不存在！**   ");
       	        printf("\n\t\t\t-----------------------------------------------------------------");
                printf("\n\t		=================================================================");   
	}
    
    sleep(1);
    return rtn;
}
