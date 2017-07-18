/*
 * account.c
 *
 *  Created on: 2015年6月12日
 *      Author: Administrator
 */
#include "Account.h"
#include "EntityKey.h"
#include "../Common/list.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>
#include<stdio.h>

extern account_t gl_CurUser;

//创建系统初始化账号admin
void Account_Srv_InitSys(){
	char entName[8];
	if(Account_Perst_CheckAccFile());
	else
		{
			account_t data_admin;
			data_admin.id=EntKey_Srv_CompNewKey(entName);//调用函数获取用户id
			scanf("%s",data_admin.username);//为data_admin账号赋值成员信息 
			scanf("%d",&data_admin.type);
			scanf("%s",data_admin.password);
			Account_Srv_Add(&data_admin);//将新建data_admin账号写入文件 
		}

}

//验证登录账号是否已存在，存在，保存登录用户信息到全局变量gl_CurUser，return 1；否则return 0
inline int Account_Srv_Verify(char usrName[], char pwd[]){
	account_t usr;
	int n=0;
	
	if(Account_Perst_SelByName(usrName,&usr))
	{
		if(strcmp(pwd,usr.password)==0){
			n=1;
			gl_CurUser.id=usr.id;
			strcpy(gl_CurUser.password,usr.password);
			gl_CurUser.type=usr.type;
			strcpy(gl_CurUser.username,usr.username);
		}
	}
	return n;
}

//验证用户名是否存在，遍历list，若存在，返回对应结点指针；否则，返回null
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {
	assert(NULL!=list);//如果它的条件返回错误，则终止程序的执行 
	account_node_t *pos=list->next;
	while(pos!=list){
		if(pos->data.username==usrName)
			return pos;
		else
			return NULL;
	} 
}

//添加一个用户账号，通过调用Account_Perst_Insert(data)函数实现
inline int Account_Srv_Add(const account_t *data){
	 return Account_Perst_Insert(data);	 
}

//修改一个用户账号，通过调用Account_Perst_Update(data)函数实现
inline int Account_Srv_Modify(const account_t *data){
	return Account_Perst_Update(data);
}

//删除一个用户账号，通过调用Account_Perst_DeleteByID(usrID)函数实现
inline int Account_Srv_DeleteByID(int usrID){
	return Account_Perst_DeleteByID(usrID);	
}

//提取usrID对应的用户账号信息，通过调用Account_Perst_SelectByID(usrID, buf)函数实现
inline int Account_Srv_FetchByID(int usrID, account_t *buf){
	return Account_Perst_SelectByID(usrID, buf);	
}

//提取usrName对应的用户账号信息，通过调用Account_Perst_SelByName(usrName, buf)函数实现
inline int Account_Srv_FetchByUsrName(char usrName[], account_t *buf){
	return Account_Perst_SelByName(usrName, buf);
}

//提取所有用户账号信息，保存到list链表中，通过调用Account_Perst_SelectAll(list)函数实现
inline int Account_Srv_FetchAll(account_list_t list){
	return Account_Perst_SelectAll(list);
}

