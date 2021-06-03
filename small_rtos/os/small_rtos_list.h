/*
 * @FileName: small_rtos_list.h
 * @Author: chen jixuan
 * @Date: 2021-03-26 11:20:06
 * @Version: v1.0
 * @Description: 链表.h文件
 */
#ifndef _SMALL_RTOS_LIST_H_
#define _SMALL_RTOS_LIST_H_

#include  "os_rtos_malloc.h"
#include "small_rtos_define.h"


#define PROCESS_STACK_MAX 25    //进程堆栈大小
//进程状态
enum process_state{ready=1,block=2,running=3,hangup=4};
//记录进程pcb信息
typedef struct _core_pcb
{
    enum process_state process_state_;//进程状态
    uint8 process_priority_;//任务优先级
    uint8 process_stack_[PROCESS_STACK_MAX];//进程堆栈
    uint8 process_pid_;//进程PID
    uint8 sp_;
    void(*process_function_)(void);//进程函数
} core_pcb;
//链表数据类型
typedef core_pcb ListType;
//链表数据结构
typedef struct _LNode
{
    ListType data_;
    struct _LNode *next_;
    
}ListNode,*PListNode;
//链表数据结构
typedef struct _OsList
{
    uint16 num_;//链表节点的数量
    bool is_init_;//链表是否初始化
    PListNode next_;//指向下一个数据域
}OsList,*POsList;


//构造一个空的线性表
bool InitList(POsList* now_list);
//销毁线性表l
bool DestroyList(POsList *now_list);
//将L重置为空表
bool ClearList(POsList now_list);
//向列表最后添加数据
bool ListAppend(POsList now_list,ListType *dat);
//删除链表里的和给定元素相等的元素
PListNode ListDelete(POsList now_list,ListType* now_data);
bool CompareListType(ListType* first_data,ListType* second_data);
//返回列表第一个数据的指针
PListNode ListFirstNode(POsList now_list);
//将列表第一个数据移至最后一位
void NodeFirstToLast(POsList now_list);



#endif
