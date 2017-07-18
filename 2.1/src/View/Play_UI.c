#include"Account_UI.h"
#include<gtk/gtk.h>
#include"Window_UI.h"
#include"Sale_UI.h"
#include"../Service/Sale.h"
#include "../Common/List.h"
#include "../Persistence/Query_Persist.h"
#include<stdio.h>
#include<string.h>

//演出信息查找窗口
GtkWidget* Play_UI_find()
{
	GtkWidget* window;
	GtkWidget* button;
	GtkWidget* label;
	GtkWidget* text;
	GtkWidget* box;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(Play_find_to_Clerk_Menu),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	gtk_window_set_title(GTK_WINDOW(window),"查询演出功能页面");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),600,250);

	box = gtk_vbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(window),box);

	label = gtk_label_new("请输入要查询的影片名称");
	text = gtk_entry_new();
	button = gtk_button_new_with_label("查询");

	gtk_box_pack_start_defaults(GTK_BOX(box),label);
	gtk_box_pack_start_defaults(GTK_BOX(box),text);
	
	//g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(print_play),(gpointer)window);
	gtk_box_pack_start_defaults(GTK_BOX(box),button);

	return window;

}

//演出信息输出窗口
GtkWidget* print_play_window()
{
	
}
