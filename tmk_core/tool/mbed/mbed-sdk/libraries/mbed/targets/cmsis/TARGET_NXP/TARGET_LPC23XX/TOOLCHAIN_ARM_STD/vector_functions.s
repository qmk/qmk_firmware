;/* mbed Microcontroller Library - InterruptIn
; * Copyright (c) 2006-2009 ARM Limited. All rights reserved.
; */
 
#line 1 "vector_functions.s"
;
;
;

#line 1 "vector_defns.h"



 



 

#line 21 "vector_defns.h"


















#line 47 "vector_defns.h"


#line 58 "vector_defns.h"


















#line 6 "vector_functions.s"


        AREA    VECFUNCS, CODE, READONLY
        ARM
        PRESERVE8





        EXPORT __mbed_fiq [WEAK]
        EXPORT __mbed_undef [WEAK]
        EXPORT __mbed_prefetch_abort [WEAK]
        EXPORT __mbed_data_abort [WEAK]
        EXPORT __mbed_irq [WEAK]
        EXPORT __mbed_swi [WEAK]
        EXPORT __mbed_dcc_irq [WEAK]
        EXPORT __mbed_reset [WEAK]
        IMPORT __mbed_init_realmonitor

;
;
__mbed_fiq
        B       __mbed_fiq

;
;
__mbed_undef
        LDR     PC, =0x7fffffa0

;
;
__mbed_prefetch_abort
        LDR     PC, =0x7fffffb0

;
;
__mbed_data_abort
        LDR     PC, =0x7fffffc0

;
;
;
;
;
;
;
;
;
__mbed_irq
        ;
        MSR     CPSR_c, #0x1F:OR:0x80:OR:0x40
                
        ;
        STMDB   sp!, {r0-r3,r12,lr}    

        ;
        MOV	r0, #0xFFFFFF00
        LDR	r0, [r0]	

        ;
        MOV     lr, pc       
        BX      r0           
			    				
        ;
        MOV	r0, #0xFFFFFF00
        STR	r0, [r0]			;
				
        ;
        LDMFD   sp!,{r0-r3,r12,lr}

        ;
        MSR     CPSR_c, #0x12:OR:0x80:OR:0x40

        ;
        SUBS    pc, lr, #4 

;
;
;
;
__mbed_swi
        ;
        ;
        STMFD   sp!, {a4, r4, ip, lr}

        ;
        LDR     r4, =0x40000040

        ;
        ;
        LDR     a4, =0x00940000
        LDR	PC, =0x7ffff820				

;
;
;
;
__mbed_dcc_irq

        ;
			
        ;
        LDMFD    sp!,{r0-r3,r12,lr}

        ;
        MSR     CPSR_c, #0x12:OR:0x80:OR:0x40

        ;
				
        ;
        SUB     lr, lr, #4              ;
        STMFD   sp!, {ip,lr}            ;
			
        ;
        LDR     LR, =0xfffff000
        STR     LR, [LR, #0xf00]
			
        ;
        ;
        ;
        ;
        LDR     PC, =0x7fffffe0			 

;
; __mbed_reset is called after reset
; we setup the stacks and realmonitor, then call Reset_Handler like on M3

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                MOV     LR, PC       
                BX      R0
                LDR     R0, =__main
                BX      R0
                ENDP

__mbed_reset

        ;

        LDR     R0, =(0x40000000 + 0x8000)

        ;
        MSR     CPSR_c, #0x1B:OR:0x80:OR:0x40
        MOV     SP, R0
        SUB     R0, R0, #0x00000040

        ;
        MSR     CPSR_c, #0x17:OR:0x80:OR:0x40
        MOV     SP, R0
        SUB     R0, R0, #0x00000040

        ;
        MSR     CPSR_c, #0x11:OR:0x80:OR:0x40
        MOV     SP, R0
        SUB     R0, R0, #0x00000000

        ;
        MSR     CPSR_c, #0x12:OR:0x80:OR:0x40
        MOV     SP, R0
        SUB     R0, R0, #0x00000040

        ;
        MSR     CPSR_c, #0x13:OR:0x80:OR:0x40
        MOV     SP, R0
        SUB     R0, R0, #0x00000040

        ;
        MSR     CPSR_c, #0x10
        MOV     SP, R0

        ;
        LDR     R0, =__mbed_init_realmonitor
        MOV     LR, PC       
        BX      R0           
        
        ;
        LDR     R0, =Reset_Handler
        BX      R0

        
        END
