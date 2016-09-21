#ifndef _UART_IRQ_
#define _UART_IRQ_

#define INTMSK   		(*(volatile unsigned  long *)0X4A000008)
#define INTSUBMSK   (*(volatile unsigned  long *)0X4A00001C)
#define SUBSRCPND   (*(volatile unsigned  long *)0X4A000018)
#define URXH0		    (*(volatile unsigned  long *)0x50000024)
#define UTXH0   		(*(volatile unsigned  long *)0x50000020)
#define SUBSRCPND   (*(volatile unsigned  long *)0X4A000018)
#define SUBSRCPND   (*(volatile unsigned  long *)0X4A000018)
#define SUBSRCPND   (*(volatile unsigned  long *)0X4A000018)


extern void Uart0_Interrupt_Init(void);
extern void Uart0_Interrupt_Close(void);

#endif


