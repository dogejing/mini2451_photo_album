#include "timer.h"
#include "irq.h"

void time0_init(void)
{
	//��ʱ������ʱ������
	//PCLK / (prescaler value + 1) / (divider value) //PCLK����ʼ��66.666...mhz
	TCFG0 = 99;	//����prescaler value		
	TCFG1 = 0x03;	//����divider value  ��� //66666666 / 100 /16 = 41666
	TCNTB0 = 41666;	//��ʱʱ��Ϊ1s 
	TCON |= (1<<1);	//�ֶ����¼���ֵ
	TCON = 0x09;	//���ֶ����¡����Զ����£��򿪶�ʱ��
	INTMSK1 &= ~(1<<10);	//�򿪶�ʱ���ж�
}

