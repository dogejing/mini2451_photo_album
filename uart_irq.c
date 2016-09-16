#include "app.h"

void Uart0_Interrupt_Init(void)
{ 
	INTMSK &= ~(1<<28);     //Uart0中断带有子中断，需要将UART0总中断屏蔽位，置为无效。
	INTSUBMSK &= ~((1<<0)|(1<<1));   //将发送中断和接受中断屏蔽位，置为无效     
}      

void Uart0_Interrupt_Close(void)
{
	INTMSK |= (1<<28);
	INTSUBMSK |= ((1<<0)|(1<<1));
}


