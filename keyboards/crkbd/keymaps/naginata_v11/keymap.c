/* Copyright 2018-2019 eswai <@eswai>
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "keymap_japanese.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

void update_led(void);

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keymap_layers {
  _QWERTY,
  _EUCALYN,
  _WORKMAN,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

// 薙刀式
// FG, HJの同時押しでかな/英数モードを切り替えられるようにする
enum combo_events {
  NAGINATA_ON_CMB,
  NAGINATA_OFF_CMB,
};

#if defined(DQWERTY)
const uint16_t PROGMEM ngon_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_F, KC_G, COMBO_END};
#endif
#if defined(DEUCALYN)
const uint16_t PROGMEM ngon_combo[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_I, KC_U, COMBO_END};
#endif
#if defined(DWORKMAN)
const uint16_t PROGMEM ngon_combo[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_T, KC_G, COMBO_END};
#endif

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
  [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
};

// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed) {
        naginata_on();
        update_led();
      }
      break;
    case NAGINATA_OFF_CMB:
      if (pressed) {
        naginata_off();
        update_led();
      }
      break;
  }
}
// 薙刀式

enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  EUCALYN,
  WORKMAN,
  EISU,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  KANA2,
  UNDGL,
  RGBRST
};

#define CTLTB CTL_T(KC_TAB)
#define GUITB GUI_T(KC_TAB)
#define ABLS    LALT(KC_BSLS)
#define CMDENT  CMD_T(KC_ENT)
#define SFTSPC  LSFT_T(KC_SPC)
#define CTLSPC  CTL_T(KC_SPC)
#define ALTSPC  ALT_T(KC_SPC)
#define ALTENT  ALT_T(KC_ENT)
#define CTLBS   CTL_T(KC_BSPC)
#define CTLENT  CTL_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _QWERTY
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  W   |  E   |  R   |  T   |      |      |  Y   |  U   |  I   |  O   |  P   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  S   |  D   |  F   |  G   |      |      |  H   |  J   |  K   |  L   |  ;   | RGUI |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LSFT |  Z   |  X   |  C   |  V   |  B   |      |      |  N   |  M   |  ,   |  .   |  /   | RCMD |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |      |      |      |      |LOWER | LSFT |CTLSPC|ALTENT| RSFT |RAISE |      |      |      |      |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_QWERTY] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,                KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,                KC_H   ,KC_J   ,KC_K   ,KC_L   ,JP_SCLN,KC_RGUI, \
    KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,                KC_N   ,KC_M   ,JP_COMM,JP_DOT ,JP_SLSH,KC_RCMD, \
                                    LOWER  ,KC_LSFT,CTLSPC ,ALTENT ,KC_RSFT,RAISE
  ),

/* _LOWER
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | ESC |  ~  |  @  |  #  |  $  |  %  |     |     |  /  |  7  |  8  |  9  |  -  |BSPC |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  | TAB |  ^  |  &  |  !  |  ?  |  \  |     |     |  *  |  4  |  5  |  6  |  +  |  .  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |LSFT |  |  |  `  |  '  |  "  |  _  |     |     |  0  |  1  |  2  |  3  |  =  |  ,  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
  |     |     |     |     | __  | __  | __  | __  | __  | __  |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
  [_LOWER] = LAYOUT(
    KC_ESC ,JP_TILD,JP_AT  ,JP_HASH,JP_DLR ,JP_PERC,                JP_SLSH,KC_7   ,KC_8   ,KC_9   ,JP_MINS,KC_BSPC, \
    KC_TAB ,JP_CIRC,JP_AMPR,JP_EXLM,JP_QUES,JP_BSLS,                JP_ASTR,KC_4   ,KC_5   ,KC_6   ,JP_PLUS,JP_DOT , \
    KC_LSFT,JP_PIPE,JP_GRV ,JP_QUOT,JP_DQUO ,JP_UNDS,                KC_0   ,KC_1   ,KC_2   ,KC_3   ,JP_EQL ,JP_COMM, \
                                    _______,_______,_______,_______,_______,_______
  ),

/* _RAISE
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  ESC  |       |       |       |       |       |       |       |       |       |  UP   |       | PGUP  |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  TAB  |       |   [   |   {   |   (   |   <   |       |       | HOME  | LEFT  | DOWN  | RGHT  | PGDN  |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  | LSFT  |       |   ]   |   }   |   )   |   >   |       |       |  END  |S(LEFT)|S(DOWN)|S(RGHT)|       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |  __   |  __   |  __   |  __   |  __   |  __   |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_RAISE] = LAYOUT(
    KC_ESC    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,                      XXXXXXX   ,XXXXXXX   ,KC_UP     ,XXXXXXX   ,KC_PGUP   ,XXXXXXX   , \
    KC_TAB    ,XXXXXXX   ,JP_LBRC   ,JP_LCBR   ,JP_LPRN   ,KC_LT     ,                      KC_HOME   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,KC_PGDN   ,XXXXXXX   , \
    KC_LSFT   ,XXXXXXX   ,JP_RBRC   ,JP_RCBR   ,JP_RPRN   ,KC_GT     ,                      KC_END    ,S(KC_LEFT),S(KC_DOWN),S(KC_RGHT),XXXXXXX   ,XXXXXXX   , \
                                                _______   ,_______   ,_______   ,_______   ,_______   ,_______
  ),

/* _ADJUST
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |RGB_HUI|RGB_HUD| WAKE  |       | RESET | UNDGL |       |       |RGB_TOG|       |KC_VOLU|       |KC_BRIU|QWERTY |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |RGB_SAI|RGB_SAD|       |       |       |       |       |       |RGB_MOD|KC_MRWD|KC_VOLD|KC_MFFD|KC_BRID|EUCALYN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |RGB_VAI|RGB_VAD| SLEP  |       |       |       |       |       |RGBRST |       |KC_MPLY|       |       |WORKMAN|
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       |  __   |  __   |  __   |  __   |  __   |  __   |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
  [_ADJUST] = LAYOUT(
    RGB_HUI,RGB_HUD,KC_WAKE,XXXXXXX,RESET  ,UNDGL  ,                RGB_TOG,XXXXXXX,KC_VOLU,XXXXXXX,KC_BRIU,QWERTY , \
    RGB_SAI,RGB_SAD,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                RGB_MOD,KC_MRWD,KC_VOLD,KC_MFFD,KC_BRID,EUCALYN, \
    RGB_VAI,RGB_VAD,KC_SLEP,XXXXXXX,XXXXXXX,XXXXXXX,                RGBRST ,XXXXXXX,KC_MPLY,XXXXXXX,XXXXXXX,WORKMAN, \
                                    _______,_______,_______,_______,_______,_______
  ),

/* _EUCALYN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  W   |  ,   |  .   |  ;   |      |      |  M   |  R   |  D   |  Y   |  P   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  O   |  E   |  I   |  U   |      |      |  G   |  T   |  K   |  S   |  N   | RGUI |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LSFT |  Z   |  X   |  C   |  V   |  F   |      |      |  B   |  H   |  J   |  L   |  /   | RCMD |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |      |      |      |      |LOWER | LSFT |CTLSPC|ALTENT| RSFT |RAISE |      |      |      |      |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_EUCALYN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_W   ,JP_COMM,JP_DOT ,JP_SCLN,                KC_M   ,KC_R   ,KC_D   ,KC_Y   ,KC_P   ,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_O   ,KC_E   ,KC_I   ,KC_U   ,                KC_G   ,KC_T   ,KC_K   ,KC_S   ,KC_N   ,KC_RGUI, \
    KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_F   ,                KC_B   ,KC_H   ,KC_J   ,KC_L   ,JP_SLSH,KC_RCMD, \
                                    LOWER  ,KC_LSFT,CTLSPC ,ALTENT ,KC_RSFT,RAISE
  ),

/* _WORKMAN
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | ESC  |  Q   |  D   |  R   |  W   |  B   |      |      |  J   |  F   |  U   |  P   |  ;   | BSPC |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | TAB  |  A   |  S   |  H   |  T   |  G   |      |      |  Y   |  N   |  E   |  O   |  I   | RGUI |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  | LSFT |  Z   |  X   |  M   |  C   |  V   |      |      |  K   |  L   |  ,   |  .   |  /   | RCMD |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
  |      |      |      |      |LOWER | LSFT |CTLSPC|ALTENT| RSFT |RAISE |      |      |      |      |
  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+
*/
  [_WORKMAN] = LAYOUT(
    KC_ESC ,KC_Q   ,KC_D   ,KC_R   ,KC_W   ,KC_B   ,                KC_J   ,KC_F   ,KC_U   ,KC_P   ,JP_SCLN,KC_BSPC, \
    KC_TAB ,KC_A   ,KC_S   ,KC_H   ,KC_T   ,KC_G   ,                KC_Y   ,KC_N   ,KC_E   ,KC_O   ,KC_I   ,KC_RGUI, \
    KC_LSFT,KC_Z   ,KC_X   ,KC_M   ,KC_C   ,KC_V   ,                KC_K   ,KC_L   ,JP_COMM,JP_DOT ,JP_SLSH,KC_RCMD, \
                                    LOWER  ,KC_LSFT,CTLSPC ,ALTENT ,KC_RSFT,RAISE
  ),

/* _NAGINATA
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_Q  | NG_W  | NG_E  | NG_R  | NG_T  |       |       | NG_Y  | NG_U  | NG_I  | NG_O  | NG_P  |  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_A  | NG_S  | NG_D  | NG_F  | NG_G  |       |       | NG_H  | NG_J  | NG_K  | NG_L  |NG_SCLN|  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |  __   | NG_Z  | NG_X  | NG_C  | NG_V  | NG_B  |       |       | NG_N  | NG_M  |NG_COMM|NG_DOT |NG_SLSH|  __   |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
  |       |       |       |       | LOWER |NG_SHFT|  __   |  __   |NG_SHFT| RAISE |       |       |       |       |
  +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
*/
// 薙刀式
  [_NAGINATA] = LAYOUT(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,                NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
                                    LOWER  ,NG_SHFT,_______,_______,NG_SHFT,RAISE
  ),
// 薙刀式

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
  // 薙刀式
  set_naginata(_NAGINATA);
  #ifdef NAGINATA_EDIT_MAC
  set_unicode_input_mode(UC_OSX);
  #endif
  #ifdef NAGINATA_EDIT_WIN
  set_unicode_input_mode(UC_WINC);
  #endif
  // 薙刀式

  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

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

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool underglow = false;

void update_led() {
  if (layer_state_is(_LOWER) && !isLeftHand) {
    // rgblight_setrgb_at(0, 0, 200, 7);
    rgblight_sethsv_at(200, 100, 255, 15);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 18);
    rgblight_sethsv_at(200, 100, 255, 19);
    rgblight_sethsv_at(200, 100, 255, 20);
    rgblight_sethsv_at(200, 100, 255, 21);
    rgblight_sethsv_at(200, 100, 255, 22);
    rgblight_sethsv_at(200, 100, 255, 23);
  }
  if (layer_state_is(_RAISE) && !isLeftHand) {
    rgblight_sethsv_at(200, 100, 255, 11);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 19);
  }
  if (!layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
    rgblight_sethsv_range(0, 0, 0, 6, 27);
  }
  if (naginata_state()) {
    rgblight_sethsv_at(200, 200, 255, 6);
    rgblight_sethsv_at(200, 200, 255, 13);
    rgblight_sethsv_at(200, 200, 255, 14);
  } else {
    rgblight_sethsv_at(0, 0, 0, 6);
    rgblight_sethsv_at(0, 0, 0, 13);
    rgblight_sethsv_at(0, 0, 0, 14);
  }
  if (underglow) {
    rgblight_sethsv_range(200, 200, 255, 0, 6);
  } else {
    rgblight_sethsv_range(200, 200, 0, 0, 6);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case UNDGL:
      if (record->event.pressed) {
        underglow = !underglow;
      }
      update_led();
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        // 薙刀式
        naginata_off();
        // 薙刀式
        update_led();
      }
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        // 薙刀式
        naginata_on();
        // 薙刀式
        update_led();
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
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      update_led();
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      update_led();
      return false;
      break;
  }

  // 薙刀式
  bool a = true;
  if (naginata_state()) { // 薙刀式モードONなら
    naginata_mode(keycode, record); // modifierを押していたら薙刀式レイヤーはOFFにする
    a = process_naginata(keycode, record); // 薙刀式の処理をする
    // update_led();
  }
  if (a == false) return false; // 以降のevent chainを中断する
  // 薙刀式

  return true;
}
