/*
 * Salesanalysis_UI.h
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#ifndef SALESANALYSIS_UI_H_
#define SALESANALYSIS_UI_H_
#include "../Common/list.h"
#include "../Service/Account.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"


void SalesAanalysis_UI_BoxOffice();
void SalesAanalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate);
void SalesAanalysis_UI_MgtEntry();

#endif /* SALESANALYSIS_UI_H_ */


