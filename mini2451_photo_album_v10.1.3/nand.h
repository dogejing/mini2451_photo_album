#ifndef _NAND_H_
#define _NAND_H_

#define rNFCONF	 (*(volatile unsigned long *)(0x4e000000))
#define rNFCONT	 (*(volatile unsigned long *)(0x4e000004))
#define rNFCMD	 (*(volatile unsigned long *)(0x4e000008))
#define rNFADDR	 (*(volatile unsigned long *)(0x4e00000c))
#define rNFDATA8 (*(volatile unsigned char *)(0x4e000010))
#define rNFSTAT  (*(volatile unsigned long *)(0x4e000028))
#define rGPACON  (*(volatile unsigned long *)(0x56000000))

#define TACLS 1
#define TWRPH0 4
#define TAWTH1 1

#define NAND_INT_DIABLE 0
#define NAND_ENABLE 1

#define NF_CMD_READ1         0x00
#define NF_CMD_READ2         0x30

#define NF_CMD_WRITE1        0x80
#define NF_CMD_WRITE2        0x10

#define NF_CMD_RESET         0xff

#define NF_CMD_ERASE1        0x60
#define NF_CMD_ERASE2        0xd0

#define NF_CMD_READ_ID  		0x90

/*片选函数*/
#define NF_Enable() 			 {rNFCONT &= ~(1<<1);}
#define NF_Disable() 			 {rNFCONT |= (1<<1);}
/*发送命令函数*/
#define NF_Send_Cmd(cmd) 	 {rNFCMD = (cmd);}
/*发送地址函数*/
#define NF_Send_Addr(addr) {rNFADDR = addr;}
/*发送数据函数*/
#define NF_Send_Data(data) {rNFDATA8 = (data);}
/*打开忙检测*/
#define NF_Check_RB() 		 {rNFSTAT |= (1 << 4);}
/*判忙函数：等待，直到NFSTAT的bit0为1*/
#define NF_Check_Busy() 	 {while(!(rNFSTAT & (1 << 0)));} // 0 busy ,1 ready
/*读字节函数*/
#define NF_Read_Byte() 	 	 (rNFDATA8)

extern void nand_read_page(unsigned int block,unsigned int page,unsigned char * str);
extern void nand_write_page(unsigned int block,unsigned int page,unsigned char * str);
extern void nand_erase(unsigned int block);
extern void nand_init(void);
extern void nand_reset(void);
extern void nand_read_ID(unsigned char * str);

#endif

