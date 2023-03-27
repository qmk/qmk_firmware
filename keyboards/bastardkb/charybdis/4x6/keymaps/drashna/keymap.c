/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include "drashna.h"

// clang-format off
#define LAYOUT_charybdis_4x6_wrapper(...) LAYOUT_charybdis_4x6(__VA_ARGS__)
#define LAYOUT_charybdis_4x6_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_charybdis_4x6_wrapper( \
     KC_ESC,  ________________NUMBER_LEFT________________,            ________________NUMBER_RIGHT_______________, UC_CLUE, \
     SH_TT,   K01,    K02,      K03,     K04,     K05,                K06,     K07,     K08,     K09,     K0A,     SH_TT, \
     LALT_T(KC_TAB), K11, K12,  K13,     K14,     K15,                K16,     K17,     K18,     K19,     K1A,     RALT_T(K1B), \
     OS_LSFT,CTL_T(K21),ALT_T(K22),GUI_T(K23),K24,K25,                K26,K27,RGUI_T(K28),RALT_T(K29),RCTL_T(K2A), OS_RSFT, \
                           SFT_T(KC_GRV), OS_LALT, OS_LGUI,    TT(_MOUSE),  KC_ENT, \
                                           KC_SPC, BK_LWER,     DL_RAIS \
    )

#define LAYOUT_base_wrapper(...)       LAYOUT_charybdis_4x6_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_DEFAULT_LAYER_2] = LAYOUT_base_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),
    [_DEFAULT_LAYER_3] = LAYOUT_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DEFAULT_LAYER_4] = LAYOUT_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_GAMEPAD] = LAYOUT_charybdis_4x6(
        KC_ESC,  KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,       _______, _______, _______, _______, _______, _______,
        KC_F1,   KC_K,    KC_Q,    KC_W,    KC_E,    KC_R,       _______, _______, _______, _______, _______, _______,
        KC_TAB,  KC_G,    KC_A,    KC_S,    KC_D,    KC_F,       _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_H,       _______, _______, _______, _______, _______, _______,
                                   KC_V,    _______, _______,    _______, TG_GAME,
                                           KC_SPC, KC_H,          _______
    ),
    [_DIABLO] = LAYOUT_charybdis_4x6(
        KC_ESC,  KC_V,    KC_D,    KC_LALT, KC_NO,   KC_NO,      KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
        KC_TAB,  KC_S,    KC_I,    KC_F,    KC_M,    KC_T,       _______, _______, _______, _______, _______, _______,
        KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,       _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, KC_Z,       _______, _______, _______, _______, _______, _______,
                                   KC_G,    _______, _______,    TO(_DIABLOII), TG_DBLO,
                                           KC_LSFT, KC_LCTL,      _______
    ),
    [_DIABLOII] = LAYOUT_charybdis_4x6(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_GRV,     _______, _______, _______, _______, _______, _______,
        KC_TAB,  KC_A,    KC_T,    KC_Q,    KC_I,    KC_M,       _______, _______, _______, _______, _______, _______,
        KC_S,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,     _______, _______, _______, _______, _______, _______,
                           KC_DIABLO_CLEAR, _______, _______,    _______, TG(_DIABLOII),
                               SFT_T(KC_SPACE),  ALT_T(KC_Q),      _______
    ),
    [_MOUSE] = LAYOUT_charybdis_4x6(
        _______, _______, _______, _______, _______, _______,   _______, DPI_RMOD,DPI_MOD, S_D_RMOD,S_D_MOD, _______,
        _______, _______, _______, _______, _______, _______,   KC_WH_U, _______, _______, _______, _______, DRGSCRL,
        _______, _______, _______, _______, _______, _______,   KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN6, SNIPING,
        _______, _______, _______, _______, _______, _______,   KC_BTN7, KC_BTN4, KC_BTN5, KC_BTN8, _______, _______,
                                   _______, _______, _______,   _______, _______,
                                           _______, _______,     _______
    ),

    [_LOWER] = LAYOUT_charybdis_4x6_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,    _________________FUNC_RIGHT________________, KC_F11,
        _______, _________________LOWER_L1__________________,    _________________LOWER_R1__________________, _______,
        _______, _________________LOWER_L2__________________,    _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________,    _________________LOWER_R3__________________, _______,
                                   _______, _______, _______,    _______, _______,
                                           _______, _______,      _______
    ),

    [_RAISE] = LAYOUT_charybdis_4x6_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,    _________________FUNC_RIGHT________________, KC_F11,
        KC_GRV,  _________________RAISE_L1__________________,    _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________,    _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________,    _________________RAISE_R3__________________, _______,
                                   _______, _______, _______,    _______, _______,
                                           _______, _______,      _______
    ),

    [_ADJUST] = LAYOUT_charybdis_4x6_wrapper(
        QK_MAKE, KC_WIDE,KC_AUSSIE,KC_SCRIPT,KC_ZALGO,KC_SUPER, KC_NOMODE,KC_COMIC,KC_REGIONAL,TG_GAME,TG_DBLO, QK_BOOT,
        VRSN,    _________________ADJUST_L1_________________,    _________________ADJUST_R1_________________, EE_CLR,
        KEYLOCK, _________________ADJUST_L2_________________,    _________________ADJUST_R2_________________, TG_MODS,
        UC_NEXT, _________________ADJUST_L3_________________,    _________________ADJUST_R3_________________, KC_MPLY,
                                   QK_RBT, AUTO_CTN, _______,    _______, KC_NUKE,
                                           _______, _______,      _______
    )
};
// clang-format on

void keyboard_post_init_keymap(void) {
#ifdef RGB_MATRIX_ENABLE
    g_led_config.flags[53] = g_led_config.flags[54] = g_led_config.flags[55] = g_led_config.flags[0] = g_led_config.flags[1] = g_led_config.flags[2] = g_led_config.flags[3] = g_led_config.flags[29] = g_led_config.flags[30] = g_led_config.flags[31] = g_led_config.flags[32] = LED_FLAG_MODIFIER;
#endif
}

#if defined(KEYBOARD_bastardkb_charybdis_4x6_blackpill)
void keyboard_pre_init_keymap(void) {
    setPinInputHigh(A0);
}

void housekeeping_task_keymap(void) {
    if (!readPin(A0)) {
        reset_keyboard();
    }
}
#endif

#ifdef USB_VBUS_PIN
bool usb_vbus_state(void) {
    setPinInputLow(USB_VBUS_PIN);
    wait_us(5);
    return readPin(USB_VBUS_PIN);
}
#endif

#if defined(KEYBOARD_bastardkb_charybdis_4x6_blackpill)
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}
#endif

#ifdef SWAP_HANDS_ENABLE
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
    {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}},
    {{2, 9}, {4, 9}, {5, 9}, {1, 9}, {0, 9}, {3, 9}},
    /* Right hand, matrix positions */
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}},
    {{0, 4}, {3, 4}, {2, 4}, {5, 4}, {4, 4}, {2, 4}}
};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1, 0};
#    endif
#endif
