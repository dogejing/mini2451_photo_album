#include "app.h"

extern int UartRcvFlag ;
extern char temp[30];
extern unsigned int ChangePhotoTime;
extern int PhotoModel;

void change_photo_set(void)	//设置图片轮换时间
{
	if(UartRcvFlag == 2)
	{
		if((temp[2] == '(')&&(temp[3] == 's'))
		{
			ChangePhotoTime = (((temp[0]-48) * 10) + (temp[1] - 48));
			memset(temp,0,sizeof(temp));
			UartRcvFlag = 0;
		}	
	}
}

void change_photo_display(int AutoNextPhoto)	//显示图片，轮换显示
{
	const unsigned char *add[7] = {gImage_tu1,gImage_tu2,gImage_tu3,gImage_tu4,gImage_tu5,gImage_tu6,gImage_tu7};
	
	lcd_dis_pic_time(add[AutoNextPhoto]);
}

void change_photo_style_two(int AutoNextPhoto)	//刷图模式选择
{
	const unsigned char *add[7] = {gImage_tu1,gImage_tu2,gImage_tu3,gImage_tu4,gImage_tu5,gImage_tu6,gImage_tu7};

	if(PhotoModel == 0)
		lcd_dis_pic_half(add[AutoNextPhoto]);
	if(PhotoModel == 1)
		lcd_dis_pic_ten(add[AutoNextPhoto]);
	if(PhotoModel == 2)
		lcd_dis_pic_four(add[AutoNextPhoto]);
}


