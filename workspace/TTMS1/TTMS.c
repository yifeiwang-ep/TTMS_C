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
#include <sys/io.h>
#include "./Service/EntityKey.h"
#include "./UI/Main_Menu.h"
#include "./UI/Account_UI.h"
#include"./Service/EntityKey.h"
#include <time.h>


//定义全局变量，用于存储登陆用户信息
account_t gl_CurUser={0, USR_ANOMY, "Anonymous",""};

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

if(!SysLogin()) {
        system("clear");
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\033[31m对不起您无权登录本系统\033[0m\n");
		sleep(2);
        system("clear");
		exit(0);
}
    system("clear");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    \033[31m登录成功\033[0m\n");
    sleep(2);
	Main_Menu();
	return EXIT_SUCCESS;
}
