/*
 * common.h
 *
 *  Created on: 2015年4月25日
 *      Author: Administrator
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef struct {
	int year;
	int month;
	int day;
}user_date_t;

typedef struct {
	int hour;
	int minute;
	int second;
}user_time_t;

//直接读取键盘输入值
int ScanKeyboard();

//将字符串str就地转换为大写字符串，并返回字符串头指针
char *Str2Upper(char *str);

//将字符串str就地转换为小写字符串，并返回字符串头指针
char *Str2Lower(char *str);

//比较日期dt1, dt2的大小。相等返回0，dt1<dt2返回-1，否则1
int DateCmp(user_date_t dt1, user_date_t dt2);

//获取系统当前日期
user_date_t DateNow();

//获取系统当前时间
user_time_t TimeNow();

#endif /* COMMON_H_ */
