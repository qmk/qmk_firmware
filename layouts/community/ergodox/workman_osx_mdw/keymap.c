#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
// readme
// This keyboard layout is based on the [Workman Dead layout](https://github.com/ojbucao/Workman/tree/master/mac#workman-dead-for-programmers), which uses the comma as a dead key to trigger a second layer.
// Since I have more keys at my disposal on the ErgoDox, I moved the dead key to the bottom right. There are still a lot of
// blanks so still discovering what I like.
// If you aren't familiar with a dead key, the idea is that you tap the dead key which switches the layout. the next key you hit
// triggers the key you pressed AND switches the layout back to the original. For now I do this with a super kludgey macro and I
// look forward to learning about a more elegant way to do the same thing. Until then, this will have to do.


// TODO: Define layer names that make sense for the ErgoDox EZ.
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define DEAD 3 // dead version of the symbols layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   D  |   R  |   W  |   B  |  L1  |           |  L1  |   J  |   F  |   U  |   P  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Hyper  |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   '    |
 * |--------+------+------+------+------+------|      |           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      | CTRL |  OPT |  CMD |                                       | Left | Down |  Up  | Right|  L3  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Bckspc| Space|------|       |------| Space  |Enter |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,         KC_Q,         KC_D,   KC_R,   KC_W,   KC_B,   TG(1),
        ALL_T(KC_ESC),  KC_A,         KC_S,   KC_H,   KC_T,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_M,   KC_C,   KC_V,   KC_NO,
        KC_NO,          KC_NO,        KC_LCTL,KC_LALT,KC_LGUI,
                                              KC_NO,  KC_NO,
                                                              KC_HOME,
                                               KC_BSPC,KC_SPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             TG(1),       KC_J,   KC_F,   KC_U,   KC_P,   KC_SCLN,          KC_BSLS,
                          KC_Y,   KC_N,   KC_E,   KC_O,   KC_I,             KC_QUOT,
             MEH_T(KC_NO),KC_K,   KC_L,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,          F(4),
             KC_NO,        KC_NO,
             KC_PGUP,
             KC_PGDN,KC_SPC,KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   %  |   &  |   ?  |   +  |   @  |      |           |      |   $  |   _  |   [  |   ]  |   !  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   /  |   (  |   =  |   0  |   {  |------|           |------|   }  |   1  |   *  |   )  |   -  |   "    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   |  |      |           |      |   \  |   2  |   3  |   4  |   5  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_F1,    KC_F2,    KC_F3,          KC_F4,        KC_F5,          KC_TRNS,
       KC_TRNS,   KC_PERC,  KC_AMPR,  LSFT(KC_SLSH),  LSFT(KC_EQL), KC_AT,          KC_TRNS,
       KC_TRNS,   KC_SLSH,  KC_LPRN,  KC_EQL,         KC_0,     LSFT(KC_LBRC),
       KC_TRNS,   KC_6,     KC_7,     KC_8,           KC_9,     KC_PIPE,        KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,          KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
       KC_TRNS, KC_DLR,         KC_UNDERSCORE,  KC_LBRC,  KC_RBRC,  KC_EXLM,  KC_F12,
                KC_RCBR,        KC_1,     KC_ASTR,  KC_RPRN,  KC_MINS,  KC_QUOT,
       KC_TRNS, KC_SLSH,        KC_2,     KC_3,     KC_4,     KC_5,     KC_TRNS,
                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 4: Dead Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  %   |   &  |   ?  |   +  |   @  |      |           |      |   $  |   _  |   [  |   ]  |   !  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   /  |   (  |   =  |   0  |   {  |------|           |------|   }  |   1  |   *  |   )  |   -  |   "    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   |  |      |           |      |   \  |   2  |   3  |   4  |   5  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[DEAD] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_F1,    KC_F2,    KC_F3,      KC_F4,    KC_F5,          KC_TRNS,
       KC_TRNS,   M(100),   M(101),   M(102),     M(103),   M(104),         KC_TRNS,
       KC_TRNS,   M(109),  M(110),  M(111),       M(112),   M(113),
       KC_TRNS,   M(120),     M(121),     M(122),           M(123),     M(124),        KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
       KC_TRNS, M(105),   M(106),   M(107),   M(108),   M(130),   KC_F12,
                M(114),   M(115),   M(116),   M(117),   M(118),   M(119),
       KC_TRNS, M(125),   M(126),   M(127),   M(128),   M(129),   KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [2] = ACTION_LAYER_ON(BASE,0),                       // FN2 - Go back to the base layer
    [3] = ACTION_LAYER_ON(DEAD,0),
    [4] = ACTION_LAYER_TOGGLE(DEAD),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
          break;
        case 100:
          layer_clear();
          return MACRODOWN(D(LSFT), T(5), U(LSFT), T(FN4), END);
          break;
        case 101:
          layer_clear();
          return MACRODOWN(D(LSFT), T(7), U(LSFT), T(FN4), END);
          break;
        case 102:
          layer_clear();
          return MACRODOWN(D(LSFT), T(SLSH), U(LSFT), T(FN4), END);
          break;
        case 103:
          layer_clear();
          return MACRODOWN(D(LSFT), T(EQL), U(LSFT), T(FN4), END);
          break;
        case 104:
          layer_clear();
          return MACRODOWN(D(LSFT), T(2), U(LSFT), T(FN4), END);
          break;
        case 105:
          layer_clear();
          return MACRODOWN(D(LSFT), T(4), U(LSFT), T(FN4), END);
          break;
        case 106:
          layer_clear();
          return MACRODOWN(D(LSFT), T(MINS), U(LSFT), T(FN4), END);
          break;
        case 107:
          layer_clear();
          return MACRODOWN(T(LBRC), T(FN4), END);
          break;
        case 108:
          layer_clear();
          return MACRODOWN(T(RBRC), T(FN4), END);
          break;
        case 130:
          layer_clear();
          return MACRODOWN(D(LSFT), T(1), U(LSFT), T(FN4), END);
          break;
        case 109:
          layer_clear();
          return MACRODOWN(T(SLSH), T(FN4), END);
          break;
        case 110:
          layer_clear();
          return MACRODOWN(D(LSFT), T(9), U(LSFT), T(FN4), END);
          break;
        case 111:
          layer_clear();
          return MACRODOWN(T(EQL), T(FN4), END);
          break;
        case 112:
          layer_clear();
          return MACRODOWN(T(0), T(FN4), END);
          break;
        case 113:
          layer_clear();
          return MACRODOWN(D(LSFT), T(LBRC), U(LSFT), T(FN4), END);
          break;
        case 114:
          layer_clear();
          return MACRODOWN(D(LSFT), T(RBRC), U(LSFT), T(FN4), END);
          break;
        case 115:
          layer_clear();
          return MACRODOWN(T(1), T(FN4), END);
          break;
        case 116:
          layer_clear();
          return MACRODOWN(D(LSFT), T(8), U(LSFT), T(FN4), END);
          break;
        case 117:
          layer_clear();
          return MACRODOWN(D(LSFT), T(0), U(LSFT), T(FN4), END);
          break;
        case 118:
          layer_clear();
          return MACRODOWN(T(MINS), T(FN4), END);
          break;
        case 119:
          layer_clear();
          return MACRODOWN(D(LSFT), T(QUOT), U(LSFT), T(FN4), END);
          break;
        case 120:
          layer_clear();
          return MACRODOWN(T(6), T(FN4), END);
          break;
        case 121:
          layer_clear();
          return MACRODOWN(T(7), T(FN4), END);
          break;
        case 122:
          layer_clear();
          return MACRODOWN(T(8), T(FN4), END);
          break;
        case 123:
          layer_clear();
          return MACRODOWN(T(9), T(FN4), END);
          break;
        case 124:
          layer_clear();
          return MACRODOWN(D(LSFT), T(BSLS), U(LSFT), T(FN4), END);
          break;
        case 125:
          layer_clear();
          return MACRODOWN(T(BSLS), T(FN4), END);
          break;
        case 126:
          layer_clear();
          return MACRODOWN(T(2), T(FN4), END);
          break;
        case 127:
          layer_clear();
          return MACRODOWN(T(3), T(FN4), END);
          break;
        case 128:
          layer_clear();
          return MACRODOWN(T(4), T(FN4), END);
          break;
        case 129:
          layer_clear();
          return MACRODOWN(T(5), T(FN4), END);
          break;

        default:
        return MACRO_NONE;
      }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
