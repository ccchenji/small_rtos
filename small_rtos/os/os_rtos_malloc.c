/*
 * @FileName: os_rtos_malloc.c
 * @Author: chen jixuan
 * @Date: 2021-05-02 14:59:45
 * @Version: v1.0
 * @Description: .c�ļ�
 */

#include "os_rtos_malloc.h"

//���ٵ��ڴ��С
xdata int8 os_memory[OS_MEMORY_SIZE] = {0};
//���ڱ�
os_block xdata *free_list = NULL;

/**
 * @Name: InitMemory
 * @Description: ���ڴ�������г�ʼ��
 * @Date: 2021-05-02 17:17:17
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void InitMemory()
{
    free_list = (void *)os_memory;
    free_list->size_ = OS_MEMORY_SIZE - sizeof(os_block);
    free_list->is_free_ = TRUE;
    free_list->next_ = NULL;
}

/**
 * @Name: OsMalloc
 * @Description: �����ڴ�
 * @Date: 2021-05-02 17:23:10
 * @Author: chen jixuan
 * @param {int} malloc_size
 * @Return: ���뵽�ĵ�ַ;����ʧ�ܷ���NULL
 */
void *OsMalloc(uint16 malloc_size)
{
    os_block *curr;
    void *result_addr;
    //���û�г�ʼ������ó�ʼ������
    if ((uint16)free_list == NULL)
        InitMemory();
    curr = free_list;
    while ((curr->size_ < malloc_size) || (curr->is_free_ == FALSE))
    {
        if (curr->next_ != NULL)
        {
            curr = curr->next_;
        }
        else
        {
            return NULL;
        }
    }
    if (curr->size_ < (malloc_size + sizeof(os_block)))
    {
        curr->is_free_ = FALSE;
        result_addr = (void *)(++curr);
        return result_addr;
    }
    else if (curr->size_ >= (malloc_size + sizeof(os_block)))
    {
        SplitMemory(curr, malloc_size);
        result_addr = (void *)(++curr);
        return result_addr;
    }
    return NULL;
}

/**
 * @Name: SplitMalloc
 * @Description: �ָ��ڴ�
 * @Date: 2021-05-02 18:12:21
 * @Author: chen jixuan
 * @Param: {os_block} *now_addr
 * @param {int} size
 * @Return: none
 */
void SplitMemory(os_block *now_addr, uint16 size)
{
    //����һ��Ҫ��xdata,��Ȼ��ָ��RAM�������ⲿ��xdata���������
    os_block *new_data = (os_block xdata *)((unsigned int)now_addr + size + sizeof(os_block));
    new_data->size_ = now_addr->size_ - size - sizeof(os_block);
    new_data->is_free_ = TRUE;
    new_data->next_ = now_addr->next_;
    now_addr->size_ = size;
    now_addr->is_free_ = FALSE;
    now_addr->next_ = new_data;
}

/**
 * @Name: osFree
 * @Description: �ͷ��ڴ�
 * @Date: 2021-05-02 19:41:39
 * @Author: chen jixuan
 * @param {os_block} *now_addr
 * @Return: none
 */
void OsFree(void *now_addr)
{
    os_block *curr;
    if (((void *)os_memory < now_addr) && (now_addr <= (void *)((unsigned int)os_memory + OS_MEMORY_SIZE)))
    {
        os_block *now_ptr = now_addr;
        --now_ptr;
        for (curr = free_list; curr != NULL;)
        {
            if ((curr == now_ptr) && curr->is_free_ == FALSE)
            {
                now_ptr->is_free_ = TRUE;
                MergeMemory();
                break;
            }
            else if (curr->next_ != NULL)
            {
                curr = curr->next_;
            }
            else
            {
                break;
            }
        }
    }
}

/**
 * @Name: MergeMemory()
 * @Description: ���ڴ���кϲ�
 * @Date: 2021-05-03 17:35:10
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void MergeMemory()
{
    os_block *curr = free_list;
    while (curr->next_ != NULL)
    {
        if (curr->is_free_ && curr->next_->is_free_)
        {
            curr->size_ = curr->size_ + curr->next_->size_ + sizeof(os_block);
            curr->next_ = curr->next_->next_;
        }
        if (curr->next_ != NULL)
            curr = curr->next_;
        else
            break;
    }
}
