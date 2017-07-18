#ifndef comFunction_H_
#define comFunction_H_

char l_getc(); //从键盘获取一个字符，避免了回车的干扰。
int prom(char *msg,char a,char b); 
/*信息确认，返回值为1,使用实例：ch=prom("是否继续输入？","y","n");*/
void cl_stdin();//清空输入的缓冲区，
int getch(void);//getch函数
void getpwd(int maxlen,char *pwd);

#endif
