#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

#define KC_ KC_TRNS
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)
#define KC_CTLEN CTL_T(KC_LANG2)    // for Linux and Windows
#define KC_GUIEN GUI_T(KC_LANG2)    // for Mac
#define KC_SFTJP SFT_T(KC_LANG1)
#define KC_ALTSP ALT_T(KC_SPACE)
#define KC_ALTDL ALT_T(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_ESC,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_CTLTB,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                      KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                      KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,   KC_ENT,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_ALTSP, KC_LOWER, KC_GUIEN,    KC_SFTJP, KC_RAISE, KC_ALTDL
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
       _______,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  _______,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       _______,  KC_HOME,   KC_END,  KC_PGDN,  KC_PGUP,   KC_F11,                   KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,   KC_F12,  KC_PIPE,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                     KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,  _______,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   _______,  _______,  _______,     _______,  _______, _______
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
       _______,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       _______, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,  KC_PSCR,                    KC_GRV,  KC_MINS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_BSLS,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       _______, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,                   KC_TILD,  KC_UNDS,   KC_EQL,  KC_LBRC,  KC_RBRC,  _______,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   _______,  _______,  _______,     _______,  _______, _______
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_RST,  KC_LRST, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,                  KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_LTOG,  KC_LHUI,  KC_LSAI,  KC_LVAI, KC_XXXXX, KC_XXXXX,                  KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_LMOD,  KC_LHUD,  KC_LSAD,  KC_LVAD, KC_XXXXX, KC_XXXXX,                  KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_GUIEI, KC_LOWER,   KC_SPC,      KC_ENT, KC_RAISE, KC_ALTKN
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

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
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
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
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
