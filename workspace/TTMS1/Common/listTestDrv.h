/*
 * listTestDrv.h
 *
 *  Created on: 2015年4月26日
 *      Author: edu
 */

#ifndef COMMON_LISTTESTDRV_H_
#define COMMON_LISTTESTDRV_H_


typedef struct TestListRec
{
    int value;
}TestListRec_t;

typedef struct TestListNode
{
    TestListRec_t data;
    struct TestListNode *next, *prev;
}TestList_Node_t, *TestList_t;

static void ListTest_Empty();

static void ListTest_Init();

static void ListTest_AddTail();

static void ListTest_AddHead();

static void ListTest_Free();

static void ListTest_Destroy();

void List_TestDriver_Entry();


#endif /* COMMON_LISTTESTDRV_H_ */
