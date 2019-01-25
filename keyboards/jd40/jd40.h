#ifndef JD40_H
#define JD40_H

#include "quantum.h"
#include "led.h"

/* GH60 LEDs
 *   GPIO pads
 *   0 F7 WASD LEDs
 *   1 F6 ESC LED
 *   2 F5 FN LED
 *   3 F4 POKER Arrow LEDs
 *   B2 Capslock LED
 *   B0 not connected
 */

 /*
inline void gh60_caps_led_on(void)      { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void gh60_poker_leds_on(void)    { DDRF |=  (1<<4); PORTF &= ~(1<<4); }
inline void gh60_fn_led_on(void)    	{ DDRF |=  (1<<5); PORTF &= ~(1<<5); }
inline void gh60_esc_led_on(void)    	{ DDRF |=  (1<<6); PORTF &= ~(1<<6); }
inline void gh60_wasd_leds_on(void)    	{ DDRF |=  (1<<7); PORTF &= ~(1<<7); }

inline void gh60_caps_led_off(void)     { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }
inline void gh60_poker_leds_off(void)   { DDRF &= ~(1<<4); PORTF &= ~(1<<4); }
inline void gh60_fn_led_off(void)   	{ DDRF &= ~(1<<5); PORTF &= ~(1<<5); }
inline void gh60_esc_led_off(void)   	{ DDRF &= ~(1<<6); PORTF &= ~(1<<6); }
inline void gh60_wasd_leds_off(void)   	{ DDRF &= ~(1<<7); PORTF &= ~(1<<7); }
*/

/* JD40 MKII keymap definition macro
 */
#define LAYOUT_kc( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, \
	K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, \
	K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, \
	K35, K36, K37, K38, K39, K40, K41, K42, K43, K44 \
) { \
    { KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K10, KC_##K11, KC_##K12 }, \
    { KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_NO    }, \
    { KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_NO    }, \
    { KC_##K35, KC_##K36, KC_##K37, KC_##K38, KC_##K39, KC_NO,    KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_NO    }  \
}

#define LAYOUT( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, \
	K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, \
	K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, \
	K35, K36, K37, K38, K39, K40, K41, K42, K43, K44 \
) { \
    { K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12 }, \
    { K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, KC_NO    }, \
    { K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34, KC_NO    }, \
    { K35, K36, K37, K38, K39, KC_NO,    K40, K41, K42, K43, K44, KC_NO    }  \
}

#endif
