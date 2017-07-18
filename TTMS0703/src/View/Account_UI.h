/*
 * Account_UI.h
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_

#include "../Common/List.h"
#include "../Service/Account.h"

static const int ACCOUNT_PAGE_SIZE = 3;

int SysLogin();
int SysLogout();
void Account_UI_MgtEntry();
int Account_UI_Add();
int Account_UI_Modify(char usrName[]);
int Account_UI_Delete(char usrName[]);
int Account_UI_Query(char usrName[]);


#endif /* ACCOUNT_UI_H_ */

