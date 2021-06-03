/*
 * @FileName: os_rtos_malloc.h
 * @Author: chen jixuan
 * @Date: 2021-05-02 14:59:57
 * @Version: v1.0
 * @Description: �Լ�ʵ�ֵ�malloc
 */
#ifndef _OS_RTOS_MALLOC_H_
#define _OS_RTOS_MALLOC_H_

#include "small_rtos_define.h"

#define OS_MEMORY_SIZE 1000 //���ֽ�Ϊ��λ

typedef struct _os_block
{
    uint16 size_;            //�����ֽڵĴ�С
    bool is_free_;           //��ǰ�ڴ��Ƿ�ʹ�� 0:��ʹ��; 1:δ��ʹ��
    struct _os_block *next_; //ָ����һ���ڴ�����
} os_block;

//���ڴ�������г�ʼ��
void InitMemory();
//�����ڴ�
void *OsMalloc(uint16 malloc_size);
//�ָ��ڴ�
void SplitMemory(os_block *now_addr, uint16 size);
//�ͷ��ڴ�
void OsFree(void *now_addr);
void MergeMemory();

#endif
