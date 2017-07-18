/*
 * account.c
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

void Account_Srv_InitSys(){
	if(!Account_Perst_CheckAccFile() ){
	
		account_t data={ 0 , USR_ADMIN , "admin" ,"123456" };
		
		
		data.id=EntKey_Srv_CompNewKey("user");
		
		Account_Perst_Insert(&data);
	}
}

int Account_Srv_Logout(){
	account_t data={0, USR_ANOMY, "Anonymous",""};
	gl_CurUser= data;
	if(gl_CurUser.type==USR_ANOMY){
		return 1;
	}else{
		return 0;
	}
}


int Account_Srv_Verify(char usrName[], char pwd[]){
	account_t data;
	
	if(Account_Perst_SelByName(usrName,&data ) ){
		if(strcmp(pwd,data.password)==0){
			gl_CurUser=data;
			return 1;
		}
	
	} 
	
       return 0;
}



account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {
	// 请补充完整
       return NULL;
}


inline int Account_Srv_Add(const account_t *data){

       return Account_Perst_Insert(data);
}
inline int Account_Srv_Modify(const account_t *data){
	
       return Account_Perst_Update(data);
}
inline int Account_Srv_DeleteByID(int usrID){

       return  Account_Perst_DeleteByID(usrID);
}
inline int Account_Srv_FetchByID(int usrID, account_t *buf){

       return Account_Perst_SelectByID(usrID, buf);
}

inline int Account_Srv_FetchByName(char usrName[], account_t *buf){
	
       return Account_Perst_SelByName(usrName,buf);
}

inline int Account_Srv_FetchAll(account_list_t list){

       return Account_Perst_SelectAll(list);
}


