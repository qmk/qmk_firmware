/*
 * light weight WS2812 Strands lib V1.0
 *
 * Controls WS2811/WS2812/WS2812B RGB-LEDs
 * Author: ANWC Limited d.b.a. ChonkerKeys (info@anwc.hk)
 *
 * Jan 10th, 2022  v1.0  Initial version taken from ws2812.c by Tim
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
#include "ws2812_strands.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define pinmask(pin) (_BV((pin)&0xF))

/*
 * Forward declare internal functions
 *
 * The functions take a byte-array and send to the data output as WS2812 bitstream.
 * The length is the number of bytes to send - three per LED.
 */

static inline void ws2812_strand_sendarray_mask(uint8_t pin, uint8_t *data, uint16_t datlen, uint8_t masklo, uint8_t maskhi);

void ws2812_strand_setleds(uint8_t strand, LED_TYPE *ledarray, uint16_t number_of_leds) {

#define _STRAND_SENDARRAY(strand) \
    DDRx_ADDRESS(RGB_STRAND_##strand##_DI_PIN) |= pinmask(RGB_STRAND_##strand##_DI_PIN); \
    ws2812_strand_sendarray_mask( \
            _SFR_IO_ADDR(PORTx_ADDRESS(RGB_STRAND_##strand##_DI_PIN)), \
            (uint8_t *)ledarray, number_of_leds * sizeof(LED_TYPE), \
            ~(pinmask(RGB_STRAND_##strand##_DI_PIN)) & PORTx_ADDRESS(RGB_STRAND_##strand##_DI_PIN), \
            pinmask(RGB_STRAND_##strand##_DI_PIN) | PORTx_ADDRESS(RGB_STRAND_##strand##_DI_PIN))

   switch(strand) {
#ifdef RGB_STRAND_0_DI_PIN
        case 0:
            _STRAND_SENDARRAY(0);
            break;
#endif
#ifdef RGB_STRAND_1_DI_PIN
        case 1:
            _STRAND_SENDARRAY(1);
            break;
#endif
#ifdef RGB_STRAND_2_DI_PIN
        case 2:
            _STRAND_SENDARRAY(2);
            break;
#endif
#ifdef RGB_STRAND_3_DI_PIN
        case 3:
            _STRAND_SENDARRAY(3);
            break;
#endif
#ifdef RGB_STRAND_4_DI_PIN
        case 4:
            _STRAND_SENDARRAY(4);
            break;
#endif
#ifdef RGB_STRAND_5_DI_PIN
        case 5:
            _STRAND_SENDARRAY(5);
            break;
#endif
#ifdef RGB_STRAND_6_DI_PIN
        case 6:
            _STRAND_SENDARRAY(6);
            break;
#endif
#ifdef RGB_STRAND_7_DI_PIN
        case 7:
            _STRAND_SENDARRAY(7);
            break;
#endif
#ifdef RGB_STRAND_8_DI_PIN
        case 8:
            _STRAND_SENDARRAY(8);
            break;
#endif
#ifdef RGB_STRAND_9_DI_PIN
        case 9:
            _STRAND_SENDARRAY(9);
            break;
#endif
#ifdef RGB_STRAND_A_DI_PIN
        case 10:
            _STRAND_SENDARRAY(A);
            break;
#endif
#ifdef RGB_STRAND_B_DI_PIN
        case 11:
            _STRAND_SENDARRAY(B);
            break;
#endif
        default:
            return;
    }

    _delay_us(WS2812_TRST_US);
}

/*
  This routine writes an array of bytes with RGB values to the Dataout pin
  using the fast 800kHz clockless WS2811/2812 protocol.
*/

// Fixed cycles used by the inner loop
#define w_fixedlow 2
#define w_fixedhigh 4
#define w_fixedtotal 8

// Insert NOPs to match the timing, if possible
#define w_zerocycles (((F_CPU / 1000) * WS2812_T0H) / 1000000)
#define w_onecycles (((F_CPU / 1000) * WS2812_T1H + 500000) / 1000000)
#define w_totalcycles (((F_CPU / 1000) * WS2812_TIMING + 500000) / 1000000)

// w1_nops - nops between rising edge and falling edge - low
#if w_zerocycles >= w_fixedlow
#    define w1_nops (w_zerocycles - w_fixedlow)
#else
#    define w1_nops 0
#endif

// w2_nops - nops between fe low and fe high
#if w_onecycles >= (w_fixedhigh + w1_nops)
#    define w2_nops (w_onecycles - w_fixedhigh - w1_nops)
#else
#    define w2_nops 0
#endif

// w3_nops - nops to complete loop
#if w_totalcycles >= (w_fixedtotal + w1_nops + w2_nops)
#    define w3_nops (w_totalcycles - w_fixedtotal - w1_nops - w2_nops)
#else
#    define w3_nops 0
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

#define w_nop1 "nop      \n\t"
#define w_nop2 "rjmp .+0 \n\t"
#define w_nop4 w_nop2 w_nop2
#define w_nop8 w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8

__attribute__((always_inline)) static inline void ws2812_strand_sendarray_mask(uint8_t pin, uint8_t *data, uint16_t datlen, uint8_t masklo, uint8_t maskhi) {
    uint8_t curbyte, ctr, sreg_prev;

    sreg_prev = SREG;
    cli();

    while (datlen--) {
        curbyte = (*data++);

        asm volatile("       ldi   %0,8  \n\t"
                     "loop%=:            \n\t"
                     "       out   %2,%3 \n\t"  //  '1' [01] '0' [01] - re
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
                     "       sbrs  %1,7  \n\t"  //  '1' [03] '0' [02]
                     "       out   %2,%4 \n\t"  //  '1' [--] '0' [03] - fe-low
                     "       lsl   %1    \n\t"  //  '1' [04] '0' [04]
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
                     "       out   %2,%4 \n\t"  //  '1' [+1] '0' [+1] - fe-high
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

                     "       dec   %0    \n\t"  //  '1' [+2] '0' [+2]
                     "       brne  loop%=\n\t"  //  '1' [+3] '0' [+4]
                     : "=&d"(ctr)
                     : "r"(curbyte), "I"(pin), "r"(maskhi), "r"(masklo));
    }

    SREG = sreg_prev;
}
