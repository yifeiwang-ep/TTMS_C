#ifndef PLAY_H_
#define PLAY_H_

#include "../Common/Common.h"

typedef enum {
	PLAY_TYPE_FILM=1,
	PLAY_TYPE_OPEAR=2,
	PLAY_TYPE_CONCERT=3
} play_type_t;

typedef enum {
	PLAY_RATE_CHILD = 1,
	PLAY_RATE_TEENAGE = 2,
	PLAY_RATE_ADULT = 3
} play_rating_t;

typedef struct {
	int id;
	char name[31];
	play_type_t type;
	char area[9];
	play_rating_t rating;
	int duration; //以分钟为单位
	user_date_t start_date;
	user_date_t end_date;
	int price;
} play_t;

//双向链表
typedef struct play_node {
	play_t data;
	struct play_node *next, *prev;
} play_node_t, *play_list_t;

inline int Play_Srv_Add(const play_t *data);

inline int Play_Srv_Modify(const play_t *data);

inline int Play_Srv_DeleteByID(int ID);

inline int Play_Srv_FetchByID(int ID, play_t *buf);

inline int Play_Srv_FetchAll(play_list_t list);

//根据剧目名称载入剧目，返回载入的剧目数量
inline int Play_Srv_FetchByName(play_list_t list, char condt[]);

//根据剧目名称过滤词filter对list进行过滤，返回过滤后剩余的剧目数量
int Play_Srv_FilterByName(play_list_t list, char filter[]);

#endif //PLAY_H_
