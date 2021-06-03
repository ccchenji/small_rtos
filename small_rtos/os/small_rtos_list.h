/*
 * @FileName: small_rtos_list.h
 * @Author: chen jixuan
 * @Date: 2021-03-26 11:20:06
 * @Version: v1.0
 * @Description: ����.h�ļ�
 */
#ifndef _SMALL_RTOS_LIST_H_
#define _SMALL_RTOS_LIST_H_

#include  "os_rtos_malloc.h"
#include "small_rtos_define.h"


#define PROCESS_STACK_MAX 25    //���̶�ջ��С
//����״̬
enum process_state{ready=1,block=2,running=3,hangup=4};
//��¼����pcb��Ϣ
typedef struct _core_pcb
{
    enum process_state process_state_;//����״̬
    uint8 process_priority_;//�������ȼ�
    uint8 process_stack_[PROCESS_STACK_MAX];//���̶�ջ
    uint8 process_pid_;//����PID
    uint8 sp_;
    void(*process_function_)(void);//���̺���
} core_pcb;
//������������
typedef core_pcb ListType;
//�������ݽṹ
typedef struct _LNode
{
    ListType data_;
    struct _LNode *next_;
    
}ListNode,*PListNode;
//�������ݽṹ
typedef struct _OsList
{
    uint16 num_;//����ڵ������
    bool is_init_;//�����Ƿ��ʼ��
    PListNode next_;//ָ����һ��������
}OsList,*POsList;


//����һ���յ����Ա�
bool InitList(POsList* now_list);
//�������Ա�l
bool DestroyList(POsList *now_list);
//��L����Ϊ�ձ�
bool ClearList(POsList now_list);
//���б�����������
bool ListAppend(POsList now_list,ListType *dat);
//ɾ��������ĺ͸���Ԫ����ȵ�Ԫ��
PListNode ListDelete(POsList now_list,ListType* now_data);
bool CompareListType(ListType* first_data,ListType* second_data);
//�����б��һ�����ݵ�ָ��
PListNode ListFirstNode(POsList now_list);
//���б��һ�������������һλ
void NodeFirstToLast(POsList now_list);



#endif
