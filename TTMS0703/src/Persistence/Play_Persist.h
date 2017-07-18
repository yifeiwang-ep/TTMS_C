
#ifndef PLAYPERSIST_H_
#define PLAYPERSIST_H_

#include "../Service/Play.h"

	int Play_Perst_Insert(const play_t *data);

	int Play_Perst_Update(const play_t *data);

	int Play_Perst_DeleteByID(int ID);

	int Play_Perst_SelectByID(int ID, play_t *buf);

	int Play_Perst_SelectByName(play_list_t list, char condt[]);

	int Play_Perst_SelectAll(play_list_t list);

#endif /* PLAYPERSIST_H_ */
