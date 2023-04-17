#include "venc0r.h"

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_ALPHA] = LAYOUT_wrapper(
        _______________S_COLEMAK_L0________________, _______________S_COLEMAK_R0________________,
        _______________S_COLEMAK_L1________________, _______________S_COLEMAK_R1________________,
        _______________S_COLEMAK_L2________________, _______________S_COLEMAK_R2________________,
        _______________S_COLEMAK_L3________________, _______________S_COLEMAK_R3________________,
        __S_THUMB_L____, __S_THUMB_R____
    ),

    [_LOWER] = LAYOUT_wrapper(
        _______________S_SYMBOL_L0_________________, _______________S_SYMBOL_R0_________________,
        _______________S_SYMBOL_L1_________________, _______________S_SYMBOL_R1_________________,
        _______________S_SYMBOL_L2_________________, _______________S_SYMBOL_R2_________________,
        _______________S_SYMBOL_L3_________________, _______________S_SYMBOL_R3_________________,
        __S_THUMB_N____, __S_THUMB_N____
    ),

    [_RAISE] = LAYOUT_wrapper(
        _______________S_NAV_L0____________________, _______________S_NAV_R0____________________,
        _______________S_NAV_L1____________________, _______________S_NAV_R1____________________,
        _______________S_NAV_L2____________________, _______________S_NAV_R2____________________,
        _______________S_NAV_L3____________________, _______________S_NAV_R3____________________,
        __S_THUMB_N____, __S_THUMB_N____
    ),

    [_ADJUST] = LAYOUT_wrapper(
        _______________S_ADJUST_L0_________________, _______________S_ADJUST_R0_________________,
        _______________S_ADJUST_L1_________________, _______________S_ADJUST_R1_________________,
        _______________S_ADJUST_L2_________________, _______________S_ADJUST_R2_________________,
        _______________S_ADJUST_L3_________________, _______________S_ADJUST_R3_________________,
        __S_THUMB_N____, __S_THUMB_N____
    ),

    [_GAME] = LAYOUT_wrapper(
        _______________S_GAME_L0___________________, _______________S_GAME_R0___________________,
        _______________S_GAME_L1___________________, _______________S_GAME_R1___________________,
        _______________S_GAME_L2___________________, _______________S_GAME_R2___________________,
        _______________S_GAME_L3___________________, _______________S_GAME_R3___________________,
        __S_G_THUMB_L__, __S_G_THUMB_R__
    ),
};

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
#ifdef RGB_MATRIX_ENABLE
    if (get_highest_layer(layer_state|default_layer_state) > 0) {
        if (index == 0) {
            if (clockwise) {
                rgb_matrix_increase_sat();
            } else {
                rgb_matrix_decrease_sat();
            }
        } else if (index == 1) {
            if (clockwise) {
                rgb_matrix_increase_hue();
            } else {
                rgb_matrix_decrease_hue();
            }
        }
    } else {  /* Layer 0 */
        if (index == 0) {
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code_delay(KC_VOLU, 10);
            } else {
                tap_code_delay(KC_VOLD, 10);
            }
        }
    }
#else
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
#endif

    return false;
}

#endif
