/*
 * @FileName: small_rtos_core.h
 * @Author: chen jixuan
 * @Date: 2021-05-04 12:35:20
 * @Version: v1.0 
 * @Description: 内核.c文件
 */
#include "small_rtos_core.h"
#include "stdio.h"

//就绪队列
xdata POsList ready_queue=NULL;	
//阻塞队列
//xdata POsList block_queue=NULL;	
//挂起队列
//xdata POsList hangup_queue=NULL; 
//进程堆栈
idata uint8 process_stack[PROCESS_STACK_MAX]={0};
//记录当前任务数量
uint8 task_num=0;
//任务pid
uint8 pid_pool[PID_POOL_SIZE]={0};
/**
 * @Name: SmallOsInit()
 * @Description: 系统初始化, 必须先初始化
 * @Date: 2021-05-04 16:57:28
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void SmallOsInit()
{
	//硬件初始化
	HardwareInit();
	//初始化内存
	InitMemory();
	//就绪队列初始化
	InitList(&ready_queue);
	////阻塞队列初始化
	//InitList(&block_queue);
	////挂起队列初始化
	//InitList(&hangup_queue);
}

/**
 * @Name: main()
 * @Description: small_rtos运行主函数
 * @Date: 2021-05-06 15:02:29
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void main()
{
	//必须先初始化
	SmallOsInit();
	//创建系统任务
	TaskCreate(small_rtos_system_task,3);
	ready_queue->next_->data_.process_state_=running;
	ready_queue->next_->data_.sp_=(uint8)(process_stack);
	ready_queue->next_->data_.process_function_();
}
/**
 * @Name: GetTaskPid
 * @Description: 从编号池获得任务pid
 * @Date: 2021-05-06 15:39:15
 * @Author: chen jixuan
 * @Param: none
 * @Return: 成功返回pid序号,失败返回-1
 */
int8 GetPoolPid()
{
	uint8 i=0;
    uint8 j=0;
    uint8 size=0;
	for(i=0;i<PID_POOL_SIZE;i++)
	{
        if((i+1)==PID_POOL_SIZE)
            size=Task_MAX_NUM-i*POOL_BLOCK_SIZE;
        else
            size=POOL_BLOCK_SIZE;
        for(j=0;j<size;j++)
        {
            if(((pid_pool[i]>>j)&0x01)==0)
            {
                pid_pool[i]=pid_pool[i]|(0x01<<j);
                return j+i*POOL_BLOCK_SIZE;
            }
        }
	}
	return -1;
}
/**
 * @Name: TaskCreate
 * @Description: 
 * @Date: 2021-05-06 15:20:01
 * @Author: chen jixuan
 * @param {void(*task_name)(void)} 
 * @param {uint8} task_priority
 * @Return: 成功返回进程pid,失败返回-1
 */
int8 TaskCreate(void(*task_name)(void),uint8 task_priority)
{
	xdata ListType temp_pcb;
	temp_pcb.process_pid_=GetPoolPid();
	if(temp_pcb.process_pid_==-1)
		return -1;
	temp_pcb.process_function_=task_name;
	temp_pcb.process_priority_=task_priority;
	temp_pcb.process_stack_[0]=((uint16)task_name)&0x00ff;
	temp_pcb.process_stack_[1]=(((uint16)task_name)>>8)&0x00ff;
	temp_pcb.sp_=(uint8)(process_stack+14);
	temp_pcb.process_state_=ready;
	task_num++;
	ListAppend(ready_queue,&temp_pcb);
	return temp_pcb.process_pid_;
}

/**
 * @Name: TaskNum
 * @Description: 返回当前任务总数
 * @Date: 2021-05-06 15:29:58
 * @Author: chen jixuan
 * @Param: none
 * @Return: 返回当前任务总数
 */
uint8 TaskNum()
{
	return task_num;
}

/**
 * @Name: small_rtos_task0
 * @Description: 系统第一个任务 
 * @Date: 2021-05-06 20:02:36
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void small_rtos_system_task()
{
	small_rtos_main();
	while(1);
}

/**
 * @Name: TimeroTaskSwitch
 * @Description: 定时器0中断用于任务切换
 * @Date: 2021-05-07 11:06:42
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void TaskSwitch() 
{
	static uint8 count=0;
	count++;
	if(count>=N_TIME_SLICE)
	{
		if (ready_queue->num_ > 1)
		{
			uint8 i = 0;
			uint8 h_addr, l_addr; //记录当前函数地址
			uint16 temp_sp = SP;  //用于记录当前SP指针值
			PListNode temp_node;
			h_addr = process_stack[temp_sp - (uint8)process_stack];
			l_addr = process_stack[temp_sp - (uint8)process_stack - 1];
			temp_node = ListFirstNode(ready_queue);
			temp_node->data_.sp_ = SP - 2; //调用函数多压了一个地址,所以将SP指针减2
			for (i = 0; i < PROCESS_STACK_MAX; i++)
			{
				temp_node->data_.process_stack_[i] = process_stack[i];
			}
			temp_node->data_.process_state_ = ready;
			//任务切换
			NodeFirstToLast(ready_queue);
			temp_node = ListFirstNode(ready_queue);
			for (i = 0; i < PROCESS_STACK_MAX; i++)
			{
				process_stack[i] = temp_node->data_.process_stack_[i];
			}
			SP = temp_node->data_.sp_ + 2; //空出两个字节存贮当前函数的返回地址
			process_stack[temp_node->data_.sp_ + 1 - (uint8)process_stack] = l_addr;
			process_stack[temp_node->data_.sp_ + 2 - (uint8)process_stack] = h_addr;
			temp_node->data_.process_state_ = running;
		}
		count=0;
	}
}
