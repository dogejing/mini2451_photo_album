#define LOCKCON0 (*(volatile unsigned long*)0x4C000000)
#define MPLLCON  (*(volatile unsigned long*)0x4C000010)
#define CLKSRC   (*(volatile unsigned long*)0x4C000020)
#define CLKDIV0  (*(volatile unsigned long*)0x4C000024)

#define MPLL_EN 0
#define MDIV    400
#define PDIV    3
#define SDIV    1

#define ARMDIV  1
#define PREDIV  2
#define HCLKDIV 1
#define PCLKDIV 1

#define SELMPLL 1

void clock_init()
{
	MPLLCON = (MPLL_EN << 24) | (MDIV << 14) | (PDIV << 5) | (SDIV); //设置MPLLout = 800M
	CLKDIV0 = (ARMDIV << 9) | (PREDIV << 4) | (HCLKDIV) | (PCLKDIV << 2);
	LOCKCON0 = 0Xffff; //锁定时间约为5.46ms
	CLKSRC = (SELMPLL << 4);
}


