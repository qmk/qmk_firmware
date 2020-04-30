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

/**
 * indicator.c
 */

#include "dp60.h"

#include "rgblight_list.h"
#include "rgblight.h"
#include "ws2812.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

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

#if w2 > 0
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
void inline indicator_sendarray_mask_ind(uint8_t *data, uint16_t datlen, uint8_t maskhi) {
    uint8_t curbyte, ctr, masklo;
    uint8_t sreg_prev;

    // masklo  =~maskhi&ws2812_PORTREG;
    // maskhi |=        ws2812_PORTREG;
    masklo = ~maskhi & _SFR_IO8((RGB_INDICATOR_PIN >> 4) + 2);
    maskhi |= _SFR_IO8((RGB_INDICATOR_PIN >> 4) + 2);
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
                     : "r"(curbyte), "I"(_SFR_IO_ADDR(_SFR_IO8((RGB_INDICATOR_PIN >> 4) + 2))), "r"(maskhi), "r"(masklo));
    }

    SREG = sreg_prev;
}

// caps led
const rgblight_segment_t PROGMEM dp60_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {18, 1, HSV_RED}
);

// scroll led
const rgblight_segment_t PROGMEM dp60_scrolllock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {19, 1, HSV_GREEN}
);

// num led
const rgblight_segment_t PROGMEM dp60_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {20, 1, HSV_BLUE}
);

// light 21 to 26 for layer 1-5
const rgblight_segment_t PROGMEM dp60_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {21, 1, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM dp60_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {22, 1, HSV_CYAN}
);
const rgblight_segment_t PROGMEM dp60_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {23, 1, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM dp60_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {24, 1, HSV_PINK}
);
const rgblight_segment_t PROGMEM dp60_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {25, 1, HSV_ORANGE}
);

// rgb light layers
const rgblight_segment_t* const PROGMEM dp60_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    dp60_capslock_layer,
    dp60_scrolllock_layer,
    dp60_numlock_layer,
    dp60_layer1_layer,
    dp60_layer2_layer,
    dp60_layer3_layer,
    dp60_layer4_layer,
    dp60_layer5_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = dp60_rgb_layers;
}

extern rgblight_config_t rgblight_config;
extern void              rgblight_layers_write(void);

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds)
{
    ws2812_setleds(led, RGBLED_NUM-RGB_INDICATOR_NUM);

    uint8_t pinmask = _BV(RGB_INDICATOR_PIN & 0xF);
    _SFR_IO8((RGB_INDICATOR_PIN >> 4) + 1) |= pinmask;
    indicator_sendarray_mask_ind((uint8_t *)(&led[RGBLED_NUM-RGB_INDICATOR_NUM]), RGB_INDICATOR_NUM * sizeof(LED_TYPE), pinmask);
    _delay_us(50);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        rgblight_set_layer_state(0, led_state.caps_lock);
        rgblight_set_layer_state(1, led_state.scroll_lock);
        rgblight_set_layer_state(2, led_state.num_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    rgblight_set_layer_state(3, layer_state_cmp(state, 1));
    rgblight_set_layer_state(4, layer_state_cmp(state, 2));
    rgblight_set_layer_state(5, layer_state_cmp(state, 3));
    rgblight_set_layer_state(6, layer_state_cmp(state, 4));
    rgblight_set_layer_state(7, layer_state_cmp(state, 5));
    return state;
}
