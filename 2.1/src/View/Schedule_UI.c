#include"Account_UI.h"
#include<gtk/gtk.h>
#include"Window_UI.h"
#include"Schedule_UI.h"
#include"../Service/Schedule.h"
#include "../Common/List.h"
#include<stdio.h>
#include<string.h>

//演出计划管理面板
GtkWidget* Schedule_UI_MgtEntry()
{
	
}

//安排演出计划页面
GtkWidget* Schedule_UI_Add()
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *box;
	GtkWidget *hbox;
	GtkWidget *vbox1;
	GtkWidget *vbox2;



	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"安排演出计划");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(destroy),(gpointer)window);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	
	box = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),box);
	
	hbox = gtk_hbox_new(FALSE,10);
	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	vbox1 = gtk_vbox_new(TRUE,10);
	vbox2 = gtk_vbox_new(TRUE,10);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),vbox1);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),vbox2);
	
	label = gtk_label_new("剧目ID");
	text_play_id = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_play_id);

	label = gtk_label_new("放映厅ID");
	text_studio_id = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_studio_id);

	label = gtk_label_new("放映日期");
	text_date = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_date);

	label = gtk_label_new("放映时间");
	text_time = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_time);

	hbox = gtk_hbox_new(TRUE,10);

	button = gtk_button_new_with_label("确定");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(to_add_schedule),(gpointer)window);
	
	button = gtk_button_new_with_label("取消");
	//gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy),window);

	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	return  window;
	
}

//安排演出计划?
void to_add_schedule(GtkWidget* button,gpointer userdate)
{
	char temp[5][10];
	const char *list_item[4];//列表项信息
	schedule_t data;	
	data.id = EntKey_Srv_CompNewKey("schedule");
	list_item[0]=gtk_entry_get_text(GTK_ENTRY(text_play_id));
	data.play_id = atoi(list_item[0]);

	list_item[1]=gtk_entry_get_text(GTK_ENTRY(text_studio_id));
	data.studio_id = atoi(list_item[1]);
//data time
	Studio_Srv_Add( &data);

	gtk_widget_destroy((GtkWidget *)userdate);
	gtk_widget_show_all(menu_window);
}

//查询演出计划
void to_find_schedule(GtkWidget* button,gpointer userdate)
{

}
