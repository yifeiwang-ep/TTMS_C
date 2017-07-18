/*
 * studio.c
 *
 *  Created on: 2015年6月12日
 *      Author: Administrator
 */
#include "Studio.h"
#include "../Persistence/Studio_Persist.h"
#include <stdlib.h>
#include <assert.h>

inline int Studio_Srv_Add(const studio_t *data) {
	return Studio_Perst_Insert(data);
}

inline int Studio_Srv_Modify(const studio_t *data) {
	return Studio_Perst_Update(data);
}

inline int Studio_Srv_DeleteByID(int ID) {
	return Studio_Perst_DeleteByID(ID);
}

inline int Studio_Srv_FetchByID(int ID, studio_t *buf) {
	return Studio_Perst_SelectByID(ID, buf);

}

inline int Studio_Srv_FetchAll(studio_list_t list) {
	return Studio_Perst_SelectAll(list);
}

//通过ID在list中查找对应放映厅结点
inline studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID){
	assert(NULL!=list);
	studio_node_t *ptr=list->next;
	while(ptr!=list){
		if(ptr->data.id==ID)
			return ptr;
		else
			ptr=ptr->next;
	}

	return NULL;
}
