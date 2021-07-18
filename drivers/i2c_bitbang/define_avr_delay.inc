#ifndef AVR_OUTER_NAME
#    define _AVR_OUTER_NAME(NAME) NAME ## _outer
#    define AVR_OUTER_NAME(NAME) _AVR_OUTER_NAME(NAME)
#    define _AVR_INNER_NAME(NAME) #NAME
#    define AVR_INNER_NAME(NAME) _AVR_INNER_NAME(NAME)
#endif

#if AVR_DELAY_AMOUNT == 8
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
}
#elif AVR_DELAY_AMOUNT == 9
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
            "nop"                     "\n\t" /* 1 cycle */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
}
#elif AVR_DELAY_AMOUNT == 10
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
            "nop"                     "\n\t" /* 1 cycle */
            "nop"                     "\n\t" /* 1 cycle */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
}
#elif AVR_DELAY_AMOUNT == 11
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
            "nop"                     "\n\t" /* 1 cycle */
            "nop"                     "\n\t" /* 1 cycle */
            "nop"                     "\n\t" /* 1 cycle */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
}
#elif AVR_DELAY_AMOUNT == 12
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
            "push r16"                "\n\t" /* 2 cycles */
            "pop r16"                 "\n\t" /* 2 cycles */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
}
#elif AVR_DELAY_AMOUNT == 13
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
            "push r16"                "\n\t" /* 2 cycles */
            "pop r16"                 "\n\t" /* 2 cycles */
            "nop"                     "\n\t" /* 1 cycle */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
}
#elif AVR_DELAY_AMOUNT == 14
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
            "push r16"                "\n\t" /* 2 cycles */
            "pop r16"                 "\n\t" /* 2 cycles */
            "nop"                     "\n\t" /* 1 cycle */
            "nop"                     "\n\t" /* 1 cycle */
            "ret"                            /* 4 cycles on 16-bit PC devices */
    :
    :
    : "memory");
}
#elif AVR_DELAY_AMOUNT >= 15
void __attribute__ ((noinline)) AVR_OUTER_NAME(AVR_DELAY_NAME)(void) {
    asm volatile (
        AVR_INNER_NAME(AVR_DELAY_NAME) ":" "\n\t"
             "push r16"                "\n\t" /* 2 cycles */
             "ldi r16, %[totalcnt]"    "\n\t" /* 1 cycle */
        "1:" "dec r16"                 "\n\t" /* 1 cycle */
             "brne 1b"                 "\n\t" /* 2 cycles when jumping, 1 cycle when not */
#    if ((AVR_DELAY_AMOUNT - 8 - 4) % 3) >= 1
             "nop"                     "\n\t" /* 1 cycle */
#    endif
#    if ((AVR_DELAY_AMOUNT - 8 - 4) % 3) >= 2
             "nop"                     "\n\t" /* 1 cycle */
#    endif
             "pop r16"                 "\n\t" /* 2 cycles */
             "ret"                            /* 4 cycles on 16-bit PC devices */

    :
    : [totalcnt] "M" ((AVR_DELAY_AMOUNT - 8 - 4)/3)
    : "memory");
}
#endif
