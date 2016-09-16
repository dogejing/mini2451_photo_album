#ifndef _IRQ_H_
#define _IRQ_H_

#define  GPFCON       (*(volatile unsigned  long *)0x56000050)
#define  EXTINT0      (*(volatile unsigned  long *)0x56000088)
#define  SRCPND1      (*(volatile unsigned  long *)0x4A000000)
#define  INTPND1      (*(volatile unsigned  long *)0x4A000010)
#define  INTMSK1      (*(volatile unsigned  long *)0x4A000008)
#define  GPFDAT       (*(volatile unsigned  long *)0x56000054)


extern void timer_interrupt(void);
extern void key_interrupt(void);
extern void uart_interrpt(void);  // ´®¿ÚÖÐ¶Ï

extern void key_init(void);
extern void delay_ini(int i);
#endif

