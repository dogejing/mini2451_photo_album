#define VIDCON0			(*(volatile unsigned *)0x4c800000)	
#define VIDCON1			(*(volatile unsigned *)0x4c800004)	
#define VIDTCON0		(*(volatile unsigned *)0x4c800008)	
#define VIDTCON1		(*(volatile unsigned *)0x4c80000C)	
#define VIDTCON2		(*(volatile unsigned *)0x4c800010)	
#define WINCON0			(*(volatile unsigned *)0x4c800014)	
#define WINCON1			(*(volatile unsigned *)0x4c800018)	
#define VIDOSD0A		(*(volatile unsigned *)0x4c800028)	
#define VIDOSD0B		(*(volatile unsigned *)0x4c80002C)
#define VIDOSD1A		(*(volatile unsigned *)0x4c800034)	
#define VIDOSD1B		(*(volatile unsigned *)0x4c800038)	
#define VIDOSD1C		(*(volatile unsigned *)0x4c80003C)	
#define VIDW00ADD0B0	(*(volatile unsigned *)0x4c800064)	
#define VIDW00ADD0B1	(*(volatile unsigned *)0x4c800068)	
#define VIDW01ADD0		(*(volatile unsigned *)0x4c80006C)	
#define VIDW00ADD1B0	(*(volatile unsigned *)0x4c80007C)	
#define VIDW00ADD1B1	(*(volatile unsigned *)0x4c800080)	
#define VIDW01ADD1		(*(volatile unsigned *)0x4c800084)	
#define VIDW00ADD2B0	(*(volatile unsigned *)0x4c800094)	
#define VIDW00ADD2B1	(*(volatile unsigned *)0x4c800098)	
#define VIDW01ADD2		(*(volatile unsigned *)0x4c80009C)	
#define VIDINTCON		(*(volatile unsigned *)0x4c8000AC)	
#define W1KEYCON0		(*(volatile unsigned *)0x4c8000B0)	
#define W1KEYCON1		(*(volatile unsigned *)0x4c8000B4)	
#define W2KEYCON0		(*(volatile unsigned *)0x4c8000B8)	
#define W2KEYCON1		(*(volatile unsigned *)0x4c8000BC)	
#define W3KEYCON0		(*(volatile unsigned *)0x4c8000C0)	
#define W3KEYCON1		(*(volatile unsigned *)0x4c8000C4)	
#define W4KEYCON0		(*(volatile unsigned *)0x4c8000C8)	
#define W4KEYCON1		(*(volatile unsigned *)0x4c8000CC)	
#define WIN0MAP			(*(volatile unsigned *)0x4c8000D0)	
#define WIN1MAP			(*(volatile unsigned *)0x4c8000D4)	
#define WPALCON			(*(volatile unsigned *)0x4c8000E4)	
#define SYSIFCON0		(*(volatile unsigned *)0x4c800130)	
#define SYSIFCON1		(*(volatile unsigned *)0x4c800134)	
#define DITHMODE1		(*(volatile unsigned *)0x4c800138)	
#define SIFCCON0		(*(volatile unsigned *)0x4c80013C)	
#define SIFCCON1		(*(volatile unsigned *)0x4c800140)	
#define SIFCCON2		(*(volatile unsigned *)0x4c800144)	
#define CPUTRIGCON1		(*(volatile unsigned *)0x4c80015C)	
#define CPUTRIGCON2		(*(volatile unsigned *)0x4c800160)	
#define VIDW00ADD0B1	(*(volatile unsigned *)0x4c800068)	
#define VIDW01ADD0		(*(volatile unsigned *)0x4c80006C)	
#define GPCCON			(*(volatile unsigned *)(0x56000020))	
#define GPCDAT			(*(volatile unsigned *)(0x56000024))	
#define GPCUDP			(*(volatile unsigned *)(0x56000028))	
#define GPDCON			(*(volatile unsigned *)(0x56000030))	
#define GPDDAT			(*(volatile unsigned *)(0x56000034))	
#define GPDUDP			(*(volatile unsigned *)(0x56000038))	
#define MISCCR			(*(volatile unsigned *)(0x56000080))	
#define GPLCON			(*(volatile unsigned *)(0x560000f0))	
#define GPLDAT			(*(volatile unsigned *)(0x560000f4))	
#define GPBCON 			(*(volatile unsigned long *)0x56000010)
#define GPBDAT 			(*(volatile unsigned long *)0x56000014)
#define GPGCON 			(*(volatile unsigned long *)0x56000060)
#define GPGDAT 			(*(volatile unsigned long *)0x56000064)

#define HSPW (0)
#define HBPD (40- 1)
#define HFPD (5 - 1)
#define VSPW (2)
#define VBPD (8 - 1)
#define VFPD (8 - 1)

extern void lcd_init(void);
extern void chear_test(void);
extern void lcd_dis_pic(const unsigned char * str);
extern const unsigned char gImage_fanbingbing[522240];
extern void lcd_draw_cline(unsigned int x0,unsigned int y0,unsigned int length,unsigned int color);
extern void lcd_draw_squ(unsigned int x0,unsigned int y0,unsigned int length_x,unsigned int length_y,unsigned int color,unsigned int flag);
extern void lcd_draw_char(unsigned char ch,unsigned int x,unsigned int y,unsigned int color,int next_photo);
extern void lcd_draw_chinese(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo);
extern void lcd_draw_str(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo);
extern void lcd_draw_ch_en_str(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo);

extern void lcd_draw_chinese_str(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo);
extern void lcd_dis_pic_half(const unsigned char * str);

extern void lcd_dis_pic_time(const unsigned char * str);

extern void lcd_dis_pic_time_model(const unsigned char * str);

extern const unsigned char ab[26][16];
extern const struct chinese_gbk_lcd font[6763];
extern const unsigned char gImage_tu1[522248];
extern const unsigned char gImage_tu2[522248];
extern const unsigned char gImage_tu3[522248];
extern const unsigned char gImage_tu4[522248];
extern const unsigned char gImage_tu5[522248];
extern const unsigned char gImage_tu6[522248];
extern const unsigned char gImage_tu7[522248];
extern const unsigned char gImage_tu8[522248];

struct chinese_gbk_lcd
{
	  unsigned char ch[2];
	  unsigned char gbklcd[32];
};

extern void lcd_dis_pic_ten(const unsigned char * str);

extern void lcd_dis_pic_four(const unsigned char * str);
