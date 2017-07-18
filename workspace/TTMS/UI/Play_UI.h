
#ifndef PLAY_UI_H_
#define PLAY_UI_H_
#include "../Common/list.h"
#include "../Service/Play.h"

static const int PLAY_PAGE_SIZE=6;

int Play_UI_Add(void);

int Play_UI_Modify(int id);

int Play_UI_Delete(int id);

//int Play_UI_Query(int id);

/*以列表模式显示剧目信息*/
//void Play_UI_ShowList(play_list_t list, Pagination_t paging);

void Play_UI_MgtEntry(int flag);//flag为0，进入管理页面，flag为1进入查询界面


void Play_UI_Query();

#endif /* PLAY_UI_H_ */
