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

#include QMK_KEYBOARD_H

enum custom_keycodes {
    // set mouse scroll
    SCROLL = SAFE_RANGE
};

#include "g/keymap_combo.h"




// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────╮
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
      OLM(KC_A),OLI(KC_S),OLR(KC_D),OLY(KC_F),OLO(KC_G),   ORO(KC_H),ORY(KC_J),ORR(KC_K),ORI(KC_L),ORM(KC_SCLN),
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────┤
        OLR(KC_Z), OLI(KC_X),    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  // ╰──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────╯
                           KC_LGUI,   O_TAB,   O_SPC,        O_ENT, KC_BSPC
  //                   ╰────────────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NAV] = LAYOUT(
  // ╭──────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, XXXXXXX,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      OLM(KC_6),OLI(KC_7),OLR(KC_8),OLY(KC_9),OLO(KC_0),   KC_LEFT, KC_DOWN,  KC_UP,  KC_RIGHT, XXXXXXX,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_DOT,        KC_LBRC, KC_RBRC, KC_LABK,   KC_RABK,XXXXXXX,
  // ╰──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                              _______, _______, _______,    _______, KC_DEL
  //                        ╰───────────────────────────╯ ╰──────────────────╯
  ),
  
  [LAYER_SYMBOLS] = LAYOUT(
  // ╭──────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_MINS,  KC_EQL,  KC_ASTR, KC_AMPR,   XXXXXXX,     KC_SLEP, _______, KC_MPLY, KC_VOLU, KC_MUTE,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_QUOT,  KC_CIRC,  KC_PERC,  KC_DLR,   _______,    _______, ORY(KC_MPRV), ORR(KC_MNXT), ORI(KC_VOLD), _______,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_GRV, KC_HASH,   KC_AT, KC_EXLM, KC_BSLS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,QK_BOOT,
  // ╰──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                              _______, _______, _______,    _______, _______
  //                        ╰───────────────────────────╯ ╰──────────────────╯
  ),

  
  [LAYER_NUM] = LAYOUT(
  // ╭────────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,              _______,    KC_7,    KC_8,    KC_9, KC_PPLS,
  // ├────────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      OLM(KC_F6),OLI(KC_F7),OLR(KC_F8),OLY(KC_F9),OLO(KC_F10),   _______, KC_4,KC_5,KC_6,KC_MINS,
  // ├────────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,             KC_0,    KC_1,    KC_2,    KC_3,XXXXXXX,
  // ╰────────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                                   _______, _______, _______,    _______, _______
  //                           ╰──────────────────────────────╯ ╰──────────────────╯
  ),  


 [LAYER_NAV_EXT] = LAYOUT(
  // ╭──────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        _______,  _______,  _______, _______,   _______,    _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______,  _______,  _______,  _______,   _______,    KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       RGB_TOG,  RGB_MOD,  _______,  _______,   _______,    _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                              _______, _______, _______,    _______, _______
  //                        ╰───────────────────────────╯ ╰──────────────────╯
  ),

  
  [LAYER_WASD] = LAYOUT(
  // ╭──────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P, 
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
  // ├──────────────────────────────────────────────────┤ ├───-──────────────────────────────────────────┤
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, 
  // ╰──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                              KC_LGUI,  KC_TAB,  KC_SPC,    KC_ENT,  KC_BSPC
  //                        ╰───────────────────────────╯ ╰──────────────────╯
  ),

  
  [LAYER_MOUSE] = LAYOUT(
  // ╭──────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX,
  // ╰──────────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                              XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
  //                        ╰───────────────────────────╯ ╰──────────────────╯
  )
//   [LAYER_NAV] = LAYOUT(
//   // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
//        RGB_TOG, KC_MNXT, KC_MPLY, KC_MPRV, XXXXXXX,    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,
//   // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
//        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,    KC_4,    KC_5,    KC_6, KC_PMNS,
//   // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
//        XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,    KC_PAST,    KC_1,    KC_2,    KC_3, KC_PSLS,
//   // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
//                          XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______
//   //                   ╰───────────────────────────╯ ╰──────────────────╯
//   ),

//   [LAYER_SYMBOLS] = LAYOUT(
//   // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX,
//   // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
//        KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
//   // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
//        KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX,
//   // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
//                          _______, _______, XXXXXXX,    _______, XXXXXXX
//   //                   ╰───────────────────────────╯ ╰──────────────────╯
//   ),
};
// clang-format on




// Mouse Scrolling
bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    set_scrolling = IS_LAYER_ON_STATE(state, LAYER_MOUSE);

    return state;
} 

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch(keycode) {
//         case SCROLL:
//             set_scrolling = record->event.pressed;
//             break;
//         default:
//             break;
//     }
//     return true;
// }