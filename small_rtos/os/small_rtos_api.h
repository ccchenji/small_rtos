/*
 * @FileName: small_rtos_api.h
 * @Author: chen jixuan
 * @Date: 2021-05-08 20:15:30
 * @Version: v1.0
 * @Description: small_rtos��api����
 */
#ifndef _SMALL_RTOS_API_H_
#define _SMALL_RTOS_API_H_
#include "small_rtos_define.h"

//�����ڴ�
extern void *OsMalloc(uint16);
//�ͷ��ڴ�
extern void OsFree(void *now_addr);
//���ص�ǰ��������
extern uint8 TaskNum();
//�������� 
extern int8 TaskCreate(void(*task_name)(void),uint8 task_priority); 



#endif
