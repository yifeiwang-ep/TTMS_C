#include<gtk/gtk.h>
#include"interface.h"
#include"callback.h"

int main(int argc,char *argv[])
{
	gtk_init(&argc , &argv);	

	theater_num = 0;

	window_main = make_window_main();

	window_main_buy = make_window_main_buy();
	window_main_login = make_window_main_login();	
	window_change_yesorno = make_window_yesorno();
	
	window_main_change = make_window_main_change();
	gtk_widget_show_all(window_main);

	gtk_main();

	return 0;
}
