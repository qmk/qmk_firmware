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
#include <config.h>
#include <stdint.h>
#include <keymap_jp.h>
#include <transactions.h>

typedef struct user_runtime_config {
    bool jpmode, keylogging;
} user_runtime_config;


user_runtime_config user_state = {
    .jpmode = true,
    .keylogging = false
};

enum user_key{
    //universal symbol keys
    MY_2 = SAFE_RANGE,
    MY_6,
    MY_7,
    MY_8,
    MY_9,
    MY_0,
    MY_MINS,
    MY_EQL,
    MY_LBRC,
    MY_RBRC,
    MY_BSLS,
    MY_SCLN,
    MY_QUOT,
    MY_GRV,

    //universal utils
    MY_ZKHK,
    MY_CAPS,

    //user utils
    MY_JP,
    MY_OLED
};

//keycode US or JP
const uint16_t my_symbols[14][3] = {
    {KC_2   , JP_2   , JP_AT  },
    {KC_6   , JP_6   , JP_CIRC},
    {KC_7   , JP_7   , JP_AMPR},
    {KC_8   , JP_8   , JP_ASTR},
    {KC_9   , JP_9   , JP_LPRN},
    {KC_0   , JP_0   , JP_RPRN},
    {KC_MINS, JP_MINS, JP_UNDS},
    {KC_EQL , JP_EQL , JP_PLUS},
    {KC_LBRC, JP_LBRC, JP_LCBR},
    {KC_RBRC, JP_RBRC, JP_RCBR},
    {KC_BSLS, JP_BSLS, JP_PIPE},
    {KC_SCLN, JP_SCLN, JP_COLN},
    {KC_QUOT, JP_QUOT, JP_DQUO},
    {KC_GRV , JP_GRV , JP_TILD}
};

const int symbol_array_size = sizeof(my_symbols) / sizeof(uint16_t[3]);

bool tap_my_symbol(uint16_t keycode, keyrecord_t *record) {
    if(!record->event.pressed) return true;
    uint16_t index = keycode - MY_2;
    if(symbol_array_size <= index) return true;

    if(user_state.jpmode) {
        bool lshift = get_mods() & MOD_BIT(KC_LSFT);
        bool rshift = get_mods() & MOD_BIT(KC_RSFT);
        bool shift  = lshift | rshift;
        uint16_t stey_code = my_symbols[index][shift ? 2 : 1];
        if(((stey_code & QK_LSFT) == QK_LSFT) | ((stey_code & QK_RSFT) == QK_RSFT)) {
            if(shift) {
                tap_code(stey_code);
            }else{
                register_code(KC_LSFT);
                tap_code(stey_code);
                unregister_code(KC_LSFT);
            }
        }else {
            if(shift) {
                if(lshift) unregister_code(KC_LSFT);
                if(rshift) unregister_code(KC_RSFT);
                tap_code(stey_code);
                if(lshift) register_code(KC_LSFT);
                if(rshift) register_code(KC_RSFT);
            }else {
                tap_code(stey_code);
            }
        }
    }else {
        tap_code(my_symbols[index][0]);
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, MY_SCLN, MY_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, MY_ZKHK,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    MY_2,    KC_3,    KC_4,    KC_5,                         MY_6,    MY_7,    MY_8,    MY_9,    MY_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       MY_GRV,  MY_EQL, MY_LBRC, MY_RBRC, MY_SCLN, MY_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,                      MY_BSLS, MY_QUOT, KC_COMM,  KC_DOT, KC_SLSH, MY_ZKHK,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,  KC_FN1,  KC_FN2,  KC_FN3,  KC_FN4, KC_NLCK,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_FN5,  KC_FN6,  KC_FN7,  KC_FN8, MY_CAPS,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,  KC_FN9, KC_FN10, KC_FN11, KC_FN12, KC_SLCK,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MY_ZKHK,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   MO(3),  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,   MY_JP,                      MY_OLED, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )

};

#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(user_state.jpmode ? PSTR(" JP:") : PSTR(" US:"), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_render_toggle_and_layer(led_t led_state) {
    oled_write_P(PSTR("["), false);
    oled_write_P(led_state.num_lock ?    PSTR("N") : PSTR("_"), false);
    oled_write_P(led_state.caps_lock ?   PSTR("C") : PSTR("_"), false);
    oled_write_P(led_state.scroll_lock ? PSTR("S") : PSTR("_"), false);
    oled_write_P(PSTR("]"), false);
    oled_render_layer_state();
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_toggle_and_layer(host_keyboard_led_state());
        if(user_state.keylogging) oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (user_state.keylogging & record->event.pressed) {
        set_keylog(keycode, record);
    }
    if(keycode <= KC_Z) return true;
    if(!tap_my_symbol(keycode, record)) return false;

    switch (keycode) {
        case MY_ZKHK:
            if(!record->event.pressed) return false;
            if(user_state.jpmode | ((get_mods() & MOD_BIT(KC_RALT)) | (get_mods() & MOD_BIT(KC_LALT)))) {
                tap_code(KC_GRV);
                return false;
            }else {
                register_code(KC_RALT);
                tap_code(KC_GRV);
                unregister_code(KC_RALT);
                return false;
            }
            break;

        case MY_CAPS:
            if(!record->event.pressed) return false;
            if((!user_state.jpmode) | ((get_mods() & MOD_BIT(KC_LSFT)) | (get_mods() & MOD_BIT(KC_RSFT)))) {
                tap_code(KC_CAPS);
                return false;
            }else {
                register_code(KC_LSFT);
                tap_code(KC_CAPS);
                unregister_code(KC_LSFT);
                return false;
            }
            break;

        case MY_JP:
            if(!record->event.pressed) return false;
            user_state.jpmode = !user_state.jpmode;
            return false;
            break;

        case MY_OLED:
            if(!record->event.pressed) return false;
            user_state.keylogging = !user_state.keylogging;
            if(!user_state.keylogging) oled_clear();
            return false;
            break;
    }
    return true;
}

#ifdef USER_DEBUG_MODE
void config_copy(struct user_runtime_config *dst, struct user_runtime_config *src) {
    dst->jpmode = src->jpmode;
    dst->keylogging = src->keylogging;
}


void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    config_copy(&user_state, (user_runtime_config*)in_data);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

void housekeeping_task_user(void){
    if(!is_keyboard_master()){
        static uint32_t last_sync;
        if(timer_elapsed32(last_sync) > 500) {
            transaction_rpc_send(USER_SYNC_A, sizeof(user_state), &user_state);
            last_sync = timer_read32();
        }
    }
}
#endif

