/*
 * Login_UI.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include<gtk/gtk.h>
#include"Login_UI.h"
#include"User_UI.h"
#include "../Service/Account.h"
#include "../Common/List.h"
#include"Window_UI.h"

//创建登录页面
GtkWidget* Login_UI_MgtEntry()
{
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *button_a;
	GtkWidget *button_b;
	GtkWidget *label_user;
	GtkWidget *label_pass;
	GtkWidget *table;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	gtk_window_set_title(GTK_WINDOW(window),"登录界面");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	table = gtk_table_new(5,5,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);

	label_user = gtk_label_new("用户名");
	label_pass = gtk_label_new("密码");

	text_user = gtk_entry_new();
	text_pass = gtk_entry_new();

	box = gtk_hbox_new(TRUE,10);

	button_a = gtk_button_new_with_label("登录");
	button_b = gtk_button_new_with_label("返回");

	gtk_box_pack_start(GTK_BOX(box),button_a,FALSE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(box),button_b,FALSE,TRUE,0);

	gtk_entry_set_visibility(GTK_ENTRY(text_pass),FALSE);

	gtk_table_attach_defaults(GTK_TABLE(table),label_user,0,1,0,2);
	gtk_table_attach_defaults(GTK_TABLE(table),label_pass,0,1,3,4);
	gtk_table_attach_defaults(GTK_TABLE(table),text_user,2,5,0,2);
	gtk_table_attach_defaults(GTK_TABLE(table),text_pass,2,5,3,4);

	gtk_table_attach_defaults(GTK_TABLE(table),box,1,4,4,5);

	g_signal_connect(G_OBJECT(button_a),"clicked",G_CALLBACK(Login_UI_Think),NULL);
	g_signal_connect(G_OBJECT(button_b),"clicked",G_CALLBACK(gtk_main_quit),NULL);

	return window;
}

//用户登录验证 并进入功能界面
void Login_UI_Think(GtkWidget *button ,gpointer userdate)
{
	account_t buf;
	int type;
	const char *user_str = gtk_entry_get_text(GTK_ENTRY(text_user));
	const char *pass_str = gtk_entry_get_text(GTK_ENTRY(text_pass));
	if(type = Account_Srv_Verify(user_str,pass_str))
	{
		gtk_widget_destroy(login_window);
		g_print("%d\n",type);
		if(type == 1)
		{
				g_print("1");
				menu_window = Clerk_UI_MgtEntry();
 		}
		else if(type == 2)
		{	
				g_print("2");
				menu_window = Mang_UI_MgtEntry();
		}
		else if(type == 9)	
		{		g_print("9");
				menu_window = Admin_UI_MgtEntry();
			
		}
		gtk_widget_show_all(menu_window);		
	}
        return;
}


