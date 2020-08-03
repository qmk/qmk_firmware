/* This is from http://www.mtcnet.net/~henryvm/wdt/ */
#ifndef _AVR_WD_H_
#define _AVR_WD_H_

#include <avr/io.h>

/*
Copyright (c) 2009, Curt Van Maanen

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


include usage-
    #include "wd.h"             //if in same directory as project
    #include <avr/wd.h>         //if wd.h is in avr directory

set watchdog modes and prescale

usage-
    WD_SET(mode,[timeout]);     //prescale always set

modes-
    WD_OFF                      disabled
    WD_RST                      normal reset mode
    WD_IRQ                      interrupt only mode (if supported)
    WD_RST_IRQ                  interrupt+reset mode (if supported)

timeout-
    WDTO_15MS                   default if no timeout provided
    WDTO_30MS
    WDTO_60MS
    WDTO_120MS
    WDTO_250MS
    WDTO_500MS
    WDTO_1S
    WDTO_2S
    WDTO_4S                     (if supported)
    WDTO_8S                     (if supported)

examples-
    WD_SET(WD_RST,WDTO_1S);     //reset mode, 1s timeout
    WD_SET(WD_OFF);             //watchdog disabled (if not fused on)
    WD_SET(WD_RST);             //reset mode, 15ms (default timeout)
    WD_SET(WD_IRQ,WDTO_120MS);  //interrupt only mode, 120ms timeout
    WD_SET(WD_RST_IRQ,WDTO_2S); //interrupt+reset mode, 2S timeout


for enhanced watchdogs, if the watchdog is not being used WDRF should be
cleared on every power up or reset, along with disabling the watchdog-
    WD_DISABLE();               //clear WDRF, then turn off watchdog

*/

// reset registers to the same name (MCUCSR)
#if !defined(MCUCSR)
#    define MCUCSR MCUSR
#endif

// watchdog registers to the same name (WDTCSR)
#if !defined(WDTCSR)
#    define WDTCSR WDTCR
#endif

// if enhanced watchdog, define irq values, create disable macro
#if defined(WDIF)
#    define WD_IRQ 0xC0
#    define WD_RST_IRQ 0xC8
#    define WD_DISABLE()            \
        do {                        \
            MCUCSR &= ~(1 << WDRF); \
            WD_SET(WD_OFF);         \
        } while (0)
#endif

// all watchdogs
#define WD_RST 8
#define WD_OFF 0

// prescale values
#define WDTO_15MS 0
#define WDTO_30MS 1
#define WDTO_60MS 2
#define WDTO_120MS 3
#define WDTO_250MS 4
#define WDTO_500MS 5
#define WDTO_1S 6
#define WDTO_2S 7

// prescale values for avrs with WDP3
#if defined(WDP3)
#    define WDTO_4S 0x20
#    define WDTO_8S 0x21
#endif

// watchdog reset
#define WDR() __asm__ __volatile__("wdr")

// avr reset using watchdog
#define WD_AVR_RESET()               \
    do {                             \
        __asm__ __volatile__("cli"); \
        WD_SET_UNSAFE(WD_RST);       \
        while (1)                    \
            ;                        \
    } while (0)

/*set the watchdog-
1. save SREG
2. turn off irq's
3. reset watchdog timer
4. enable watchdog change
5. write watchdog value
6. restore SREG (restoring irq status)
*/
#define WD_SET(val, ...)                                                                                                            \
    __asm__ __volatile__("in __tmp_reg__,__SREG__"                                                                                  \
                         "\n\t"                                                                                                     \
                         "cli"                                                                                                      \
                         "\n\t"                                                                                                     \
                         "wdr"                                                                                                      \
                         "\n\t"                                                                                                     \
                         "sts %[wdreg],%[wden]"                                                                                     \
                         "\n\t"                                                                                                     \
                         "sts %[wdreg],%[wdval]"                                                                                    \
                         "\n\t"                                                                                                     \
                         "out __SREG__,__tmp_reg__"                                                                                 \
                         "\n\t"                                                                                                     \
                         :                                                                                                          \
                         : [ wdreg ] "M"(&WDTCSR), [ wden ] "r"((uint8_t)(0x18)), [ wdval ] "r"((uint8_t)(val | (__VA_ARGS__ + 0))) \
                         : "r0")

/*set the watchdog when I bit in SREG known to be clear-
1. reset watchdog timer
2. enable watchdog change
5. write watchdog value
*/
#define WD_SET_UNSAFE(val, ...)                  \
    __asm__ __volatile__("wdr"                   \
                         "\n\t"                  \
                         "sts %[wdreg],%[wden]"  \
                         "\n\t"                  \
                         "sts %[wdreg],%[wdval]" \
                         "\n\t"                  \
                         :                       \
                         : [ wdreg ] "M"(&WDTCSR), [ wden ] "r"((uint8_t)(0x18)), [ wdval ] "r"((uint8_t)(val | (__VA_ARGS__ + 0))))

// for compatibility with avr/wdt.h
#define wdt_enable(val) WD_SET(WD_RST, val)
#define wdt_disable() WD_SET(WD_OFF)

#endif /* _AVR_WD_H_ */
