#define ULCON0   			( *((volatile unsigned long *)0x50000000) )
#define UCON0    			( *((volatile unsigned long *)0x50000004) )
#define UFCON0   	 		( *((volatile unsigned long *)0x50000008) )
#define UMCON0    		( *((volatile unsigned long *)0x5000000C) )
#define UTRSTAT0  		( *((volatile unsigned long *)0x50000010) )
#define UFSTAT0 			( *((volatile unsigned long *)0x50000018) )
#define UTXH0      		( *((volatile unsigned char *)0x50000020) )
#define URXH0      		( *((volatile unsigned char *)0x50000024) ) 
#define UBRDIV0    		( *((volatile unsigned short *)0x50000028) )
#define UDIVSLOT0  		( *((volatile unsigned short *)0x5000002C) )
#define GPHCON     		( *((volatile unsigned long *)0x56000070 ) )

void uart_init(void)
{
	GPHCON = 0xa;
	ULCON0 = 0x03;
	UCON0 = 0x05;
	UFCON0 = 0x01;
	UMCON0 = 0x0;
	UBRDIV0 = 35;
	UDIVSLOT0 = 0x0111;
}

void putchar(unsigned char c)
{
	while(UFSTAT0 & (1 << 14));
	UTXH0 = c;
}

unsigned char getchar(void)
{
	
	while((UFSTAT0 & 0x7f) == 0);
	return URXH0;
}

