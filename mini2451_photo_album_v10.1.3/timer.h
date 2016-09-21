#ifndef _TIMER_H_
#define _TIMER_H_

#define TCFG0 	(*(volatile unsigned *)(0x51000000))
#define TCFG1 	(*(volatile unsigned *)(0x51000004))
#define TCNTB0 	(*(volatile unsigned *)(0x5100000C))
#define TCON 		(*(volatile unsigned *)(0x51000008))
//#define INTMSK1 (*(volatile unsigned *)(0X4A000008))

extern void time0_init(void);

#endif

