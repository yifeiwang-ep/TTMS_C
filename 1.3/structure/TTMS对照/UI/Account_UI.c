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
#include<strings.h>
#include <stdio.h>
#include<assert.h>
#include<string.h>
#include <unistd.h>
#include <sys/time.h>

//登录函数，提示用户输入用户名和密码，登录成功return 1，否则提示重新登录，超过3次，登录失败
int SysLogin() {

	return 1;

}

//管理系统用户功能入口函数，显示用户账号管理菜单
void Account_UI_MgtEntry() {

}


//添加一个用户账号信息，如果账号名存在，提示出错信息
int Account_UI_Add(account_list_t list ) {

	return 1;

}

//根据用户账号名修改用户账号密码，不存在这个用户账号名，提示出错信息
int Account_UI_Modify(account_list_t list ,char usrName[]) {

	return 1;
}

//根据用户账号名删除一个已经存在的用户账号信息，如果不存在这个用户账号名，提示出错信息
int Account_UI_Delete(account_list_t list ,char usrName[]) {

	return 1;
}

//根据用户账号名查找该用户账号是否存在，存在返回1，否则返回0，并提示错误信息
int Account_UI_Query(account_list_t  list ,char usrName[]) {


	return 1;
}


