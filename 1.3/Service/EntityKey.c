#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EntityKey.h"
#include "../Common/common.h"
#include "../Common/list.h"
#include "../Persistence/EntityKey_Persist.h"

/*根据传入的实体名entName，为新实体分配一个唯一的主键。函数返回值为取新实体的主键值*/
inline long EntKey_Srv_CompNewKey(char entName[]) {
	return EntKey_Srv_CompNewKeys(entName, 1);
}

/*根据传入的实体名entName及实体个数count，为这个count个新实体分配一个长度为count的主键值区间，
 * 使得每个新实体在该区间内都可以分配到 唯一的 主键。返回值为该主键区间的最小值*/
inline long EntKey_Srv_CompNewKeys(char entName[], int count) {
	char entUpperName[41];

	if (count < 1) {
		printf("Entity count must be bigger than 0!\n");
		return 0;
	}

	int nameLen = strlen(entName);
	if (nameLen < 0 || nameLen > 40) {
		printf("Entity name must be within 1~40!\n");
		return 0;
	}

	memcpy(entUpperName, entName, nameLen);
	entUpperName[nameLen] = '\0';

	/*转换为大写*/
	Str2Upper(entUpperName);

	return EntKey_Perst_GetNewKeys(entUpperName, count);
}


//将主键key保存到主键链表keyList中
inline void EntKey_Srv_Add2List(entkey_list_t keyList, long key) {
	assert(NULL != keyList);
	if (!EntKey_Srv_CheckExist(keyList, key)) {
		entkey_node_t *newNode = (entkey_node_t *) malloc(
				sizeof(entkey_node_t));
		if (NULL == newNode) {
			printf("Memory overflow!\n");
			return;
		} else {

			newNode->data.key = key;
			List_AddTail(keyList, newNode);
		}
	}
}

//在主键链表keyList中检查key是否存在，返回1存在，否则0
inline int EntKey_Srv_CheckExist(entkey_list_t keyList, long key){
	assert(NULL!=keyList);
	entkey_node_t *p;
	List_ForEach(keyList, p){
		if(p->data.key==key)
			return 1;
	}
	return 0;
}
