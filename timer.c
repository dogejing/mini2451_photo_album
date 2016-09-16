#include "timer.h"
#include "irq.h"

void time0_init(void)
{
	//定时器计数时钟周期
	//PCLK / (prescaler value + 1) / (divider value) //PCLK被初始化66.666...mhz
	TCFG0 = 99;	//设置prescaler value		
	TCFG1 = 0x03;	//设置divider value  查表 //66666666 / 100 /16 = 41666
	TCNTB0 = 41666;	//定时时间为1s 
	TCON |= (1<<1);	//手动更新计数值
	TCON = 0x09;	//关手动更新。打开自动更新，打开定时器
	INTMSK1 &= ~(1<<10);	//打开定时器中断
}

