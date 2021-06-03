/*
 * @FileName: small_rtos_hardware.c
 * @Author: chen jixuan
 * @Date: 2021-05-04 17:22:44
 * @Version: 当前版本
 * @Description: 系统硬件初始化
 */

#include "small_rtos_hardware.h"

/**
 * @Name: HardwareInit
 * @Description: 硬件初始化
 * @Date: 2021-05-08 20:11:14
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void HardwareInit()
{
	//串口初始化
	Uart1Init();
	//定时器0初始化
	Timer0Init(TIMER0_SET);
}
/**
 * @Name: UartInit()
 * @Description: 串口1初始化
 * @Date: 2021-05-04 17:29:18
 * @Author: chen jixuan
 * @Param: none
 * @Return: none
 */
void Uart1Init(void)
{
    SCON = 0x50;  //8位数据,可变波特率
    AUXR |= 0x40; //定时器时钟1T模式
    AUXR &= 0xFE; //串口1选择定时器1为波特率发生器
    TMOD &= 0x0F; //设置定时器模式
    TL1 = 0xE0;   //设置定时初始值
    TH1 = 0xFE;   //设置定时初始值
    ET1 = 0;      //禁止定时器%d中断
    TR1 = 1;      //定时器1开始计时
}

/**
 * @Name: putchar()
 * @Description: 重写printf底层函数
 * @Date: 2021-05-04 17:29:48
 * @Author: chen jixuan
 * @param {char} dat
 * @Return: {char} dat
 */
int8 putchar(int8 dat)
{
    ES = 0;
    SBUF = dat;
    while (!TI);
    TI = 0;
    ES = 1;
    return dat;
}

/**
 * @Name: Timer0Init()
 * @Description: 定时器0初始化->用于任务切换
 * @Date: 2021-05-04 17:31:16
 * @Author: chen jixuan
 * @param {uint32} tim
 * @Return: none
 */
void Timer0Init(uint32 tim)
{
    //定时器0初始化，定时器零用于任务切换
    AUXR |= 0x80;   //定时器时钟1T模式
    TMOD &= 0xF0;   //设置定时器模式
    TL0 = tim;      //设置定时初值
    TH0 = tim >> 8; //设置定时初值
    TF0 = 0;        //清除TF0标志
    TR0 = 1;        //定时器0开始计时
    ET0 = 1;        //使能定时器中断
    EA  = 1;        //开启总中断
}