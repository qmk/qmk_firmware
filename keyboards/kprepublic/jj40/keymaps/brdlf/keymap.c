/* Copyright 2022 Abigail Fassl
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

#define RAISE    MO(_RAISE)
#define LOWER    MO(_LOWER)
#define FUN      MO(_FUNC)
#define MOUSE    MO(_MOUSE)

enum layers {
    _QWERTY = 0,
    _FUNC,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
    _NUMPAD
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc* |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Ent  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shft |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  | Shft |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Func |Lower |Space | Bksp |Raise | DEL  | Bksl | NUM  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  LT(_NUMPAD, KC_ESC), KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,        KC_ENT    ,
  KC_TAB,              KC_A,    KC_S,    KC_D,  KC_F,   KC_G,   KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN,     KC_QUOT   ,
  KC_LSFT,             KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH,     KC_RSFT   ,
  KC_LCTL,             KC_LALT, KC_LGUI, FUN,   LOWER,  KC_SPC, KC_BSPC, RAISE, KC_DEL,  KC_BSLS, TG(_NUMPAD), KC_RCTL
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  1!  |  2"  |  3£  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  |  ~   |INSERT|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |   _  |   -  |   +  |  =   |  \|  |  [{  |  ]}  |      |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  ___ |  ___ | ___  | ___  |  ___ |Space | Bksp |Mouse | DEL  |      |      |      | 
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_ortho_4x12(
  KC_F1,     KC_F2,        KC_F3,    KC_F4,         KC_F5,   KC_F6,        KC_F7,  KC_F8,    KC_F9,   KC_F10,  KC_F11,       KC_F12    ,
  KC_1,      KC_2,         KC_3,     KC_4,          KC_5,    KC_6,         KC_7,   KC_8,     KC_9,    KC_0,    LSFT(KC_GRV), KC_INSERT ,
  KC_LSFT,   KC_NO,        KC_NO,    LSFT(KC_MINS), KC_MINS, LSFT(KC_EQL), KC_EQL, KC_BSLS,  KC_LBRC, KC_RBRC, KC_NO,        KC_RSFT   ,
  _______,   _______,      _______,  _______,       _______, _______,      _______, _______, _______, _______, _______,      _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  1!  |  2@  |  3#  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  | DEL  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  !   |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |WrdDel|WrdBks|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift| PSCRN|  |   |  \|  |   _  |   -  |   +  |  =   |      |BL ON | BLSP |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower |      |      | ADJ  |      | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_1,    KC_2,    KC_3,       KC_4,    KC_5,          KC_6,       KC_7,         KC_8,    KC_9,    KC_0,    KC_DEL,       KC_BSPC       ,
  KC_EXLM, KC_AT,   KC_HASH,    KC_DLR,  KC_PERC,       KC_CIRC,    KC_AMPR,      KC_ASTR, KC_LPRN, KC_RPRN, LCTL(KC_DEL), LCTL(KC_BSPC) ,
  KC_LSFT, KC_PSCR, S(KC_NUHS), KC_BSLS, LSFT(KC_MINS), KC_MINS,    LSFT(KC_EQL), KC_EQL,  _______, BL_ON,   BL_STEP,      KC_RSFT       ,    
  _______, _______, _______,    _______, _______,       _______,    _______,      _______, _______, KC_VOLD, KC_VOLU,      KC_MPLY
),

/* Raise 
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  \|  |      |  [   |   ]  |      |      | PGUP | HOME |PGDOWN|      |PRNTSC|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   |  |  _   |  =   |  (   |   )  |      |      | HOME |  UP  | END  |      |ZOOM +|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |  -   |  +   |  {   |   }  |      |  |<  | LEFT | DOWN |RIGHT |  >|  |ZOOM -|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | ADJ  |      |CtrlBk|Raise |CtrlDl|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,        KC_BSLS,       KC_NO,        KC_LBRC,       KC_RBRC,       KC_NO,   KC_NO,         KC_PGUP, KC_HOME,      KC_PGDN,   KC_NO,          KC_PSCR            ,
  LSFT(KC_BSLS), LSFT(KC_MINS), KC_EQL,       LSFT(KC_9),    LSFT(KC_0),    KC_NO,   KC_NO,         KC_HOME, KC_UP,        KC_END,    KC_NO,          LCTL(LSFT(KC_EQL)) ,
  LSFT(KC_GRV),  KC_MINS,       LSFT(KC_EQL), LSFT(KC_LBRC), LSFT(KC_RBRC), KC_NO,   LCTL(KC_LEFT), KC_LEFT, KC_DOWN,      KC_RIGHT,  LCTL(KC_RIGHT), LCTL(KC_MINS)      ,
  _______,       _______,       _______,      _______,       _______,       KC_SPC,  LCTL(KC_BSPC), _______, LCTL(KC_DEL), _______,   _______,        _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|      |      |  BLON| BLOFF|      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |  RGB | MODE |  VAD |  VAI |      |      | Vol- | Vol+ | Play |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  HUD |  HUI |  SAD |  SAI |      |      | Prev | Next | Mute |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  QK_BOOT,   KC_NO,   KC_NO,   BL_ON,   BL_OFF,  KC_NO,   KC_NO,   _______,             _______,             _______,             _______, KC_DEL  ,
  KC_CAPS, RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, KC_NO,   KC_NO,   KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,     KC_MEDIA_PLAY_PAUSE, _______, _______ ,
  KC_NO,   RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, KC_NO,   KC_NO,   KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE,       _______, _______ ,
  _______, _______, _______, _______, _______, _______, _______, _______,             _______,             _______,             _______, _______
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |      |      |      |      |      | WH_L | WH_UP| BTN3 | WH_D | WH_R |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ACC0 | ACC1 | ACC2 |      |      |      |      | BTN1 |  UP  | BTN2 |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ACC0 | ACC1 | ACC2 |      |      |      |      | LEFT | DOWN |RIGHT |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_ortho_4x12(
    KC_ESC ,      _______,      _______,      _______, _______, _______,   KC_MS_WH_LEFT, KC_MS_WH_UP, KC_MS_BTN3, KC_MS_WH_DOWN, KC_MS_WH_RIGHT, _______,
    KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, _______,   _______,       KC_MS_BTN1,  KC_MS_UP,   KC_MS_BTN2,    _______,        _______,
    KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, _______,   _______,       KC_MS_LEFT,  KC_MS_DOWN, KC_MS_RIGHT,   _______,        _______,
    _______,      _______,      _______,      _______, _______, _______,   _______,       _______,     _______,    _______,       _______,        _______
),

/* Num Pad
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |      |      |      |      |      |NMLOCK|   7  |   8  |   9  |   /  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  |   +  |  -   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   0  |   .  |   ,  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______, KC_NUM,  KC_7, KC_8,      KC_9,    KC_KP_SLASH,    _______        ,
    _______, _______, _______, _______, _______, _______, _______, KC_4, KC_5,      KC_6,    KC_KP_ASTERISK, _______        ,
    _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2,      KC_3,    KC_KP_PLUS,     KC_KP_MINUS    ,
    _______, _______, _______, _______, _______, _______, _______, KC_0, KC_KP_DOT, KC_COMM, _______,        _______
)

};

layer_state_t layer_state_set_user (layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    state = update_tri_layer_state(state, _FUNC, _RAISE, _MOUSE);
    return state;
}