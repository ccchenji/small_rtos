/*
 * @FileName: small_rtos_main.c
 * @Author: chen jixuan
 * @Date: 2021-05-08 20:14:50
 * @Version: v1.0
 * @Description: 用户程序运行主函数
 */
#include "small_rtos_api.h"
#include "stdio.h"
void task1()
{
	int a=0;
	while(1)
	{
		printf("a=%d\r\n",a);
	}
}
void task2()
{
	int b=4;
	while(1)
	{
		printf("b=%d\r\n",b);
	}
}
void small_rtos_main()
{
	TaskCreate(task1,0);
	TaskCreate(task2,0);
}
