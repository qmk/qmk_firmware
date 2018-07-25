#ifdef QMK_KEYBOARD_H
#include QMK_KEYBOARD_H
#else
#include "ergodox_ez.h"
#endif
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "keymap_german.h"

#include "keymap_nordic.h"
#define ___ KC_TRANSPARENT

enum custom_keycodes
{
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    |   |   1  |   2  |   3  |   4  |   5  |   6  |           |   7  |   8  |   9  |   0  |   +  |   \  |  Bksp  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L1   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ø  |   Æ    |
 * |--------+------+------+------+------+------| T 1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   -  | Enter  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |lCrtl |   |  |  '"` | {[<  |  >]} |                                       | Left |  Up  | Down | Right| Win  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |PRTSRN| Win  |       | Home | End  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Ins  |       | PgUp |        |      |
 *                                 | Space| Bksp |------|       |------|  Enter |Space |
 *                                 |      |      | Del  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
    [0] = LAYOUT_ergodox(
        // left
        KC_EQUAL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, TG(1),
        KC_BSPACE, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, ALL_T(KC_NO),
        CTL_T(KC_GRAVE), KC_QUOTE, LALT(KC_LSHIFT), KC_LEFT, KC_RIGHT,
        ALT_T(KC_APPLICATION), KC_LGUI, KC_HOME,
        KC_SPACE, KC_BSPACE, KC_DEL,
        // right
        KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPACE,
        TG(1), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
        KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOTE,
        MEH_T(KC_NO), KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_ENTER,
        KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_LGUI,
        KC_LALT, CTL_T(KC_ESCAPE),
        TG(3), TG(2), KC_TAB,
        KC_ENTER),

    [1] = LAYOUT_ergodox(KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, ___, ___, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, ___, ___, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_GRAVE, ___, KC_PERC, KC_CIRC, KC_LBRACKET, KC_RBRACKET, KC_TILD, ___, ___, ___, ___, ___, ___, RGB_MOD, ___, ___, RGB_VAD, RGB_VAI, ___, ___, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, ___, KC_UP, KC_7, KC_8, KC_9, KC_ASTR, KC_F12, KC_DOWN, KC_4, KC_5, KC_6, KC_PLUS, ___, ___, KC_AMPR, KC_1, KC_2, KC_3, KC_BSLASH, ___, ___, KC_DOT, KC_0, KC_EQUAL, ___, RGB_TOG, RGB_SLD, ___, ___, RGB_HUD, RGB_HUI),

    [2] = LAYOUT_ergodox(___, ___, ___, ___, ___, ___, ___, ___, ___, ___, KC_MS_UP, ___, ___, ___, ___, ___, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, KC_MS_BTN1, KC_MS_BTN2, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, KC_MEDIA_PLAY_PAUSE, ___, ___, ___, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, ___, ___, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, ___, ___, ___, ___, ___, ___, ___, KC_WWW_BACK),

    [3] = LAYOUT_ergodox(RGB_MOD, RGB_SLD, ___, ___, ___, ___, ___, RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, ___, ___, ___, RGB_TOG, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(1)};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id)
  {
  case 0:
    if (record->event.pressed)
    {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    break;
  }
  return MACRO_NONE;
};

void matrix_init_user(void)
{
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  // dynamically generate these.
  case EPRM:
    if (record->event.pressed)
    {
      eeconfig_init();
    }
    return false;
    break;
  case VRSN:
    if (record->event.pressed)
    {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
    break;
  case RGB_SLD:
    if (record->event.pressed)
    {
      rgblight_mode(1);
    }
    return false;
    break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state)
{

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer)
  {
  case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#else
    rgblight_init();
#endif
    break;
  case 1:
    ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
    break;
  case 2:
    ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
    break;
  case 3:
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
    break;
  case 4:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
    break;
  case 5:
    ergodox_right_led_1_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
    break;
  case 6:
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
    break;
  case 7:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
    break;
  default:
    break;
  }

  return state;
};
