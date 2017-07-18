#ifndef SCHEDULE_UI_H_
#define SCHEDULE_UI_H_
#include"../Service/Schedule.h"

#include<gtk/gtk.h>

GtkWidget* text_id;
GtkWidget* text_play_id;
GtkWidget* text_studio_id;
GtkWidget* text_date;
GtkWidget* text_time;

//演出计划管理面板
GtkWidget* Schedule_UI_MgtEntry();

//安排演出计划页面
GtkWidget* Schedule_UI_Add();

//查询演出计划页面
GtkWidget* Schedule_UI_Find();

//安排演出计划
void to_add_schedule(GtkWidget* button,gpointer userdate);

//查询演出计划
void to_find_schedule(GtkWidget* button,gpointer userdate);

#endif
