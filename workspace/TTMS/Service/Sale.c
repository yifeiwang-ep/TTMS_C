#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Query_Persist.h"

//根据票的信息插入到订单的信息
inline int Sale_Srv_Add(const sale_t *data) {
	return Sale_Perst_Insert(data);
}

//删除订单的信息
inline int Sale_Srv_DeleteByID(int saleID) {
	return Sale_Perst_DeleteByID(saleID);
}

/*
//通过uid查询订单
inline int Sale_Srv_SelectByUid(char *queryuid, Sale_list_t head) {
	return Sale_Infor_By_Uid(queryuid, head);
}

//根据时间查询订单
inline int Sale_Srv_selectByTime(char querytime[][30], Sale_list_t head) {
	return Sale_Infor_By_Time(querytime, head);
}
*/
