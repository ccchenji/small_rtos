/*
 * @FileName: small_rtos_list.c
 * @Author: chen jixuan
 * @Date: 2021-04-29 20:39:42
 * @Version: ��ǰ�汾
 * @Description: �Ը��ļ�������
 */

#include "small_rtos_list.h"

/**
 * @Name: InitList
 * @Description: ��ʼ���б�,δ��ʼ�����б�Ҫ��ֵΪNULL,��Ȼ�ú����޷���ʼ��
 * @Date: 2021-04-29 21:20:25
 * @Author: chen jixuan
 * @Return: ��ʼ���ɹ�����true,ʧ�ܷ���false
 * @param {POsList} *now_list
 */
bool InitList(POsList *now_list)
{
    if (*now_list==NULL)
    {

        (*now_list) = (POsList)OsMalloc(sizeof(OsList));
        if((*now_list)==NULL)
            return FALSE;
        (*now_list)->next_ = NULL;
        (*now_list)->num_ = 0; //��ǰ�б�Ľڵ���
        (*now_list)->is_init_ = TRUE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @Name: DestroyList
 * @Description: �����б�
 * @Date: 2021-04-29 21:21:37
 * @Author: chen jixuan
 * @Return:  �ɹ�����true,ʧ�ܷ���false
 * @param {POsList} *now_list
 */
bool DestroyList(POsList *now_list)
{
    PListNode node;
    PListNode temp;
    if((*now_list)!=NULL&&(*now_list)->is_init_==TRUE)
    {
        node = (*now_list)->next_;
        OsFree((*now_list));
        (*now_list)=NULL;
        while (node)
        {
            temp = node->next_;
            OsFree(node);
            node = temp;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @Name: ClaerList
 * @Description: ����б�
 * @Date: 2021-04-29 21:23:30
 * @Author: chen jixuan
 * @Return: �ɹ�����true,ʧ�ܷ���false 
 * @param {POsList} now_list
 */
bool ClearList(POsList now_list)
{
    PListNode ptr,qtr;
    if(now_list!=NULL&&now_list->is_init_==TRUE)
    {
        ptr = now_list->next_;
        while (ptr!=NULL)
        {
            qtr = ptr->next_;
            OsFree(ptr);
            ptr = qtr;
        }
        now_list->is_init_ = TRUE;
        now_list->next_ = NULL;
        now_list->num_ = 0;
        return TRUE;
    }
    else
        return FALSE;
}

/**
 * @Name: ListAppend
 * @Description: ����������������
 * @Date: 2021-04-29 21:25:00
 * @Author: chen jixuan
 * @Return: �ɹ�����true,ʧ�ܷ���false
 * @param {POsList} now_list
 * @param {ListType} *dat
 */
bool ListAppend(POsList now_list,ListType *dat)
{
    PListNode ptr;
    if(now_list!=NULL&&now_list->is_init_)
    {
        ptr=now_list->next_;
        if(now_list->next_==NULL)
        {
            now_list->next_=(PListNode)OsMalloc(sizeof(ListNode));
            if(now_list->next_==NULL)
                return FALSE;
            now_list->next_->data_=*dat;
            now_list->next_->next_=NULL;
            now_list->num_=1;
            return TRUE;
        }
        else
        {
            while(ptr->next_!=NULL)
            {
                ptr=ptr->next_;
            }
            ptr->next_=(PListNode)OsMalloc(sizeof(ListNode));
            if(ptr->next_==NULL)
                return FALSE;
            ptr->next_->data_=*dat;
            ptr->next_->next_=NULL;
            now_list->num_+=1;
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * @Name: ListDelete
 * @Description: ɾ���б��еĺ͸���Ԫ����ȵ�Ԫ��
 * @Date: 2021-04-29 21:26:17
 * @Author: chen jixuan
 * @Return: ����ɾ��Ԫ�صĺ�һ��Ԫ��
 * @param {POsList} now_list
 */
PListNode ListDelete(POsList now_list,ListType* now_data)
{
    PListNode ptr;
    PListNode qtr;
    if(now_list!=NULL&&now_list->is_init_)
    {
        ptr=now_list->next_;
        //�Ե�һ���ڵ㵥������
        if(now_list->next_!=NULL)
        {
            if(CompareListType(&ptr->data_,now_data))
            {
                now_list->next_=ptr->next_;
                OsFree(ptr);
                now_list->num_-=1;
                return now_list->next_;
            }
        }
        else
            return NULL;
        while(ptr->next_!=NULL)
        {
            qtr=ptr;
            ptr=ptr->next_;
            if(CompareListType(&ptr->data_,now_data))
            {
                qtr->next_=ptr->next_;
                OsFree(ptr);
                now_list->num_-=1;
                return qtr->next_;
            }
        }
    }
    return NULL;
}

/**
 * @Name: IntCompare
 * @Description: ���ڶ�int�����ݽ��бȽ�
 * @Date: 2021-04-29 21:27:10
 * @Author: chen jixuan
 * @param {ListType} first_data
 * @param {ListType} second_data
 * @Return: ��ȷ���true,ʧ�ܷ���false
 */
bool CompareListType(ListType* first_data,ListType* second_data)
{
    if(first_data->process_pid_==second_data->process_pid_)
        return TRUE;
    else
        return FALSE;
}

/**
 * @Name: ListFirstNode
 * @Description: 
 * @Date: 2021-05-07 11:21:01
 * @Author: chen jixuan
 * @param {PosList} *now_list
 * @Return: �����һ������ָ��
 */
PListNode ListFirstNode(POsList now_list)
{
    if(now_list->num_==0)
        return NULL;
    else
        return now_list->next_;
}

/**
 * @Name: NodeFirstToLast
 * @Description: ���������һ�������Ƶ����һλ
 * @Date: 2021-05-07 11:26:34
 * @Author: chen jixuan
 * @Param: 
 * @Return: 
 * @param {PRadarList} now_list
 */
void NodeFirstToLast(POsList now_list)
{
    PListNode temp_node;
    PListNode p,q;
    if(now_list->num_>=2)
    {
        temp_node=ListFirstNode(now_list);
        now_list->next_=now_list->next_->next_;
        p=now_list->next_;
        q=p;
        while(p!=NULL)
        {
            q=p;
            p=p->next_;
        }
        temp_node->next_=NULL;
        q->next_=temp_node;
    }
}






