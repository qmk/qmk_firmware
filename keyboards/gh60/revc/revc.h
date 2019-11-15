#pragma once

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
inline void gh60_caps_led_on(void)      { setPinOutput(B2); writePinLow(B2); }
inline void gh60_poker_leds_on(void)    { setPinOutput(F4); writePinLow(F4); }
inline void gh60_fn_led_on(void)        { setPinOutput(F5); writePinLow(F5); }
inline void gh60_esc_led_on(void)       { setPinOutput(F6); writePinLow(F6); }
inline void gh60_wasd_leds_on(void)     { setPinOutput(F7); writePinLow(F7); }

inline void gh60_caps_led_off(void)     { setPinInput(B2); writePinLow(B2); }
inline void gh60_poker_leds_off(void)   { setPinInput(F4); writePinLow(F4); }
inline void gh60_fn_led_off(void)       { setPinInput(F5); writePinLow(F5); }
inline void gh60_esc_led_off(void)      { setPinInput(F6); writePinLow(F6); }
inline void gh60_wasd_leds_off(void)    { setPinInput(F7); writePinLow(F7); }

/* GH60 keymap definition macro
 * K2C, K31 and  K3C are extra keys for ISO
 */
#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K49, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K3C, \
    K40, K41, K42,           K45,                     K4A, K4B, K4C, K4D  \
) { \
    { K00, K01, K02, K03,   K04,   K05, K06,   K07,   K08,   K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13,   K14,   K15, K16,   K17,   K18,   K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23,   K24,   K25, K26,   K27,   K28,   K29, K2A, K2B, K2C, K2D }, \
    { K30, K31, K32, K33,   K34,   K35, K36,   K37,   K38,   K39, K3A, K3B, K3C, K3D }, \
    { K40, K41, K42, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, K49, K4A, K4B, K4C, K4D }  \
}

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
    K40, K41, K42,           K45,                K49, K4A, K4B, K4C, K4D  \
) { \
    { K00, K01, K02, K03,   K04,   K05, K06,   K07,   K08,   K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13,   K14,   K15, K16,   K17,   K18,   K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23,   K24,   K25, K26,   K27,   K28,   K29, K2A, K2B, K2C, K2D }, \
    { K30, K31, K32, K33,   K34,   K35, K36,   K37,   K38,   K39, K3A, K3B, K3C, K3D }, \
    { K40, K41, K42, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, K49, K4A, K4B, K4C, K4D }  \
}

/* ANSI variant. No extra keys for ISO */
#define LAYOUT_60_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
    K40, K41, K42,           K45,                     K4A, K4B, K4C, K4D  \
) { \
    { K00, K01,   K02, K03,   K04,   K05, K06,   K07,   K08,   K09,   K0A, K0B, K0C,   K0D }, \
    { K10, K11,   K12, K13,   K14,   K15, K16,   K17,   K18,   K19,   K1A, K1B, K1C,   K1D }, \
    { K20, K21,   K22, K23,   K24,   K25, K26,   K27,   K28,   K29,   K2A, K2B, KC_NO, K2D }, \
    { K30, KC_NO, K32, K33,   K34,   K35, K36,   K37,   K38,   K39,   K3A, K3B, KC_NO, K3D }, \
    { K40, K41,   K42, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, KC_NO, K4A, K4B, K4C,   K4D }  \
}

/* ISO variant. Remove useless ANSI keys */
#define LAYOUT_60_iso( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,      \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
    K40, K41, K42,           K45,                     K4A, K4B, K4C, K4D  \
) { \
    { K00, K01, K02, K03,   K04,   K05, K06,   K07,   K08,   K09,   K0A, K0B, K0C,   K0D   }, \
    { K10, K11, K12, K13,   K14,   K15, K16,   K17,   K18,   K19,   K1A, K1B, K1C,   KC_NO }, \
    { K20, K21, K22, K23,   K24,   K25, K26,   K27,   K28,   K29,   K2A, K2B, K2C,   K2D   }, \
    { K30, K31, K32, K33,   K34,   K35, K36,   K37,   K38,   K39,   K3A, K3B, KC_NO, K3D   }, \
    { K40, K41, K42, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, KC_NO, K4A, K4B, K4C,   K4D   }  \
}


/* HHKB Variant */
#define LAYOUT_60_ansi_split_bs_rshift( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K49,\
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3C, \
    K40, K41, K42,           K45,                     K4A, K4B, K4C, K4D  \
) { \
    { K00, K01,   K02, K03,   K04,   K05, K06,   K07,   K08,   K09, K0A, K0B, K0C,   K0D }, \
    { K10, K11,   K12, K13,   K14,   K15, K16,   K17,   K18,   K19, K1A, K1B, K1C,   K1D }, \
    { K20, K21,   K22, K23,   K24,   K25, K26,   K27,   K28,   K29, K2A, K2B, KC_NO, K2D }, \
    { K30, KC_NO, K32, K33,   K34,   K35, K36,   K37,   K38,   K39, K3A, K3B, K3C,   K3D }, \
    { K40, K41,   K42, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, K49, K4A, K4B, K4C,   K4D }  \
}

/* ANSI with split Right Shift. No extra keys for ISO */
#define LAYOUT_60_ansi_split_rshift( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3C, \
    K40, K41, K42,           K45,                     K4A, K4B, K4C, K4D  \
) { \
    { K00, K01,   K02, K03,   K04,   K05, K06,   K07,   K08,   K09,   K0A, K0B, K0C,   K0D }, \
    { K10, K11,   K12, K13,   K14,   K15, K16,   K17,   K18,   K19,   K1A, K1B, K1C,   K1D }, \
    { K20, K21,   K22, K23,   K24,   K25, K26,   K27,   K28,   K29,   K2A, K2B, KC_NO, K2D }, \
    { K30, KC_NO, K32, K33,   K34,   K35, K36,   K37,   K38,   K39,   K3A, K3B, K3C,   K3D }, \
    { K40, K41,   K42, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, KC_NO, K4A, K4B, K4C,   K4D }  \
}

/* LAYOUT_60_abnt2
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐2d  │
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │1e │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c │  3d  │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬──┴─┬────┤
 * │40  │41  │43  │46                      │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
*/
#define LAYOUT_60_abnt2( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1e, k2d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,      \
    k40, k41,      k43,           k46,                k4a, k4b,      k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   KC_NO, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  k3c,   k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, k4a,  k4b,  KC_NO, k4d,   k4e   }  \
}
