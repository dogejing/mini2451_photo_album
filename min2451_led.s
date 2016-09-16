 AREA Init,CODE,READONLY
 PRESERVE8	;八位字节对齐
 
 	IMPORT  |Image$$ER_ROM1$$RO$$Limit| 
    IMPORT  |Image$$RW_RAM1$$RW$$Base|   ; Base of RAM to initialise
	IMPORT  |Image$$RW_RAM1$$ZI$$Base|   ; Base and limit of area
	IMPORT  |Image$$RW_RAM1$$ZI$$Limit|  ; to zero initialise
	
 ENTRY
 
start		;设置异常向量
 b reset
 b halt
 b halt
 b halt
 b halt
 b halt
 b _irq
 b halt

    ldr	r0, TopOfROM
	ldr	r2, BaseOfBSS
	ldr	r3, BaseOfZero	
0
	cmp	r2, r3
	ldrcc	r1, [r0], #4
	strcc	r1, [r2], #4
	bcc	%B0	

	mov	r0,	#20
	ldr	r3,	EndOfBSS
1	
	cmp	r2,	r3
	strcc	r0, [r2], #4
	bcc	%B1

reset
 ldr r0,=0x53000000 ;关闭看门狗
 ldr r1,=0x0
 str r1,[r0]
 
 ;orr r0,r0,#0x00001000 ;打开Icahce
 ;mcr p15,0,r0,c1,c0,0
 
 ldr sp,=(0x32000000+0x100000)	;设置栈指针
 MOV r0,#0x53		;设置工作模式和中断允许
 msr CPSR_cxsf,r0	
 
 IMPORT clock_init
 bl clock_init
 
 IMPORT Main
 bl Main
 
 EXPORT delay ;导出

delay		;延时函数
 ;ldr r0,=0x1000000
delay_loop
 cmp r0,#0
 sub r0,#1
 bne delay_loop

 MOV pc,lr

_irq		;中断处理程序
 ldr sp,=(0x33000000+0x100000)
 sub lr,lr,#4
 stmdb sp!,{r0-r12,lr}	;入栈，保存当前程序的状态
 IMPORT do_irq			;中断服务函数无参数，无返回值
 bl do_irq
 ldmia sp!,{r0-r12,pc}^	;将之间压栈的内容出栈
 
halt
 bl halt
TopOfROM	DCD	|Image$$ER_ROM1$$RO$$Limit|
BaseOfBSS	DCD	|Image$$RW_RAM1$$RW$$Base|
BaseOfZero	DCD	|Image$$RW_RAM1$$ZI$$Base|
EndOfBSS	DCD	|Image$$RW_RAM1$$ZI$$Limit|  	
	 

 END
 
 
 