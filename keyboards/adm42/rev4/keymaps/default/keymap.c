/* Copyright 2020-2022 Lorenzo Leonini
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

enum custom_layers {
    _QWERTY,
    _COLEMAKDH,
    _SPECIAL,
    _EXTRA,
    _ADM,
    _SETUP,
};

#define LW_GRV LWIN_T(KC_GRV)
#define RW_EQU RWIN_T(KC_EQUAL)
#define RW_BS RWIN_T(KC_BSLS)
#define LC_TAB LCTL_T(KC_TAB)
#define RC_QUT RCTL_T(KC_QUOT)
#define LS_BPC LSFT_T(KC_BSPC)
#define RS_SPC RSFT_T(KC_SPC)
#define LA_BS LALT_T(KC_BSLS)
#define LW_F11 LWIN_T(KC_F11)
#define LC_APP LCTL_T(KC_APP)
#define LA_TOG LALT_T(RGB_TOG)
#define RW_F12 RWIN_T(KC_F12)

#define LLS_ESC LT(_SPECIAL, KC_ESC) 
#define LLS_RALT LT(_SPECIAL, KC_RALT) 
#define LLE_ENT LT(_EXTRA, KC_ENT) 
#define LLA_DEL LT(_ADM, KC_DEL)
#define SETUP MO(_SETUP)

enum custom_keycodes {
    REFLASH = SAFE_RANGE,
    LC_CIRC,
    RC_DLR,
    DF_QWER,
    DF_COLE,
};

// Not a mistake to have KC_LALT (also) on the right, RALT is kept for compose (LLS_RALT)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_adm42_3x12_6(
        LW_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    RW_EQU,
        LC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RC_QUT,
        KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LALT,
                                   LLS_ESC, LS_BPC,  LLA_DEL, LLE_ENT, RS_SPC,  LLS_RALT
    ),
    [_COLEMAKDH] = LAYOUT_adm42_3x12_6(
        LW_GRV,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, RW_EQU,
        LC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    RC_QUT,
        KC_LALT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_LALT,
                                   LLS_ESC, LS_BPC,  LLA_DEL, LLE_ENT, RS_SPC,  LLS_RALT
    ),

    [_SPECIAL] = LAYOUT_adm42_3x12_6(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    RW_BS,
        LC_CIRC, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_EXLM, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_MINS, RC_DLR,
        _______, KC_AMPR, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_UNDS, KC_ASTR, KC_HASH, KC_PERC, KC_TILD, _______,
                                   KC_ESC,  _______, KC_DEL,  KC_ENT,  _______, KC_RALT
    ),
    [_EXTRA] = LAYOUT_adm42_3x12_6(
        LW_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  RW_F12,
        KC_LCTL, KC_PAUS, KC_INS,  KC_VOLD, KC_VOLU, KC_MUTE, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_APP,  KC_RCTL,
        _______, KC_SLEP, KC_PWR,  KC_MSTP, KC_MNXT, KC_MPLY, _______, KC_BRID, KC_BRIU, KC_PSCR, KC_WAKE, _______,
                                   KC_CAPS, _______, _______, _______, _______, KC_CAPS
    ),
    [_ADM] = LAYOUT_adm42_3x12_6(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_M_B, RGB_VAD, RGB_VAI, RGB_SAD, RGB_SAI, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUD, RGB_HUI, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  RGB_M_P, RGB_SPD, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX,
                                   XXXXXXX, XXXXXXX, XXXXXXX, SETUP,   XXXXXXX, XXXXXXX
    ),
    [_SETUP] = LAYOUT_adm42_3x12_6(
        REFLASH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, DF_QWER, DF_COLE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
     case RC_QUT:
        return true;
     default:
        return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
     case LLS_ESC:
     case LLS_RALT:
     case LLE_ENT:
     case LLA_DEL:
        return true;
     default:
        return false;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
     case LLS_ESC:
     case LLS_RALT:
        return true;
     default:
        return false;
    }
}

static uint16_t last_timer = 0;
static int last_key = 0;
bool cleanup_return(uint16_t keycode, keyrecord_t *record, bool value) {
    if (record->event.pressed) {
        last_key = keycode;
        last_timer = timer_read();
    }
    return value;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    switch (keycode) {

     case RC_DLR:
        if (record->event.pressed) {
            register_code(KC_RCTL);
        } else {
            unregister_code(KC_RCTL);
            if (last_key == keycode && timer_elapsed(last_timer) <= TAPPING_TERM) {
                send_string("$");
            }
        }
        return cleanup_return(keycode, record, false);

     case LC_CIRC:
        if (record->event.pressed) {
            register_code(KC_LCTL);
        } else {
            unregister_code(KC_LCTL);
            if (last_key == keycode && timer_elapsed(last_timer) <= TAPPING_TERM) {
                send_string("^");
            }
        }
        return cleanup_return(keycode, record, false);

     case DF_QWER:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
            send_string("QWERTY layout");
        }
        return false;
     case DF_COLE:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAKDH);
            send_string("COLEMAKDH layout");
        }
        return false;

     case REFLASH:
        eeconfig_init();
        eeconfig_update_rgb_matrix_default();
        writePinLow(QMK_LED);
        reset_keyboard();
        return false;

     default:
        return cleanup_return(keycode, record, true);
    }
}

void keyboard_pre_init_kb(void) {
    setPinOutput(QMK_LED);
    writePinHigh(QMK_LED);
}

void keyboard_post_init_kb(void) {
    debug_enable = true;
    debug_matrix = false;
    debug_keyboard = false;
    writePinHigh(QMK_LED);
}

void suspend_power_down_kb(void) {
    writePinLow(QMK_LED);
}

void suspend_wakeup_init_kb(void) {
  writePinHigh(QMK_LED);
}
