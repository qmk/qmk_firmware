# 1 "vector_functions.s"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "vector_functions.s"
;
;
;

# 1 "vector_defns.h" 1
# 6 "vector_functions.s" 2






        .section VECFUNCS, "ax"
        .arm


        .weak __mbed_fiq
        .weak __mbed_undef
        .weak __mbed_prefetch_abort
        .weak __mbed_data_abort
        .weak __mbed_irq
        .weak __mbed_swi
        .weak __mbed_dcc_irq
        .weak __mbed_reset
        .global __mbed_init_realmonitor
        .global __mbed_init

;
;
__mbed_fiq:
        B __mbed_fiq

;
;
__mbed_undef:
        LDR PC, =0x7fffffa0

;
;
__mbed_prefetch_abort:
        LDR PC, =0x7fffffb0

;
;
__mbed_data_abort:
        LDR PC, =0x7fffffc0

;
;
;
;
;
;
;
;
;
__mbed_irq:
        ;
        MSR CPSR_c, #0x1F|0x80|0x40

        ;
        STMDB sp!, {r0-r3,r12,lr}

        ;
        MOV r0, #0xFFFFFF00
        LDR r0, [r0]

        ;
        MOV lr, pc
        BX r0

        ;
        MOV r0, #0xFFFFFF00
        STR r0, [r0] ;

        ;
        LDMFD sp!,{r0-r3,r12,lr}

        ;
        MSR CPSR_c, #0x12|0x80|0x40

        ;
        SUBS pc, lr, #4

;
;
;
;
__mbed_swi:
        ;
        ;
        STMFD sp!, {a4, r4, ip, lr}

        ;
        LDR r4, =0x40000040

        ;
        ;
        LDR a4, =0x00940000
        LDR PC, =0x7ffff820

;
;
;
;
__mbed_dcc_irq:

        ;

        ;
        LDMFD sp!,{r0-r3,r12,lr}

        ;
        MSR CPSR_c, #0x12|0x80|0x40

        ;

        ;
        SUB lr, lr, #4 ;
        STMFD sp!, {ip,lr} ;

        ;
        LDR LR, =0xfffff000
        STR LR, [LR, #0xf00]

        ;
        ;
        ;
        ;
        LDR PC, =0x7fffffe0

;
;
__mbed_reset:

        ;

        LDR R0, =(0x40000000 + 0x8000)

        ;
        MSR CPSR_c, #0x1B|0x80|0x40
        MOV SP, R0
        SUB R0, R0, #0x00000040

        ;
        MSR CPSR_c, #0x17|0x80|0x40
        MOV SP, R0
        SUB R0, R0, #0x00000040

        ;
        MSR CPSR_c, #0x11|0x80|0x40
        MOV SP, R0
        SUB R0, R0, #0x00000000

        ;
        MSR CPSR_c, #0x12|0x80|0x40
        MOV SP, R0
        SUB R0, R0, #0x00000040

        ;
        MSR CPSR_c, #0x13|0x80|0x40
        MOV SP, R0
        SUB R0, R0, #0x00000040

        ;
        MSR CPSR_c, #0x10
        MOV SP, R0

        ;
        LDR R0, =__mbed_init_realmonitor
        MOV LR, PC
        BX R0

        ;
        LDR R0, =__mbed_init
        BX R0
