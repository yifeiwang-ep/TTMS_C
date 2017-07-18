/*
 *account.h
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

//定义枚举类型account_type，administrator 系统管理员，manager 经理，clerk 售票员
typedef enum {
	USR_ANOMY = 0,  //匿名
	USR_CLERK =1,   //销售员
	USR_MANG = 2,   //经理
	USR_ADMIN = 9   //系统管理员
} account_type_t;

typedef struct {
	int  id;//用户id
	account_type_t type;//用户类型
	char username[30];//用户名
	char password[30];//用户密码
} account_t;

//双向链表
typedef struct account_node {
	account_t data;
	struct account_node *next, *prev;
} account_node_t, *account_list_t;



void Account_Srv_InitSys();

int Account_Srv_Verify(char usrName[], char pwd[]);

inline int Account_Srv_Add(const account_t *data);

inline int Account_Srv_Modify(const account_t *data);

inline int Account_Srv_DeleteByID(int usrID);

inline int Account_Srv_FetchByID(int usrID, account_t *buf);

inline int Account_Srv_FetchByName(char usrName[], account_t *buf);

inline int Account_Srv_FetchAll(account_list_t list);

account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]);


#endif //ACCOUNT_H_
