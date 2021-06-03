/*
 * @FileName: small_rtos_api.h
 * @Author: chen jixuan
 * @Date: 2021-05-08 20:15:30
 * @Version: v1.0
 * @Description: small_rtos的api函数
 */
#ifndef _SMALL_RTOS_API_H_
#define _SMALL_RTOS_API_H_
#include "small_rtos_define.h"

//申请内存
extern void *OsMalloc(uint16);
//释放内存
extern void OsFree(void *now_addr);
//返回当前任务总数
extern uint8 TaskNum();
//创建任务 
extern int8 TaskCreate(void(*task_name)(void),uint8 task_priority); 



#endif
