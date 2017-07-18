/*
 *  account.c
 *
 *  Created on: 2015年6月12日
 *      Author: Administrator
 */
#include "Account.h"
#include "EntityKey.h"
#include "../Common/List.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>

extern account_t gl_CurUser;

//创建管理员Admin账号服务
void Account_Srv_InitSys(){
	account_t *buf=(account_t *)malloc(sizeof(account_t));
	if(!Account_Perst_SelByName("admin", buf))
	{
		buf->type = 9;
		strcpy(buf->username,"admin");
		strcpy(buf->password,"000000");
		Account_Perst_Insert(buf);
	}
}

//验证用户账号密码服务
inline int Account_Srv_Verify(char usrName[], char pwd[]){
	account_t buf;
	if(!Account_Perst_SelByName(usrName, &buf))
	{
		return 0;
	}
	if(strcmp(pwd,buf.password)!=0)
	{
		return 0;
	}
	return buf.type;
}


//根据用户名查找用户信息
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {
	account_list_t curPos;
	List_ForEach(list, curPos)
	{
		if(strcmp(curPos->data.username , usrName)==0)
		{
			return curPos;
		}	
	} 
       return NULL;
}

//添加系统用户服务
inline int Account_Srv_Add(const account_t *data){
	return Account_Perst_Insert(data);
}

//根据usrName修改系统用户密码服务
inline int Account_Srv_Modify(const account_t *data){
	return Account_Perst_Update(data);
}

//根据id删除系统用户服务
inline int Account_Srv_DeleteByID(int usrID){
	return Account_Perst_DeleteByID(usrID);
}

//根据id获取系统用户服务
inline int Account_Srv_FetchByID(int usrID, account_t *buf){
	return Account_Perst_SelectByID(usrID, buf);
}

//根据名称获取系统用户服务
inline int Account_Srv_FetchByName(char usrName[], account_t *buf){
	return Account_Perst_SelByName(usrName,buf);
}

//获取所有系统用户服务
inline int Account_Srv_FetchAll(account_list_t list){
	return Account_Perst_SelectAll(list);
}

