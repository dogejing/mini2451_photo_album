#include "nand.h"

void nand_reset(void)
{
	NF_Enable();
	NF_Check_RB();
	NF_Send_Cmd(NF_CMD_RESET);
	NF_Check_Busy();
	NF_Disable();
}

void nand_init(void)
{
	rGPACON &= ~(0x3f<<17);	/*操作位清零*/
	rGPACON |= (0x3f<<17);	/*初始化化GPA*/
	rNFCONT = (TACLS<<12)|(TWRPH0<<8)|(TAWTH1<<4);
	rNFCONT = (NAND_INT_DIABLE<<12)|(NAND_ENABLE<<0);
	rNFSTAT = 0x0;	/*NAND相关状态清零*/
	nand_reset();	/*复位*/
}

void nand_erase(unsigned int block)	/*块擦除*/
{
	unsigned int blocknum = (block<<6);	/*左移6位（移除A12-17）*/
	
	nand_reset();	/*复位NAND FLASH*/
	NF_Enable();	/*选中NAND FLASH*/
	NF_Check_RB();	/*忙检测*/
	NF_Send_Cmd(NF_CMD_ERASE1);	/*发送块擦除发起命令（0x60）*/
	NF_Send_Addr(blocknum & 0xff);
	NF_Send_Addr((blocknum>>8) & 0xff);	/*发送块地址*/
	NF_Send_Addr((blocknum>>16) & 0xff);
	NF_Send_Cmd(NF_CMD_ERASE2);		/*发送块擦除确认命令（0xd0）*/
	NF_Check_Busy();	/*忙等待*/
	NF_Disable();		/*取消选中芯片*/
}

void nand_write_page(unsigned int block,unsigned int page,unsigned char * str)
{
	unsigned int pagenum = (block<<6) + page;
	unsigned int i;
	
	nand_reset();
	NF_Enable();	/*选中NAND FLASH*/
	NF_Check_RB();	/*忙检测*/
	NF_Send_Cmd(NF_CMD_WRITE1);
	NF_Send_Addr(0x0);
	NF_Send_Addr(0x0);
	NF_Send_Addr(pagenum & 0xff);
	NF_Send_Addr((pagenum>>8) & 0xff);
	NF_Send_Addr((pagenum>>16) & 0xff);
	for(i=0; i<2048; i++)
	{
		NF_Send_Data(str[i]);
	}
	NF_Send_Cmd(NF_CMD_WRITE2);
	NF_Check_Busy();	/*忙等待*/
	NF_Disable();		/*取消选中芯片*/
}

void nand_read_page(unsigned int block,unsigned int page,unsigned char * str)
{
	unsigned int pagenum = (block<<6) + page;
	unsigned int i;
	
	nand_reset();
	NF_Enable();	/*选中NAND FLASH*/
	NF_Check_RB();	/*忙检测*/
	NF_Send_Cmd(NF_CMD_READ1);
	NF_Send_Addr(0x0);
	NF_Send_Addr(0x0);
	NF_Send_Addr(pagenum & 0xff);
	NF_Send_Addr((pagenum>>8) & 0xff);
	NF_Send_Addr((pagenum>>16) & 0xff);
	NF_Send_Cmd(NF_CMD_READ2);
	NF_Check_Busy();	/*忙等待*/
	for(i=0; i<2048; i++)
	{
		str[i] = NF_Read_Byte();
	}
	NF_Disable();		/*取消选中芯片*/
}

void nand_read_ID(unsigned char * str)
{
	unsigned int i;
	
//	nand_reset();
	NF_Enable();	/*选中NAND FLASH*/
	NF_Check_RB();	/*忙检测*/
	NF_Send_Cmd(NF_CMD_READ_ID);
	NF_Send_Addr(0x0);
	NF_Check_Busy();	/*忙等待*/
	for(i=0; i<2048; i++)
	{
		str[i] = NF_Read_Byte();
	}
	NF_Disable();
}

