/* Copyright 2021 Drashna Jael're
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

#include QMK_KEYBOARD_H
#include "rgb_functions.h"

#ifdef RGBLIGHT_ENABLE
#    include "ws2812.h"
#    include <avr/interrupt.h>
#    include <avr/io.h>
#    include <util/delay.h>

#    define pinmask(pin) (_BV((pin)&0xF))

/*
 * Forward declare internal functions
 *
 * The functions take a byte-array and send to the data output as WS2812 bitstream.
 * The length is the number of bytes to send - three per LED.
 */

static inline void ws2812_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t masklo, uint8_t maskhi);

/*
  This routine writes an array of bytes with RGB values to the Dataout pin
  using the fast 800kHz clockless WS2811/2812 protocol.
*/

// Timing in ns
#    define w_zeropulse 350
#    define w_onepulse 900
#    define w_totalperiod 1250

// Fixed cycles used by the inner loop
#    define w_fixedlow 2
#    define w_fixedhigh 4
#    define w_fixedtotal 8

// Insert NOPs to match the timing, if possible
#    define w_zerocycles (((F_CPU / 1000) * w_zeropulse) / 1000000)
#    define w_onecycles (((F_CPU / 1000) * w_onepulse + 500000) / 1000000)
#    define w_totalcycles (((F_CPU / 1000) * w_totalperiod + 500000) / 1000000)

// w1_nops - nops between rising edge and falling edge - low
#    if w_zerocycles >= w_fixedlow
#        define w1_nops (w_zerocycles - w_fixedlow)
#    else
#        define w1_nops 0
#    endif

// w2_nops - nops between fe low and fe high
#    if w_onecycles >= (w_fixedhigh + w1_nops)
#        define w2_nops (w_onecycles - w_fixedhigh - w1_nops)
#    else
#        define w2_nops 0
#    endif

// w3_nops - nops to complete loop
#    if w_totalcycles >= (w_fixedtotal + w1_nops + w2_nops)
#        define w3_nops (w_totalcycles - w_fixedtotal - w1_nops - w2_nops)
#    else
#        define w3_nops 0
#    endif

// The only critical timing parameter is the minimum pulse length of the "0"
// Warn or throw error if this timing can not be met with current F_CPU settings.
#    define w_lowtime ((w1_nops + w_fixedlow) * 1000000) / (F_CPU / 1000)
#    if w_lowtime > 550
#        error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#    elif w_lowtime > 450
#        warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
#        warning "Please consider a higher clockspeed, if possible"
#    endif

#    define w_nop1 "nop      \n\t"
#    define w_nop2 "rjmp .+0 \n\t"
#    define w_nop4 w_nop2 w_nop2
#    define w_nop8 w_nop4 w_nop4
#    define w_nop16 w_nop8 w_nop8

static inline void ws2812_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t masklo, uint8_t maskhi) {
    uint8_t curbyte, ctr, sreg_prev;

    sreg_prev = SREG;
    cli();

    while (datlen--) {
        curbyte = (*data++);

        asm volatile("       ldi   %0,8  \n\t"
                     "loop%=:            \n\t"
                     "       out   %2,%3 \n\t"  //  '1' [01] '0' [01] - re
#    if (w1_nops & 1)
                     w_nop1
#    endif
#    if (w1_nops & 2)
                         w_nop2
#    endif
#    if (w1_nops & 4)
                             w_nop4
#    endif
#    if (w1_nops & 8)
                                 w_nop8
#    endif
#    if (w1_nops & 16)
                                     w_nop16
#    endif
                     "       sbrs  %1,7  \n\t"  //  '1' [03] '0' [02]
                     "       out   %2,%4 \n\t"  //  '1' [--] '0' [03] - fe-low
                     "       lsl   %1    \n\t"  //  '1' [04] '0' [04]
#    if (w2_nops & 1)
                     w_nop1
#    endif
#    if (w2_nops & 2)
                         w_nop2
#    endif
#    if (w2_nops & 4)
                             w_nop4
#    endif
#    if (w2_nops & 8)
                                 w_nop8
#    endif
#    if (w2_nops & 16)
                                     w_nop16
#    endif
                     "       out   %2,%4 \n\t"  //  '1' [+1] '0' [+1] - fe-high
#    if (w3_nops & 1)
                     w_nop1
#    endif
#    if (w3_nops & 2)
                         w_nop2
#    endif
#    if (w3_nops & 4)
                             w_nop4
#    endif
#    if (w3_nops & 8)
                                 w_nop8
#    endif
#    if (w3_nops & 16)
                                     w_nop16
#    endif

                     "       dec   %0    \n\t"  //  '1' [+2] '0' [+2]
                     "       brne  loop%=\n\t"  //  '1' [+3] '0' [+4]
                     : "=&d"(ctr)
                     : "r"(curbyte), "I"(_SFR_IO_ADDR(PORTx_ADDRESS(RGBLIGHT_DI_PIN))), "r"(maskhi), "r"(masklo));
    }

    SREG = sreg_prev;
}

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {
    DDRx_ADDRESS(RGBLIGHT_DI_PIN) |= pinmask(RGBLIGHT_DI_PIN);

    uint8_t masklo = ~(pinmask(RGBLIGHT_DI_PIN)) & PORTx_ADDRESS(RGBLIGHT_DI_PIN);
    uint8_t maskhi = pinmask(RGBLIGHT_DI_PIN) | PORTx_ADDRESS(RGBLIGHT_DI_PIN);

    ws2812_sendarray_mask((uint8_t *)start_led, num_leds * sizeof(LED_TYPE), masklo, maskhi);

    _delay_us(WS2812_TRST_US);
}
#endif

#ifdef RGB_MATRIX_ENABLE
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }

    if (record->event.pressed) {
        switch(keycode) {
        case RGB_MATRIX_TOGGLE: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case RGB_MATRIX_MODE_INC:
            rgb_matrix_step();
            return false;
        case RGB_MATRIX_MODE_DEC:
            rgb_matrix_step_reverse();
            return false;
        case RGB_MATRIX_HUE_INC:
            rgb_matrix_increase_hue();
            return false;
        case RGB_MATRIX_HUE_DEC:
            rgb_matrix_decrease_hue();
            return false;
        case RGB_MATRIX_SAT_INC:
            rgb_matrix_increase_sat();
            return false;
        case RGB_MATRIX_SAT_DEC:
            rgb_matrix_decrease_sat();
            return false;
        case RGB_MATRIX_VAL_INC:
            rgb_matrix_increase_val();
            return false;
        case RGB_MATRIX_VAL_DEC:
            rgb_matrix_decrease_val();
            return false;
        default:
            break;
        }
    }
    return true;
}
#endif
