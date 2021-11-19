// clang-format off
#ifndef AVR_OUTER_NAME
#    define _AVR_OUTER_NAME(NAME) NAME ## _outer
#    define AVR_OUTER_NAME(NAME) _AVR_OUTER_NAME(NAME)
#    define _AVR_INNER_NAME(NAME) #NAME
#    define AVR_INNER_NAME(NAME) _AVR_INNER_NAME(NAME)
#endif

void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
#if (ARCH == ARCH_XMEGA)
            "nop"                     "\n\t" /* 1 cycle: xmega call instruction is 1 cycle faster */
#endif
#if ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == 8) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == (8 + 2))
            NOPS_0                    "\n\t" /* 0 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
#elif ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == 9) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == (9 + 2))
            NOPS_1                    "\n\t" /* 1 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
#elif ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == 10) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == (10 + 2))
            NOPS_2                    "\n\t" /* 2 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
#elif ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == 11) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == (11 + 2))
            NOPS_3                    "\n\t" /* 3 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
#elif ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == 12) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == (12 + 2))
            NOPS_4                    "\n\t" /* 4 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
#elif ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == 13) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == (13 + 2))
            NOPS_5                    "\n\t" /* 5 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
#elif ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == 14) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT == (14 + 2))
            NOPS_6                    "\n\t" /* 6 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
#elif ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 15) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= (15 + 2))
#    if (ARCH == ARCH_XMEGA)
             "push r16"                "\n\t" /* 1 cycle */
             "ldi r16, %[totalcnt]"    "\n\t" /* 1 cycle */
        "1:" "dec r16"                 "\n\t" /* 1 cycle */
             "brne 1b"                 "\n\t" /* 2 cycles when jumping, 1 cycle when not */
#        if ((AVR_DELAY_AMOUNT - 8 - 2) % 3) >= 1
             "nop"                     "\n\t" /* 1 cycle */
#        endif
#        if ((AVR_DELAY_AMOUNT - 8 - 2) % 3) >= 2
             "nop"                     "\n\t" /* 1 cycle */
#        endif
             "pop r16"                 "\n\t" /* 1 cycle */
             "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    : [totalcnt] "M" ((AVR_DELAY_AMOUNT - 8 - 2)/3)
    : "memory");
#    else
             "push r16"                "\n\t" /* 2 cycles */
             "ldi r16, %[totalcnt]"    "\n\t" /* 1 cycle */
        "1:" "dec r16"                 "\n\t" /* 1 cycle */
             "brne 1b"                 "\n\t" /* 2 cycles when jumping, 1 cycle when not */
#        if ((AVR_DELAY_AMOUNT - 8 - 4) % 3) >= 1
             "nop"                     "\n\t" /* 1 cycle */
#        endif
#        if ((AVR_DELAY_AMOUNT - 8 - 4) % 3) >= 2
             "nop"                     "\n\t" /* 1 cycle */
#        endif
             "pop r16"                 "\n\t" /* 2 cycles */
             "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    : [totalcnt] "M" ((AVR_DELAY_AMOUNT - 8 - 4)/3)
    : "memory");
#    endif
#endif
}
// clang-format on