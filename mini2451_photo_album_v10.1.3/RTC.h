#ifndef _RTC_H_
#define _RTC_H_

#define rRTCCON   (*(volatile unsigned  long *)0x57000040)
#define rBCDYEAR  (*(volatile unsigned  long *)0x57000088) 
#define rBCDMON   (*(volatile unsigned  long *)0x57000084) 
#define rBCDDAY   (*(volatile unsigned  long *)0x57000080) 
#define rBCDDATE  (*(volatile unsigned  long *)0x5700007C) 
#define rBCDHOUR  (*(volatile unsigned  long *)0x57000078) 
#define rBCDMIN   (*(volatile unsigned  long *)0x57000074) 
#define rBCDSEC   (*(volatile unsigned  long *)0x57000070) 

extern void RTC_Time_Set(char wRTCyear,char wRTCmon,char wRTCday,char wRTCdate,char wRTChour,char wRTCmin,char wRTCsec );//时间设置函数
extern void RTC_Time_display(void);
extern char BCDToInt(char bcd);
extern void time_set(void);
extern char IntToBCD(char num);
extern void RTC_Time_model_display(void);

#endif

