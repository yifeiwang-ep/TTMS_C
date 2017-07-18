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
#include <time.h>


//定义全局变量，用于存储登陆用户信息
account_t gl_CurUser={0, USR_ANOMY, "Anonymous",""};

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
    int flag;
    FILE *fp;
    char choice;
    char readme[21];
if(!(flag=SysLogin())) {
        system("clear");
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\033[31m对不起您无权登录本系统\033[0m\n");
		sleep(1);
        system("clear");
		exit(0);
}
    system("clear");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    \033[31m登录成功\033[0m\n");
    sleep(1);
    do{
        fp=fopen("readme.txt","rt");
        if(!fp){
            printf("\n\n\n\n\t\t\terror!");
            exit(0);
        }
        system("clear");
        while((fgets(readme,20,fp))!=NULL){
            printf("%s",readme);
            }
        printf("\n\n\t\t\t\t\t\t\t\tI‘ve already read it(y):");
        scanf("%c",&choice);
    }while(choice!='y'&&choice!='Y');
	Main_Menu(flag);
	return EXIT_SUCCESS;
}
