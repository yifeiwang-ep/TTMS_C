/*
* File name:  Play.h
* File ID:	  TTMS_SSF_Play_Srv_Head
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/

#ifndef PLAY_H_
#define PLAY_H_

#include "../Common/common.h"

typedef enum {
	PLAY_TYPE_FILE=1,
	PLAY_TYPE_OPEAR=2,
	PLAY_TYPE_CONCERT=3
} play_type_t;//剧目类型定义，1表示电影，2表示歌剧，3表示音乐会

typedef enum {
	PLAY_RATE_CHILD = 1,
	PLAY_RATE_TEENAGE = 2,
	PLAY_RATE_ADULT = 3
} play_rating_t;//演出级别类型定义，1表示儿童可观看，2表示青少年可观看，3表示成人可观看

typedef struct {//剧目信息定义
	int id;                  //信息ID号
	char name[31];           //剧目名称
	play_type_t type;        //剧目类型
	char area[9];            //剧目来源地区
	play_rating_t rating;    //剧目级别
	int duration; //以分钟为单位   //演出时长
	user_date_t start_date;  //上映日期
	user_date_t end_date;    //结束日期
	int price;               //票的价格
} play_t;

//定义剧目信息的双向链表结构
typedef struct play_node {
	play_t data;
	struct play_node *next, *prev;
} play_node_t, *play_list_t;

/*
 * Function:    Play_Srv_Add
 * Function ID:	TTMS_SCU_Play_Srv_Add
 * Description: 添加一条剧目信息
 * Input:       待添加的剧目信息数据
 * Output:      无
 * Return:      添加的记录数
 */
inline int Play_Srv_Add(const play_t *data);

/*
 * Function:    Play_Srv_Modify
 * Function ID:	TTMS_SCU_Play_ Srv _Mod
 * Description: 更新一条剧目信息
 * Input:       待更新的剧目信息数据
 * Output:      无
 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
 */
inline int Play_Srv_Modify(const play_t *data);

/*
 * Function:    Play_Srv_DeleteByID
 * Function ID:	TTMS_SCU_Play_Srv_DelByID
 * Description: 按照ID号删除剧目信息
 * Input:       待删除的剧目ID号
 * Output:      无
 * Return:      0表示删除失败，1表示删除成功
 */
inline int Play_Srv_DeleteByID(int ID);

/*
 * Function:    Play_Srv_FetchByID
 * Function ID:	TTMS_SCU_Play_Srv_FetchByID
 * Description: 按照ID号查找一条剧目信息，存入buf所指单元
 * Input:       待查找的剧目ID号，将查找到的信息保存到buf中
 * Output:      无
 * Return:      0表示未找到，1表示找到了
 */
inline int Play_Srv_FetchByID(int ID, play_t *buf);

/*
 * Function:    Play_Srv_FetchAll
 * Function ID:	TTMS_SCU_Play_Srv_FetchAll
 * Description: 将所有剧目信息建立成一条链表
 * Input:       list剧目信息链表的头指针
 * Output:      无
 * Return:      返回查找到的记录数目
 */
inline int Play_Srv_FetchAll(play_list_t list);

/*
 * Function:    Play_Srv_FetchByName
 * Function ID:	TTMS_SCU_Play_Srv_FetchByName
 * Description: 根据剧目名称查找剧目，返回载入的剧目数量
 * Input:       list为查找到的剧目信息链表的头指针，condt为模糊查询的关键字
 * Output:      无
 * Return:      返回查找到的记录数目
 */
inline int Play_Srv_FetchByName(play_list_t list, char condt[]);

/*
 * Function:    Play_Srv_FilterByName
 * Function ID:	TTMS_SCU_Play_Srv_FilterByName
 * Description: 根据剧目名称查找剧目，返回载入的剧目数量
 * Input:       list为查找到的剧目信息链表的头指针，filter为过滤词
 * Output:      无
 * Return:      返回查找到的记录数目
 */
int Play_Srv_FilterByName(play_list_t list, char filter[]);

#endif //PLAY_H_
