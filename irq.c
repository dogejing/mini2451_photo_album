#include "app.h"

unsigned int IrqTimeCount = 0;
extern unsigned int ChangePhotoTime;	//图片轮换时间
extern int AutoNextPhoto;
extern int KeyNextPhoto;
extern unsigned int KeyOrAutoFlag;
extern int ChangePhotoStyleFlag;	//刷图的标志
extern int AutoNextPhotoFlag;
extern int KeyNextPhotoFlagPlus;
extern int KeyNextPhotoFlagSub;
extern int IntoTimeFlag ;
extern int PhotoModel;

void delay_int(int i)
{
	while(i--);
}

void do_irq(void)	//中断服务函数
{
	timer_interrupt();
	key_interrupt();
	uart_interrpt();

	SRCPND1 = SRCPND1;		//发生中断，中断发生寄存器和中断仲裁寄存器都会置1，需要再次清零
	INTPND1 = INTPND1;
}


void timer_interrupt(void)	//定时器中断
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

void key_interrupt(void)	//按键中断
{
	unsigned int i;
	
	for(i=0; i<4; i++)	//四个按键
	{
		if(SRCPND1 & (1<<i))	//中断发生
		{
			if(GPFDAT & (1<<i))		//上升沿
			{
				delay_ini(1000);
				if(i == 0)	//按键模式 还是自动模式
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
				if(i == 1)	//上一张
				{
					KeyNextPhotoFlagSub = 1;
					ChangePhotoStyleFlag = 1;
				}
				if(i == 2)	//下一张
				{
					KeyNextPhotoFlagPlus = 1;
					ChangePhotoStyleFlag = 1;
				}
				if(i == 3)	//进入时钟模式或相册
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

void uart_interrpt(void)  // 串口中断
{
	unsigned char buf;

	
	if(SRCPND1 & (1<<28))
	{
		if(SUBSRCPND & (1<<0))     //接受中断
		{
			buf = URXH0;  //将接受到的字符存放在buf中		
			temp[ch_i++] = buf;
			if(buf == '!')
			{
				temp[ch_i-1] = '\0';
				my_printf("\r\n");
				ch_i = 0;
			}
			
			SUBSRCPND |= 1<<0; //清除接受中断
			SRCPND1 |= 1<<28;
			INTPND1 |= 1<<28;
			if(buf != '!')
			{
				UTXH0 = buf;         //PC将接受的字符通过串口调试工具发送到屏幕上    
			}		
		}	
		SUBSRCPND = SUBSRCPND;

		if(strcmp("time",temp) == 0)	//系统时间
		{
			UartRcvFlag = 1;
			memset(temp,0,sizeof(temp));
			my_printf("\r\n正在设置时间！");
			my_printf("\r\n请按照该格式输入：20xx xx xx xx:xx:xx/x!");
			my_printf("\r\n");
		}
		else if(strcmp("photo",temp) == 0)	//刷图间隔
		{
			UartRcvFlag = 2;
			memset(temp,0,sizeof(temp));
			my_printf("\r\n正在设置刷图时间！");
			my_printf("\r\n请按照该格式输入:xx(s)!");
			my_printf("\r\n");
		}
		else if(strcmp("auto",temp) == 0)	//自动模式，手动模式
		{
			//UartRcvFlag = 3;
			memset(temp,0,sizeof(temp));
			KeyOrAutoFlag++;
			if((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 0))
			{
				IrqTimeCount = 0;
				my_printf("\r\n进入自动模式");
			}
			if((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 1))
			{
				KeyNextPhoto = AutoNextPhoto;
				IrqTimeCount = ChangePhotoTime + 1;
				my_printf("\r\n进入手动模式");
			}
			my_printf("\r\n");
		}
		else if(strcmp("model",temp) == 0)	//切换刷图模式
		{
			memset(temp,0,sizeof(temp));
			my_printf("\r\n切换刷图模式！");
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
	GPFCON = 0xaa;				//设置GPF0，1，2，3位外部中断模式
	EXTINT0 = (0x4<<12)|(0x4<<8)|(0x4<<4)|(0x4<<0);		//模式设置,上升沿触发中断
	SRCPND1 = SRCPND1;	//中断触发会硬件置1，需要清0
	INTPND1 = INTPND1;
	INTMSK1 &= ~(0x0f);		//打开中断允许
}

void delay_ini(int i)
{
	while(i--);
}
