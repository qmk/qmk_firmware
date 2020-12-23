/* Copyright 2020 Gaëtan Ark <gaetan.ark@gmail.com>
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
#include "keymap_bepo.h"
#include "base.h"

/* See
 *
 * https://github.com/manna-harbour/qmk_firmware/blob/miryoku/users/manna-harbour_miryoku/manna-harbour_miryoku.h
 */

/* Macos commands (cancel, paste…) */
#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)

/* Miryoku specific keys */
#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

// Modifiers
#define B00 KC_NO
#define B01 KC_NO
#define B02 LT(MEDR, KC_ESC)
#define B03 LT(NAVR, KC_SPC)
#define B04 LT(MOUR, KC_TAB)
#define B05 LT(NSSL, KC_ENT)
#define B06 LT(NSL, KC_BSPC)
#define B07 LT(FUNL, KC_DEL)
#define B08 KC_NO
#define B09 KC_NO

enum layers { BASE, MBO, MEDR, NAVR, MOUR, NSSL, NSL, FUNL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
      B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
      ),
  [NAVR] = LAYOUT(
      KC_NO, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                       U_RDO,    U_PST,   U_CPY,   U_CUT,   U_UND,   KC_NO,
      KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_SPC,                                     KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS, KC_NO,
      KC_NO, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, KC_NO, KC_NO,        KC_NO,  KC_NO,   KC_HOME,  KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_NO,
                               U_NP,    U_NP,    U_NA, U_NA,  U_NA,         KC_ENT, KC_BSPC, KC_DEL,   U_NP,    U_NP
      ),
  [MOUR] = LAYOUT(
      KC_NO, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    KC_NO,
      KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, U_NU,    KC_NO,
      KC_NO, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, KC_NO, KC_NO,        KC_NO,   KC_NO,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, U_NU,    KC_NO,
                               U_NP,    U_NP,    U_NA, U_NA,  U_NA,         KC_BTN1, KC_BTN3, KC_BTN2, U_NP,    U_NP
     ),
  [MEDR] = LAYOUT(
      KC_NO, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                                        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,
      KC_NO, KC_LGUI, KC_LALT, KC_LGUI, KC_LSFT, U_NA,                                        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, U_NU,    KC_NO,
      KC_NO, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, KC_NO, KC_NO,        KC_NO,   KC_NO,   U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    KC_NO,
                               U_NP,    U_NP,    U_NA, U_NA,  U_NA,         KC_MSTP, KC_MPLY, KC_MUTE, U_NP,    U_NP
      ),
  [MBO] = LAYOUT(
      KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,
      KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,
      KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,
                               U_NP,    U_NP,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_BTN1, KC_BTN3, KC_BTN2, U_NP,    U_NP
      ),
  [FUNL] = LAYOUT(
      KC_NO, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                U_NA,    U_NA,    U_NA,    U_NA,    RESET, KC_NO,
      KC_NO, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK,                                U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
      KC_NO, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_NO,  KC_NO,   KC_NO, KC_NO, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA, KC_NO,
                               U_NP,    U_NP,    KC_APP,  KC_SPC, KC_TAB,  U_NA,  U_NA,  U_NA,    U_NP,    U_NP
      ),
  [NSL] = LAYOUT(
      KC_NO, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                                 U_NA,    U_NA,    U_NA,    U_NA,    RESET, KC_NO,
      KC_NO, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                                  U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
      KC_NO, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, KC_NO,   KC_NO,   KC_NO, KC_NO, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA, KC_NO,
                               U_NP,    U_NP,    KC_DOT,  KC_0,    KC_MINS, U_NA,  U_NA,  U_NA,    U_NP,    U_NP
      ),
  [NSSL] = LAYOUT(
      KC_NO, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                                 U_NA,    U_NA,    U_NA,    U_NA,    RESET, KC_NO,
      KC_NO, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                                 U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,
      KC_NO, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, KC_NO,   KC_NO,  KC_NO, KC_NO, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA, KC_NO,
                      U_NP,    U_NP,    KC_LPRN, KC_RPRN, KC_UNDS, U_NA,   U_NA,    U_NA,    U_NP,    U_NP
      )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, BASE, MBO, MOUR);
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}


static void render_status(void) {
    // QMK Logo and version information
    //oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_P(PSTR("abcdefghijklmnopqrstuvwxyz#123456Z789ABCDEFGHIJKLMNOPQRSTUVWYXZ\n"), false);
            break;
        case MBO:
            oled_write_P(PSTR("NumSym\n"), false);
            break;
        case MEDR:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case NAVR:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case MOUR:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case NSSL:
            oled_write_P(PSTR("Shifted symbols\n"), false);
            break;
        case NSL:
            oled_write_P(PSTR("Num & Symb\n"), false);
            break;
        case FUNL:
            oled_write_P(PSTR("Func & Sys\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif
