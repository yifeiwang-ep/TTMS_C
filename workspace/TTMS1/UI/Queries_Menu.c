#include <stdio.h>
#include <stdlib.h>

#include "../Common/ComFunction.h"
#include "Queries_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"

void Queries_Menu(int flag){

	char choice;
     while(1){
		system("clear");
       		printf("\n\n\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		printf("\t\t\t------------------------------------查询 菜单--------------------------------------\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		printf("\t\t==============[A]剧目查询=============================[B]演出计划查询==================\n\n");
       		printf("\t\t==============[R]返回====================================================================\n\n");
       		printf("\t\t=======================================================================================\n\n");
       		printf("\t\t请选择:");
			
		choice=l_getc();
		if('r'==choice || 'R'==choice) break;	
		switch(choice){
					
					case 'a':
					case 'A':
						DisplayQueryPlay();
						break;
					case 'b':
					case 'B':
						Schedule_UI_Query(-1);
						
						break;
					
		}
	}
       		
		
}
