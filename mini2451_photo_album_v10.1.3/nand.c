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
	rGPACON &= ~(0x3f<<17);	/*����λ����*/
	rGPACON |= (0x3f<<17);	/*��ʼ����GPA*/
	rNFCONT = (TACLS<<12)|(TWRPH0<<8)|(TAWTH1<<4);
	rNFCONT = (NAND_INT_DIABLE<<12)|(NAND_ENABLE<<0);
	rNFSTAT = 0x0;	/*NAND���״̬����*/
	nand_reset();	/*��λ*/
}

void nand_erase(unsigned int block)	/*�����*/
{
	unsigned int blocknum = (block<<6);	/*����6λ���Ƴ�A12-17��*/
	
	nand_reset();	/*��λNAND FLASH*/
	NF_Enable();	/*ѡ��NAND FLASH*/
	NF_Check_RB();	/*æ���*/
	NF_Send_Cmd(NF_CMD_ERASE1);	/*���Ϳ�����������0x60��*/
	NF_Send_Addr(blocknum & 0xff);
	NF_Send_Addr((blocknum>>8) & 0xff);	/*���Ϳ��ַ*/
	NF_Send_Addr((blocknum>>16) & 0xff);
	NF_Send_Cmd(NF_CMD_ERASE2);		/*���Ϳ����ȷ�����0xd0��*/
	NF_Check_Busy();	/*æ�ȴ�*/
	NF_Disable();		/*ȡ��ѡ��оƬ*/
}

void nand_write_page(unsigned int block,unsigned int page,unsigned char * str)
{
	unsigned int pagenum = (block<<6) + page;
	unsigned int i;
	
	nand_reset();
	NF_Enable();	/*ѡ��NAND FLASH*/
	NF_Check_RB();	/*æ���*/
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
	NF_Check_Busy();	/*æ�ȴ�*/
	NF_Disable();		/*ȡ��ѡ��оƬ*/
}

void nand_read_page(unsigned int block,unsigned int page,unsigned char * str)
{
	unsigned int pagenum = (block<<6) + page;
	unsigned int i;
	
	nand_reset();
	NF_Enable();	/*ѡ��NAND FLASH*/
	NF_Check_RB();	/*æ���*/
	NF_Send_Cmd(NF_CMD_READ1);
	NF_Send_Addr(0x0);
	NF_Send_Addr(0x0);
	NF_Send_Addr(pagenum & 0xff);
	NF_Send_Addr((pagenum>>8) & 0xff);
	NF_Send_Addr((pagenum>>16) & 0xff);
	NF_Send_Cmd(NF_CMD_READ2);
	NF_Check_Busy();	/*æ�ȴ�*/
	for(i=0; i<2048; i++)
	{
		str[i] = NF_Read_Byte();
	}
	NF_Disable();		/*ȡ��ѡ��оƬ*/
}

void nand_read_ID(unsigned char * str)
{
	unsigned int i;
	
//	nand_reset();
	NF_Enable();	/*ѡ��NAND FLASH*/
	NF_Check_RB();	/*æ���*/
	NF_Send_Cmd(NF_CMD_READ_ID);
	NF_Send_Addr(0x0);
	NF_Check_Busy();	/*æ�ȴ�*/
	for(i=0; i<2048; i++)
	{
		str[i] = NF_Read_Byte();
	}
	NF_Disable();
}

