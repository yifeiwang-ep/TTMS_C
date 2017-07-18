
#include<stdlib.h>
#include<string.h>

gint theater_num;
gint temp_row;
gchar *temp[9];
gchar choose_name[50];
gint weizhi[8][8];

GtkWidget *window_main;
GtkWidget *window_main_login;
GtkWidget *window_main_change;
GtkWidget *window_main_buy;
GtkWidget *window_change_yesorno;
GtkWidget *window_choose_seat;
GtkWidget *window_choose_to_buy;

GtkWidget *list;

GtkWidget *text_name;
GtkWidget *text_type;
GtkWidget *text_people;
GtkWidget *text_time;
GtkWidget *text_place;
GtkWidget *text_message;
GtkWidget *text_photo;
GtkWidget *text_price;
GtkWidget *text_score;

struct findrc
{
	int r;
	int c;
};

struct findrc *q;

struct theater
{

	gchar name[500];
	gchar type[500];
	gchar people[500];
	gchar time[30];
	gchar place[30];
	gchar message[500];
	gchar photo[20];
	gchar price[10];
	gchar score[10];
}th;

struct theater* p;

FILE *fp;

void on_main_to_login(GtkWidget *widget , gpointer userdate);

void on_login_to_main(GtkWidget *widget , gpointer userdate);

void want_to_quit(GtkWidget *widget ,gpointer userdate);

void on_change_yes(GtkWidget *widget ,gpointer userdate);

void on_change_no(GtkWidget *widget ,gpointer userdate);

void on_login_to_change(GtkWidget *widget , gpointer userdate);

void list_delete (GtkButton *button,gpointer userdate);

void list_clear(GtkButton *button,gpointer userdate);

void list_add(GtkButton *button , gpointer userdate);

void list_change(GtkButton *button , gpointer userdate);

void on_main_to_buy(GtkWidget *widget ,gpointer userdate);

void selection_made( GtkWidget *list,gint row,gint column,GdkEventButton *event,gpointer userdate);

void list_made(GtkWidget *list,struct theater *p);

void destroy(GtkWidget *button,GtkWidget *window);

void to_add_list_item(GtkWidget *button ,gpointer userdate);

void to_change_list_item(GtkWidget *button ,gpointer userdate);

void made_file();

void on_seat_to_buy(GtkWidget *button,gpointer userdate);

void on_choose_seat(GtkWidget *button,struct theater* p);

void on_choose_seat_ok (GtkWidget *button,struct theater* p);

void toggle_clicked_callback (GtkWidget *widget, struct findrc *p);

void on_put_money(GtkWidget *button,struct theater *p);

void update_seat_file(struct theater *p);

void on_ok_to_seat(GtkWidget *button,gpointer userdate);

void on_succeed_login(GtkWidget *button,struct theater *p);

void on_succeed_buy(GtkWidget *button,struct theater *p);
