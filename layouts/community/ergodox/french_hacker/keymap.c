#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_french.h"

#define BASE 0 // default Colemak Mod-DH layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define ACC 3 // accented characters

#define QCOPY 0 // Qubes OS VM to VM copy
#define QPASTE 1 // Qubes OS VM to VM paste
#define M_ACIRC 2 // â
#define M_ECIRC 3 // ê
#define M_ICIRC 4 // î
#define M_OCIRC 5 // ô
#define M_UCIRC 6 // û
#define M_YCIRC 7 // ŷ
#define M_AUMLT 8 // ä
#define M_EUMLT 9 // ë
#define M_IUMLT 10 // ï
#define M_OUMLT 11 // ö
#define M_UUMLT 12 // ü
#define M_YUMLT 13 // ÿ

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base Colemak Mod-DH layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   F  |   P  |   B  | TO(0)|           |TO(2) |   J  |   L  |   U  |   Y  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Tab    |   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  | Bcksp  |
 * |--------+------+------+------+------+------| TO(1)|           |OSL(3)|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |   ,  |   .  |   :  | Rshift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ins  | Caps | Left | Right| MO(2)|                                       | MO(2)| Down |  Up  | PgDn | PgUp  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |QCopy | Ralt |       | Ralt |QPaste|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       | End  |      |      |
 *                                 | Space| Ctrl |------|       |------| Ctrl |Enter |
 *                                 |      |      | LAlt |       | LAlt |      |      |
 *                                 `--------------------'       `--------------------'
 */
  // If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_TRNS,
        KC_TRNS,        FR_Q,         FR_W,   KC_F,   KC_P,   KC_B,   TO(BASE),
        KC_TAB,         FR_A,         KC_R,   KC_S,   KC_T,   KC_G,
        KC_LSFT,        FR_Z,         KC_X,   KC_C,   KC_D,   KC_V,   TO(SYMB),
        KC_INS,         KC_CAPS,      KC_LEFT,KC_RIGHT, MO(SYMB),
                                               M(QCOPY),          KC_RALT,
                                                                  KC_HOME,
                                               KC_SPC,KC_LCTRL,   KC_LALT,
        // right hand
        KC_TRNS,     KC_6,    KC_7,   KC_8,     KC_9,    KC_0,             KC_TRNS,
        TO(MDIA),    KC_J,    KC_L,   KC_U,     KC_Y,    FR_SCLN,          KC_TRNS,
                     FR_M,    KC_N,   KC_E,     KC_I,    KC_O,             KC_BSPC,
        OSL(ACC),    KC_K,    KC_H,   FR_COMM,  FR_DOT,  FR_COLN,          KC_RSFT,
        MO(SYMB),    KC_DOWN, KC_UP,  KC_PGDN,  KC_PGUP,

        KC_RALT,        M(QPASTE),
        KC_END,
        KC_LALT,KC_RCTL, KC_ENT
                  ),


/* Keymap 1: Symbol Layer
 * // TODO missing: ¤
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   §  |   <  |   {  |   \  |   ~  |      |           |      |   %  |   @  |   }  |  >   |  µ   |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   '  |   =  |   -  |   (  |   +  |------|           |------|   *  |   )  |   _  |  /   |   "  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   `  |   ?  |   #  |   [  |   |  |      |           |      |   &  |   ]  |   $  |   !  |   ^  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   €  |   £  |   $  |      |      |                                       |      |      |      |   ß  |      |
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
       M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,FR_SECT,FR_LESS,  FR_LCBR,FR_BSLS,FR_TILD,KC_TRNS,
       KC_TRNS,FR_APOS,FR_EQL, FR_MINS,FR_LPRN,FR_PLUS,
       KC_TRNS,FR_GRV,FR_QUES,FR_HASH,FR_LBRC,FR_PIPE,KC_TRNS,
          FR_EURO,FR_PND,FR_DLR,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, FR_PERC, FR_AT,  FR_RCBR, FR_GRTR, FR_MU, KC_F12,
                FR_ASTR,   FR_RPRN, FR_UNDS, FR_SLSH, FR_QUOT, KC_TRNS,
       KC_TRNS, FR_AMP,  FR_RBRC, FR_DLR,  FR_EXLM,  FR_CIRC, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS,  ALGR(KC_S),  KC_TRNS,
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
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Lclk | Rclk |      |      |  Play  |
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
                 KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap 3: accented characters
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  à   |  â   |  ä   |      |      |           |      |      |      |  î   |  ï   |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  é   |  è   |  ê   |  ë   |      |------|           |------|      |      |  ô   |  ö   |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |  ù   |  û   |  ü   |      |      |           |      |      |      |  ŷ   |  ÿ   |      |        |
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
// ACCENTED CHARACTERS
[ACC] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS, FR_AGRV, M(M_ACIRC),  M(M_AUMLT), KC_TRNS, KC_TRNS,
       KC_TRNS, FR_EACU, FR_EGRV, M(M_ECIRC),  M(M_EUMLT), KC_TRNS,
       KC_TRNS, KC_TRNS, FR_UGRV, M(M_UCIRC),  M(M_UUMLT), KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, M(M_ICIRC), M(M_IUMLT), KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, M(M_OCIRC), M(M_OUMLT), KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, M(M_YCIRC), M(M_YUMLT), KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
  case QCOPY:
    if (record->event.pressed) {
      return MACRO(I(255),
                   D(LCTRL),
                   T(C),
                   D(LSFT),
                   T(C),
                   U(LCTRL),
                   U(LSFT),
                   END);
    }
    break;
  case QPASTE:
    if (record->event.pressed) {
      return MACRO(I(255),
                   D(LCTRL),
                   D(LSFT),
                   T(V),
                   U(LCTRL),
                   T(INS),
                   U(LSFT),
                   END);
    }
    break;
  case M_ACIRC:
    if (record->event.pressed) {
      return MACRO(T(LBRC), // FR_CIRC
                   T(Q), // FR_A
                   END);
    }
    break;
  case M_ECIRC:
    if (record->event.pressed) {
      return MACRO(T(LBRC), // FR_CIRC
                   T(E),
                   END);
    }
    break;
  case M_UCIRC:
    if (record->event.pressed) {
      return MACRO(T(LBRC), // FR_CIRC
                   T(U),
                   END);
    }
    break;
  case M_ICIRC:
    if (record->event.pressed) {
      return MACRO(T(LBRC), // FR_CIRC
                   T(I),
                   END);
    }
    break;
  case M_OCIRC:
    if (record->event.pressed) {
      return MACRO(T(LBRC), // FR_CIRC
                   T(O),
                   END);
    }
    break;
  case M_YCIRC:
    if (record->event.pressed) {
      return MACRO(T(LBRC), // FR_CIRC
                   T(Y),
                   END);
    }
    break;
  case M_AUMLT:
    if (record->event.pressed) {
      return MACRO(D(LSFT),
                   T(LBRC),
                   U(LSFT),
                   T(Q),
                   END);
    }
    break;
  case M_EUMLT:
    if (record->event.pressed) {
      return MACRO(D(LSFT),
                   T(LBRC),
                   U(LSFT),
                   T(E),
                   END);
    }
    break;
  case M_UUMLT:
    if (record->event.pressed) {
      return MACRO(D(LSFT),
                   T(LBRC),
                   U(LSFT),
                   T(U),
                   END);
    }
    break;
  case M_IUMLT:
    if (record->event.pressed) {
      return MACRO(D(LSFT),
                   T(LBRC),
                   U(LSFT),
                   T(I),
                   END);
    }
    break;
  case M_OUMLT:
    if (record->event.pressed) {
      return MACRO(D(LSFT),
                   T(LBRC),
                   U(LSFT),
                   T(O),
                   END);
    }
    break;
  case M_YUMLT:
    if (record->event.pressed) {
      return MACRO(D(LSFT),
                   T(LBRC),
                   U(LSFT),
                   T(Y),
                   END);
    }
    break;

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
    case SYMB:
      ergodox_right_led_1_on();
      break;
    case MDIA:
      ergodox_right_led_2_on();
      break;
    case ACC:
      ergodox_right_led_3_on();
      break;
    default:
      // none
      break;
    }

};
