/*
 * light weight WS2812 lib V2.0b
 *
 * Controls WS2811/WS2812/WS2812B RGB-LEDs
 * Author: Tim (cpldcpu@gmail.com)
 *
 * Jan 18th, 2014  v2.0b Initial Version
 * Nov 29th, 2015  v2.3  Added SK6812RGBW support
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ws2812.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "timer.h"

#define pinmask(pin) (_BV((pin)&0xF))

/*
 * Forward declare internal functions
 *
 * The functions take a byte-array and send to the data output as WS2812 bitstream.
 * The length is the number of bytes to send - three per LED.
 */

static inline void ws2812_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t masklo, uint8_t maskhi);

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds) {
    DDRx_ADDRESS(RGB_DI_PIN) |= pinmask(RGB_DI_PIN);

    uint8_t masklo = ~(pinmask(RGB_DI_PIN)) & PORTx_ADDRESS(RGB_DI_PIN);
    uint8_t maskhi = pinmask(RGB_DI_PIN) | PORTx_ADDRESS(RGB_DI_PIN);

    ws2812_sendarray_mask((uint8_t *)ledarray, number_of_leds * sizeof(LED_TYPE), masklo, maskhi);

    _delay_us(WS2812_TRST_US);
}

/*
  This routine writes an array of bytes with RGB values to the Dataout pin
  using the fast 800kHz clockless WS2811/2812 protocol.
*/

// Timing in ns
#define w_zeropulse 350
#define w_onepulse 900
#define w_totalperiod 1250

// Fixed cycles used by the inner loop
#define w_fixedlow 2
#define w_fixedhigh 4
#define w_fixedtotal 8

// Insert NOPs to match the timing, if possible
#define w_zerocycles (((F_CPU / 1000) * w_zeropulse) / 1000000)
#define w_onecycles (((F_CPU / 1000) * w_onepulse + 500000) / 1000000)
#define w_totalcycles (((F_CPU / 1000) * w_totalperiod + 500000) / 1000000)

// w1 - nops between rising edge and falling edge - low
#define w1 (w_zerocycles - w_fixedlow)
// w2   nops between fe low and fe high
#define w2 (w_onecycles - w_fixedhigh - w1)
// w3   nops to complete loop
#define w3 (w_totalcycles - w_fixedtotal - w1 - w2)

#if w1 > 0
#    define w1_nops w1
#else
#    define w1_nops 0
#endif

// The only critical timing parameter is the minimum pulse length of the "0"
// Warn or throw error if this timing can not be met with current F_CPU settings.
#define w_lowtime ((w1_nops + w_fixedlow) * 1000000) / (F_CPU / 1000)
#if w_lowtime > 550
#    error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime > 450
#    warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
#    warning "Please consider a higher clockspeed, if possible"
#endif

// Interrupt flag register and bit which correspond to the QMK timer interrupt
// (this must match the code in tmk_core/common/avr/timer.c).
#if defined(__AVR_ATmega32U4__)
#    define TIFRx TIFR0
#    define OCFxx OCF0A
#endif

#ifdef TIFRx
// Number of cycles consumed by the code to check for pending timer interrupts.
#    define timer_fixup_cycles 5
#    if w2 >= timer_fixup_cycles
#        define DO_TIMER_FIXUP
#    else
#        pragma message "ws2812: The clock speed is not enough to fix the timer skew with a long LED chain"
#    endif
#endif

#if defined(DO_TIMER_FIXUP)
#    define w2_nops (w2 - timer_fixup_cycles)
#elif w2 > 0
#    define w2_nops w2
#else
#    define w2_nops 0
#endif

#if w3 > 0
#    define w3_nops w3
#else
#    define w3_nops 0
#endif

#define w_nop1 "nop      \n\t"
#define w_nop2 "rjmp .+0 \n\t"
#define w_nop4 w_nop2 w_nop2
#define w_nop8 w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8

static inline void ws2812_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t masklo, uint8_t maskhi) {
    uint8_t curbyte, ctr, sreg_prev;
#ifdef DO_TIMER_FIXUP
    uint8_t irqs = 0;
    uint8_t tifr;
#endif

    sreg_prev = SREG;
    cli();

    while (datlen--) {
        curbyte = (*data++);

        asm volatile("       ldi   %[ctr],8             \n\t"
                     "loop%=:                           \n\t"
                     "       out   %[port],%[maskhi]    \n\t"  //  '1' [01] '0' [01] - re
#if (w1_nops & 1)
                     w_nop1
#endif
#if (w1_nops & 2)
                         w_nop2
#endif
#if (w1_nops & 4)
                             w_nop4
#endif
#if (w1_nops & 8)
                                 w_nop8
#endif
#if (w1_nops & 16)
                                     w_nop16
#endif
                     "       sbrs  %[curbyte],7         \n\t"  //  '1' [03] '0' [02]
                     "       out   %[port],%[masklo]    \n\t"  //  '1' [--] '0' [03] - fe-low
                     "       lsl   %[curbyte]           \n\t"  //  '1' [04] '0' [04]
#ifdef DO_TIMER_FIXUP
                     // Check for a pending timer compare interrupt which is
                     // used to maintain the QMK clock.  If the interrupt was
                     // pending, reset the status register bit by writing 1.
                     "       in    %[tifr],%[tifr_port] \n\t"
                     "       andi  %[tifr],%[tifr_mask] \n\t"
                     "       out   %[tifr_port],%[tifr] \n\t"

                     // Now %[tifr] is nonzero if the interrupt was pending,
                     // and in that case we need to increment %[irqs].  Do it
                     // by treating %[irqs]:%[tifr] as a 16-bit number and
                     // adding 0x00ff to it (if the low byte is nonzero, this
                     // will result in propagating the carry to the high byte).
                     // Because AVR does not have an "addi" instruction,
                     // instead of adding 0x00ff, we need to subtract its
                     // two's-complement - 0xff01.
                     "       subi  %[tifr],0x01         \n\t"
                     "       sbci  %[irqs],0xff         \n\t"

                     // The above code takes 5 cycles to execute; the value of
                     // timer_fixup_cycles must match this.
#endif
#if (w2_nops & 1)
                     w_nop1
#endif
#if (w2_nops & 2)
                         w_nop2
#endif
#if (w2_nops & 4)
                             w_nop4
#endif
#if (w2_nops & 8)
                                 w_nop8
#endif
#if (w2_nops & 16)
                                     w_nop16
#endif
                     "       out   %[port],%[masklo]    \n\t"  //  '1' [+1] '0' [+1] - fe-high
#if (w3_nops & 1)
                     w_nop1
#endif
#if (w3_nops & 2)
                         w_nop2
#endif
#if (w3_nops & 4)
                             w_nop4
#endif
#if (w3_nops & 8)
                                 w_nop8
#endif
#if (w3_nops & 16)
                                     w_nop16
#endif

                     "       dec   %[ctr]               \n\t"  //  '1' [+2] '0' [+2]
                     "       brne  loop%=               \n\t"  //  '1' [+3] '0' [+4]
                     : [ctr] "=&d"(ctr)
#ifdef DO_TIMER_FIXUP
                     , [irqs] "=&d"(irqs), [tifr] "=&d"(tifr)
#endif
                     : [curbyte] "r"(curbyte), [port] "I"(_SFR_IO_ADDR(PORTx_ADDRESS(RGB_DI_PIN))), [maskhi] "r"(maskhi), [masklo] "r"(masklo)
#ifdef DO_TIMER_FIXUP
                     , [tifr_port] "I"(_SFR_IO_ADDR(TIFRx)), [tifr_mask] "M"(_BV(OCFxx))
#endif
                     );
    }

#ifdef DO_TIMER_FIXUP
    timer_count += irqs;
#endif
    SREG = sreg_prev;
}
