/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include "keycodes.h"
#include <print.h>

#ifdef TAP_DANCE_ENABLE
  #include "tapdance.c"
#endif

#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split(
  //,--------------------------------------------------------------.                 ,--------------------------------------------------------------------.    ,---------------------------.
      TD(TD_GRAVE_ESC),   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,           KC_7,    KC_8,    KC_9,    KC_0, KC_MINUS,  KC_EQUAL, KC_BSPACE,        KC_INS, KC_HOME,  KC_PGUP,
  //|--------+--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+---------+----------+-----------|    +--------+--------+---------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,   KC_LBRC,   KC_RBRC,        KC_DEL, KC_END, KC_PGDOWN,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+---------+----------+-----------|    `---------------------------.
        MO(_FUNC),    KC_A,    KC_S,    KC_D,   KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,    KC_ENTER,
  //|-----------+--------+--------+--------+--------+--------+--------|              |--------+--------+--------+--------+--------+--------+--------------|             ,--------.
         KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,             KC_RSFT,                  KC_UP,
  //|-----------+--------+--------+--------+--------+--------|                       |--------+--------+--------+--------+--------+--------+--------------|    ,--------+--------+---------.
        KC_LCTRL, KC_LGUI, KC_LALT,   MO(_SYSTEM),   KC_SPACE,                            KC_SPACE,      KC_RALT,     MO(_FUNC),    MO(_MEDIA),   KC_RCTRL,     KC_LEFT,  KC_DOWN, KC_RIGHT
  //`--------------------------------------------------------|                       |--------------------------------------------------------------------|    `---------------------------'
  ),

  [_FUNC] = LAYOUT_split(
  //,--------------------------------------------------------------.                 ,--------------------------------------------------------------------.    ,---------------------------.
       TD(TD_GRAVE_ESC),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,    KC_F12,    XXXXXXX,      XXXXXXX, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+---------+----------+-----------|    +--------+--------+---------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+---------+----------+-----------|    `---------------------------.
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
  //|-----------+--------+--------+--------+--------+--------+--------|              |--------+--------+--------+--------+--------+--------+--------------|             ,--------.
         KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX,               XXXXXXX,
  //|-----------+--------+--------+--------+--------+--------|                       |--------+--------+--------+--------+--------+--------+--------------|    ,--------+--------+---------.
        KC_LCTRL, KC_LGUI, KC_LALT,   MO(_SYSTEM),   KC_SPACE,                        KC_SPACE,      KC_RALT,     MO(_FUNC),      MO(_MEDIA),     KC_RCTRL,    XXXXXXX,  XXXXXXX, XXXXXXX
  //`--------------------------------------------------------|                       |--------------------------------------------------------------------|    `---------------------------'
  ),

  [_MEDIA] = LAYOUT_split(
  //,--------------------------------------------------------------.                 ,--------------------------------------------------------------------.    ,---------------------------.
       TD(TD_GRAVE_ESC),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,    KC_F12,    XXXXXXX,       XXXXXXX, KC_MPLY, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+---------+----------+-----------|    +--------+--------+---------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX, KC_MSTP, KC_VOLD,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+---------+----------+-----------|    `---------------------------.
        KC_MPRV, KC_MNXT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
  //|-----------+--------+--------+--------+--------+--------+--------|              |--------+--------+--------+--------+--------+--------+--------------|             ,--------.
         KC_LSFT, XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               XXXXXXX,               XXXXXXX,
  //|-----------+--------+--------+--------+--------+--------|                       |--------+--------+--------+--------+--------+--------+--------------|    ,--------+--------+---------.
        KC_LCTRL, KC_LGUI, KC_LALT,   MO(_SYSTEM),  KC_SPACE,                          KC_SPACE,      KC_RALT,     MO(_FUNC),      MO(_MEDIA),   KC_RCTRL,      KC_MPRV,  XXXXXXX,  KC_MNXT
  //`--------------------------------------------------------|                       |--------------------------------------------------------------------|    `---------------------------'
  ),

  [_SYSTEM] = LAYOUT_split(
  //,--------------------------------------------------------------.                 ,--------------------------------------------------------------------.    ,---------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,      XXXXXXX, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+---------+----------+-----------|    +--------+--------+---------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                            BL_TOGG,  BL_INC, BL_BRTG, XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,      XXXXXXX, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+---------+----------+-----------|    `---------------------------.
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                            BL_STEP,  BL_DEC, XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,
  //|-----------+--------+--------+--------+--------+--------+--------|              |--------+--------+--------+--------+--------+--------+--------------|             ,--------.
       KC_PWR,   XXXXXXX,  KC_SLEP,  XXXXXXX, XXXXXXX,XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,              XXXXXXX,               XXXXXXX,
  //|-----------+--------+--------+--------+--------+--------|                       |--------+--------+--------+--------+--------+--------+--------------|    ,--------+--------+---------.
        XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,     XXXXXXX,                                    XXXXXXX,      XXXXXXX,     XXXXXXX,      XXXXXXX,   XXXXXXX,      XXXXXXX,  XXXXXXX, XXXXXXX
  //`--------------------------------------------------------|                       |--------------------------------------------------------------------|    `---------------------------'
  )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
  xprintf("Hello! initing!");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    // uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    xprintf("Hello!");
#endif
  return true;
}

// #if defined(OLED_DRIVER_ENABLE) && defined(WPM_ENABLE)
//     #include "oled.c"
// #endif
