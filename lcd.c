#include "lcd.h"
#include <string.h>
#include "irq.h"
#include "RTC.h"
#include "printf.h"

#define LCD_x 480
#define LCD_y 272

unsigned long FRAME_BUFFER[272][480];

void lcd_init(void)
{
	GPCCON = 0xaaaaaaaa;	//设置GPC,GPD
	GPDCON = 0xaaaaaaaa;
	GPBCON &= ~(0x3<<2);	//操作位清零
	GPBCON |= (0x1<<2);		
	GPBDAT |= (0x1<<1);		//打开背光灯
	VIDCON0 = 0;
	VIDCON0 = (0x0<<22)|(0x0<<13)|(9<<6)|(1<<5)|(1<<4)|(0x3<<0);	//设置
	VIDCON1 = 0;
	VIDCON1 |= (1<<6)|(1<<5);
	VIDTCON0 = 0;
	VIDTCON1 = 0;
	VIDTCON0 |= (VBPD<<16)|(VFPD<<8)|(VSPW<<0);
	VIDTCON1 |= (HBPD<<16)|(HFPD<<8)|(HSPW<<0);
	VIDTCON2 = 0;
	VIDTCON2 |= (271<<11)|(479<<0);
	WINCON0 = 0;
	WINCON0 |= (0xb<<2)|(1<<0);
	VIDOSD0A = 0;
	VIDOSD0A |= (0<<11)|(0<<0);
	VIDOSD0B = 0;
	VIDOSD0B |= (479<<11)|(271<<0);
	
	VIDW00ADD0B0 = (unsigned long)FRAME_BUFFER;
	VIDW00ADD1B0 = (unsigned long)FRAME_BUFFER+sizeof(FRAME_BUFFER);
}

void chear_test(void)
{
	unsigned int x,y;
	
	for(y=0; y<272; y++)
	{
		for(x=0; x<480; x++)
		{
			FRAME_BUFFER[y][x] = 0x00ffffff;	//初始化白色
		}
	}
}

void lcd_dis_pic_time(const unsigned char * str)		//显示照片+时间
{
	unsigned int x,y;
	unsigned int i = 0;
	for(y=0; y<LCD_y; y++)
	{
//		RTC_Time_display();		//显示当前时间	
		for(x=0; x<LCD_x; x++)
		{
			FRAME_BUFFER[y][x] = (str[i]<<24)|(str[i+1]<<16)|(str[i+2]<<8)|(str[i+3]<<0);	//灰度<<24 红<<16 绿<<8 蓝<<0
			i += 4;
		}
	}
}

void lcd_dis_pic(const unsigned char * str)		//显示照片
{
	unsigned int x,y;
	unsigned int i = 0;
	for(y=0; y<LCD_y; y++)
	{
//		RTC_Time_display();		//显示当前时间	
		for(x=0; x<LCD_x; x++)
		{
			FRAME_BUFFER[y][x] = (str[i]<<24)|(str[i+1]<<16)|(str[i+2]<<8)|(str[i+3]<<0);	//灰度<<24 红<<16 绿<<8 蓝<<0
			i += 4;
		}
	}
}

void lcd_dis_pic_time_model(const unsigned char * str)		//显示照片+中间显示时间
{
	unsigned int x,y;
	unsigned int i = 0;
	
//	my_printf("1111");
	RTC_Time_model_display();
	for(y=0; y<LCD_y; y++)
	{
		RTC_Time_model_display();
		for(x=0; x<LCD_x; x++)
		{
			FRAME_BUFFER[y][x] = (str[i]<<24)|(str[i+1]<<16)|(str[i+2]<<8)|(str[i+3]<<0);	//灰度<<24 红<<16 绿<<8 蓝<<0
			i += 4;
		}
	}
}

void lcd_draw_cline(unsigned int x0,unsigned int y0,unsigned int length,unsigned int color)	//设置一条竖线
{
	unsigned int i;
	if((x0>LCD_x)||(y0>LCD_y))
	{
		return;
	}
	for(i=0; i<length; i++)
	{
		FRAME_BUFFER[y0+i][x0] = color;
	}
}

void lcd_draw_squ(unsigned int x0,unsigned int y0,unsigned int length_x,unsigned int length_y,unsigned int color,unsigned int flag)	//设置一条方形
{
	unsigned int i,j;
	if((x0>LCD_x)||(y0>LCD_y)||((flag != 1)&&(flag != 0)))
	{
		return;
	}
	if(flag == 1)
	{
		for(i=0; i<length_y; i++)
		{
			for(j=0; j<length_x;j++)
			{
				FRAME_BUFFER[y0+j][x0+i] = color;
			}
		}
	}
	else
	{
		for(i=0; i<length_y; i++)
		{
			for(j=0; j<length_x;j++)
			{
				FRAME_BUFFER[y0][x0+i] = color;
				FRAME_BUFFER[y0+j][x0] = color;
				FRAME_BUFFER[y0+length_x][x0+i] = color;
				FRAME_BUFFER[y0+j][x0+length_y] = color;
			}
		}
	}
}



void lcd_draw_char(unsigned char ch,unsigned int x,unsigned int y,unsigned int color,int next_photo)//显示单个字符
{
	unsigned int i,j;
	unsigned char mask;
	unsigned int k;
	const unsigned char *add[8] = {gImage_tu1,gImage_tu2,gImage_tu3,gImage_tu4,gImage_tu5,gImage_tu6,gImage_tu7,gImage_tu8};
	int point_color;
	int temp;

	k = ch - 32;
	for(j=0; j<16; j++)
	{
		mask = 0x80;
		for(i=0; i<8; i++)
		{	
			if(ab[k][j] & mask)
			{
				FRAME_BUFFER[j+y][i+x] = color;
			}
			else
			{
				temp = ((((480*(y+j))+(x+i)))*4);
				point_color = ((add[next_photo][temp]<<24)
											|(add[next_photo][temp+1]<<16)
											|(add[next_photo][temp+2]<<8)
											|(add[next_photo][temp+3]<<0));
				FRAME_BUFFER[j+y][i+x] = point_color;
			}
			mask >>= 1;
		}
	}
}

void lcd_draw_str(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo)//显示字符串
{
	if((x>LCD_x)||(y>LCD_y))
	{
		return;
	}
	while(*str)
	{
		if(x+8 > 480)
		{
			y += 16;
			x = 0;
		}
		lcd_draw_char(*str,x,y,color,next_photo);
		x += 8;
		str++;
	}
}



void lcd_draw_chinese(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo)//显示单个汉字
{
	unsigned int i,j;
	unsigned char mask;
	const unsigned char *add[8] = {gImage_tu1,gImage_tu2,gImage_tu3,gImage_tu4,gImage_tu5,gImage_tu6,gImage_tu7,gImage_tu8};
	int point_color;
	int temp;

	for(j=0; j<16; j++)
	{
		mask = 0x80;
		for(i=0; i<8; i++)
		{	
			if(str[j*2] & mask)
			{
				FRAME_BUFFER[j+y][i+x] = color;
			}
			else
			{
				temp = ((((480*(y+j))+(x+i)))*4);
				point_color = ((add[next_photo][temp]<<24)
											|(add[next_photo][temp+1]<<16)
											|(add[next_photo][temp+2]<<8)
											|(add[next_photo][temp+3]<<0));
				FRAME_BUFFER[j+y][i+x] = point_color;
			}
			mask >>= 1;
		}
		mask = 0x80;
		for(i=0; i<8; i++)
		{	
			if(str[j*2+1] & mask)
			{
				FRAME_BUFFER[j+y][i+8+x] = color;
			}
			else
			{
				temp = ((((480*(y+j))+(x+i+8))-1)*4);
				point_color = ((add[next_photo][temp]<<24)
											|(add[next_photo][temp+1]<<16)
											|(add[next_photo][temp+2]<<8)
											|(add[next_photo][temp+3]<<0));
				FRAME_BUFFER[j+y][i+8+x] = point_color;
			}
			mask >>= 1;
		}
	}
}


void lcd_draw_chinese_str(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo)//显示汉字字符串
{
	int i=0;
	int flag = 1;
	
	while(*str != '\0')
	{
		i = 0;
		flag = 1;
		while(flag)
		{
			if(((*str) == font[i].ch[0])&&((*(str+1)) == font[i].ch[1]))
			{
				flag = 0;
				if((x+16) > 480)
				{
					y += 17;
					x = 0;
				}
				lcd_draw_chinese(font[i].gbklcd,x,y,color,next_photo);
				x += 16;
			}
			else
			{
				i++;
			}
		}
		str += 2;
	}
}

void lcd_draw_ch_en_str(const unsigned char *str,unsigned int x,unsigned int y,unsigned int color,int next_photo)	//中英混合
{
	int i;
	int flag;
	
	while(*str)
	{
		if(*str<127)
		{
			if((x>LCD_x)||(y>LCD_y))
			{
				return;
			}
			if(x+8 > 480)
			{
				y += 16;
				x = 0;
			}
			lcd_draw_char(*str,x,y,color,next_photo);
			x += 8;
			str++;
		}
		else
		{
			i = 0;
			flag = 1;
			while(flag)
			{
				if(((*str) == font[i].ch[0])&&((*(str+1)) == font[i].ch[1]))
				{
					flag = 0;
					if((x+16) > 480)
					{
						y += 17;
						x = 0;
					}
					lcd_draw_chinese(font[i].gbklcd,x,y,color,next_photo);
					x += 16;
				}
				else
				{
					i++;
				}
			}
			str += 2;
		}	
	}
}

void lcd_dis_pic_half(const unsigned char * str)		//显示照片(刷半屏)
{
	unsigned int x,y;
	unsigned int m,n;
	unsigned int i = 0,j=522240-(480*4);
	
	for(y=0,m=LCD_y-1; (y<(136)); m--,y++)
	{		
//		RTC_Time_display();
		for(x=0,n=0; (x<LCD_x)&&(n<LCD_x); n++,x++)
		{
			FRAME_BUFFER[y][x] = (str[i]<<24)|(str[i+1]<<16)|(str[i+2]<<8)|(str[i+3]<<0);	//灰度<<24 红<<16 绿<<8 蓝<<0
			i += 4;
			FRAME_BUFFER[m][n] = (str[j]<<24)|(str[j+1]<<16)|(str[j+2]<<8)|(str[j+3]<<0);
			j += 4;
		}
		j -= 480*4*2;
	}
}

void lcd_dis_pic_ten(const unsigned char * str)//分成十分
{
	unsigned int x,y;
	unsigned int i;
	
	i = 0;
	for(y=0; y<LCD_y; y++)
	{
//		RTC_Time_display();		//显示当前时间	
		for(x=0; x<LCD_x; x++)
		{
			if((x/48)%2 == 1)
			{
				FRAME_BUFFER[y][x] = (str[i]<<24)|(str[i+1]<<16)|(str[i+2]<<8)|(str[i+3]<<0);	//灰度<<24 红<<16 绿<<8 蓝<<0
				i += 4;
			}
			else
			{
				i += 4;
			}
		}
		delay_ini(0x20000);
	}
}

void lcd_dis_pic_four(const unsigned char * str)		//左右刷图
{
	unsigned int x,y;
	unsigned int i = 0;
	
	for(x = 0; x < 480; x++)
	{
		for(y = 0; y < 272 ; y++)
		{
		  i = 4*(480*y+x);
			FRAME_BUFFER[y][x] = (str[i] << 24) | (str[i+1] << 16) | (str[i+2] << 8) | (str[i+3]);
		  i = 4*(480*(271-y)+(479-x));
      FRAME_BUFFER[271-y][479-x] = (str[i] << 24) | (str[i+1] << 16) | (str[i+2] << 8) | (str[i+3]);							
		}
		delay_ini(0x20000);
	}
}
