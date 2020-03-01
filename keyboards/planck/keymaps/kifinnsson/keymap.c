/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

bool     is_lgui_active = false;
uint16_t lgui_timer     = 0;

extern keymap_config_t keymap_config;

enum planck_layers { _COLEMAK, _LOWER, _RAISE, _EXTEND, _MACRO, _ADJUST };

enum planck_keycodes { COLEMAK = SAFE_RANGE, KI_BSPC, KI_COMM, KI_DOT, KI_ESC, KI_QUOT, KI_SCLN, KI_SLSH, KI_TAB, KI_A, KI_B, KI_C, KI_D, KI_E, KI_F, KI_G, KI_H, KI_I, KI_J, KI_K, KI_L, KI_M, KI_N, KI_O, KI_P, KI_Q, KI_R, KI_S, KI_T, KI_U, KI_V, KI_W, KI_X, KI_Y, KI_Z, KI_WLFT, KI_WRGT, KI_WUP, KI_WDN };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define MACROS MO(_MACRO)
#define EXTEND MO(_EXTEND)
#define SPC_LOW LT(_LOWER, KC_SPC)
#define SPC_RAI LT(_RAISE, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Colemak
     * ,------------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   F  |   P  |   G   |   J   |   L  |   U  |   Y  |   ;  | Bksp |
     * |------+------+------+------+------+-------+-------+------+------+------+------+------|
     * | Esc  |   A  |   R  |   S  |   T  |   D   |   H   |   N  |   E  |   I  |   O  |  "   |
     * |------+------+------+------+------+-------+-------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B   |   K   |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+-------+-------+------+------+------+------+------|
     * | Brite| Ctrl | Alt  | GUI  |Lower |SPC_LOW|SPC_RAI|Raise | Left | Down |  Up  |Right |
     * `-------------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,  KC_G,    KC_J,    KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        EXTEND,  KC_A,    KC_R,    KC_S,    KC_T,  KC_D,    KC_H,    KC_N,  KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,    KC_K,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        MACROS,  KC_LCTL, KC_LALT, KC_LGUI, LOWER, SPC_LOW, SPC_RAI, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
        ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |XXXXXX|XXXXXX| Home | End  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_HOME, KC_END,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
        ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |XXXXXX|XXXXXX|Pg Up |Pg Dn |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
        ),

    /* Extend
     * ,-----------------------------------------------------------------------------------.
     * |      | Esc  | WH_U | WBAK | WFWD | MS_U | PgUp | Home |  Up  | End  | Del  | Esc  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | Alt  | WH_D |Shift | Ctrl | MS_D | PgDn | Left | Down |Right | Bksp | Menu |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | WH_L | Undo | Cut  | Copy |Paste |MS_B_1|MS_B_2|MS_B_3| MS_L | MS_R | WH_R |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_EXTEND] = LAYOUT_planck_grid(
        _______, KC_ESC,  KC_WH_U, KC_WBAK, KC_WFWD, KC_MS_U, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_ESC,
        _______, KC_LALT, KC_WH_D, KC_LSFT, KC_LCTL, KC_MS_D, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_MENU,
        KC_WH_L, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_BTN1, KC_BTN2, KC_BTN3, KC_MS_L, KC_MS_R, KC_WH_R, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

    /* Macros
     * ,--------------------------------------------------------------------------------------.
     * |KI_TAB| KI_Q | KI_W | KI_F | KI_P | KI_G | KI_J | KI_L | KI_U  | KI_Y |KI_SCLN|KI_BSPC|
     * |------+------+------+------+------+------+------+------+-------+------+-------+-------|
     * |KI_ESC| KI_A | KI_R | KI_S | KI_T | KI_D | KI_H | KI_N | KI_E  | KI_I | KI_O  |KI_QUOT|
     * |------+------+------+------+------+------+------+------+-------+------+-------+-------|
     * |      | KI_Z | KI_X | KI_C | KI_V | KI_B | KI_K | KI_M |KI_COMM|KI_DOT|KI_SLSH|       |
     * |------+------+------+------+------+------+------+------+-------+------+-------+-------|
     * |      |      |      |      |      |      |      |      |KI_WLFT|KI_WDN|KI_WUP |KI_WGRT|
     * `--------------------------------------------------------------------------------------'
     */
    [_MACRO] = LAYOUT_planck_grid(
        KI_TAB,  KI_Q,    KI_W,    KI_F,    KI_P,    KI_G,    KI_J,    KI_L,    KI_U,    KI_Y,   KI_SCLN, KI_BSPC,
        KI_ESC,  KI_A,    KI_R,    KI_S,    KI_T,    KI_D,    KI_H,    KI_N,    KI_E,    KI_I,   KI_O,    KI_QUOT,
        _______, KI_Z,    KI_X,    KI_C,    KI_V,    KI_B,    KI_K,    KI_M,    KI_COMM, KI_DOT, KI_SLSH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KI_WLFT, KI_WDN, KI_WUP,  KI_WRGT
        ),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |      | Reset| Debug|      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |AGnorm|AGswap|      |Colemk|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |TermOn|TrmOff|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______,  _______, _______, _______,
        _______, _______, _______, _______, _______, AG_NORM, AG_SWAP, _______, COLEMAK,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, TERM_ON, TERM_OFF, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
        )
    };

uint32_t layer_state_set_user(uint32_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //
        // Layout Macros
        //
        // Enable Colemak layout
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;  // Skip all further processing of this key
            break;
        //
        // Non-Alpha Macros
        //
        // 'Backspace' Macro
        case KI_BSPC:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Backspace");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Comma' Macro
        case KI_COMM:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Comma");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Dot' Macro
        case KI_DOT:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Dot");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Escape' Macro
        case KI_ESC:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Escape");
            } else {
            }
        // 'Quote' Macro
        case KI_QUOT:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Quote");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Semicolon' Macro
        case KI_SCLN:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Semicolon");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Slash' Macro
        case KI_SLSH:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Slash");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Tab' Macro
        case KI_TAB:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Tab");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        //
        // Alpha Macros
        //
        // 'A' Macro
        case KI_A:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED A");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'B' Macro
        case KI_B:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED B");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'C' Macro
        case KI_C:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED C");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'D' Macro
        case KI_D:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED D");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'E' Macro
        case KI_E:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED E");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'F' Macro
        case KI_F:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED F");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'G' Macro
        case KI_G:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED G");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'H' Macro
        case KI_H:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED H");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'I' Macro
        case KI_I:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED I");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'J' Macro
        case KI_J:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED J");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'K' Macro
        case KI_K:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED K");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'L' Macro
        case KI_L:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED L");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'M' Macro
        case KI_M:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED M");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'N' Macro
        case KI_N:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED N");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'O' Macro
        case KI_O:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED O");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'P' Macro
        case KI_P:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED P");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Q' Macro
        case KI_Q:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Q");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'R' Macro
        case KI_R:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED R");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'S' Macro
        case KI_S:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED S");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'T' Macro
        case KI_T:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED T");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'U' Macro
        case KI_U:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED U");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'V' Macro
        case KI_V:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED V");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'W' Macro
        case KI_W:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED W");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'X' Macro
        case KI_X:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED X");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Y' Macro
        case KI_Y:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Y");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // 'Z' Macro
        case KI_Z:
            if (record->event.pressed) {
                // Reserved for future use
                SEND_STRING("RESERVED Z");
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        //
        // Arrow key macros
        //
        // Windows Win+Left tap to move window without resetting KC_LGUI
        // Additional code is in matrix_scan_user()
        case KI_WLFT:
            if (record->event.pressed) {
                if (!is_lgui_active) {
                    is_lgui_active = true;
                    register_code(KC_LGUI);
                }
                lgui_timer = timer_read();
                tap_code(KC_LEFT);
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // Windows Win+Right tap to move window without resetting KC_LGUI
        // Additional code is in matrix_scan_user()
        case KI_WRGT:
            if (record->event.pressed) {
                if (!is_lgui_active) {
                    is_lgui_active = true;
                    register_code(KC_LGUI);
                }
                lgui_timer = timer_read();
                tap_code(KC_RIGHT);
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // Windows Win+Up tap to move window without resetting KC_LGUI
        // Additional code is in matrix_scan_user()
        case KI_WUP:
            if (record->event.pressed) {
                if (!is_lgui_active) {
                    is_lgui_active = true;
                    register_code(KC_LGUI);
                }
                lgui_timer = timer_read();
                tap_code(KC_UP);
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        // Windows Win+Down tap to move window without resetting KC_LGUI
        // Additional code is in matrix_scan_user()
        case KI_WDN:
            if (record->event.pressed) {
                if (!is_lgui_active) {
                    is_lgui_active = true;
                    register_code(KC_LGUI);
                }
                lgui_timer = timer_read();
                tap_code(KC_DOWN);
            } else {
            }
            return false;  // Skip all further processing of this key
            break;
        default:
            return true;  // Process all other keycodes normally
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    // Check if KC_LGUI is active in KI_WLFT, KI_WRGT, KI_WUP
    if (is_lgui_active) {
        if (timer_elapsed(lgui_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_lgui_active = false;
        }
    }
}
