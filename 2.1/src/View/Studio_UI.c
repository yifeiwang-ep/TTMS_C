#include"Studio_UI.h"
#include<gtk/gtk.h>
#include"Window_UI.h"
#include"User_UI.h"
#include"Seat_UI.h"
#include"../Service/Studio.h"
#include"../Service/Seat.h"
#include "../Common/List.h"
#include<stdio.h>
#include<string.h>

//放映厅管理页面
GtkWidget* Studio_UI_MgtEntry()
{
	GtkWidget *swindow;
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *button;
	
	gint i;
	gchar *title[4]={"ID","放映厅名","座位行号","座位列号"};
	
	studio_list_t head;
	List_Init(head,studio_node_t);	
	Studio_Srv_FetchAll(head);	

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(Studio_to_Admin_Menu),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"放映厅管理");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_window_set_default_size(GTK_WINDOW(window),600,250);

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);

	swindow = gtk_scrolled_window_new(NULL,NULL);
	gtk_box_pack_start_defaults(GTK_BOX(vbox),swindow);	

	gtk_container_set_border_width (GTK_CONTAINER (swindow), 10);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	studio_list = gtk_clist_new_with_titles(4,title);
	gtk_clist_set_shadow_type (GTK_CLIST(studio_list), GTK_SHADOW_OUT);

	gtk_signal_connect(GTK_OBJECT(studio_list), "select_row",GTK_SIGNAL_FUNC(selection_made_studio),NULL);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW(swindow),studio_list);

	for(i=0;i<4;i++)
	{	
		 gtk_clist_set_column_justification(GTK_CLIST(studio_list),i,GTK_JUSTIFY_CENTER);
	}
	
	gtk_clist_set_column_width(GTK_CLIST(studio_list),0,100);
	gtk_clist_set_column_width(GTK_CLIST(studio_list),1,100);
	gtk_clist_set_column_width(GTK_CLIST(studio_list),2,100);
	gtk_clist_set_column_width(GTK_CLIST(studio_list),3,100);

	hbox = gtk_hbox_new(TRUE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);

	button = gtk_button_new_with_label("添加");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Studio_Menu),(gpointer)1);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
	
	button = gtk_button_new_with_label("修改");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Studio_Menu),(gpointer)2);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label("删除");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(list_delete_studio),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label("座位");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(studio_to_seat),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label("返回");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Studio_to_Admin_Menu),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	Studio_Clist_Make(studio_list,head);

	return window;
}

//创建功能回调函数
GtkWidget* Studio_Menu(GtkWidget *button,gpointer data)
{
	switch ((int)data)
	{
		case 1:
			studio_menu = Studio_UI_Add();
			break;
		
		case 2:
			studio_menu = Studio_UI_Change();
			break;
	}
	gtk_widget_show_all(studio_menu);
}

//创建放映厅添加页面
GtkWidget* Studio_UI_Add()
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *box;
	GtkWidget *hbox;
	GtkWidget *vbox1;
	GtkWidget *vbox2;



	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"添加放映厅");
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

	label = gtk_label_new("放映厅名称");
	text_name = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_name);
	
	label = gtk_label_new("座位行数");
	text_row = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_row);

	label = gtk_label_new("座位列数");
	text_cols = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_cols);

	hbox = gtk_hbox_new(TRUE,10);

	button = gtk_button_new_with_label("确定");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(to_add_list_studio),(gpointer)window);
	
	button = gtk_button_new_with_label("取消");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy),window);

	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	return  window;
}

//创建放映厅修改页面
GtkWidget* Studio_UI_Change()
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
		gtk_clist_get_text(GTK_CLIST(studio_list),studio_now,i,(gchar **)(&temp[i]));
	}

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"修改放映厅");
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

	label = gtk_label_new("放映厅名称");
	text_name = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_name),temp[1]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_name);
	
	label = gtk_label_new("座位行数");
	text_row = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_row),temp[2]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_row);

	label = gtk_label_new("座位列数");
	text_cols = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_cols),temp[3]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_cols);

	hbox = gtk_hbox_new(TRUE,10);

	button = gtk_button_new_with_label("确定");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(to_change_list_studio),(gpointer)window);
	
	button = gtk_button_new_with_label("取消");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy),window);

	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	return  window;
}


//将新增数据加入列表
void to_add_list_studio(GtkWidget *button ,gpointer userdate)
{
	studio_num++;
	char temp[10];
	int newRecCount = 0;
	const char *list_item[4];//列表项信息
	studio_t data;		
	seat_list_t buf;
	data.id = EntKey_Srv_CompNewKey("studio");
	sprintf(temp,"%d",data.id);
	list_item[0]=temp;
	list_item[1]=gtk_entry_get_text(GTK_ENTRY(text_name));
	strcpy(data.name , list_item[1]);
	list_item[2]=gtk_entry_get_text(GTK_ENTRY(text_row));
	list_item[3]=gtk_entry_get_text(GTK_ENTRY(text_cols));

	data.rowsCount = atoi(list_item[2]);
	data.colsCount = atoi(list_item[3]);

	Studio_Srv_Add( &data);
	newRecCount += 1;
	List_Init(buf, seat_node_t);
	Seat_Srv_RoomInit(buf, data.id, data.rowsCount, data.colsCount);
	Seat_Srv_AddBatch(buf);

	gtk_clist_append((GtkCList *)studio_list,(gchar **)list_item);

	gtk_widget_destroy((GtkWidget *)userdate);
}

//将修改的数据加入列表
void to_change_list_studio(GtkWidget *button ,gpointer userdate)
{
	gint i;
	studio_t data;	
	const gchar *list_item[4];//列表项信息
	gtk_clist_get_text(GTK_CLIST(studio_list), studio_now, 0, &list_item[0]);
	data.id = atoi(list_item[0]);
	list_item[1]=gtk_entry_get_text(GTK_ENTRY(text_name));
	list_item[2]=gtk_entry_get_text(GTK_ENTRY(text_row));
	list_item[3]=gtk_entry_get_text(GTK_ENTRY(text_cols));
 	strcpy(data.name , list_item[1]);	
	data.rowsCount = atoi(list_item[2]);
	data.colsCount = atoi(list_item[3]);

	Studio_Srv_Modify(&data);

	for(i=1;i<4;i++)
	{
		gtk_clist_set_text (GTK_CLIST(studio_list),studio_now,i ,list_item[i]);
	}
	gtk_widget_destroy((GtkWidget *)userdate);
}

//从列表中删除数据
void list_delete_studio(GtkButton *button, gpointer userdate)
{
	int id;
	gchar *text;
	gtk_clist_get_text(GTK_CLIST(studio_list), studio_now, 0, &text);
	id = atoi(text);
	Studio_Srv_DeleteByID(id);
	Seat_Srv_DeleteAllByRoomID(id);
	studio_num--;
	gtk_clist_remove( studio_list,studio_now);
}

//演出厅列表初始化
void Studio_Clist_Make(GtkWidget *Clist, studio_list_t head)
{
	char *s[4];
	char temp1[10],temp2[10],temp[10];
	studio_list_t curPos;

	List_ForEach(head, curPos)
	{
		sprintf(temp,"%d",curPos->data.id);
		s[0] = temp;
		s[1] = curPos->data.name;
		sprintf(temp1,"%d",curPos->data.rowsCount);
		s[2] = temp1;
		sprintf(temp2,"%d",curPos->data.colsCount);
		s[3] = temp2;
		gtk_clist_append((GtkCList *)Clist,s);
	}
}

//定位放映厅列表界面选中行
void selection_made_studio( GtkWidget *list,gint row,gint column,GdkEventButton *event,gpointer userdate)
{
	gchar *text;
	gtk_clist_get_text(GTK_CLIST(list), row, column, &text);
	studio_now=row;
}

//进入座位管理页面
void studio_to_seat()
{
	char *temp;
	int id;
	GtkWidget *window;

	gtk_clist_get_text(GTK_CLIST(studio_list), studio_now, 0, &temp);
	id = atoi(temp);
	window = Seat_UI_MgtEntry(id);
	gtk_widget_show_all(window);
}
