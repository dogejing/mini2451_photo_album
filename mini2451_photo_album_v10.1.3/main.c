
#include "app.h"

#define GPACON (*(volatile unsigned long*)0x56000000)
#define GPADAT (*(volatile unsigned long*)0x56000004)
#define GPBSEL (*(volatile unsigned long*)0x5600001c)

const unsigned char hao[32] = {0x10,0x00,0x10,0xFC,0x10,0x04,0x10,0x08,0xFC,0x10,0x24,0x20,0x24,0x20,0x25,0xFE,0x24,0x20,0x48,0x20,0x28,0x20,0x10,0x20,0x28,0x20,0x44,0x20,0x84,0xA0,0x00,0x40};
extern void delay(unsigned int n);
unsigned int ChangePhotoTime;	//图片轮换时间	
int AutoNextPhoto = 0;	//自动切换到第几张图
int KeyNextPhoto = 0;	//按键切换到第几张图
unsigned int KeyOrAutoFlag = 0;	//按键or自动模式切换标志位
unsigned int ChangePhotoStyleFlag = 1;	//刷图的标志
int	AutoNextPhotoFlag = 0;	//自动模式，切下一张
int KeyNextPhotoFlagPlus = 0;	//切上一张图
int KeyNextPhotoFlagSub = 0;	//切下一张图
int IntoTimeFlag ;	//进入时钟模式的标志
int PhotoModel = 0; //选择第几种刷图方式	
	
	
void Main()
{		
	unsigned int BeginFlag = 1;
	
	GPACON = 0x0;		//初始化led
	GPBCON = (0x5 << 10);
	GPBSEL = 0x0;
	
	MMU_Init();		//先初始化MMU
	uart_init();		
	lcd_init();
	chear_test();	
	key_init();		//初始化中断
	Uart0_Interrupt_Init();	//串口中断初始化
	time0_init();	//初始化定时器
	 
	
	my_printf("\r\n改变时间：time!,改变刷图间隔：photo! \r\n");
	IntoTimeFlag = 0;
	while(1)
	{		
			while(IntoTimeFlag)	//进入时钟界面
			{
				led_flag();
				time_set();
				lcd_dis_pic(gImage_tu8);
				lcd_dis_pic_time_model(gImage_tu8);
			}
			if(BeginFlag)	//只在第一次开始后出现
			{
				BeginFlag = 0;
				KeyOrAutoFlag = 2;
				AutoNextPhoto = 0;
				ChangePhotoStyleFlag = 1;
				ChangePhotoTime = 3;	//设置图片轮换时间	
			}
//			my_printf("/r/n*****%d*******",KeyOrAutoFlag);
			while((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 0)&&(IntoTimeFlag == 0))	//进入自动切图 KeyOrAutoFlag % 2 == 0
			{
				led_flag();			
				time_set();		//是否时间设置	
				change_photo_set();
				if(ChangePhotoStyleFlag)
				{
	//				my_printf("****%d****",ChangePhotoStyleFlag);
					ChangePhotoStyleFlag = 0;
					change_photo_style_two(AutoNextPhoto);
				}
				change_photo_display(AutoNextPhoto);
				if(AutoNextPhotoFlag == 1)
				{
					AutoNextPhoto++;
					if(AutoNextPhoto == 7)
					{
						AutoNextPhoto = 0;
					}
					AutoNextPhotoFlag = 0;
				}				
			}
			while((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 1)&&(IntoTimeFlag == 0))	//进入手动切图界面 KeyOrAutoFlag % 2 == 1
			{		
				time_set();		//是否时间设置	
				change_photo_set();
				led_flag();
				if(ChangePhotoStyleFlag)
				{
					ChangePhotoStyleFlag = 0;
					change_photo_style_two(KeyNextPhoto);
				}
				change_photo_display(KeyNextPhoto);
				if(KeyNextPhotoFlagPlus == 1)	//下一张
				{	
					KeyNextPhoto++;
					if(KeyNextPhoto == 7)
					{
						KeyNextPhoto = 0;
					}
					KeyNextPhotoFlagPlus = 0;
				}
				if(KeyNextPhotoFlagSub == 1)	//上一张
				{
					KeyNextPhoto--;
					if(KeyNextPhoto == -1)
					{
						KeyNextPhoto = 6;
					}
					KeyNextPhotoFlagSub = 0;
				}			
			}	
	}
}


