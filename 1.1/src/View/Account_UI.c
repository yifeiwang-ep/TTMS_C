/*
 * Account_UI.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include "Account_UI.h"

#include "../Common/List.h"
#include "../Common/ComFunction.h"
#include "../Service/Account.h"
#include "../Service/EntityKey.h"
#include "Account_UI.h"

#include <stdio.h>
#include<assert.h>
#include<string.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_TIMES 3

extern account_t gl_CurUser;

int SysLogin() {
	
	
	int i=MAX_TIMES;
	char uname[30],pwd[30];
	
	Account_Srv_InitSys();
	
	while(i--){
		system("clear");
		
	       	printf("\t\t***************************************************************************************\n\n");
       		printf("\t\t--------------------------------------用户 登录-----------------------------------------\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		
       		
       		printf("\t\t\t\t用户名:");
       		scanf("%s",uname);
       		
       		printf("\t\t\t\t密  码:");
       		cl_stdin();
       		getpwd(30,pwd); //input passwd
       		
		
		if(Account_Srv_Verify(uname,pwd)){
			printf("\n\n\n\n\n\n\n\n\n\n\n\t\t	--------------------------\033[31m% 登录成功 \033[0m次-----------------------------",i);
			
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

int SysLogout() {
	
	
	int choice;
	
	
       	printf("\t\t\t=======================================================================================\n\n");
       		
       		
       	printf("\t\t\t\t当前用户为:%s\n",gl_CurUser.username);
        choice=prom("\t\t\t\t真的要注销吗？",'y','n');
        if(1==choice){
	       	if(Account_Srv_Logout()){
				printf("\n\n\t\t\t注销成功!请稍后....\n");
				sleep(1);
				return 1;
		}else{
				printf("\n\t\t\t注销失败，请稍后重试!\n");
				
				sleep(1);
				return 0;
				   
		}
	}
	return 0;
		
}

void Change_Passwd(){
	char oldpwd[30],newpwd[30],newpwd1[30];
	account_t data=gl_CurUser;
	int i=MAX_TIMES,q=0;
	system("clear");
		
	       	printf("\t\t=======================================================================================\n\n");
       		printf("\t\t\t------------------------------------用户 密码修改-------------------------------------\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		
       		
       		printf("\t\t\t\t当前用户为:%s\n",gl_CurUser.username);
       		
       		
       		printf("\t\t\t\t请输入原始密码:");
       		cl_stdin();
       		
       		while(i--){
	       		getpwd(30,oldpwd); //input passwd
	       		
	       		if( strcmp(oldpwd,gl_CurUser.password)==0 ){
	       			q=1;
	       			break;
	       		}else{
	       		
		       		if(i>0){  
					printf("\n\t\t\t\t用户名或密码输入错误!\n");
					printf("\n\t\t\t\t您还有%d次机会!",i);
					
				}
			}
		}
		while(q){
				printf("\n\t\t\t\t请新密码：");
				//cl_stdin();
				getpwd(30,newpwd);
				printf("\n\t\t\t\t请再次输入新密码：");
							
				getpwd(30,newpwd1);
				if( strcmp(newpwd,newpwd1)==0 ){
						strcpy(data.password,newpwd);
						
						if(Account_Srv_Modify(&data)){
							gl_CurUser=data;
							printf("\n\n\t\t\t密码修改成功!请稍后....\n");
			
						}else{

							printf("\n\n\t\t\t密码修改失败!请稍后重试....\n");
						}
						
						break;
				}else{
							
						printf("\n\t\t\t两次密码输入不一致！请重新输入：");
				}
		}
		
		printf("\n\t\t\t按任意键继续。");
		
		getchar();
	

}


//管理系统用户功能入口函数，显示用户账号管理菜单
void Account_UI_MgtEntry() {
	
	int i;
	char choice,uname[30];

	account_list_t head;
	account_node_t *p;
	Pagination_t paging;

	List_Init(head, account_node_t);
	
	paging.offset = 0;
	paging.pageSize = ACCOUNT_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Account_Srv_FetchAll(head);
	
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		
		printf("\n\t\t=====================================================================================\n\n");
		printf("\t\t*********************************** 用户 列表 ****************************************\n\n");
		printf("\t\t\t\t%s\t\t%s\t\t%s\n", "ID", "用户类型", "用户名");
		printf("\t\t----------------------------------------------------------------------------------------\n\n");
		
		
		//显示数据
		Paging_ViewPage_ForEach(head, paging, account_node_t, p, i){
			printf("\t\t\t\t%d\t\t", p->data.id);
			
			switch(p->data.type){
				case USR_CLERK:  printf("%12s\t\t ","销售员"); 	break;
				case USR_MANG:	 printf("%10s\t\t","经理");  	break;
				case USR_ADMIN:  printf("%10s\t\t","系统管理员"); 	break;
			
			
			}
			//销售员  经理  系统管理员 

			printf("%s\n", p->data.username);
		}

		printf("\n\t\t--------------- 共:%2d条数据 -------------------------- 页码： %2d/%2d --------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t*************************************************************************************\n\n");
		printf("\t\t=============[Q]查询====================[P]上页================[N]下页===============\n\n");
		
	
		printf("\t\t==========[A]新增=========[D]删除===========[U]修改 ===================[R]返回=======\n");
		
		
		printf("\n\n\t\t=====================================================================================\n");
		printf("\t\t请选择:");
		
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
			
			printf("\t\t请输入要删除的用户名:");
			scanf("%s",uname);
			
			
			
			if (Account_UI_Delete(uname)) {	//从新载入数据
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
			}
			
			break;
		
		case 'u':
		case 'U':
			
			printf("\t\t请输入要修改用户的用户名:");
			scanf("%s",uname);
			
			
			if (Account_UI_Modify(uname)) {	//从新载入数据
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
			}
			
			break;
			
		case 'q':
		case 'Q':
			//Account_UI_Query();
			break;
			
		
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1,account_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
			}
			break;
		
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, account_node_t);
	
	
}


//添加一个用户账号信息
int Account_UI_Add() {
	
	int er=0,newRecCount=0;
       		char choice;
		account_t data,buf;	
		do { 

				system("clear");
				
				printf("\t\t\t========================================================================\n\n");
       				printf("\t\t\t----------------------------新添 用户-------------------------------\n\n");
       				printf("\t\t\t========================================================================\n\n");
       				
				data.id = EntKey_Srv_CompNewKey("user");
				
				printf("\t\t\t请输入用户名：");
				while(1){
					scanf("%s",data.username);
					if( Account_Srv_FetchByName(data.username,&buf) ) {
						printf("\t\t\t用户名已存在，请重新输入！\n\t\t\t");
					}else break;
				}
		
				printf("\t\t\t请输入用户密码：");
				scanf("%s",data.password);
				
				printf("\t\t\t请选择用户类型：\n\t\t\t==[1].销售员====[2].经理====[3].系统管理员==\n\t\t\t");
				while(1){
					er=0;
					choice=l_getc();
					switch(choice){
						case '1': data.type= USR_CLERK;  	break;
						case '2': data.type= USR_MANG;   	break;
						case '3': data.type= USR_ADMIN; 	break;
						default : er=1; printf("\t\t\t您的选择有误！请重新选择。\n\t\t\t");
					}
					if(er!=1) break;
				}
			
				
				if(Account_Srv_Add(&data)){
					newRecCount++;
					printf("\t\t\t添加成功！\n");
				}else{
					
				}
				printf("\t\t\t===== [A]继续添加 ==== [R]返回=====:");
		
				choice=l_getc();
		} while ('a' == choice || 'A' == choice);
	return newRecCount;
	
}

//根据用户账号名修改用户账号密码，不存在这个用户账号名，提示出错信息
int Account_UI_Modify(char usrName[]) {
       		int er=0,ret=0,q=0;
       		char choice;
		account_t data;	
		if( Account_Srv_FetchByName(usrName,&data) ){
			if(gl_CurUser.id==data.id){
				printf("\t\t\t\t无法修改自己的信息！按任意键返回。。。");
				cl_stdin();
				getchar();
				return 0;
			}
			while(1) { 

				system("clear");
				printf("\t\t\t========================================================================\n\n");
       				printf("\t\t\t\t----------------------------修改 用户-------------------------------\n\n");
       				printf("\t\t\t========================================================================\n\n");
       				printf("\t\t\t%5s \t %10s \t %20s \n", "ID", "用户类型", "用户名");
				printf("\t\t\t-------------------------------------------------------------------------\n\n");
		
				printf("\t\t\t%5d\t ", data.id);
			
				switch(data.type){
					case USR_CLERK:  printf("%10s","销售员"); 	break;
					case USR_MANG:	 printf("%10s","经理");  	break;
					case USR_ADMIN:  printf("%10s","系统管理员"); 	break;
				}
				printf("\t%20s\n", data.username);
				printf("\n\t\t\t-------------------------------------------------------------------------\n\n");
				printf("\t\t\t========================================================================\n\n");
				printf("\t\t\t====[A]修改用户类型===========[B]重置用户密码============[R]返回==========\n\n");
				printf("\t\t\t========================================================================\n\n");
				printf("\t\t\t\033[31m 该功能涉及系统安全，请谨慎操作！\033[0m\n");
				
				printf("\t\t\t请选择:");
			
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				switch(choice){
					
						
					case 'b':
					case 'B':
						{
						char fpwd[30],spwd[30];
						while(1){
							printf("\n\t\t\t请输入用户密码：");
							cl_stdin();
							getpwd(30,fpwd);
							printf("\n\t\t\t请再次输入用户密码：");
							
							getpwd(30,spwd);
							if( strcmp(fpwd,spwd)==0 ){
								strcpy(data.password,fpwd);
								q=1;
								break;
							}else{
							
								printf("\n\t\t\t两次密码输入不一致！请重新输入：");
							}
						}
						}
						break;
						
					case 'a':
					case 'A':
						printf("\t\t\t请选择用户类型：\n\t\t\t==[1].销售员====[2].经理====[3].系统管理员==\n\t\t\t");
						while(1){
							er=0;
							choice=l_getc();
							switch(choice){
								case '1': 
									
									if(data.type!= USR_CLERK){
										data.type= USR_CLERK;
									}else{
										printf("\n\t\t\t类型相同，不用修改！");
									} 	
									break;
									
								case '2': 
								
									if(data.type!= USR_MANG){
										data.type= USR_MANG;
										q=1;
									}else{
										printf("\n\t\t\t类型相同，不用修改！");
										q=0;
									} 	
									break;
								case '3': 
								
									if(data.type!= USR_ADMIN){
										data.type= USR_ADMIN;
										q=1;
									}else{
										printf("\n\t\t\t类型相同，不用修改！");
										q=0;
									} 	
									break;
								default : er=1; printf("\n\t\t\t您的选择有误！请重新选择。\n\t\t\t");
							}
							if(er!=1) break;
						}
						break;
					}
			
				
				if(q && Account_Srv_Modify(&data)){
					printf("\n\t\t\t修改成功！\n");
					ret=1;
				}else{
					if(q!=0) printf("\n\t\t\t修改失败！\n");
				}
				
				printf("\n\t\t\t按任意键继续。。。");
				cl_stdin();
				getchar();
		
		}
       
       }else{
       		printf("\n\t\t\t未找到！");
       		printf("\n\t\t\t按任意键返回。。。");
		cl_stdin();
		getchar();
       	}
       
       return ret;
}

//根据用户账号名删除一个已经存在的用户账号信息，如果不存在这个用户账号名，提示出错信息
int Account_UI_Delete(char usrName[]) {

		int ret=0;
       		char choice;
		account_t data;	
		if( Account_Srv_FetchByName(usrName,&data) ){
			if(gl_CurUser.id==data.id){
				printf("\t\t\t\t无法删除自己的信息！按任意键返回。。。");
				cl_stdin();
				getchar();
				return 0;
			}
			while(1){
				system("clear");
				
				printf("\t\t\t========================================================================\n\n");
       				printf("\t\t\t\t----------------------------删除 用户-------------------------------\n\n");
       				printf("\t\t\t========================================================================\n\n");
       				printf("\t\t\t%5s \t %10s \t %20s \n", "ID", "用户类型", "用户名");
				printf("\t\t\t-------------------------------------------------------------------------\n\n");
		
				printf("\t\t\t%5d ", data.id);
			
				switch(data.type){
					case USR_CLERK:  printf("%10s","销售员"); 	break;
					case USR_MANG:	 printf("%10s","经理");  	break;
					case USR_ADMIN:  printf("%10s","系统管理员"); 	break;
				}
				printf("\t%20s\n", data.username);
				printf("\n\t\t\t-------------------------------------------------------------------------\n\n");
				printf("\t\t\t========================================================================\n\n");
				printf("\t\t\t====[A]确认删除用户=====================================[R]返回==========\n\n");
				printf("\t\t\t========================================================================\n\n");
				printf("\t\t\t\033[31m 该功能涉及系统安全，请谨慎操作！\033[0m\n");
				
				printf("\t\t\t请选择:");
			
				choice=l_getc();
				if('r'==choice || 'R'==choice) break;	
				
				if('a'==choice || 'A'==choice){
					
					if(Account_Srv_DeleteByID(data.id)){
						printf("\n\t\t\t删除成功！\n");
						ret=1;
					}else{
						 printf("\n\t\t\t删除失败！\n");
					}
				
					printf("\n\t\t\t按任意键继续。。。");
					
					getchar();
				}
			}
		
		
       
       }else{
       		printf("\n\t\t\t未找到！");
       		printf("\n\t\t\t按任意键返回。。。");
		cl_stdin();
		getchar();
       	}
       
       return ret;
}
//根据用户账号名查找该用户账号是否存在，存在返回1，否则返回0，并提示错误信息
int Account_UI_Query(char usrName[]) {
	account_t data;
	if( Account_Srv_FetchByName(usrName,&data) ){
		return 1;
	}
	printf("\n\t\t\t该用户不存在！");
	return 0;
}


