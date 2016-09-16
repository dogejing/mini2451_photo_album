
#define GPACON (*(volatile unsigned long*)0x56000000)
#define GPADAT (*(volatile unsigned long*)0x56000004)
#define GPBCON (*(volatile unsigned long*)0x56000010)
#define GPBDAT (*(volatile unsigned long*)0x56000014)
#define GPBSEL (*(volatile unsigned long*)0x5600001c)

#define GPFCON (*(volatile unsigned long*)0x56000050)
#define GPFDAT (*(volatile unsigned long*)0x56000054)

extern int IntoTimeFlag ;
extern unsigned int KeyOrAutoFlag;

void led_flag(void)
{
		if(IntoTimeFlag == 1)  //1 ʱ��ģʽ
		{
			GPBDAT &= ~(0x1<<5); //led1
			GPBDAT |= (0x1<<6);		//led2
		}
		else 
		{
			GPBDAT |= (0x1<<5);
			GPBDAT &= ~(0x1<<6);
		}
/*		
		if(IntoTimeFlag == 0)	//2 ���ģʽ
		{
			GPBDAT &= ~(0x1<<6);
		}
		else
		{
			GPBDAT |= (0x1<<6);
		}
	*/	
		if(KeyOrAutoFlag % 2 == 0)	//3	�Զ�ģʽ
		{
			GPADAT &= ~(0x1<<25);	//led3
			GPADAT |= (0x1<<26);	//led4
		}
		else
		{
			GPADAT |= (0x1<<25);
			GPADAT &= ~(0x1<<26);
		}
		
/*		if(KeyOrAutoFlag % 2 == 1)	//4 �ֶ�ģʽ
		{
			GPADAT &= ~(0x1<<26);
		}
		else
		{
			GPADAT |= (0x1<<26);
		}
	*/
}


