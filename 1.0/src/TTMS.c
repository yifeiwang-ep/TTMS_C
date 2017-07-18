/*
 ============================================================================
 Name        : TTMS.c
 Author      : shu xinfeng
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "./View/Main_Menu.h"
#include "./View/Account_UI.h"


//定义全局变量，用于存储登陆用户信息
account_t gl_CurUser={0, USR_ANOMY, "Anonymous",""};

int main(void) {
	//setvbuf(stdout, NULL, _IONBF, 0);

	Account_Srv_InitSys();

	if(!SysLogin()) {
		printf("\n对不起您无权登录本系统请按任意键退出......\n");
		getchar();
		exit(0);
	}


	Main_Menu();
	return EXIT_SUCCESS;
}
