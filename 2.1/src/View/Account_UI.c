#include"Account_UI.h"
#include<gtk/gtk.h>
#include"Window_UI.h"
#include"User_UI.h"
#include"../Service/Account.h"
#include "../Common/List.h"
#include<stdio.h>
#include<string.h>



//用户管理页面
GtkWidget* Account_UI_MgtEntry()
{
	GtkWidget *swindow;
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *button;
	
	gint i;
	gchar *title[4]={"ID","用户类型","用户名","密码"};
	
	account_list_t head;
	List_Init(head,account_node_t);	
	Account_Srv_FetchAll(head);	

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(Account_to_Admin_Menu),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"用户管理");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_window_set_default_size(GTK_WINDOW(window),600,250);

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);

	swindow = gtk_scrolled_window_new(NULL,NULL);
	gtk_box_pack_start_defaults(GTK_BOX(vbox),swindow);	

	gtk_container_set_border_width (GTK_CONTAINER (swindow), 10);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	account_list = gtk_clist_new_with_titles(4,title);
	gtk_clist_set_shadow_type (GTK_CLIST(account_list), GTK_SHADOW_OUT);

	gtk_signal_connect(GTK_OBJECT(account_list), "select_row",GTK_SIGNAL_FUNC(selection_made_account),NULL);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW(swindow),account_list);

	for(i=0;i<4;i++)
	{	
		 gtk_clist_set_column_justification(GTK_CLIST(account_list),i,GTK_JUSTIFY_CENTER);
	}
	
	gtk_clist_set_column_width(GTK_CLIST(account_list),0,100);
	gtk_clist_set_column_width(GTK_CLIST(account_list),1,100);
	gtk_clist_set_column_width(GTK_CLIST(account_list),2,100);
	gtk_clist_set_column_width(GTK_CLIST(account_list),3,100);

	hbox = gtk_hbox_new(TRUE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);

	button = gtk_button_new_with_label("添加");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Account_Menu),(gpointer)1);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
	
	button = gtk_button_new_with_label("修改");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Account_Menu),(gpointer)2);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label("删除");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(list_delete_account),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label("返回");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Account_to_Admin_Menu),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	Account_Clist_Make(account_list,head);

	return window;
}

//创建功能回调函数
GtkWidget* Account_Menu(GtkWidget *button,gpointer data)
{
	switch ((int)data)
	{
		case 1:
			account_menu = Account_UI_Add();
			break;
		
		case 2:
			account_menu = Account_UI_Change();
			break;
	}
	gtk_widget_show_all(account_menu);
}

//创建用户添加页面
GtkWidget* Account_UI_Add()
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *box;
	GtkWidget *hbox;
	GtkWidget *vbox1;
	GtkWidget *vbox2;



	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"添加用户");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_widget_destroy),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	
	box = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),box);
	
	hbox = gtk_hbox_new(FALSE,10);
	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	vbox1 = gtk_vbox_new(TRUE,10);
	vbox2 = gtk_vbox_new(TRUE,10);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),vbox1);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),vbox2);

	label = gtk_label_new("账户类型");
	text_type = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_type);
	
	label = gtk_label_new("用户名");
	text_user = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_user);

	label = gtk_label_new("密码");
	text_pass = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_pass);

	hbox = gtk_hbox_new(TRUE,10);

	button = gtk_button_new_with_label("确定");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(to_add_list_account),(gpointer)window);
	
	button = gtk_button_new_with_label("取消");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy),window);

	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	return  window;
}

//创建用户修改页面
GtkWidget* Account_UI_Change()
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *box;
	GtkWidget *hbox;
	GtkWidget *vbox1;
	GtkWidget *vbox2;

	gchar *temp[4];
	gint i;

	for(i=1;i<4;i++)
	{
		gtk_clist_get_text(GTK_CLIST(account_list),account_now,i,(gchar **)(&temp[i]));
	}

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"修改用户");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_widget_destroy),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	
	box = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),box);
	
	hbox = gtk_hbox_new(FALSE,10);
	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	vbox1 = gtk_vbox_new(TRUE,10);
	vbox2 = gtk_vbox_new(TRUE,10);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),vbox1);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),vbox2);

	label = gtk_label_new("用户类型");
	text_type = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_type),temp[1]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_type);
	
	label = gtk_label_new("用户名");
	text_user = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_user),temp[2]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_user);

	label = gtk_label_new("密码");
	text_pass = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_pass),temp[3]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_pass);

	hbox = gtk_hbox_new(TRUE,10);

	button = gtk_button_new_with_label("确定");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(to_change_list_account),(gpointer)window);
	
	button = gtk_button_new_with_label("取消");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy),window);

	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	return  window;
}


//将新增数据加入列表
void to_add_list_account(GtkWidget *button ,gpointer userdate)
{
	account_num++;
	char temp[10];
	const char *list_item[4];//列表项信息
	account_t data;	
	data.id = EntKey_Srv_CompNewKey("account");
	sprintf(temp,"%d",data.id);
	list_item[0]=temp;
	list_item[1]=gtk_entry_get_text(GTK_ENTRY(text_type));
	data.type = atoi(list_item[1]);
	list_item[2]=gtk_entry_get_text(GTK_ENTRY(text_user));
	list_item[3]=gtk_entry_get_text(GTK_ENTRY(text_pass));
	strcpy(data.username,list_item[2]);	
	strcpy(data.password,list_item[3]);

	Account_Srv_Add( &data);

	gtk_clist_append((GtkCList *)account_list,(gchar **)list_item);

	gtk_widget_destroy((GtkWidget *)userdate);
}

//将修改的数据加入列表
void to_change_list_account(GtkWidget *button ,gpointer userdate)
{
	gint i;
	account_t data;	
	const gchar *list_item[4];//列表项信息
	gtk_clist_get_text(GTK_CLIST(account_list), account_now, 0, &list_item[0]);
	data.id = atoi(list_item[0]);
	list_item[1]=gtk_entry_get_text(GTK_ENTRY(text_type));
	data.type = atoi(list_item[1]);
	list_item[2]=gtk_entry_get_text(GTK_ENTRY(text_user));
	list_item[3]=gtk_entry_get_text(GTK_ENTRY(text_pass));	
	strcpy(data.username,list_item[2]);
	strcpy(data.password,list_item[3]);

	Account_Srv_Modify(&data);

	for(i=1;i<4;i++)
	{
		gtk_clist_set_text (GTK_CLIST(account_list),account_now,i ,list_item[i]);
	}
	gtk_widget_destroy((GtkWidget *)userdate);
}

//从列表中删除数据
void list_delete_account(GtkButton *button, gpointer userdate)
{
	int id;
	gchar *text;
	gtk_clist_get_text(GTK_CLIST(account_list), account_now, 0, &text);
	id = atoi(text);
	Account_Srv_DeleteByID(id);
	account_num--;
	gtk_clist_remove( account_list,account_now);
}

//用户列表初始化
void Account_Clist_Make(GtkWidget *Clist, account_list_t head)
{
	char *s[4];
	char temp1[10],temp2[10],temp[10];
	account_list_t curPos;

	List_ForEach(head, curPos)
	{
		sprintf(temp,"%d",curPos->data.id);
		s[0] = temp;
		sprintf(temp1,"%d",curPos->data.type);
		s[1] = temp1;
		s[2] = curPos->data.username;
		s[3] = curPos->data.password;
		gtk_clist_append((GtkCList *)Clist,s);
	}
}


//定位用户列表界面选中行
void selection_made_account( GtkWidget *list,gint row,gint column,GdkEventButton *event,gpointer userdate)
{
	gchar *text;
	gtk_clist_get_text(GTK_CLIST(account_list), row, column, &text);
	account_now=row;
}


