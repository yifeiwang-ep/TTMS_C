#include<gtk/gtk.h>
#include"callback.h"
#include"interface.h"

extern struct findrc *q;

void on_main_to_buy(GtkWidget *widget ,gpointer userdate)//从主界面转至购票页面
{
	gtk_widget_hide(window_main);
	gtk_widget_show_all(window_main_buy);
}

void on_main_to_login(GtkWidget *widget , gpointer userdate)//从主界面转至登录界面
{
	gtk_widget_hide(window_main);
	gtk_widget_show_all(window_main_login);
}

void on_login_to_main(GtkWidget *widget , gpointer userdate)//从登录界面转至主界面
{
	gtk_widget_hide(window_main_login);
	gtk_widget_show_all(window_main);
}

void on_login_to_change(GtkWidget *widget , gpointer userdate)//从登录界面转至管理页面
{
	gtk_widget_hide(window_main_login);
	gtk_widget_show_all(window_main_change);
}

void on_seat_to_buy(GtkWidget *button,gpointer userdate)//从选座界面转至选电影界面
{
	gtk_widget_hide(window_choose_seat);
	gtk_widget_show_all(window_main_buy);
}



void on_ok_to_seat(GtkWidget *button,gpointer userdate)//从付款界面返回选做界面
{
	gtk_widget_destroy(window_choose_to_buy);
	gtk_widget_show_all(window_choose_seat);
}

void on_change_yes(GtkWidget *widget ,gpointer userdate)//确认是
{
	gtk_main_quit();
}

void on_change_no(GtkWidget *widget ,gpointer userdate)//确认否
{
	gtk_widget_hide(window_change_yesorno);
}

void want_to_quit(GtkWidget *widget ,gpointer userdate)//打开确认界面
{
	gtk_widget_show_all(window_change_yesorno);
}

void list_made(GtkWidget *list,struct theater *p)
{
	gchar *s[9];
	
	fp = fopen("data.txt","rt");
	while(fscanf(fp,"%s%s%s%s%s%s%s%s%s\n",p->name,p->type,p->people,p->time,p->place,p->message,p->photo,p->price,p->score)!=EOF)
	{
		theater_num++;
		s[0]=p->name;
		s[1]=p->type;
		s[2]=p->people;
		s[3]=p->time;
		s[4]=p->place;
		s[5]=p->message;
		s[6]=p->photo;
		s[7]=p->price;
		s[8]=p->score;
		gtk_clist_append((GtkCList *)list,s);
	}
	fclose(fp);
}

void list_add(GtkButton *button , gpointer userdate)//添加影片
{

	GtkWidget *window;

	window = make_window_insert();

	gtk_widget_show_all(window);	
}

void to_add_list_item(GtkWidget *button ,gpointer userdate)//将新增数据显示并存入文件
{
	theater_num++;
	const gchar *list_item[9];//列表项信息
	list_item[0]=gtk_entry_get_text(GTK_ENTRY(text_name));
	list_item[1]=gtk_entry_get_text(GTK_ENTRY(text_type));
	list_item[2]=gtk_entry_get_text(GTK_ENTRY(text_people));
	list_item[3]=gtk_entry_get_text(GTK_ENTRY(text_time));
	list_item[4]=gtk_entry_get_text(GTK_ENTRY(text_place));
	list_item[5]=gtk_entry_get_text(GTK_ENTRY(text_message));
	list_item[6]=gtk_entry_get_text(GTK_ENTRY(text_photo));
	list_item[7]=gtk_entry_get_text(GTK_ENTRY(text_price));
	list_item[8]=gtk_entry_get_text(GTK_ENTRY(text_score));

	gtk_clist_append((GtkCList *)list,(gchar **)list_item);
	fp = fopen("data.txt","at+");

	fprintf(fp,"%s %s %s %s %s %s %s %s %s\n",list_item[0],list_item[1],list_item[2],list_item[3],list_item[4],list_item[5],list_item[6],list_item[7],list_item[8]);
	fclose(fp);
	gtk_widget_destroy((GtkWidget *)userdate);
}


void to_change_list_item(GtkWidget *button ,gpointer userdate)//将修改后的数据显示并存入文件
{
	gint i;
	const gchar *list_item[9];//列表项信息
	list_item[0]=gtk_entry_get_text(GTK_ENTRY(text_name));
	list_item[1]=gtk_entry_get_text(GTK_ENTRY(text_type));
	list_item[2]=gtk_entry_get_text(GTK_ENTRY(text_people));
	list_item[3]=gtk_entry_get_text(GTK_ENTRY(text_time));
	list_item[4]=gtk_entry_get_text(GTK_ENTRY(text_place));
	list_item[5]=gtk_entry_get_text(GTK_ENTRY(text_message));
	list_item[6]=gtk_entry_get_text(GTK_ENTRY(text_photo));
	list_item[7]=gtk_entry_get_text(GTK_ENTRY(text_price));
	list_item[8]=gtk_entry_get_text(GTK_ENTRY(text_score));
 	
	for(i=0;i<9;i++)
	{
		gtk_clist_set_text (GTK_CLIST(list),temp_row,i ,list_item[i]);
	}
	gtk_widget_destroy((GtkWidget *)userdate);
}


void list_change(GtkButton *button , gpointer userdate)//修改影片
{
	GtkWidget *window;

	window = make_window2_insert();

	gtk_widget_show_all(window);
}

void list_delete(GtkButton *button, gpointer userdate)//删除影片
{
	theater_num--;
	gtk_clist_remove( (GtkCList*)userdate,temp_row);
}

void list_clear(GtkButton *button, gpointer userdate)//清空影片
{
	theater_num = 0;
	gtk_clist_clear((GtkCList*)userdate);
}

void selection_made( GtkWidget *list,gint row,gint column,GdkEventButton *event,gpointer userdate)//定位管理界面选中行
{
	gchar *text;
	gtk_clist_get_text(GTK_CLIST(list), row, column, &text);
	temp_row=row;
}

void destroy(GtkWidget *button,GtkWidget *window)//销毁窗体
{
	gtk_widget_destroy(window);
}

void made_file()//更新文件
{
	gint i,j;
	gchar *temp[9];

	fp=fopen("data.txt","wt+");
	for(i=0;i<theater_num;i++)
	{
		for(j=0;j<9;j++)
		{
			gtk_clist_get_text(GTK_CLIST(list),i,j,(gchar **)(&temp[j]));
		}
		fprintf(fp,"%s %s %s %s %s %s %s %s %s\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8]);
		//printf("%s %s %s %s %s %s %s %s %s\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8]);
	}
	fclose(fp);
	gtk_main_quit();
}


void on_choose_seat_ok (GtkWidget *button,struct theater* p)//显示购票的选择信息
{
	window_choose_to_buy = make_window_ok_seat(p);	
	gtk_widget_show_all(window_choose_to_buy);

}

void on_choose_seat(GtkWidget *button,struct theater* p)//选择影片完毕
{

	window_choose_seat = make_window_choose_seat(p);
	gtk_widget_show_all(window_choose_seat);
}

void toggle_clicked_callback (GtkWidget *widget, struct findrc *q)//点击座位按钮
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		weizhi[q->r][q->c]=2;
	}
	else
	{
		weizhi[q->r][q->c]=0;
	}
}

void update_seat_file(struct theater *p)//更新座位数据
{	
	gint i,j;
	strcpy(choose_name,p->name);
	strcat(choose_name,".txt");
	fp=fopen(choose_name,"wt+");
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
			if(weizhi[i][j]==0)
			{
				fprintf(fp,"0 ");
			}
			else
			{
				fprintf(fp,"1 ");
			}
		}
	}
	fclose(fp);
}

void on_put_money(GtkWidget *button,struct theater *p)//付款，即将输入账户密码
{
	GtkWidget *window;
	window = make_window_buy_passwd(p);
	gtk_widget_show_all(window);

}

void on_succeed_login(GtkWidget *button,struct theater *p)//支付登录成功
{
	GtkWidget *window;
	window = make_tobuy_yesorno(p);
	gtk_widget_show_all(window);
	
}

void on_succeed_buy(GtkWidget *button,struct theater *p)//成功支付
{
	update_seat_file(p);
	gtk_main_quit();
}



