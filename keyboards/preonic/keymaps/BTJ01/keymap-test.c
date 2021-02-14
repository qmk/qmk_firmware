/*
* Created By: BTJ01
* Created: Nov 2020
*
*
*/

#include QMK_KEYBOARD_H
#include "muse.h"

/* --- +++ Preonic V3 +++ --- */

enum preonic_layers {
  _COLE,
  _QWRT,
  _BLUE,
  _RED,
  _FC
};

enum preonic_keycodes {
  COLE = SAFE_RANGE,
  QWRT,
  BLUE,
  RED,
  FC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 0 - COLEMAK  *************************************************************************************************************************
 *                                    .-----------------------------------------------------------------------------------.
 *                                    | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  \|  |
 *                                    |------+------+------+------+------+-------------+------+------+------+------+------|
 *                                    |FnCps |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  | Enter|
 *                                    |------+------+------+------+--^^--+------+------+--^^--+------+------+------+------|
 *                                    |Shift |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | Shift|
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |  ←   |  ↓   |  ↑   |  →   |             |             |   ←  |   ↓  |   ↑  |   →  |
 *                                    | Ctrl | GUI  |Ct-Alt| Alt  |   FnSpace   |   FnSpace   |  Alt |Ct-Alt| GUI  | Ctrl |
 *                                    '-----------------------------------------------------------------------------------'
 */
[COLE] = LAYOUT_preonic_2x2u( \
  KC_GESC,         KC_1,            KC_2,         KC_3,            KC_4,           KC_5,           KC_6,           KC_7,           KC_8,            KC_9,            KC_0,          KC_BSPC,        \
  KC_TAB,          KC_Q,            KC_W,         KC_F,            KC_P,           KC_G,           KC_J,           KC_L,           KC_U,            KC_Y,            KC_SCLN,       KC_BSLS,        \
  LT(FC, KC_CAPS), KC_A,            KC_R,         KC_S,            KC_T,           KC_D,           KC_H,           KC_N,           KC_E,            KC_I,            KC_O,          KC_ENT,         \
  KC_LSFT,         KC_Z,            KC_X,         KC_C,            KC_V,           KC_B,           KC_K,           KC_M,           KC_COMM,         KC_DOT,          KC_SLSH,       KC_RSFT,        \
  LCTL_T(KC_LEFT), LGUI_T(KC_DOWN), LCA_T(KC_UP), LALT_T(KC_RGHT),     LT(BLUE, KC_SPC),             LT(RED, KC_SPC),            RALT_T(KC_LEFT), RCAG_T(KC_DOWN), RGUI_T(KC_UP), RCTL_T(KC_RGHT) \
),                                                          /*   | ----------Fn-SPACE----------  | ----------Fn-SPACE----------  |     */

/* 1 - QWERTY  *************************************************************************************************************************
 *                                    .-----------------------------------------------------------------------------------.
 *                                    | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |FnCps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 *                                    |------+------+------+------+--^^--+------+------+--^^--+------+------+------+------|
 *                                    |Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |  ←   |  ↓   |  ↑   |  →   |             |             |   ←  |   ↓  |   ↑  |   →  |
 *                                    | Ctrl | GUI  |Ct-Alt| Alt  |   FnSpace   |   FnSpace   |  Alt |Ct-Alt| GUI  | Ctrl |
 *                                    '-----------------------------------------------------------------------------------'
 */
[QWERT] = LAYOUT_preonic_2x2u( \
  KC_GESC,         KC_1,            KC_2,         KC_3,            KC_4,            KC_5,           KC_6,           KC_7,           KC_8,            KC_9,            KC_0,          KC_BSPC,        \
  KC_TAB,          KC_Q,            KC_W,         KC_E,            KC_R,            KC_T,           KC_Y,           KC_U,           KC_I,            KC_O,            KC_P,          KC_BSLS,        \
  LT(4, KC_CAPS),  KC_A,            KC_S,         KC_D,            KC_F,            KC_G,           KC_H,           KC_J,           KC_K,            KC_L,            KC_SCLN,       KC_ENT,         \
  KC_LSFT,         KC_Z,            KC_X,         KC_C,            KC_V,            KC_B,           KC_N,           KC_M,           KC_COMM,         KC_DOT,          KC_SLSH,       KC_RSFT,        \
  LCTL_T(KC_LEFT), LGUI_T(KC_DOWN), LCA_T(KC_UP), LALT_T(KC_RGHT),     LT(BLUE, KC_SPC),             LT(RED, KC_SPC),             RALT_T(KC_LEFT), RCAG_T(KC_DOWN), RGUI_T(KC_UP), RCTL_T(KC_RGHT) \
),                                                          /*   | ----------Fn-SPACE----------  | ----------Fn-SPACE----------  |     */

/* 2 - BLUE (LEFT SPACE)
 *                                    .-----------------------------------------------------------------------------------.
 *                                    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |  F11 |  F12 |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |  `   |   7  |   8  |   9  |   +  |   -  | BkSp | Home | PgDn | PgUp | End  | Tab  |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |  '   |   4  |   5  |   6  |   *  |   /  | Del  |   ←  |   ↓  |   ↑  |   →  | Entr |
 *                                    |------+------+------+------+--^^--+------+------+--^^--+------+------+------+------|
 *                                    |Shift |   1  |   2  |   3  |   (  |   )  | Ins  |  C←  |  C↓  |  C↑  |  C→  |Shift |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |  _   |   =  |   0  |   .  |___FnSpace___|   FnSpace   |  Alt |Ct-Alt| GUI  | Ctrl |
 *                                    '-----------------------------------------------------------------------------------'
 */                                                                                    NEED TO ADD [BRACKETS] SOMEWHERE!

[BLUE] = LAYOUT_preonic_2x2u( \
  KC_F1,     KC_F2,   KC_F3,  KC_F4,   KC_F5,        KC_F6,          KC_F7,       KC_F8,        KC_F9,       KC_F10,     KC_F11,      KC_F12,  \
  KC_GRAVE,  KC_P7,   KC_P8,  KC_P9,   KC_PLUS,      KC_MINS,        KC_BSPC,     KC_HOME,      KC_PGDN,     KC_PGUP,    KC_END,      KC_TAB,  \
  KC_QUOT,   KC_P4,   KC_P5,  KC_P6,   KC_ASTR,      KC_SLSH,        KC_DEL,      KC_LEFT,      KC_DOWN,     KC_UP,      KC_RGHT,     _______, \
  _______,   KC_P1,   KC_P2,  KC_P3,   KC_LPRN,      KC_RPRN,        KC_INS,      C(KC_LEFT),   C(KC_DOWN),  C(KC_UP),   C(KC_RGHT),  _______, \
  KC_UNDS,   KC_EQL,  KC_0,   KC_DOT,         _______,                     _______,             _______,     _______,    _______,     _______  \
),                              /*   | _______Fn-SPACE_________|--------Fn-SPACE---------|     */

/* 3 - RED (RIGHT SPACE)
 *                                    .-----------------------------------------------------------------------------------.
 *                                    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |  F11 |  F12 |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |  Tab | Home | PgDn | PgUp | End  | BkSp |  -   |  +   |   7  |   8  |   9  |  `   |
 *                                    | -----+------+------+------+------+------+------+------+------+------+------+------|
 *                                    |  Entr|   ←  |   ↓  |   ↑  |   →  | Del  |  /   |  *   |   4  |   5  |   6  |  '   |
 *                                    | -----+--^^--+------+------+--^^--+------+------+--^^--+------+------+------+------|
 *                                    | Shift|  C←  |  C↓  |  C↑  |  C→  | Ins  |   (  |   )  |   1  |   2  |   3  |Shift |
 *                                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                                    | Ctrl | GUI  |Ct-Alt| Alt  |   FnSpace   |___FnSpace___|  .   |  0   |  =   |  _   |
 *                                    '-----------------------------------------------------------------------------------'
 */

[RED] = LAYOUT_preonic_2x2u( \
  KC_F1,    KC_F2,      KC_F3,      KC_F4,    KC_F5,        KC_F6,       KC_F7,      KC_F8,       KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______,  KC_HOME,    KC_PGDN,    KC_PGUP,  KC_END,       KC_BSPC,     KC_MINS,    KC_PLUS,     KC_7,    KC_8,    KC_9,    KC_GRAVE,\
  KC_ENT,   KC_LEFT,    KC_DOWN,    KC_UP,    KC_RGHT,      KC_DEL,      KC_SLSH,    KC_ASTR,     KC_4,    KC_5,    KC_6,    KC_QUOT, \
  _______,  C(KC_LEFT), C(KC_DOWN), C(KC_UP), C(KC_RGHT),   KC_INS,      KC_LPRN,    KC_RPRN,     KC_1,    KC_2,    KC_3,    _______, \
  _______,  _______,    _______,    _______,            _______,                _______,          KC_DOT,  KC_0,    KC_EQL,  KC_UNDS  \
),                                     /*   |--------Fn-SPACE---------|_________Fn-SPACE_________|     */

// 4 -- FN-CAPSLOCK

[FC] = LAYOUT_preonic_2x2u( \
  C(S(KC_ESC)), RESET,     DEBUG,    KC_NO,      KC_NO,        KC_NO,           KC_BRK,        KC_NLCK,     KC_SLCK, KC_PSCR,  KC_NO,  KC_NO,   \
  KC_NO,        KC_NO,     KC_NO,    KC_NO,      KC_NO,        KC_NO,           KC_NO,         KC_NO,       KC_NO,   KC_NO,    KC_NO,  KC_NO,   \
  _______,      KC_NO,     KC_NO,    KC_NO,      KC_NO,        KC_NO,           KC_NO,         KC_NO,       KC_NO,   KC_NO,    KC_NO,  EEP_RST, \
  KC_NO,        KC_NO,     KC_NO,    KC_NO,      KC_NO,        KC_NO,           KC_NO,         KC_NO,       KC_NO,   KC_NO,    KC_NO,  KC_NO,   \
  DF(QWRT),     DF(COLE),  KC_NO,    KC_NO,            _______,                        _______,             KC_NO,   KC_NO,    KC_NO,  KC_NO    \
)                                          /*   | --------Fn-SPACE--------  | --------Fn-SPACE--------  |     */

};

#ifdef  AUDIO_ENABLE
float start_up[][2] = {
   MUSICAL_NOTE(_B5, 20),
   MUSICAL_NOTE(_B6, 8),
   MUSICAL_NOTE(_DS6, 20),
   MUSICAL_NOTE(_B6, 8),
};

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);

float goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_qwerty);
            #endif
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          break;
        case _COLEMAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          break;
        case _DVORAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dvorak);
            #endif
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          break;
        case _GAME:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_GAME);
          }
          break;
        case _NUMPAD:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dvorak);
            #endif
            persistent_default_layer_set(1UL<<_NUMPAD);
          }
          break;
        case _ARROW:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            persistent_default_layer_set(1UL<<_LOWER);
          }
          break;
        case _LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          break;
        case _RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          break;
        case M_BL:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(start_up);
  #endif
}

#ifdef AUDIO_ENABLE

void play_goodbye_tone(void)
{
  PLAY_SONG(goodbye);
  _delay_ms(150);
}

#endif
