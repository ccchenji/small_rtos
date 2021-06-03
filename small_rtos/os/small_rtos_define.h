/*
 * @FileName: small_rtos_define.h
 * @Author: chen jixuan
 * @Date: 2021-04-29 20:48:29
 * @Version: v1.0
 * @Description: 定义的类型
 */
#ifndef _SMALL_RTOS_DEFINE_H_
#define _SMALL_RTOS_DEFINE_H_

#define uint8       unsigned char
#define uint16      unsigned int
#define uint32      unsigned long
#define int8        char
#define bool        uint8
#define int16       int
#define int32       long
#define TRUE        1
#define FALSE       0
#define NULL        ((void*)2000) //不能用((void*)0),因为这个内存会被使用




#endif