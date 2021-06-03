/*
 * @FileName: small_rtoe_hardware.h
 * @Author: chen jixuan
 * @Date: 2021-05-04 17:23:00
 * @Version: v1.0
 * @Description: 系统硬件初始化
 */
#ifndef _SMALL_RTOS_HARDWARE_H_
#define _SMALL_RTOS_HARDWARE_H_

#include "small_rtos_define.h"
#include "os_register.h"


#define TIME_SLICE  5 //时间片长度以ms为单位
#define FOSC 11059200L //晶振频率
#define TIMER0_SET (65536-TIME_SLICE*FOSC/1000)


//硬件初始化
void HardwareInit();
//串口初始化
void Uart1Init(void);
char putchar(char dat);
//定时器零初始化
void Timer0Init(uint32 tim);

#endif
