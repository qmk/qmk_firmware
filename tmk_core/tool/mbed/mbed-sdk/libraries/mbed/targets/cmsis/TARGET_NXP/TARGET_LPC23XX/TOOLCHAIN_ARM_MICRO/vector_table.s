;/* mbed Microcontroller Library - InterruptIn
; * Copyright (c) 2006-2009 ARM Limited. All rights reserved.
; */
 
#line 1 "vector_table.s"
;


 

#line 1 "vector_defns.h"



 



 

#line 21 "vector_defns.h"


















#line 47 "vector_defns.h"


#line 58 "vector_defns.h"


















#line 7 "vector_table.s"
        
;


        AREA    RESET, CODE, READONLY
        ARM
;        ENTRY
        PRESERVE8





;        EXPORT __main
        IMPORT __mbed_reset
        IMPORT __mbed_undef
        IMPORT __mbed_swi
        IMPORT __mbed_prefetch_abort
        IMPORT __mbed_data_abort
        IMPORT __mbed_irq
        IMPORT __mbed_fiq

;

 
;__main
        LDR     PC, =__mbed_reset
        LDR     PC, =__mbed_undef
        LDR     PC, =__mbed_swi
        LDR     PC, =__mbed_prefetch_abort
        LDR     PC, =__mbed_data_abort
        NOP     ;
        LDR     PC, =__mbed_irq
        LDR     PC, =__mbed_fiq
        

        END
