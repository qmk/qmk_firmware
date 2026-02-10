/* Copyright 2024 Vaarai
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

#include "./keymap.h"
#include "./tap_dances.h"

/* Flag to enable/disable trackpad scroll */
bool set_scrolling = false;

/* Variables to store accumulated scroll values */
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT_split_3x6_3( /* Fire (Oxey) : https://bit.ly/layout-doc-v2 */
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_P,    KC_L,    KC_D,    KC_G,    KC_V,                         KC_Q,    KC_F,    KC_O,    KC_U, KC_COMM, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_N,    KC_R,    KC_T,    KC_S,    KC_Y,                         KC_J,    KC_H,    KC_A,    KC_E,    KC_I, KC_LALT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_X,    KC_K,    KC_C,    KC_W,    KC_Z,                         KC_B,    KC_M, KC_QUOT, KC_SCLN,  KC_DOT, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        TD(TD_SFT_CAPSW), TD(TD_NAV_ACCENT), KC_SPC,   KC_ENT, TD(TD_NUM_ACCENT), TD(TD_SFT_CAPSW)
                                      //`--------------------------'  `--------------------------'
  ),

    [_NAV] = LAYOUT_split_3x6_3(
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, G(KC_L), XXXXXXX, CK_SCRL, C(KC_A), XXXXXXX,                      MS_BTN1, MS_BTN2, MS_BTN3, XXXXXXX, XXXXXXX,  KC_DEL,
  //|--------+--------+ GUI V  +--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, C(KC_X), G(KC_V), C(KC_V), C(KC_C), C(KC_Z),                      MS_WHLU, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, 
  //|ALT LEFT+--------+ ALT SFT+scrnshot+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   A(KC_LEFT),C(KC_S),S(KC_LALT), CK_SSHT,C(KC_F), C(KC_Y),                      MS_WHLD, KC_HOME, CK_SELL, CK_SELR,  KC_END, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______, _______,  _______,MO(_ADJUST),_______
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUM] = LAYOUT_split_3x6_3(
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+-- / ---+-- { ---+-- ( ---+-- [ ---+-- - ---|                    |--- _ --+--- ] --+-- ) ---+-- } ---+-- \ ---+--------|
      _______, KC_SLSH, KC_LCBR, KC_LPRN, KC_LBRC, KC_MINS,                      KC_UNDS, KC_RBRC, KC_RPRN, KC_RCBR, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX,  KC_GRV, KC_QUES,  KC_EQL, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______,MO(_ADJUST),_______,    _______, _______, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3(
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_TOGG, RM_HUEU, RM_VALU, CK_DPII, XXXXXXX,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------|--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_NEXT, RM_HUED, RM_VALD, CK_DPID, XXXXXXX,                      TO(_G0), TO(_G1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  /* Generic game */
    [_G0] = LAYOUT_split_3x6_3(
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_SPC,  KC_SPC, XXXXXXX,    XXXXXXX, TG(_G0), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  /* Warframe */
    [_G1] = LAYOUT_split_3x6_3(
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,  KC_ESC,    KC_Q,    KC_W,    KC_1,    KC_2,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_F, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_3,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, KC_LCTL,    KC_M,    KC_Y,    KC_X,    KC_4,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_SPC,CK_RKJMP,    KC_5,    XXXXXXX, TG(_G1), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_RKJMP: /* Warframe rocket jump */
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_C));
            } else {
                SEND_STRING(SS_DOWN(X_SPC) SS_DELAY(50) SS_UP(X_C) SS_DELAY(50) SS_UP(X_SPC));
            }
            return false;
        case CK_DPII: /* Increase trackpad DPI */
            if (record->event.pressed) {
                pointing_device_set_cpi(pointing_device_get_cpi()+100);
            }
            return false;
        case CK_DPID: /* Decrease trackpad DPI */
            if (record->event.pressed) {
                pointing_device_set_cpi(pointing_device_get_cpi()-100);
            }
            return false;
        case CK_SCRL: /* Toggle set_scrolling when CK_SCRL key is pressed or released */
            set_scrolling = record->event.pressed;
            return false;
    }
    /* Accented letters */
    if (accent_state != ACCENT_NONE && record->event.pressed)
    {
        switch (keycode) {
            case KC_A:
                SEND_STRING(SS_ACCENT_A_GRAVE);
                break;  
            case KC_C:
                SEND_STRING(SS_ACCENT_C_CEDIL);
                break;
            case KC_E:
                switch (accent_state) {
                    case ACCENT_LEFT:
                        SEND_STRING(SS_ACCENT_E_ACUTE); break;
                    case ACCENT_RIGHT:
                        SEND_STRING(SS_ACCENT_E_GRAVE); break;
                    case ACCENT_NONE:
                        break;
                }
                break;
            case KC_O:
                SEND_STRING(SS_ACCENT_O_CIRCU);
                break;
            case KC_U:
                SEND_STRING(SS_ACCENT_U_GRAVE);
                break;
        }
        accent_state = ACCENT_NONE;
        return false;
    }
    return true;
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_clear();
    oled_set_cursor(0, 2);
    if (jump_to_bootloader) {
        oled_write_P(PSTR("FLASH"), false);
    } else {
        oled_write_P(PSTR("RESET"), false);
    }
    oled_render_dirty(true);
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    /* Print cornia logo */
    cornia_render_logo();

    /* Print layer status */
    oled_set_cursor(0, 7);
    switch (get_highest_layer(layer_state)) {
        case _ALPHA:
            oled_write_ln("ALPHA", 0);
            break;
        case _NAV:
            oled_write_ln("NAV", 0);
            break;
        case _NUM:
            oled_write_ln("NUM", 0);
            break;
        case _ADJUST:
            oled_write_ln("ADJUS", 0);
            break;
        case _G0:
            oled_write_ln("GAME0", 0);
            break;
        case _G1:
            oled_write_ln("GAME1", 0);
            break;
    }
    return false;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    /* Check if drag scrolling is active */
    if (set_scrolling) {
        /* Calculate and accumulate scroll values based on mouse movement and divisors */
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        /* Assign integer parts of accumulated scroll values to the mouse report */
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        /* Update accumulated scroll values by subtracting the integer parts */
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        /* Clear the X and Y values of the mouse report */
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}