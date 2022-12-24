/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 @dlford

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
#include "features/caps_word.h"

// Layers
enum layers {
    _QWERTY = 0,
    _COLEMAK,
    _NAVIGATION,
    _SPECIAL,
    _MOUSE,
};

static uint16_t default_animation = RGB_MATRIX_CYCLE_SPIRAL;
static int default_speed = 50;
static uint16_t secondary_animation = RGB_MATRIX_HUE_WAVE;
static int secondary_speed = 150;
static bool is_macro_recording = false;

// Init
void keyboard_post_init_user(void) {
    rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
    rgb_matrix_mode_noeeprom(default_animation);
    rgb_matrix_set_speed_noeeprom(default_speed);
}

// Permissive hold per key
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(3, KC_SPC):
      return true; // Enable permissive hold
    case LT(2, KC_TAB):
      return true;
    default:
      return false; // Disable permissive hold
  }
}

// Tapping force hold per key
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(3, KC_SPC):
      return true; // Enable force hold
    case LT(2, KC_TAB):
      return true;
    default:
      return false; // Disable force hold
  }
}

// Tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case C_S_T(KC_E):
    case C_S_T(KC_I):
      return 215;
    default:
      return 190;
  }
}

// RGB timeout
#define RGB_CUSTOM_TIMEOUT 5 // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;
void matrix_scan_user(void) {
    if (is_keyboard_master()) {
        // idle_timer needs to be set one time
        if (idle_timer == 0) idle_timer = timer_read();

        if (led_on && timer_elapsed(idle_timer) > 30000) {
          halfmin_counter++;
          idle_timer = timer_read();
        }

        if (led_on && halfmin_counter >= RGB_CUSTOM_TIMEOUT * 2) {
          rgb_matrix_disable_noeeprom();
          led_on = false;
          halfmin_counter = 0;
        }
    }
}

// Macros
enum macro_events {
    M_KEYMAP = SAFE_RANGE,
    M_COMM,
    M_DOT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // RGB resume
    if (is_keyboard_master()) {
        if (record->event.pressed) {
            if (led_on == false) {
                rgb_matrix_enable_noeeprom();
                led_on = true;
            }
            idle_timer = timer_read();
            halfmin_counter = 0;
        }
    }

    // Caps word
    if (!process_caps_word(keycode, record)) { return false; }

    // Macros
    const uint8_t mods = get_mods();
    static uint8_t backstepCounter = 0;
    static bool keyDown = false;
    switch (keycode) {
      case M_KEYMAP:
          if (record->event.pressed) {
              SEND_STRING("https://raw.githubusercontent.com/dlford/qmk_firmware/master/keyboards/crkbd/keymaps/dlford/legends.svg");
          }
          return false;
      case M_COMM:
          if (record->event.pressed) {
              if ((mods & MOD_BIT(KC_LCTL)) && (mods & MOD_BIT(KC_LSFT) && (mods & MOD_BIT(KC_LALT)))) {
                  backstepCounter = 1;
                  clear_mods();
                  SEND_STRING("<>");
              } else if ((mods & MOD_BIT(KC_LCTL)) && (mods & MOD_BIT(KC_LALT))) {
                  backstepCounter = 1;
                  clear_mods();
                  SEND_STRING("()");
              } else if ((mods & MOD_BIT(KC_LCTL)) && (mods & MOD_BIT(KC_LSFT))) {
                  backstepCounter = 2;
                  clear_mods();
                  SEND_STRING("{};");
              } else if (mods & MOD_BIT(KC_LCTL)) {
                  backstepCounter = 1;
                  clear_mods();
                  SEND_STRING("{}");
              } else if ((mods & MOD_BIT(KC_LALT)) && (mods & MOD_BIT(KC_LSFT))) {
                  backstepCounter = 2;
                  clear_mods();
                  SEND_STRING("[];");
              } else if (mods & MOD_BIT(KC_LALT)) {
                  backstepCounter = 1;
                  clear_mods();
                  SEND_STRING("[]");
              } else {
                  keyDown = true;
                  register_code(KC_COMM);
                  return true;
              }
              if (backstepCounter) {
                  while (backstepCounter > 0) {
                      tap_code(KC_LEFT);
                      backstepCounter--;
                  }
                  set_mods(mods);
              }
          } else {
              if (keyDown) {
                  unregister_code(KC_COMM);
                  keyDown = false;
                  return true;
              }
          }
          return false;
      case M_DOT:
          if (record->event.pressed) {
              if (mods & MOD_BIT(KC_LCTL)) {
                  clear_mods();
                  SEND_STRING("=>");
              } else if (mods & MOD_BIT(KC_LALT)) {
                  clear_mods();
                  SEND_STRING("->");
              } else {
                  keyDown = true;
                  register_code(KC_DOT);
                  return true;
              }
          } else {
              if (keyDown) {
                  unregister_code(KC_DOT);
                  keyDown = false;
                  return true;
              }
          }
          set_mods(mods);
          return false;
    }

    return true;
}

// RGB Layers (Enable animations in config.h)
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SPECIAL:
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        case _NAVIGATION:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        case _MOUSE:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        default:
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
            rgb_matrix_set_speed_noeeprom(default_speed);
            rgb_matrix_mode_noeeprom(default_animation);
            break;
    }
    return state;
}

// Dynamic Macro Recording Backlight
void dynamic_macro_record_start_user(void) {
    is_macro_recording = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_macro_recording = false;
}

// Indicators
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock || caps_word_enabled) {
        // Left master
        rgb_matrix_set_color(3, RGB_RED);
        // Right master
        rgb_matrix_set_color(21, RGB_RED);
    }
    if (is_macro_recording) {
        // Left master
        rgb_matrix_set_color(4, RGB_ORANGE);
        // Right master
        rgb_matrix_set_color(22, RGB_ORANGE);
    }
    if (default_layer_state - 1 == _COLEMAK) {
        // Left master
        rgb_matrix_set_color(5, RGB_GREEN);
        // Right master
        rgb_matrix_set_color(23, RGB_GREEN);
    }
    return false;
}

// Quantum keys / Abbreviations
enum custom_keycodes {
    VVV = KC_TRNS,
    XXX = KC_NO,
    CSA_Q = MEH_T(KC_Q),
    CSA_F1 = MEH_T(KC_F1),
    CSA_1 = MEH_T(KC_1),
    CA_W = LCA_T(KC_W),
    CA_F2 = LCA_T(KC_F2),
    CA_2 = LCA_T(KC_2),
    CS_E = C_S_T(KC_E),
    CS_F = C_S_T(KC_F),
    CS_I = C_S_T(KC_I),
    CS_U = C_S_T(KC_U),
    CS_F3 = C_S_T(KC_F3),
    CS_3 = C_S_T(KC_3),
    CS_F8 = C_S_T(KC_F8),
    CS_8 = C_S_T(KC_8),
    CA_O = LCA_T(KC_O),
    CA_Y = LCA_T(KC_Y),
    CA_F9 = LCA_T(KC_F9),
    CA_9 = LCA_T(KC_9),
    CSA_P = MEH_T(KC_P),
    CSA_SCLN = MEH_T(KC_SCLN),
    CSA_F10 = MEH_T(KC_F10),
    CSA_0 = MEH_T(KC_0),
    LGUI_A = LGUI_T(KC_A),
    LGUI_FIND = LGUI_T(KC_FIND),
    LGUI_GRV = LGUI_T(KC_GRV),
    LALT_S = LALT_T(KC_S),
    LALT_R = LALT_T(KC_R),
    LALT_HOME = LALT_T(KC_HOME),
    LCTL_D = LCTL_T(KC_D),
    LCTL_S = LCTL_T(KC_S),
    LCTL_PGUP = LCTL_T(KC_PGUP),
    LCTL_LBRC = LCTL_T(KC_LBRC),
    LSFT_F = LSFT_T(KC_F),
    _LSFT_T = LSFT_T(KC_T),
    LSFT_PGDN = LSFT_T(KC_PGDN),
    LSFT_RBRC = LSFT_T(KC_RBRC),
    RSFT_J = RSFT_T(KC_J),
    RSFT_N = RSFT_T(KC_N),
    RSFT_DOWN = RSFT_T(KC_DOWN),
    RSFT_MINS = RSFT_T(KC_MINS),
    RCTL_K = RCTL_T(KC_K),
    RCTL_E = RCTL_T(KC_E),
    RCTL_UP = RCTL_T(KC_UP),
    RCTL_EQL = RCTL_T(KC_EQL),
    RALT_L = RALT_T(KC_L),
    RALT_I = RALT_T(KC_I),
    RALT_RGHT = RALT_T(KC_RGHT),
    RALT_BSLS = RALT_T(KC_BSLS),
    RGUI_SCLN = RGUI_T(KC_SCLN),
    RGUI_O = RGUI_T(KC_O),
    RGUI_F11 = RGUI_T(KC_F11),
    RGUI_QUOT = RGUI_T(KC_QUOT),
    LT3_SPC = LT(3,KC_SPC),
    LT2_TAB = LT(2,KC_TAB),
    DF_QWERTY = DF(0),
    DF_COLEMAK = DF(1),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            CSA_Q,   CA_W,    CS_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    CS_I,    CA_O,    CSA_P,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            LGUI_A,  LALT_S,  LCTL_D,  LSFT_F,  KC_G,                         KC_H,    RSFT_J,  RCTL_K,  RALT_L, RGUI_SCLN,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    M_COMM,  M_DOT,  KC_SLSH,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                       KC_ESC,  LT3_SPC, KC_BSPC,    KC_DEL, LT2_TAB,  KC_ENT
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
    [_COLEMAK] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            CSA_Q,   CA_W,    CS_F,    KC_P,    KC_G,                         KC_J,    KC_L,    CS_U,    CA_Y,    CSA_SCLN,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            LGUI_A,  LALT_R,  LCTL_S,  _LSFT_T, KC_D,                         KC_H,    RSFT_N,  RCTL_E,  RALT_I,  RGUI_O,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M,    M_COMM,  M_DOT,  KC_SLSH,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                       KC_ESC,  LT3_SPC, KC_BSPC,    KC_DEL, LT2_TAB,  KC_ENT
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
    [_NAVIGATION] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            CSA_F1,  CA_F2,   CS_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   CS_F8,  CA_F9,   CSA_F10,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         LGUI_FIND,LALT_HOME,LCTL_PGUP,LSFT_PGDN,KC_END,                     KC_LEFT,RSFT_DOWN,RCTL_UP,RALT_RGHT,RGUI_F11,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         DF_QWERTY,DF_COLEMAK,KC_VOLD, KC_VOLU, QK_BOOT,                      KC_MUTE, KC_MPLY, KC_MPRV, KC_MNXT, KC_F12,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                        VVV,    TG(4),    VVV,         VVV,    VVV,     VVV
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
    [_SPECIAL] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            CSA_1,   CA_2,    CS_3,    KC_4,    KC_5,                         KC_6,    KC_7,    CS_8,    CA_9,    CSA_0,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
           LGUI_GRV,KC_LALT,LCTL_LBRC,LSFT_RBRC,KC_LPRN,                     KC_RPRN,RSFT_MINS,RCTL_EQL,RALT_BSLS,RGUI_QUOT,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_TILD, KC_CAPS, KC_LCBR, KC_RCBR,TG(_MOUSE),                     EE_CLR, KC_UNDS, KC_PLUS, KC_PIPE, KC_DQUO,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                        VVV,     VVV,     VVV,        VVV,    TG(4),    VVV
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
    [_MOUSE] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, DM_REC1,                      KC_WSTP, KC_ACL2, KC_ACL1, KC_ACL0, KC_WFWD,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, DM_PLY1,                      KC_WREF, KC_BTN1, KC_BTN2, KC_BTN3, KC_WBAK,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
           M_KEYMAP,KC_BTN3, KC_BTN2, KC_BTN1,  XXX,                          XXX,     XXX,     XXX,     XXX,     XXX,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                        VVV,    TG(4),    VVV,        VVV,    TG(4),    VVV
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
};
