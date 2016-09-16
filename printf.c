#include "app.h"



int my_printf(const char * fmt,...) //接受来自arm的信息
{
	int i;
	int len;
	va_list args;
	char g_pcOutBuf[1024];
	
	va_start(args,fmt);
	len = vsprintf(g_pcOutBuf,fmt,args);
	va_end(args);
	for(i=0; i<strlen(g_pcOutBuf); i++)
	{
		putchar(g_pcOutBuf[i]);
	}
	memset(g_pcOutBuf,0,1024);
	
	return len;
}

int my_scanf(const char * fmt,...)	//发送消息给arm
{
	int i = 0;
	unsigned char c;
	va_list args;
	char g_pcInBuf[1024];
	
	while(1)
	{
		c = getchar();
		putchar(c);
		if((c == 0x0d)||(c == 0x0a)) //换行和回车的16进制ASCII码
		{
			g_pcInBuf[i] = '\0';
			break;
		}
		else
		{
			g_pcInBuf[i++] = c;
		}	
	}
	
	va_start(args,fmt);
	i = my_vsscanf(g_pcInBuf,fmt,args);
	va_end(args);
	memset(g_pcInBuf,0,1024);
	
	return i;
}


