/*
 ============================================================================
 Name        : TTMS.c
 Author      : shu xinfeng
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <gtk/gtk.h>
#include "./View/Window_UI.h"
#include "./View/Login_UI.h"
#include "./Service/Account.h"

int main(int argc, char *argv[])
{
	Account_Srv_InitSys();
	gtk_init(&argc,&argv);
	login_window = Login_UI_MgtEntry();
	gtk_widget_show_all(login_window);
	gtk_main();
	return 0;
}
