#include QMK_KEYBOARD_H
#include "hvp.c"
#ifdef SSD1306OLED
#    include "ssd1306.h"
#    include <string.h>
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
     LT(_ADJUST,KC_TAB),  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    LSFT_T(KC_ESC),  KC_A,  KC_S,  KC_D,  LT(3,KC_F), KC_G, KC_H,  KC_J,  KC_K,  KC_L,TD(TD1),TD(TD2),
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M,KC_COMM,KC_DOT,TD(TD3),KC_SFTENT,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LT(1,KC_SPC),MT(MOD_LSFT, KC_SPC),   MT(MOD_LSFT,KC_ENT), LT(2,KC_SPC),KC_LALT
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                   KC_6,  KC_7,  KC_8,  KC_9,  KC_0,KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_DEL, _______, _______, _______, _______, _______,                _______,KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL, _______, _______, _______, _______, _______,                  _______, KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_PIPE,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                _______, _______, _______, _______, _______, _______
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_TAB,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,              KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_DEL, _______, _______, _______, _______, _______, _______,KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_BSLS,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL, _______, _______, _______, _______, _______, _______,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_TILD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                _______, _______, _______, _______, _______, _______
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
      _______,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                  KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_F1,_______,_______,D_NAVI,_______,_______,                 KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    QK_BOOT,KC_PSCR,_______,_______,_______,_______,                 KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                _______, KC_VOLD,KC_MPLY, KC_MNXT, KC_VOLU,_______
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_ENABLE

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write(read_layer_state(), false);
    oled_write(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state()), false;
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
  return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
      break;
  }
  return true;
}
