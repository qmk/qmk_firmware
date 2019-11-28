#include QMK_KEYBOARD_H
#include "keymap_nordic.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _MQWERTY 5
#define _MLOWER 8
#define _MRAISE 9
#define _ADJUST 16

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MQWERTY,
  MLOWER,
  MRAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   <  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   .  |   ,  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |AltGr |Lower | Space| Enter|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    NO_PLUS, KC_BSPC, \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    NO_AM,   \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NO_AE,   NO_OSLH, \
  KC_LSFT, NO_LESS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_DOT,  KC_COMM, NO_MINS, \
  KC_LCTL, KC_LALT, KC_LGUI, KC_ALGR, LOWER,   KC_SPC,  KC_ENT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   @  |   £  |   $  |      |      |   {  |   [  |   ]  |   }  |   \  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |VolUp |      |      |  ~   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |LastS |PauseP|NextS |      |  *   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   |  |      |      |      |      |      |      |VolDwn|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |Bspc  |      |      |PgDn  |PgUp  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  _______, NO_AT,   NO_PND,  NO_DLR,  _______, _______, NO_LCBR, NO_LBRC, NO_RBRC, NO_RCBR, NO_BSLS, KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______, _______, NO_TILD, \
  _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, LSFT(KC_BSLS), \
  _______, NO_PIPE, _______, _______, _______, _______, _______, _______, KC_VOLD, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_BSPC, _______, _______, KC_PGDN, KC_PGUP, _______  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   !  |   "  |   #  |   ¤  |   %  |   &  |   /  |   (  |   )  |   =  |   ?  | Ins  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Mouse^|      |      |      |      |ScrlUp|      |      |  ^   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Mouse<|MouseV|Mouse>|      |      |MLC   |MMC   |MRC   |   '  |  ¨   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   >  |      |      |      |      |      |      |ScrlDown| :  |  ;   |  _   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |Bspc  |      |      |      | PgDn | PgUp |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  LSFT(KC_1),NO_QUO2,LSFT(KC_3), NO_BULT,LSFT(KC_5), NO_AMPR, NO_SLSH, NO_LPRN, NO_RPRN, NO_EQL,  NO_QUES, KC_INS, \
  _______, _______, _______, KC_MS_U, _______, _______, _______, _______, KC_WH_U, _______, _______, NO_CIRC, \
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, NO_APOS, NO_QUOT, \
  _______, NO_GRTR, _______, _______, _______, _______, _______, _______, KC_WH_D, NO_COLN, NO_SCLN, NO_UNDS, \
  _______, _______, _______, _______, _______, KC_BSPC, _______, _______, _______, KC_PGDN, KC_PGUP, _______  \
),

/* Mac Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   <  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   .  |   ,  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |AltGr |Lower | Space| Enter|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_MQWERTY] = LAYOUT_preonic_grid( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    NO_PLUS, KC_BSPC, \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    NO_AM,   \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NO_AE,   NO_OSLH, \
  KC_LSFT, NO_LESS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_DOT,  KC_COMM, NO_MINS, \
  KC_LCTL, KC_LALT, KC_LGUI, KC_ALGR, MLOWER,  KC_SPC,  KC_ENT,  MRAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Mac Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   @  |   £  |   $  |      |      |   {  |   [  |   ]  |   }  |   \  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |VolUp |      |      |  ~   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |LastS |PauseP|NextS |      |  *   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   |  |      |      |      |      |      |      |VolDwn|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |Bspc  |      |      |PgDn  |PgUp  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MLOWER] = LAYOUT_preonic_grid( \
  _______, NO_AT,   NO_PND,  NO_DLR,  _______, _______, LSFT(LALT(KC_8)), NO_LBRC, NO_RBRC, LSFT(LALT(KC_9)), LSFT(LALT(KC_7)), KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______, _______, NO_TILD, \
  _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, LSFT(KC_BSLS), \
  _______, NO_LBRC, _______, _______, _______, _______, _______, _______, KC_VOLD, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, KC_BSPC, _______, _______, KC_PGDN, KC_PGUP, _______  \
),

/* Mac Raise
 * ,-----------------------------------------------------------------------------------.
 * |   !  |   "  |   #  |   ¤  |   %  |   &  |   /  |   (  |   )  |   =  |   ?  | Ins  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Mouse^|      |      |      |      |ScrlUp|      |      |  ^   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Mouse<|MouseV|Mouse>|      |      |MLC   |MMC   |MRC   |   '  |  ¨   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   >  |      |      |      |      |      |      |ScrlDown| :  |  ;   |  _   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |Bspc  |      |      |      | PgDn | PgUp |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MRAISE] = LAYOUT_preonic_grid( \
  LSFT(KC_1),NO_QUO2,LSFT(KC_3), NO_BULT,LSFT(KC_5), NO_AMPR, NO_SLSH, NO_LPRN, NO_RPRN, NO_EQL,  NO_QUES, KC_INS, \
  _______, _______, _______, KC_MS_U, _______, _______, _______, _______, KC_WH_U, _______, _______, NO_CIRC, \
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, NO_APOS, NO_QUOT, \
  _______, NO_GRTR, _______, _______, _______, _______, _______, _______, KC_WH_D, NO_COLN, NO_SCLN, NO_UNDS, \
  _______, _______, _______, _______, _______, KC_BSPC, _______, _______, _______, KC_PGDN, KC_PGUP, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | Reset|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Rshift|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |MusOn |MusOff|      |      |      |      |NrmMode|MacMode|    |      | Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, \
  _______, MU_ON,   MU_OFF,  _______, _______, _______, _______, TO(0),   TO(5),   _______, _______, RESET,   \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)


};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_D5, 8},
  {NOTE_E6, 8},
  {NOTE_D6, 8},
  {NOTE_E5, 8}
};

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case MQWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_MQWERTY);
          }
          return false;
          break;
        case MLOWER:
          if (record->event.pressed) {
            layer_on(_MLOWER);
            update_tri_layer(_MLOWER, _MRAISE, _ADJUST);
          } else {
            layer_off(_MLOWER);
            update_tri_layer(_MLOWER, _MRAISE, _ADJUST);
          }
          return false;
          break;
        case MRAISE:
          if (record->event.pressed) {
            layer_on(_MRAISE);
            update_tri_layer(_MLOWER, _MRAISE, _ADJUST);
          } else {
            layer_off(_MRAISE);
            update_tri_layer(_MLOWER, _MRAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif
