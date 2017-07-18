/*
 * EntityKey.h
 *
 *  Created on: 2015年6月13日
 *      Author: Administrator
 */

#ifndef ENTITYKEY_H_
#define ENTITYKEY_H_

typedef struct {
	char entyName[41];
	long key;
} entity_key_t;

typedef struct entity_key_node{
	entity_key_t data;
	struct entity_key_node *prev;
	struct entity_key_node *next;
}entkey_node_t, *entkey_list_t;

/*根据传入的实体名entName，为新实体分配一个唯一的主键。函数返回值为取新实体的主键值*/
inline long EntKey_Srv_CompNewKey(char entName[]);

/*根据传入的实体名entName及实体个数count，为这个count个新实体分配一个长度为count的主键值区间，
 * 使得每个新实体在该区间内都可以分配到 唯一的 主键。返回值为该主键区间的最小值*/
inline long EntKey_Srv_CompNewKeys(char entName[], int count);

//将主键key保存到主键链表keyList中
inline void EntKey_Srv_Add2List(entkey_list_t keyList, long key);

//在主键链表keyList中检查key是否存在，返回1存在，否则0
inline int EntKey_Srv_CheckExist(entkey_list_t keyList, long key);

#endif /* ENTITYKEY_H_ */
