 AREA Init,CODE,READONLY
 PRESERVE8	;��λ�ֽڶ���
 
 	IMPORT  |Image$$ER_ROM1$$RO$$Limit| 
    IMPORT  |Image$$RW_RAM1$$RW$$Base|   ; Base of RAM to initialise
	IMPORT  |Image$$RW_RAM1$$ZI$$Base|   ; Base and limit of area
	IMPORT  |Image$$RW_RAM1$$ZI$$Limit|  ; to zero initialise
	
 ENTRY
 
start		;�����쳣����
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
 ldr r0,=0x53000000 ;�رտ��Ź�
 ldr r1,=0x0
 str r1,[r0]
 
 ;orr r0,r0,#0x00001000 ;��Icahce
 ;mcr p15,0,r0,c1,c0,0
 
 ldr sp,=(0x32000000+0x100000)	;����ջָ��
 MOV r0,#0x53		;���ù���ģʽ���ж�����
 msr CPSR_cxsf,r0	
 
 IMPORT clock_init
 bl clock_init
 
 IMPORT Main
 bl Main
 
 EXPORT delay ;����

delay		;��ʱ����
 ;ldr r0,=0x1000000
delay_loop
 cmp r0,#0
 sub r0,#1
 bne delay_loop

 MOV pc,lr

_irq		;�жϴ������
 ldr sp,=(0x33000000+0x100000)
 sub lr,lr,#4
 stmdb sp!,{r0-r12,lr}	;��ջ�����浱ǰ�����״̬
 IMPORT do_irq			;�жϷ������޲������޷���ֵ
 bl do_irq
 ldmia sp!,{r0-r12,pc}^	;��֮��ѹջ�����ݳ�ջ
 
halt
 bl halt
TopOfROM	DCD	|Image$$ER_ROM1$$RO$$Limit|
BaseOfBSS	DCD	|Image$$RW_RAM1$$RW$$Base|
BaseOfZero	DCD	|Image$$RW_RAM1$$ZI$$Base|
EndOfBSS	DCD	|Image$$RW_RAM1$$ZI$$Limit|  	
	 

 END
 
 
 