#include "app.h"

void Uart0_Interrupt_Init(void)
{ 
	INTMSK &= ~(1<<28);     //Uart0�жϴ������жϣ���Ҫ��UART0���ж�����λ����Ϊ��Ч��
	INTSUBMSK &= ~((1<<0)|(1<<1));   //�������жϺͽ����ж�����λ����Ϊ��Ч     
}      

void Uart0_Interrupt_Close(void)
{
	INTMSK |= (1<<28);
	INTSUBMSK |= ((1<<0)|(1<<1));
}


