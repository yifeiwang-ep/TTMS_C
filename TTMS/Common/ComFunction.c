
#include<stdio.h>
#include "../Service/Account.h"
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include"common.h"
#include"ComFunction.h"
extern account_t gl_CurUser;
char l_getc(){
	char a;
	scanf("%c",&a);
	while(a=='\n') scanf("%c",&a);
	return a;
}


int prom(char *msg,char a,char b){
	char ch;
	printf("\n%s [ %c / %c ] ",msg,a,b);
	cl_stdin();
	ch=l_getc();
	cl_stdin();
	if(ch==a||ch==a-32) return 1;
	if(ch==b||ch==a-32) return 0;
	return -1;
}

void cl_stdin(){
	char ch;
	while((ch=getchar())!='\n'&&ch!=EOF);
}

int getch(void)
{
        int c=0;
        struct termios org_opts, new_opts;
        int res=0;
        //-----  store old settings -----------
        res=tcgetattr(STDIN_FILENO, &org_opts);
        assert(res==0);
        //---- set new terminal parms --------
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();
            //------  restore old settings ---------
        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);
        return c;
}

void getpwd(int maxlen,char *pwd){
	int j=0;
	char c;
	//cl_stdin();
	while(j<maxlen && (c=getch())!='\n')
	{
		if(c!=127)
		{
			    printf("*");
			    pwd[j++]=c;
		}else{
			 if(j>0){
				  j=j-1;
				  printf("\b \b");
			        }
		}
	} 
			
	pwd[j]='\0';
	
}
	


int SysLogout() {
	
	
	int choice;
	
		system("clear");
       	printf("\n\t\t==================================================================");
       	printf("\n\t\t\t\t\t%s\t\t\t%s","用户类型", "用户名");
		printf("\n\t\t------------------------------------------------------------------");
       	printf("\n\t\t\t\t\t%s",gl_CurUser.username);
		switch(gl_CurUser.type){
					case USR_CLERK:  printf("\t\t\t%s","CLERK"); 	break;
					case USR_MANG:	 printf("\t\t\t%s","MANG");  	break;
					case USR_ADMIN:  printf("\t\t\t%s","ADMIN"); 	break;
				}
		printf("\n		-----------------------------------------------------------------");
		printf("\n		|          [L]og Out          |               [R]eturn           |");
		printf("\n		******************************************************************");
        printf("\n		Input Your choice:");
        scanf("%c",&choice);
        if(choice=='l'||choice=='L'){
	       	if(Account_Perst_CheckAccFile()){
				printf("\n		----------------------------注销成功！------------------------------");
				sleep(1);
                SysLogin();
				return 1;
		}else{
				  printf("\n		----------------------------注销失败！------------------------------");
				
				sleep(1);
				return 0;
				   
			}
		}
		
}

