#include "app.h"

unsigned int IrqTimeCount = 0;
extern unsigned int ChangePhotoTime;	//ͼƬ�ֻ�ʱ��
extern int AutoNextPhoto;
extern int KeyNextPhoto;
extern unsigned int KeyOrAutoFlag;
extern int ChangePhotoStyleFlag;	//ˢͼ�ı�־
extern int AutoNextPhotoFlag;
extern int KeyNextPhotoFlagPlus;
extern int KeyNextPhotoFlagSub;
extern int IntoTimeFlag ;
extern int PhotoModel;

void delay_int(int i)
{
	while(i--);
}

void do_irq(void)	//�жϷ�����
{
	timer_interrupt();
	key_interrupt();
	uart_interrpt();

	SRCPND1 = SRCPND1;		//�����жϣ��жϷ����Ĵ������ж��ٲüĴ���������1����Ҫ�ٴ�����
	INTPND1 = INTPND1;
}


void timer_interrupt(void)	//��ʱ���ж�
{
	if(SRCPND1 & (1<<10))
	{
		IrqTimeCount++;
		if(IrqTimeCount == ChangePhotoTime)
		{
			IrqTimeCount = 0;
			AutoNextPhotoFlag = 1;
			ChangePhotoStyleFlag = 1;
		}
	}
}

void key_interrupt(void)	//�����ж�
{
	unsigned int i;
	
	for(i=0; i<4; i++)	//�ĸ�����
	{
		if(SRCPND1 & (1<<i))	//�жϷ���
		{
			if(GPFDAT & (1<<i))		//������
			{
				delay_ini(1000);
				if(i == 0)	//����ģʽ �����Զ�ģʽ
				{
					KeyOrAutoFlag++;
					if((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 0))	//	KeyOrAutoFlag % 2 == 0
					{
						IrqTimeCount = 0;
					}
					else
					{
						KeyNextPhoto = AutoNextPhoto;
						IrqTimeCount = ChangePhotoTime + 1;
					}
				}
				if(i == 1)	//��һ��
				{
					KeyNextPhotoFlagSub = 1;
					ChangePhotoStyleFlag = 1;
				}
				if(i == 2)	//��һ��
				{
					KeyNextPhotoFlagPlus = 1;
					ChangePhotoStyleFlag = 1;
				}
				if(i == 3)	//����ʱ��ģʽ�����
				{
					IntoTimeFlag++;
					if(IntoTimeFlag - (IntoTimeFlag>>1<<1) == 0)	//IntoTimeFlag % 2 == 0
					{
						IntoTimeFlag = 0;
						IrqTimeCount = 0;
					}
					else
					{
						IntoTimeFlag = 1;
						IrqTimeCount = ChangePhotoTime + 1;
					}
				}				
			}
		}	
	}
}

char temp[30];
int ch_i = 0;
int UartRcvFlag = 0;

void uart_interrpt(void)  // �����ж�
{
	unsigned char buf;

	
	if(SRCPND1 & (1<<28))
	{
		if(SUBSRCPND & (1<<0))     //�����ж�
		{
			buf = URXH0;  //�����ܵ����ַ������buf��		
			temp[ch_i++] = buf;
			if(buf == '!')
			{
				temp[ch_i-1] = '\0';
				my_printf("\r\n");
				ch_i = 0;
			}
			
			SUBSRCPND |= 1<<0; //��������ж�
			SRCPND1 |= 1<<28;
			INTPND1 |= 1<<28;
			if(buf != '!')
			{
				UTXH0 = buf;         //PC�����ܵ��ַ�ͨ�����ڵ��Թ��߷��͵���Ļ��    
			}		
		}	
		SUBSRCPND = SUBSRCPND;

		if(strcmp("time",temp) == 0)	//ϵͳʱ��
		{
			UartRcvFlag = 1;
			memset(temp,0,sizeof(temp));
			my_printf("\r\n��������ʱ�䣡");
			my_printf("\r\n�밴�ոø�ʽ���룺20xx xx xx xx:xx:xx/x!");
			my_printf("\r\n");
		}
		else if(strcmp("photo",temp) == 0)	//ˢͼ���
		{
			UartRcvFlag = 2;
			memset(temp,0,sizeof(temp));
			my_printf("\r\n��������ˢͼʱ�䣡");
			my_printf("\r\n�밴�ոø�ʽ����:xx(s)!");
			my_printf("\r\n");
		}
		else if(strcmp("auto",temp) == 0)	//�Զ�ģʽ���ֶ�ģʽ
		{
			//UartRcvFlag = 3;
			memset(temp,0,sizeof(temp));
			KeyOrAutoFlag++;
			if((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 0))
			{
				IrqTimeCount = 0;
				my_printf("\r\n�����Զ�ģʽ");
			}
			if((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 1))
			{
				KeyNextPhoto = AutoNextPhoto;
				IrqTimeCount = ChangePhotoTime + 1;
				my_printf("\r\n�����ֶ�ģʽ");
			}
			my_printf("\r\n");
		}
		else if(strcmp("model",temp) == 0)	//�л�ˢͼģʽ
		{
			memset(temp,0,sizeof(temp));
			my_printf("\r\n�л�ˢͼģʽ��");
			PhotoModel++;
			if(PhotoModel == 3)
			{
				PhotoModel = 0;
			}
		}
	}
}

void key_init(void)
{
	GPFCON = 0xaa;				//����GPF0��1��2��3λ�ⲿ�ж�ģʽ
	EXTINT0 = (0x4<<12)|(0x4<<8)|(0x4<<4)|(0x4<<0);		//ģʽ����,�����ش����ж�
	SRCPND1 = SRCPND1;	//�жϴ�����Ӳ����1����Ҫ��0
	INTPND1 = INTPND1;
	INTMSK1 &= ~(0x0f);		//���ж�����
}

void delay_ini(int i)
{
	while(i--);
}
