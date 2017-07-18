#include<gtk/gtk.h>
#include"callback.h"
#include<stdlib.h>
//extern struct findrc *q;

GtkWidget* make_window_main()//创建主页面
{
	GtkWidget *window;
	GtkWidget *button_buy;
	GtkWidget *button_change;
	GtkWidget *button_quit;
	GtkWidget *image;
	GtkWidget *box_b;
	GtkWidget *box_s;
	

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_window_set_title(GTK_WINDOW(window),"影院系统");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	//gtk_window_set_default_size(GTK_WINDOW(window),10,10);

	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(want_to_quit),NULL);

	box_b = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),box_b);

	image = gtk_image_new_from_file("3.png");	
	box_s = gtk_hbox_new(TRUE,10);

	gtk_box_pack_start(GTK_BOX(box_b),image,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box_b),box_s,TRUE,FALSE,0);

	button_buy = gtk_button_new_with_label("开始购票");
	button_change = gtk_button_new_with_label("管理登录");
	button_quit = gtk_button_new_with_label("退出系统");

	g_signal_connect(G_OBJECT(button_buy),"clicked",G_CALLBACK(on_main_to_buy),NULL);
	g_signal_connect(G_OBJECT(button_change),"clicked",G_CALLBACK(on_main_to_login),NULL);
	g_signal_connect(G_OBJECT(button_quit),"clicked",G_CALLBACK(want_to_quit),NULL);

	gtk_box_pack_start(GTK_BOX(box_s),button_buy,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box_s),button_change,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box_s),button_quit,TRUE,FALSE,0);

	return window;

}

void on_dian_jie(struct theater* p,GtkWidget *boxs)//创建单项影片信息
{
	GtkWidget *button;
	GtkWidget *image;
	GtkWidget *label;
	GtkWidget *frame;
	GtkWidget *frame1;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *tbox;
	GtkWidget *box;

	box = gtk_hbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(boxs),box);

	image = gtk_image_new_from_file(p->photo);
	gtk_box_pack_start_defaults(GTK_BOX(box),image);

	frame1 = gtk_frame_new(NULL);
	gtk_container_add(GTK_CONTAINER(box),frame1);
	gtk_widget_set_size_request(GTK_WIDGET(frame1),800,300);

	hbox = gtk_hbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(frame1),hbox);

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(hbox),vbox);

	frame = gtk_frame_new("影片名");
	label = gtk_label_new(p->name);
	gtk_label_set_line_wrap (GTK_LABEL(label),TRUE);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(vbox),frame);

	frame = gtk_frame_new("影片类型");
	label = gtk_label_new(p->type);
	gtk_label_set_line_wrap (GTK_LABEL(label),TRUE);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(vbox),frame);

	frame = gtk_frame_new("影片简介");
	label = gtk_label_new(p->message);
	gtk_label_set_line_wrap (GTK_LABEL(label),TRUE);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(vbox),frame);

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(hbox),vbox);

	frame = gtk_frame_new("主演");
	label = gtk_label_new(p->people);
	gtk_label_set_line_wrap (GTK_LABEL(label),TRUE);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(vbox),frame);

	tbox = gtk_hbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(vbox),tbox);

	frame = gtk_frame_new("放映时间");
	label = gtk_label_new(p->time);
	gtk_label_set_line_wrap (GTK_LABEL(label),TRUE);	
	gtk_container_add(GTK_CONTAINER(frame),label);	
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(tbox),frame);
	frame = gtk_frame_new("放映地点");
	label = gtk_label_new(p->place);
	gtk_label_set_line_wrap (GTK_LABEL(label),TRUE);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(tbox),frame);

	tbox = gtk_hbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(vbox),tbox);

	frame = gtk_frame_new("票价");
	label = gtk_label_new(p->price);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(tbox),frame);
	frame = gtk_frame_new("评分");
	label = gtk_label_new(p->score);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start_defaults(GTK_BOX(tbox),frame);

	button = gtk_button_new_with_label("购买");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_choose_seat),p);
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
}


GtkWidget* make_window_main_buy ()//创建影片选择页面
{
	GtkWidget *boxs;
	GtkWidget *window;
	GtkWidget *swindow;	

	gchar *title = "影票购买" ;

	fp=fopen("data.txt","rt");

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_default_size(GTK_WINDOW(window),1100,500);

	gtk_window_set_title(GTK_WINDOW(window),title);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);


	swindow = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	gtk_container_add(GTK_CONTAINER(window),swindow);

	boxs = gtk_vbox_new(TRUE,20);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(swindow),boxs);
	
	p = (struct theater*)malloc(sizeof(struct theater));

	while (fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",p->name,p->type,p->people,p->time,p->place,p->message,p->photo,p->price,p->score)!=EOF)
	{
		on_dian_jie(p,boxs);
		p = (struct theater*)malloc(sizeof(struct theater));
	}

	
	fclose(fp);
	
	return window;
}

GtkWidget* make_window_choose_seat(struct theater *p)//创建选坐窗口
{
	GtkWidget *button;
	GtkWidget *button1;
	GtkWidget *label;
	GtkWidget *frame;
	GtkWidget *fbox;
	GtkWidget *dbox;
	GtkWidget *boxs;
	GtkWidget *box;
	GtkWidget *image;
	GtkWidget *window;
	
	gint i,j;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_window_set_title(GTK_WINDOW(window),"guanli");

	box = gtk_vbox_new(FALSE,30);
	gtk_container_add(GTK_CONTAINER(window),box);

	button = gtk_image_new_from_file("1.jpg");
	gtk_widget_set_size_request(GTK_WIDGET(button),100,80); 
	gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);

	dbox = gtk_vbox_new(FALSE,10);
	gtk_container_add(GTK_CONTAINER(box),dbox);

	frame = gtk_frame_new("");
	gtk_box_pack_start(GTK_BOX(dbox),frame,FALSE,FALSE,0);


	strcpy(choose_name,p->name);
	strcat(choose_name,".txt");
	fp=fopen(choose_name,"r+");
	for (i=0;i<8;i++)
	{
		boxs = gtk_hbox_new(FALSE,10);
		gtk_container_add(GTK_CONTAINER(dbox),boxs);
		for (j=0;j<8;j++)
		{
			fscanf(fp,"%d",&weizhi[i][j]);
			q =(struct findrc*)malloc(sizeof(struct findrc));
			q->r=i;
			q->c=j;
			if (weizhi[i][j]==0)
			{
				button =gtk_toggle_button_new();
				gtk_widget_set_size_request(GTK_WIDGET(button),30,30); 
				gtk_box_pack_start(GTK_BOX(boxs),button,FALSE,FALSE,10);
				g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(toggle_clicked_callback),q);
			}
			else
			{
				image = gtk_image_new_from_stock(GTK_STOCK_CANCEL,GTK_ICON_SIZE_MENU);
				button = gtk_button_new();
				gtk_widget_set_size_request(GTK_WIDGET(button),30,30); 
				gtk_container_add(GTK_CONTAINER(button),image);
				gtk_box_pack_start(GTK_BOX(boxs),button,FALSE,FALSE,10);
			}	
		}
	}

	frame = gtk_frame_new("");
	gtk_box_pack_start(GTK_BOX(dbox),frame,FALSE,FALSE,0);
	fclose(fp);
	boxs = gtk_hbox_new(FALSE,20);
	button1 = gtk_button_new_with_label("购买");
	gtk_widget_set_size_request(GTK_WIDGET(button1),50,40); 
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(on_choose_seat_ok),p);
	gtk_box_pack_start(GTK_BOX(boxs),button1,FALSE,FALSE,90);
	button1 = gtk_button_new_with_label("返回");
	gtk_widget_set_size_request(GTK_WIDGET(button1),50,40); 
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(on_seat_to_buy),NULL);
	gtk_box_pack_start(GTK_BOX(boxs),button1,FALSE,FALSE,80);
	gtk_container_add(GTK_CONTAINER(box),boxs);

	return window;
}

GtkWidget* make_window_main_login()//创建管理登录界面
{
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *button_a;
	GtkWidget *button_b;
	GtkWidget *label_user;
	GtkWidget *label_pass;
	GtkWidget *text_user;
	GtkWidget *text_pass;
	GtkWidget *table;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(on_login_to_main),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	gtk_window_set_title(GTK_WINDOW(window),"log in");
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

	g_signal_connect(G_OBJECT(button_a),"clicked",G_CALLBACK(on_login_to_change),NULL);
	g_signal_connect(G_OBJECT(button_b),"clicked",G_CALLBACK(on_login_to_main),NULL);

	return window;
}

GtkWidget* make_window_main_change()//创建影片管理页面
{
	GtkWidget *swindow;
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *button;


	gint i;
	gint temp_row;
	gchar *title[9]={"影片名","影片类型","主演","播放时间","播放地点","影片简介","影片插图","价格","评分"};
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(made_file),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"影片管理");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_window_set_default_size(GTK_WINDOW(window),1200,500);

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);

	swindow = gtk_scrolled_window_new(NULL,NULL);
	gtk_box_pack_start_defaults(GTK_BOX(vbox),swindow);	

	gtk_container_set_border_width (GTK_CONTAINER (swindow), 10);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	list = gtk_clist_new_with_titles(9,title);
	gtk_clist_set_shadow_type (GTK_CLIST(list), GTK_SHADOW_OUT);

	gtk_signal_connect(GTK_OBJECT(list), "select_row",GTK_SIGNAL_FUNC(selection_made),NULL);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW(swindow),list);

	for(i=0;i<9;i++)
	{	
		 gtk_clist_set_column_justification(GTK_CLIST(list),i,GTK_JUSTIFY_CENTER);
	}

	gtk_clist_set_column_width(GTK_CLIST(list),0,100);
	gtk_clist_set_column_width(GTK_CLIST(list),1,100);
	gtk_clist_set_column_width(GTK_CLIST(list),2,100);
	gtk_clist_set_column_width(GTK_CLIST(list),3,100);
	gtk_clist_set_column_width(GTK_CLIST(list),4,100);
	gtk_clist_set_column_width(GTK_CLIST(list),5,300);
	gtk_clist_set_column_width(GTK_CLIST(list),6,100);
	gtk_clist_set_column_width(GTK_CLIST(list),7,50);
	gtk_clist_set_column_width(GTK_CLIST(list),8,50);

	hbox = gtk_hbox_new(TRUE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);

	button = gtk_button_new_with_label("添加");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(list_add),(gpointer)list);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);
	
	button = gtk_button_new_with_label("修改");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(list_change),(gpointer)list);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label("删除");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(list_delete),(gpointer)list);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	button = gtk_button_new_with_label("清空");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(list_clear),(gpointer)list);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5);

	list_made(list,&th);

	return window;
}

GtkWidget* make_window_yesorno(GtkWidget *userdate) //创建退出确认框？
{
	GtkWidget *window;
	GtkWidget *button_yes;
	GtkWidget *button_no;
	GtkWidget *label;	
	GtkWidget *box_b;
	GtkWidget *box_s;

	window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_default_size(GTK_WINDOW(window),150,70);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(on_change_no),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	box_b = gtk_vbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(window),box_b);

	label = gtk_label_new("是否确定？");
	gtk_box_pack_start_defaults(GTK_BOX(box_b),label);

	box_s = gtk_hbox_new(TRUE,10);
	gtk_box_pack_start_defaults(GTK_BOX(box_b),box_s);

	button_yes = gtk_button_new_with_label("是");
	button_no = gtk_button_new_with_label("否");

	gtk_box_pack_start_defaults(GTK_BOX(box_s),button_yes);
	gtk_box_pack_start_defaults(GTK_BOX(box_s),button_no);

	g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(on_change_yes),NULL);
	g_signal_connect(G_OBJECT(button_no),"clicked",G_CALLBACK(on_change_no),NULL);
	
	return window;
}

GtkWidget* make_window_insert()//创建信息输入窗口
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *box;
	GtkWidget *hbox;
	GtkWidget *vbox1;
	GtkWidget *vbox2;


	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"添加影片");
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

	label = gtk_label_new("影片名");
	text_name = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_name);
	
	label = gtk_label_new("影片类型");
	text_type = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_type);

	label = gtk_label_new("主演");
	text_people = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_people);

	label = gtk_label_new("放映时间");
	text_time = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_time);

	label = gtk_label_new("放映地点");
	text_place = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_place);

	label = gtk_label_new("影片简介");
	text_message = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_message);

	label = gtk_label_new("影片封面");
	text_photo = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_photo);

	label = gtk_label_new("票价");
	text_price = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_price);

	label = gtk_label_new("评分");
	text_score = gtk_entry_new();
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_score);

	hbox = gtk_hbox_new(TRUE,10);

	button = gtk_button_new_with_label("确定");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(to_add_list_item),(gpointer)window);
	
	button = gtk_button_new_with_label("取消");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy),window);

	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	return  window;
}

GtkWidget* make_window2_insert()//修改信息输入窗口
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *box;
	GtkWidget *hbox;
	GtkWidget *vbox1;
	GtkWidget *vbox2;

	gchar *temp[9];
	gint i;

	for(i=0;i<9;i++)
	{
		gtk_clist_get_text(GTK_CLIST(list),temp_row,i,(gchar **)(&temp[i]));
	}

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"修改影片");
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

	label = gtk_label_new("影片名");
	text_name = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_name),temp[0]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_name);
	
	label = gtk_label_new("影片类型");
	text_type = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_type),temp[1]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_type);

	label = gtk_label_new("主演");
	text_people = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_people),temp[2]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_people);

	label = gtk_label_new("放映时间");
	text_time = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_time),temp[3]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_time);

	label = gtk_label_new("放映地点");
	text_place = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_place),temp[4]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_place);

	label = gtk_label_new("影片简介");
	text_message = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_message),temp[5]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_message);

	label = gtk_label_new("影片封面");
	text_photo = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_photo),temp[6]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_photo);

	label = gtk_label_new("票价");
	text_price = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_price),temp[7]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_price);

	label = gtk_label_new("评分");
	text_score = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(text_score),temp[8]);
	gtk_box_pack_start_defaults(GTK_BOX(vbox1),label);
	gtk_box_pack_start_defaults(GTK_BOX(vbox2),text_score);

	hbox = gtk_hbox_new(TRUE,10);

	button = gtk_button_new_with_label("确定");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(to_change_list_item),(gpointer)window);
	
	button = gtk_button_new_with_label("取消");
	gtk_box_pack_start_defaults(GTK_BOX(hbox),button);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(destroy),window);

	gtk_box_pack_start_defaults(GTK_BOX(box),hbox);	

	return  window;
}


GtkWidget* make_window_ok_seat(struct theater *p)//创建确定付款窗口
{
	GtkWidget *box;
	GtkWidget *frame;
	GtkWidget *label;
	GtkWidget *hbox;
	GtkWidget *boxx;
	GtkWidget *boxs;
	GtkWidget *button_buy;
	GtkWidget *button_log;
	GtkWidget *window1;

	char f[20];
	
	gint i,j;

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window1),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_position(GTK_WINDOW(window1),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window1),10);
	gtk_window_set_title(GTK_WINDOW(window1),"确认购买");
	
	box = gtk_vbox_new(FALSE,10);

	gtk_container_add(GTK_CONTAINER(window1),box);
	
	frame = gtk_frame_new("电影名");
	label = gtk_label_new(p->name);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(box),frame,FALSE,FALSE,0);

	frame = gtk_frame_new("上映时间");
	label = gtk_label_new(p->time);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(box),frame,FALSE,FALSE,0);

	frame = gtk_frame_new("上映地点");
	label = gtk_label_new(p->place);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(box),frame,FALSE,FALSE,0);
	
	frame = gtk_frame_new("购票价格");
	label = gtk_label_new(p->price);
	gtk_container_add(GTK_CONTAINER(frame),label);
	gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(box),frame,FALSE,FALSE,0);
	
	boxx = gtk_vbox_new(FALSE,0);
	for (i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(weizhi[i][j]==2)
			{		

				sprintf(f,"  第%d排 第%d列  ",i+1,j+1);
				frame = gtk_frame_new("");
				label = gtk_label_new(f);
				gtk_container_add(GTK_CONTAINER(frame),label);
				gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
				gtk_box_pack_start(GTK_BOX(boxx),frame,FALSE,FALSE,0);
			}
		}
	}
	gtk_container_add(GTK_CONTAINER(box),boxx);
	
	hbox = gtk_hbox_new(FALSE,20);
	gtk_container_add(GTK_CONTAINER(box),hbox);


	button_buy = gtk_button_new_with_label("确认");
	button_log = gtk_button_new_with_label("返回");

	gtk_box_pack_start(GTK_BOX(hbox),button_buy,FALSE,FALSE,20);
	gtk_box_pack_start(GTK_BOX(hbox),button_log,FALSE,FALSE,20);
	g_signal_connect(G_OBJECT(button_buy),"clicked",G_CALLBACK(on_put_money),p);
	g_signal_connect(G_OBJECT(button_log),"clicked",G_CALLBACK(on_ok_to_seat),NULL);
	
	return window1;
}


GtkWidget* make_window_buy_passwd(struct theater *p)//支付登录界面
{
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *button_a;
	GtkWidget *button_b;
	GtkWidget *label_user;
	GtkWidget *label_pass;
	GtkWidget *text_user;
	GtkWidget *text_pass;
	GtkWidget *table;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(on_login_to_main),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	gtk_window_set_title(GTK_WINDOW(window),"log in");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	table = gtk_table_new(5,5,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);

	label_user = gtk_label_new("账户");
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

	g_signal_connect(G_OBJECT(button_a),"clicked",G_CALLBACK(on_succeed_login),p);
	g_signal_connect(G_OBJECT(button_b),"clicked",G_CALLBACK(destroy),(gpointer)window);

	return window;
}

GtkWidget* make_tobuy_yesorno(struct theater *p) //创建支付后确认框？
{
	GtkWidget *window;
	GtkWidget *button_yes;
	GtkWidget *button_no;
	GtkWidget *label;	
	GtkWidget *box_b;
	GtkWidget *box_s;

	window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_default_size(GTK_WINDOW(window),150,70);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(on_change_no),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	box_b = gtk_vbox_new(TRUE,10);
	gtk_container_add(GTK_CONTAINER(window),box_b);

	label = gtk_label_new("确定支付？");
	gtk_box_pack_start_defaults(GTK_BOX(box_b),label);

	box_s = gtk_hbox_new(TRUE,10);
	gtk_box_pack_start_defaults(GTK_BOX(box_b),box_s);

	button_yes = gtk_button_new_with_label("是");
	button_no = gtk_button_new_with_label("否");

	gtk_box_pack_start_defaults(GTK_BOX(box_s),button_yes);
	gtk_box_pack_start_defaults(GTK_BOX(box_s),button_no);

	g_signal_connect(G_OBJECT(button_yes),"clicked",G_CALLBACK(on_succeed_buy),p);
	g_signal_connect(G_OBJECT(button_no),"clicked",G_CALLBACK(destroy),(gpointer)window);
	
	return window;
}

