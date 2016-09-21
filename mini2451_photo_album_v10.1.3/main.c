
#include "app.h"

#define GPACON (*(volatile unsigned long*)0x56000000)
#define GPADAT (*(volatile unsigned long*)0x56000004)
#define GPBSEL (*(volatile unsigned long*)0x5600001c)

const unsigned char hao[32] = {0x10,0x00,0x10,0xFC,0x10,0x04,0x10,0x08,0xFC,0x10,0x24,0x20,0x24,0x20,0x25,0xFE,0x24,0x20,0x48,0x20,0x28,0x20,0x10,0x20,0x28,0x20,0x44,0x20,0x84,0xA0,0x00,0x40};
extern void delay(unsigned int n);
unsigned int ChangePhotoTime;	//ͼƬ�ֻ�ʱ��	
int AutoNextPhoto = 0;	//�Զ��л����ڼ���ͼ
int KeyNextPhoto = 0;	//�����л����ڼ���ͼ
unsigned int KeyOrAutoFlag = 0;	//����or�Զ�ģʽ�л���־λ
unsigned int ChangePhotoStyleFlag = 1;	//ˢͼ�ı�־
int	AutoNextPhotoFlag = 0;	//�Զ�ģʽ������һ��
int KeyNextPhotoFlagPlus = 0;	//����һ��ͼ
int KeyNextPhotoFlagSub = 0;	//����һ��ͼ
int IntoTimeFlag ;	//����ʱ��ģʽ�ı�־
int PhotoModel = 0; //ѡ��ڼ���ˢͼ��ʽ	
	
	
void Main()
{		
	unsigned int BeginFlag = 1;
	
	GPACON = 0x0;		//��ʼ��led
	GPBCON = (0x5 << 10);
	GPBSEL = 0x0;
	
	MMU_Init();		//�ȳ�ʼ��MMU
	uart_init();		
	lcd_init();
	chear_test();	
	key_init();		//��ʼ���ж�
	Uart0_Interrupt_Init();	//�����жϳ�ʼ��
	time0_init();	//��ʼ����ʱ��
	 
	
	my_printf("\r\n�ı�ʱ�䣺time!,�ı�ˢͼ�����photo! \r\n");
	IntoTimeFlag = 0;
	while(1)
	{		
			while(IntoTimeFlag)	//����ʱ�ӽ���
			{
				led_flag();
				time_set();
				lcd_dis_pic(gImage_tu8);
				lcd_dis_pic_time_model(gImage_tu8);
			}
			if(BeginFlag)	//ֻ�ڵ�һ�ο�ʼ�����
			{
				BeginFlag = 0;
				KeyOrAutoFlag = 2;
				AutoNextPhoto = 0;
				ChangePhotoStyleFlag = 1;
				ChangePhotoTime = 3;	//����ͼƬ�ֻ�ʱ��	
			}
//			my_printf("/r/n*****%d*******",KeyOrAutoFlag);
			while((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 0)&&(IntoTimeFlag == 0))	//�����Զ���ͼ KeyOrAutoFlag % 2 == 0
			{
				led_flag();			
				time_set();		//�Ƿ�ʱ������	
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
			while((KeyOrAutoFlag-(KeyOrAutoFlag>>1<<1) == 1)&&(IntoTimeFlag == 0))	//�����ֶ���ͼ���� KeyOrAutoFlag % 2 == 1
			{		
				time_set();		//�Ƿ�ʱ������	
				change_photo_set();
				led_flag();
				if(ChangePhotoStyleFlag)
				{
					ChangePhotoStyleFlag = 0;
					change_photo_style_two(KeyNextPhoto);
				}
				change_photo_display(KeyNextPhoto);
				if(KeyNextPhotoFlagPlus == 1)	//��һ��
				{	
					KeyNextPhoto++;
					if(KeyNextPhoto == 7)
					{
						KeyNextPhoto = 0;
					}
					KeyNextPhotoFlagPlus = 0;
				}
				if(KeyNextPhotoFlagSub == 1)	//��һ��
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


