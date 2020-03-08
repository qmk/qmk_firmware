#include QMK_KEYBOARD_H
#include "keymap_nordic.h"
enum layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _FN
};

enum custom_keycodes {
    PRKL = SAFE_RANGE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FN MO(_FN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default
 * ,-----------------------------------------------------------------------------------.------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  ¨^  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|------|
 * |  Tab |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   | Entr |
 * |------+------+------+------+------+------|------+------+------+------+------+------|------'
 * | Shift|   Z  |   X  |   C  |   V  |    Space    |   B  |   N  |   M  |   ,  |   .  |
 * |------+------+------+------+------+------+------+------+------+------+------+------'
 */
[_DEFAULT] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,
    KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    LT(_LOWER, KC_SPC),  _______,    KC_B,    KC_N,    KC_M,
    KC_P,    NO_QUOT, KC_BSPC, NO_AE,   NO_OSLH, LT(_FN, KC_ENT), KC_COMM, LT(_RAISE, KC_DOT)
),

/* Lower - Numbers and some symbols
 * ,------------------------------------------------------------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0   |  +  | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------'
 * |      |      |      |      |      |             |      |      |      |  -   |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------'
 */
[_LOWER] = LAYOUT_all(
    KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    NO_PLUS, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NO_MINS, _______
),

/* Raise - AltGred Characters and more symbols
 * ,------------------------------------------------------------------------------------------.
 * |   ~  |   >  |   @  |   £  |   $  |   %  |   &  |   |  |   [  |   ]  |   ≈  | ?    | {    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------|
 * |      |      |      |  UP  |      |      |      |      |      |      |      |      | }    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------'
 * |      |   <  | LEFT | DOWN | RIGHT|             |      |      |      |      |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------'
 */
[_RAISE] = LAYOUT_all(
    NO_TILD, NO_SECT, NO_AT,   NO_PND,  NO_DLR,  KC_PERC, NO_AMPR, NO_LCBR, NO_LBRC, NO_RBRC, NO_RCBR, NO_QUES, LSFT(NO_LBRC),
    _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, LSFT(NO_RBRC),
    _______, NO_HALF, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______
),

 /* FN
 * ,------------------------------------------------------------------------------------------.
 * |RESET |   F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F7 |   F8 |   F9 |  F10 |  F11 | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------|
 * |      |RGB_P |RGB_HD|RGB_HI| VOL- | PREV | NEXT | VOL+ |      |      |      | PRKL |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------'
 * | RGB_M|RGB_VD|RGB_VI|RGB_TG|      | PLAY/PAUSE  |      |      |      |LCA(DEL)|    |
 * `------+------+------+------+------+------+------+------+------+------+------+------'
 */
[_FN] = LAYOUT_all(
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, RGB_M_P, RGB_HUD, RGB_HUI, KC_VOLD, KC_MPRV, KC_MNXT, KC_VOLU, _______, _______, _______, PRKL,    _______,
    RGB_MOD, RGB_VAD, RGB_VAI, RGB_TOG, _______, KC_MPLY, _______, _______, _______, _______, LCA(KC_DEL), _______
),


};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_TAB);
    } else {
      tap_code(KC_PGUP);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PRKL:
      if (record->event.pressed) {
        //When PRKL is pressed, print out the holy power word of our people
        SEND_STRING("PERKELE");
      }
      break;
  }
  return true;
};
