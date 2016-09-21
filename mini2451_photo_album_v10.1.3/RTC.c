#include "app.h"

extern int AutoNextPhoto;	//�Զ��л����ڼ���ͼ
extern int KeyNextPhoto;	
extern unsigned int KeyOrAutoFlag;

void RTC_Time_Set(char wRTCyear,char wRTCmon,char wRTCday,char wRTCdate,char wRTChour,char wRTCmin,char wRTCsec )//ʱ�����ú��� 
//ע�⣬���Ӧ��ʮ����ת��ΪBCD����ʽ����ʮ�����Ƹ�ʽ
{
	rRTCCON = (1 << 0) ;  //RTC ��дʹ��//����RTCEN��1��RTC control enable.
	rBCDYEAR = wRTCyear ;  //��
	rBCDMON  = wRTCmon ;  //��
	rBCDDAY  = wRTCday ;  //��
	rBCDDATE = wRTCdate ;  //���� 
	rBCDHOUR = wRTChour ;  //ʱ
	rBCDMIN  = wRTCmin ;  //��
	rBCDSEC  = wRTCsec ;  //��
	rRTCCON  &= ~(1 << 0) ;  //RTC read and write disable
}

void RTC_Time_display(void)//ʱ����ʾ
{
	unsigned char time[30];
	char rRTCyear;
	char rRTCmon;
	char rRTCdate;
//	char rRTCday;
	char rRTChour;
	char rRTCmin;
	char rRTCsec;
	
	rRTCCON = (1 << 0) ;  //RTC ��дʹ��//����RTCEN��1��RTC control enable.
	rRTCyear = rBCDYEAR ;  //��
	rRTCmon  = rBCDMON;  //��
	rRTCdate = rBCDDATE ;  //�� 
//	rRTCday  = rBCDDAY ;  //����
	rRTChour = rBCDHOUR ;  //ʱ
	rRTCmin  = rBCDMIN  ;  //��
	rRTCsec  = rBCDSEC ;  //��
	rRTCCON  &= ~(1 << 0) ;  //RTC read and write disable
	
	rRTCyear = BCDToInt(rRTCyear);
	rRTCmon  = BCDToInt(rRTCmon);
	rRTCdate = BCDToInt(rRTCdate);
	rRTChour = BCDToInt(rRTChour);
	rRTCmin  = BCDToInt(rRTCmin);
	rRTCsec  = BCDToInt(rRTCsec);
	
	time[0] = '2';
	time[1] = '0';	
	time[2] = (rRTCyear/10)+48;
	time[3] = (rRTCyear%10)+48;
	time[4] = 0xc4;
	time[5] = 0xea;
	time[6] = (rRTCmon/10)+48;
	time[7] = (rRTCmon%10)+48;
	time[8] = 0xd4;
	time[9] = 0xc2;	
	time[10] = (rRTCdate/10)+48;
	time[11] = (rRTCdate%10)+48;
	time[12] = 0xc8;
	time[13] = 0xd5;
	time[14] = (rRTChour/10)+48;
	time[15] = (rRTChour%10)+48;
	time[16] = ':';
	time[17] = (rRTCmin/10)+48;
	time[18] = (rRTCmin%10)+48;
	time[19] = ':';
	time[20] = (rRTCsec/10)+48;
	time[21] = (rRTCsec%10)+48;
	time[22] = '\0';
//	sprintf(time,"20%2d��%2d��%2d��%2d:%2d:%2d",rRTCyear,rRTCmon,rRTCdate,rRTChour,rRTCmin,rRTCsec);
	if(KeyOrAutoFlag % 2 == 0)
	{
		lcd_draw_ch_en_str(time,304,1,0x0,AutoNextPhoto);
	}
	if(KeyOrAutoFlag % 2 == 1)
	{
		lcd_draw_ch_en_str(time,304,1,0x0,KeyNextPhoto);
	}
}


void RTC_Time_model_display(void)//ʱ����ʾ
{
	unsigned char time[30];
	unsigned char week[10];
	char rRTCyear;
	char rRTCmon;
	char rRTCdate;
	char rRTCday;
	char rRTChour;
	char rRTCmin;
	char rRTCsec;
	
	rRTCCON = (1 << 0) ;  //RTC ��дʹ��//����RTCEN��1��RTC control enable.
	rRTCyear = rBCDYEAR ;  //��
	rRTCmon  = rBCDMON;  //��
	rRTCdate = rBCDDATE ;  //�� 
	rRTCday  = rBCDDAY ;  //����
	rRTChour = rBCDHOUR ;  //ʱ
	rRTCmin  = rBCDMIN  ;  //��
	rRTCsec  = rBCDSEC ;  //��
	rRTCCON  &= ~(1 << 0) ;  //RTC read and write disable
	
	rRTCyear = BCDToInt(rRTCyear);
	rRTCmon  = BCDToInt(rRTCmon);
	rRTCdate = BCDToInt(rRTCdate);
	rRTChour = BCDToInt(rRTChour);
	rRTCmin  = BCDToInt(rRTCmin);
	rRTCsec  = BCDToInt(rRTCsec);
	
	time[0] = '2';
	time[1] = '0';	
	time[2] = (rRTCyear/10)+48;
	time[3] = (rRTCyear%10)+48;
	time[4] = 0xc4;
	time[5] = 0xea;
	time[6] = (rRTCmon/10)+48;
	time[7] = (rRTCmon%10)+48;
	time[8] = 0xd4;
	time[9] = 0xc2;	
	time[10] = (rRTCdate/10)+48;
	time[11] = (rRTCdate%10)+48;
	time[12] = 0xc8;
	time[13] = 0xd5;
	time[14] = (rRTChour/10)+48;
	time[15] = (rRTChour%10)+48;
	time[16] = ':';
	time[17] = (rRTCmin/10)+48;
	time[18] = (rRTCmin%10)+48;
	time[19] = ':';
	time[20] = (rRTCsec/10)+48;
	time[21] = (rRTCsec%10)+48;
	time[22] = '\0';

	rRTCday  = BCDToInt(rRTCday);
	
	week[0] = 0xd0;
	week[1] = 0xc7;
	week[2] = 0xc6;
	week[3] = 0xda;
	switch (rRTCday)
	{
		case 1:week[4] = 0xd2 ;week[5] = 0xbb ;break;
		case 2:week[4] = 0xeb ;week[5] = 0x6f ;break;
		case 3:week[4] = 0xc8 ;week[5] = 0xfd ;break;
		case 4:week[4] = 0xcb ;week[5] = 0xc4 ;break;
		case 5:week[4] = 0xce ;week[5] = 0xe5 ;break;
		case 6:week[4] = 0xc1 ;week[5] = 0xf9 ;break;
		case 7:week[4] = 0xc8 ;week[5] = 0xd5 ;break;
	}
	week[6] = '\0';

//sprintf(time,"20%2d��%2d��%2d��%2d:%2d:%2d",rRTCyear,rRTCmon,rRTCdate,rRTChour,rRTCmin,rRTCsec);//TODO
	lcd_draw_ch_en_str(time,156,128,0x0,7);
	lcd_draw_ch_en_str(week,222,112,0x0,7);
}

extern int UartRcvFlag ;
extern char temp[30];

void time_set(void)		//ʱ�����ú���
{
		int nu;
	
		if(UartRcvFlag == 1)
		{
			unsigned char year,month,data,day,hour,min,sec;
			
			if((temp[0] == '2')&&(temp[16] == ':'))
			{
				year = 	(char)((temp[2]-48)*10 + (temp[3]-48));
				nu = (char)((temp[5]-48)*10 + (temp[6]-48));	
				if(nu > 12)
				{
					my_printf("�·ݴ���\r\n");
				}
				else
				{
					month = nu;
				}
				nu = 	(char)((temp[8]-48)*10 + (temp[9]-48));
				if(nu > 31)
				{
					my_printf("���ڴ���\r\n");
				}
				else
				{
					data = nu;
				}
				nu = 	(char)((temp[11]-48)*10 + (temp[12]-48));
				if(nu > 24)
				{
					my_printf("Сʱ����\r\n");
				}
				else
				{
					hour = nu;
				}
				nu = 	(char)((temp[14]-48)*10 + (temp[15]-48));
				if(nu > 60)
				{
					my_printf("�ִ���\r\n");
				}
				else
				{
					min = nu;
				}
				nu = 	(char)((temp[17]-48)*10 + (temp[18]-48));
				if(nu > 60)
				{
					my_printf("�����\r\n");
				}
				else
				{
					sec = nu;
				}
				nu = 	(char)(temp[20]-48);
				if(nu > 7)
				{
					my_printf("�����\r\n");
				}
				else
				{
					day = nu;
				}
				memset(temp,0,sizeof(temp));
			
				year 	= IntToBCD(year);
				month = IntToBCD(month);
				data 	= IntToBCD(data);
				hour	= IntToBCD(hour);
				min 	= IntToBCD(min);
				sec 	= IntToBCD(sec);
				day 	= IntToBCD(day);
				RTC_Time_Set(year,month,day,data,hour,min,sec);		//��ʼ��RTCʱ��
				UartRcvFlag = 0;
			}
		}
}

char BCDToInt(char bcd) //BCDתʮ���� 8421��
{
      return (0xff & (bcd >> 4))*10 + (0xf & bcd);
}

char IntToBCD(char num)	//ʮ����ת��Ϊʮ��������ʽBCD��
{
			return (((num / 10) * 16) + (num % 10));
}

