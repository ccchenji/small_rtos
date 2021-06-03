/*
 * @FileName: small_rtos_core.h
 * @Author: chen jixuan
 * @Date: 2021-05-04 12:35:37
 * @Version: v1.0
 * @Description: 内核.h文件
 */
#ifndef _SMALL_RTOS_CORE_H_
#define _SMALL_RTOS_CORE_H_
#include "small_rtos_define.h"
#include "os_register.h"
#include "os_rtos_malloc.h"
#include "small_rtos_hardware.h"
#include "small_rtos_list.h"

#define N_TIME_SLICE 4 //时间片具体长度以5ms为单位
//任务pid池相关
#define Task_MAX_NUM 5  //任务最大数量
#define POOL_BLOCK_SIZE 8
#define PID_POOL_SIZE Task_MAX_NUM/POOL_BLOCK_SIZE+1


//系统初始化
void SmallOsInit(void); 
//返回当前任务总数
uint8 TaskNum();
//创建任务 
int8 TaskCreate(void(*task_name)(void),uint8 task_priority); 
//从编号池获得任务pid
int8 GetPoolPid(void);
//系统第一个任务
void small_rtos_system_task(void);
//任务切换
void TaskSwitch();
//用户mian函数
extern void small_rtos_main(void);

#endif
