/*
  * Account_UI.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include "Account_UI.h"
#include "../Common/list.h"
#include "../Service/Account.h"
#include "../Service/EntityKey.h"
#include "Account_UI.h"
#include<string.h>
#include <stdio.h>
#include<assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "../Common/ComFunction.h"
#define MAX_TIMES  3
//static const int  ACCOUNT_PAGE_SIZE=5;

extern account_t gl_CurUser;

int SysLogin() {
	
	
	int i=MAX_TIMES;
	char uname[30],pwd[30];
	
	Account_Srv_InitSys();
	
	while(i--){
		system("clear");
        printf("\n\n\n	\t\t==================================================================");
        printf("\n	\t\t***************************用户登陆********************************");
        printf("\n	\t\t==================================================================");
        printf("\n\n\n\t\t\t\t\t\t用户名:");
       	scanf("%s",&uname);
       	printf("\n\t\t\t\t\t\t密  码:");
       	cl_stdin();
       	getpwd(30,pwd); //input passwd	
		if(Account_Srv_Verify(uname,pwd)){ 
			return 1;
		}else{

			if(i>0){  
            system("clear");
printf("\n\n\n\n\n\n\n\n\n\n\n\t\t	--------------------用户名或密码错误！还可以输入\033[31m%d\033[0m次----------------------",i);
				sleep(1.5);
			}
			   
		}
	}
		return 0;
       		
}

void Passwd(){
	char oldpwd[30],newpwd[30],newpwd1[30];
	account_t data=gl_CurUser;
	int i=MAX_TIMES,q=0;
	system("clear");
        printf("\n	\t\t==================================================================");
        printf("\n	\t\t***************************密码修改********************************");
        printf("\n	\t\t==================================================================");
        printf("\n	\t\t|	当前用户为:%s",gl_CurUser.username);
       	cl_stdin();      		
       		while(i--){
       	        printf("\n	\t\t|	旧密码:");
	       		getpwd(30,oldpwd); //input passwd
	       		
	       		if( strcmp(oldpwd,gl_CurUser.password)==0 ){
	       			q=1;
	       			break;
	       		}else{
	       		
		       		if(i>0){  
					printf("\n	\n		------------用户名或密码错误！还可以输入%d次-------------",i);
					sleep(1);
                    }
		        }
            }
		while(q){
				 	printf("\n	\t\t|	新密码:");
				//cl_stdin();
				getpwd(30,newpwd);
				 	printf("\n	\t\t|	再输一次:");
							
				getpwd(30,newpwd1);
				if( strcmp(newpwd,newpwd1)==0 ){
						strcpy(data.password,newpwd);
						
						if(Account_Srv_Modify(&data)){
							gl_CurUser=data;
							printf("\n			----------------------------修改成功！------------------------------");
			
						}else{

							printf("\n			----------------------------修改失败！------------------------------");
						}
						
						break;
				}else{
							
						printf("\n	\n		-----------------两次新密码输入不一致！-------------------------");
					sleep(1);
				}
		}
		
		sleep(1);
	

}


//管理系统用户功能入口函数，显示用户账号管理菜单
void  Account_UI_MgtEntry(int flag) {
	
	int i,id;
	char choice,uname[30];
	account_list_t head;
	Pagination_t paging;
	List_Init(head, account_node_t);
	account_node_t *p;
	paging.offset = 0;
	paging.pageSize = ACCOUNT_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Account_Srv_FetchAll(head);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n	\t\t==================================================================");
        printf("\n	\t\t***************************用户管理********************************");
        printf("\n	\t\t==================================================================");
		printf("\n	\t\t\t%s\t\t%s\t\t%s", "ID", "用户类型", "用户名");
		printf("\n	\t\t------------------------------------------------------------------");
		
		
		//显示数据
		for (i = 0, p = (account_node_t *) (paging.curPos);
						p != head && i < paging.pageSize; i++){
			printf("\n	\t\t\t%d\t\t", p->data.id);
			
			switch(p->data.type){
				case USR_CLERK:  printf("%s\t\t\t","CLERK"); 	break;
				case USR_MANG:	 printf("%s\t\t\t","MANG");  	break;
				case USR_ADMIN:  printf("%s\t\t\t","ADMIN"); 	break;
			
			
			}
			//CLERK  MANG  ADMIN 

			printf("%s\n", p->data.username);
            p=p->next;
		}

		
        printf("\n			==================================================================");
        printf("\n			|---------总数%2d------------------------------%2d/%2d页----------|",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
        printf("\n			==================================================================");;
		printf("\n			******************************************************************");
        printf("\n	\t\t[P]revPage|[N]extPage |[A]dd |[D]elete |[U]pdate |[Q]uery |[R]eturn");
        printf("\n			******************************************************************");
        printf("\n	\t\tYour choice:");
		choice=l_getc();
		switch (choice) {
		
		case 'a':
		case 'A':
			if (Account_UI_Add()) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Account_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, account_node_t);
			}
			break;
		
		case 'd':
		case 'D':
			
			printf("\n	\t\t|	用户名:");
			scanf("%s",&uname);
			if (Account_UI_Delete(head,uname)) {	//从新载入数据
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
			}
			
			break;
		
		case 'u':
		case 'U':
			
			printf("\n	\t\t|	用户名:");
			scanf("%s",&uname);
			
			
			if (Account_UI_Modify(head,uname)) {	//从新载入数据
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
			}
			
			break;
			
		case 'q':
		case 'Q':
			Account_UI_Query(head,uname);
			break;
			
		
		case 'p':
		case 'P':
			system("clear");
	        if(1<Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,-1,account_node_t);
            }
			break;
		case 'n':
		case 'N':
			system("clear");
            if(Pageing_TotalPages(paging)>Pageing_CurPage(paging)){
                Paging_Locate_OffsetPage(head,paging,1,account_node_t);
			break;
		
		}

	}} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, account_node_t);
	
	
}


//添加一个用户账号信息
int Account_UI_Add(void) {
	
	int er=0,newRecCount=0;
       		char choice;
		account_t data,buf;	
		do { 

				system("clear");
				printf("\n	\t\t==================================================================");
       			printf("\n	\t\t***************************添加用户********************************");
        		printf("\n	\t\t==================================================================");
       				
                cl_stdin();
				while(1){
				printf("\n	\t\t|	用户名:");
                    gets(data.username);
					if(Account_Srv_FetchByUsrName(data.username,&buf)){
						printf("\t\t           	          **用户已存在！**");
                        //cl_stdin();
					}else break;
				}
		        //cl_stdin();
				printf("\n	\t\t|       密码：");
			gets(data.password);	
            printf("\n			-------[1].CLERK------------[2].MANG-------------[3].ADMAIN--------");
				while(1){
				printf("\n			|     请选择用户类型：");
					er=0;
					choice=l_getc();
					switch(choice){
						case '1': data.type= USR_CLERK;  	break;
						case '2': data.type= USR_MANG;   	break;
						case '3': data.type= USR_ADMIN; 	break;
						default : er=1; printf("\n	\t\t         	           **输入有误！**   ");
					}
					if(er!=1) break;
				}
				data.id = EntKey_Srv_CompNewKey("User");
			
				
				if(Account_Srv_Add(&data)){
					newRecCount++;
					printf("\n			----------------------------添加成功！------------------------------");
				}else{
					printf("\n			----------------------------添加失败！------------------------------");
					
				}
				printf("\n			==================================================================");
       				printf("\n			|         [A]dd More               |             [R]eturn        |");
        			printf("\n			******************************************************************");
        			printf("\n			Input Your choice:");
				choice=l_getc();
        } while ('a' == choice || 'A' == choice);	
        return newRecCount;

}

//根据用户账号名修改用户账号密码，不存在这个用户账号名，提示出错信息
int Account_UI_Modify(account_list_t head,char usrName[]) {
       		int er=0,ret=0,q=0;
       		char choice;
            void Passwd();
            
	Pagination_t paging;
	paging.totalRecords = Account_Srv_FetchAll(head);
		account_t data;	
		if( Account_Srv_FetchByUsrName(usrName,&data) ){
			if(gl_CurUser.id==data.id){
				printf("\n			----------------------------没有权限！------------------------------");
				cl_stdin();
				getchar();
				return 0;
			}
			while(1) { 

				system("clear");
				
				printf("\n	\t\t==================================================================");
       			printf("\n	\t\t***************************修改用户********************************");
        		printf("\n	\t\t==================================================================");
       			printf("\n	\t\t\t%s\t\t%s\t\t%s", "ID", "用户类型", "用户名");
				printf("\n	\t\t------------------------------------------------------------------");
            	printf("\n			             \033[31m**该功能涉及系统安全，请谨慎操作！**\033[0m\n");
				printf("\n	\t\t------------------------------------------------------------------");
				printf("\n	\t\t\t%d\t\t ", data.id);
			
				switch(data.type){
					case USR_CLERK:  printf("%s\t\t\t","CLERK"); 	break;
					case USR_MANG:	 printf("%s\t\t\t","MANG");  	break;
					case USR_ADMIN:  printf("%s\t\t\t","ADMIN"); 	break;
				}
				printf("%-20s", data.username);
				printf("\n			==================================================================");
        		printf("\n			|---------总数%2d------------------------------%2d/%2d页----------|",paging.totalRecords ,Pageing_CurPage(paging),Pageing_TotalPages(paging));
        		printf("\n			==================================================================");;
				printf("\n			******************************************************************");
        		printf("\n	\t\t|	  [T]ype	|	[P]asswd	|	[R]eturn	|");
        		printf("\n			******************************************************************");
        		printf("\n	\t\tYour choice:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				switch(choice){
					
						
					case 'p':
					case 'P':
                        Passwd();
						/*{
						char fpwd[30]spwd[30];
						while(1){
							printf("\n	\t\t|	新密码:");
							cl_stdin();
							getpwd(30,fpwd);
							printf("\n	\t\t|请再次输入新密码：");
							
							getpwd(30spwd);
							if( strcmp(fpwdspwd)==0 ){
								strcpy(data.password,fpwd);
								q=1;
								break;
							}else{
							printf("\n	\n		-----------------两次新密码输入不一致！-------------------------");
							}
						}
						}*/
						break;
						
					case 't':
					case 'T':
						printf("\n			-------[1].CLERK------------[2].MANG-------------[3].ADMAIN--------");
						printf("\n			|     请选择用户类型：");
						while(1){
							er=0;
							choice=l_getc();
							switch(choice){
								case '1': 
									
									if(data.type!= USR_CLERK){
										data.type= USR_CLERK;
									}else{
										printf("\n			----------------------------类型相同！------------------------------");
									} 	
									break;
									
								case '2': 
								
									if(data.type!= USR_MANG){
										data.type= USR_MANG;
										q=1;
									}else{
										printf("\n			----------------------------类型相同！------------------------------");
										q=0;
									} 	
									break;
								case '3': 
								
									if(data.type!= USR_ADMIN){
										data.type= USR_ADMIN;
										q=1;
									}else{
										printf("\n			----------------------------类型相同！------------------------------");
										q=0;
									} 	
									break;
								default : er=1; printf("\n	\t\t        	           **输入有误！**   ");
							}
							if(er!=1) break;
						}
						break;
					}
			
				
				if(q && Account_Srv_Modify(&data)){
					printf("\n			----------------------------修改成功！------------------------------");
					ret=1;
				}else{
					if(q!=0) printf("\n			----------------------------修改成功！------------------------------");;
				}
				cl_stdin();
				sleep(1);
		
		}
       
       }else{
       		printf("\n			----------------------------未找到信息！------------------------------");
		cl_stdin();
		sleep(1);
       	}
       
       return ret;
}

//根据用户账号名删除一个已经存在的用户账号信息，如果不存在这个用户账号名，提示出错信息
int Account_UI_Delete(account_list_t head,char usrName[]) {

		int ret=0;
       		char choice;
		account_t data;	
		if( Account_Srv_FetchByUsrName(usrName,&data) ){
			if(gl_CurUser.id==data.id){
				printf("\n			----------------------------没有权限！------------------------------");
				cl_stdin();
				getchar();
				return 0;
			}
			while(1){
				system("clear");
				
				printf("\n	\t\t==================================================================");
       			printf("\n	\t\t***************************删除用户********************************");
        		printf("\n	\t\t==================================================================");
       			printf("\n	\t\t\t%s\t\t%s\t\t%s", "ID", "用户类型", "用户名");
				printf("\n	\t\t------------------------------------------------------------------");
				printf("\n			          \033[31m**该功能涉及系统安全，请谨慎操作！**\033[0m\n");
				printf("\n	\t\t------------------------------------------------------------------");
				printf("\n	\t\t\t%d\t\t ", data.id);
			
				switch(data.type){
					case USR_CLERK:  printf("%s\t\t\t","CLERK"); 	break;
					case USR_MANG:	 printf("%s\t\t\t","MANG");  	break;
					case USR_ADMIN:  printf("%s\t\t\t","ADMIN"); 	break;
				}
				printf("%20s\n", data.username);
				printf("\n			-----------------------------------------------------------------");
				printf("\n			|          [D]elete          |               [R]eturn           |");
				printf("\n			******************************************************************");
       			 printf("\n			Input Your choice:");
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				
				if('d'==choice || 'D'==choice){
					
					if(Account_Srv_DeleteByID(data.id)){
						printf("\n			----------------------------删除成功！------------------------------");
						ret=1;
					}else{
						 printf("\n			----------------------------删除失败！------------------------------");
					}
				sleep(1);
				}
			}
		
		
       
       }else{
       		printf("\n			----------------------------未找到信息！------------------------------");
		cl_stdin();
		sleep(1);
       	}
       
       return ret;
}
//根据用户账号名查找该用户账号是否存在，存在返回1，否则返回0，并提示错误信息
int Account_UI_Query(account_list_t head,char usrName[]) {
	account_t data;
	if( Account_Srv_FetchByUsrName(usrName,&data) ){
		return 1;
	}
	printf("\n			----------------------------用户不存在！------------------------------");
	return 0;
}



