/*
 * @FileName: os_rtos_malloc.h
 * @Author: chen jixuan
 * @Date: 2021-05-02 14:59:57
 * @Version: v1.0
 * @Description: 自己实现的malloc
 */
#ifndef _OS_RTOS_MALLOC_H_
#define _OS_RTOS_MALLOC_H_

#include "small_rtos_define.h"

#define OS_MEMORY_SIZE 1000 //以字节为单位

typedef struct _os_block
{
    uint16 size_;            //申请字节的大小
    bool is_free_;           //当前内存是否被使用 0:被使用; 1:未被使用
    struct _os_block *next_; //指向下一个内存区块
} os_block;

//对内存链表进行初始化
void InitMemory();
//申请内存
void *OsMalloc(uint16 malloc_size);
//分割内存
void SplitMemory(os_block *now_addr, uint16 size);
//释放内存
void OsFree(void *now_addr);
void MergeMemory();

#endif
