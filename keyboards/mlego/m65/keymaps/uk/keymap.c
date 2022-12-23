/*
Copyright 2021-2022 Alin M Elena <alinm.elena@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_uk.h"

enum layer_names {
    _QW = 0,
    _LWR,
    _RSE,
    _ADJ
};

#ifdef CONSOLE_ENABLE

#include "print.h"

#endif

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_lwr_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_CYAN});
const rgblight_segment_t PROGMEM my_rse_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_RED});
const rgblight_segment_t PROGMEM my_adj_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_GREEN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_qwerty_layer, my_lwr_layer, my_rse_layer, my_adj_layer);
#endif

const uint32_t PROGMEM unicode_map[] = {
    [la] = 0x03B1,  // å
    [lA] = 0x0391,  // Å
    [lb] = 0x03B2,  // β
    [lB] = 0x0392,  // Β
    [lc] = 0x03C7,  //
    [lC] = 0x0307,  //
    [ld] = 0x03B4,   [lD] = 0x2202, [le] = 0x03B5, [lE] = 0x2107,
    [lf]  = 0x03C6,   //
    [lF]  = 0x03C8,   //
    [lg]  = 0x03B3,   //
    [lG]  = 0x0393,   //
    [lh]  = 0x210F,   //
    [lH]  = 0x1D4D7,  //
    [li]  = 0x222B,   //
    [lI]  = 0x222E,   //
    [lj]  = 0x2208,   //
    [lJ]  = 0x2209,   //
    [lk]  = 0x03F0,   //
    [lK]  = 0x2206,   //
    [ll]  = 0x03BB,   //
    [lL]  = 0x039B,   //
    [lm]  = 0x03BC,   //
    [lM]  = 0x2218,   //
    [ln]  = 0x03B7,   //
    [lN]  = 0x222A,   //
    [lo]  = 0x221E,   //
    [lO]  = 0x2297,   //
    [lp]  = 0x03C0,   //
    [lP]  = 0x220F,   //
    [lq]  = 0x03C3,   //
    [lQ]  = 0x03D5,   //
    [lr]  = 0x03C1,   //
    [lR]  = 0x2207,   //
    [ls]  = 0x2211,   //
    [lS]  = 0x2A0B,   //
    [lt]  = 0x03D1,   //
    [lT]  = 0x03B8,   //
    [lu]  = 0x03C4,   //
    [lU]  = 0x2102,   //
    [lv]  = 0x03BD,   //
    [lV]  = 0x039D,   //
    [lw]  = 0x03C9,   //
    [lW]  = 0x03A9,   //
    [lx]  = 0x03BE,   //
    [lX]  = 0x039E,   //
    [ly]  = 0x211d,
    [lY]  = 0x2124,   //
    [lz]  = 0x03B6,   //
    [lZ]  = 0x2221,   //
    [lZ]  = 0x2221,   //
    [lc1] = 0x224A,   //
    [lC1] = 0x2248,   //
    [lp1] = 0x00B1,   //
    [lP1] = 0x2213,   //
    [lq1] = 0x00D7,   //
    [lQ1] = 0x22C5,   //
    [ll1] = 0x1D53C,  //
    [lL1] = 0x212b,   //
    [lk1] = 0x221D,   //
    [lK1] = 0x2112,   //
    [rc]  = 0x00E7,   // ç
    [rC]  = 0x00C7,   // Ç
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QW] = LAYOUT_ortho_5x13(
       KC_ESC, UK_1   , UK_2    , UK_3   , UK_4    , UK_5  , UK_6  , UK_7  , UK_8   , UK_9   , UK_0   , UK_MINS, KC_BSPC ,
       KC_TAB, UK_Q   , UK_W    , UK_E   , UK_R    , UK_T  , UK_Y  , UK_U  , UK_I   , UK_O   , UK_P   , UK_LBRC, UK_RBRC ,
      UK_HASH, UK_A   , UK_S    , UK_D   , UK_F    , UK_G  , UK_H  , UK_J  , UK_K   , UK_L   , UK_SCLN, UK_QUOT, KC_ENT  ,
      KC_LSPO, UK_BSLS, UK_Z    , UK_X   , UK_C    , UK_V  , UK_B  , UK_N  , UK_M   , UK_COMM, UK_DOT , KC_UP  , UK_SLSH ,
      KC_LCTL, KC_LGUI, TT(_LWR), KC_LALT, TT(_RSE), KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_RSPC, KC_LEFT, KC_DOWN, KC_RGHT),

  [_LWR] = LAYOUT_ortho_5x13(
     KC_GRV , KC_MUTE, KC_VOLU, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, G(KC_P), KC_SLEP, KC_WAKE, KC_PSCR, KC_DEL , UK_EQL  ,
     KC_BTN3, XP(lq  , lQ)    , XP(lw  , lW)    , XP(le  , lE)    , XP(lr  , lR)    , XP(lt  , lT)    , XP(ly  , lY)     , XP(lu, lU)  , XP(li, lI)   , XP(lo, lO)   , XP(lp , lP)    , _______, _______,
     KC_BTN2, XP(la  , lA)    , XP(ls  , lS)    , XP(ld  , lD)    , XP(lf  , lF)    , XP(lg  , lG)    , XP(lh  , lH)     , XP(lj, lJ)  , XP(lk, lK)   , XP(ll, lL)   , XP(ll1, lL1)   , XP(lk1 , lK1)   , _______,
     _______, KC_BTN1, XP(lz  , lZ)    , XP(lx  , lX)    , XP(lc  , lC)    , XP(lv  , lV)    , XP(lb  , lB)    , XP(ln   , lN)  , XP(lm, lM)  , XP(lc1, lC1) , XP(lp1, lP1)  , KC_MS_U, XP(lq1 , lQ1)   ,
     _______, KC_BTN4, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),


  [_RSE] = LAYOUT_ortho_5x13(
      KC_ESC , KC_F1  , KC_F2  , KC_F3  ,  KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12  ,
      _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
      KC_CAPS, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
      _______, _______, _______, _______,XP(rc,rC), _______, _______, _______, _______, _______, _______, KC_WH_U, _______ ,
      _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R),

  [_ADJ] = LAYOUT_ortho_5x13(
      RGB_MOD, RGB_RMOD, A(KC_F2), _______, _______, _______, _______, _______, _______, _______, _______, _______ , RGB_M_SW,
      RGB_HUI, RGB_HUD , RGB_M_P , _______, RESET  , RGB_M_T, _______, _______, _______, _______, _______, _______ , RGB_M_SN,
      RGB_SAI, RGB_SAD , RGB_M_B , _______, _______, _______, _______, _______, _______, _______, _______, _______ , RGB_M_K ,
      RGB_VAI, RGB_VAD , RGB_M_R , _______, _______, _______, _______, _______, _______, _______, _______, _______ , RGB_M_X ,
      RGB_TOG, _______ , _______ , _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_TW, RGB_M_G),
};
// clang-format on

// let us assume we start with both layers off
bool toggle_lwr = false;
bool toggle_rse = false;

bool led_update_user(led_t led_state) {
    // Disable the default LED update code, so that lock LEDs could be reused to show layer status.
    return false;
}

void matrix_scan_user(void) {
    led_lwr(toggle_lwr);
    led_rse(toggle_rse);
    led_t led_state = host_keyboard_led_state();
    led_caps(led_state.caps_lock);
    if (layer_state_is(_ADJ)) {
        led_lwr(true);
        led_rse(true);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    switch (keycode) {
        case (TT(_LWR)):
            if (!record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                // This runs before the TT() handler toggles the layer state, so the current layer state is the opposite of the final one after toggle.
                toggle_lwr = !layer_state_is(_LWR);
            }
            return true;
            break;
        case (TT(_RSE)):
            if (record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                toggle_rse = !layer_state_is(_RSE);
            }
            return true;
            break;
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE

    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LWR));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJ));

#endif
    return update_tri_layer_state(state, _LWR, _RSE, _ADJ);
}

#ifdef RGBLIGHT_ENABLE

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
    return state;
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
#ifdef CONSOLE_ENABLE

    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
#endif
}
#endif

#ifdef ENCODER_ENABLE

#    define MEDIA_KEY_DELAY 10

static inline void my_encoders(const uint8_t index, const bool clockwise) {
    if (index == 0) { /* First encoder */
        if (IS_LAYER_ON(_LWR)) {
            if (clockwise) {
                rgblight_decrease_val_noeeprom();
            } else {
                rgblight_increase_val_noeeprom();
            }
        } else if (IS_LAYER_ON(_RSE)) {
            if (clockwise) {
                rgblight_decrease_hue_noeeprom();
            } else {
                rgblight_increase_hue_noeeprom();
            }

        } else {
            if (clockwise) {
                tap_code_delay(KC_VOLD, MEDIA_KEY_DELAY);
            } else {
                tap_code_delay(KC_VOLU, MEDIA_KEY_DELAY);
            }
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    my_encoders(index, clockwise);
    return true;
}
#endif
