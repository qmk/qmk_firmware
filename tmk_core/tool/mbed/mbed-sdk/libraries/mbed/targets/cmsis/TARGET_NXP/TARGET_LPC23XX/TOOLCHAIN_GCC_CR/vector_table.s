# 1 "vector_table.s"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "vector_table.s"
;




# 1 "vector_defns.h" 1
# 7 "vector_table.s" 2

;







        .section .vectors, "ax"
        .arm


        .global __main
        .global __mbed_reset
        .global __mbed_undef
        .global __mbed_swi
        .global __mbed_prefetch_abort
        .global __mbed_data_abort
        .global __mbed_irq
        .global __mbed_fiq

;


_start:
        LDR PC, =__mbed_reset
        LDR PC, =__mbed_undef
        LDR PC, =__mbed_swi
        LDR PC, =__mbed_prefetch_abort
        LDR PC, =__mbed_data_abort
        NOP ;
        LDR PC, =__mbed_irq
        LDR PC, =__mbed_fiq
