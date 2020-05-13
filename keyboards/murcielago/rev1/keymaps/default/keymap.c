#include QMK_KEYBOARD_H

enum layers {
    BASE,
    _RAISE,
    _LOWER,
    _POWER
};

#define PRE_WRD LCTL(KC_LEFT)  // jump to next word
#define NXT_WRD LCTL(KC_RGHT)  // jump to previous word

#define NXT_WDL LCTL(KC_DEL)   // delete next word
#define PRE_WDL LCTL(KC_BSPC)  // delete previous word

#define KC_EURO ALGR(KC_5)
#define LA_CAP MT(MOD_LALT, KC_CAPS) // Left alt on hold, caps lock on tap
#define RA_ENT MT(MOD_RALT, KC_ENT)  // Right alt on hold, enter on tap

#define RAISE MO(_RAISE) // Raise layer access
#define LOWER MO(_LOWER) // Lower layer access
#define POWER MO(_POWER) // Power layer access (raise and lower)

/*
 * This default keymap is aimed at users of the US international layout
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* BASE
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |  =+  |  1!  |  2@  |  3#  |  4$  |  5%  |                        |  6^  |  7&  |  8*  |  9(  |  0)  |  -_  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |  [{  |  Q   |  W   |  E   |  R   |  T   |                        |   Y  |   U  |   I  |   O  |   P  |  }]  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | Del  |  A   |  S   |  D   |  F   |  G   |                        |   H  |   J  |   K  |   L  |  ;:  |  '"  |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       | Sft  |  Z   |  X   |  C   |  V   |  B   | GEsc |          |  Tab |   N  |   M  |  ,<  |  .>  |  /?  |  Sft |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  | LA/CL| LGUI |LOWER | Back | Ctrl |                |RA/Ent|Space |RAISE | RGUI | Play |
   *                  `----------------------------------'                `----------------------------------'
   */
  [BASE] = LAYOUT( /* qwerty */
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_LBRC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,
    KC_DEL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GESC, KC_TAB,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
             LA_CAP,  KC_LGUI, LOWER,   KC_BSPC, KC_LCTL,                   RA_ENT,  KC_SPC,  RAISE,   KC_RGUI, KC_MPLY
  ),

  /* RAISE
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       | RST  |  F1  |  F2  |  F3  |  F4  | F5   |                        | F6   |  F7  |  F8  |  F9  | F10  | F11  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |  !   |  @   |  #   |  $   |  %   |                        |      |PRE W |  UP  |NXT W |      | F12  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |  |   |  (   |  [   |  {   |  <   |                        |      | LEFT | DOWN |RIGHT |      |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |  ~   |  =   |  +   |  \   |      |      |          |      |      |DEL PW| Ins  |DEL NW|      |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |POWER |      |      |                |      |      |      |      |      |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_RAISE] = LAYOUT( /* raise layer */
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   XXXXXXX, PRE_WRD, KC_UP,   NXT_WRD, XXXXXXX, KC_F12,
    _______, KC_PIPE, KC_LPRN, KC_LBRC, KC_LCBR, KC_LABK,                   XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,  
    _______, KC_TILD, KC_EQL,  KC_PLUS, KC_BSLS, XXXXXXX, _______, _______, XXXXXXX, PRE_WDL, KC_INS,  NXT_WDL, XXXXXXX, _______,
             _______, _______, POWER,   _______, _______,                   _______, _______, _______, _______, _______
  ),

  /* LOWER
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       | RST  |  F1  |  F2  |  F3  |  F4  | F5   |                        | F6   |  F7  |  F8  |  F9  | F10  | F11  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      |PRE W |  UP  |NXT W |      |                        |   ^  |   &  |   *  |   €  |   ?  | F12  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      | LEFT | DOWN |RIGHT |      |                        |   >  |   }  |   ]  |   )  |   |  |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |      |DEL PW| Ins  |DEL NW|      |      |          |      |      |   /  |   -  |   _  |   `  |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |      |POWER |      |      |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_LOWER] = LAYOUT( /* lower layer */
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, XXXXXXX, PRE_WRD, KC_UP,   NXT_WRD, XXXXXXX,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_EURO, KC_QUES, KC_F12,
    _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                   KC_RABK, KC_RCBR, KC_RBRC, KC_RPRN, KC_PIPE, XXXXXXX,  
    _______, XXXXXXX, PRE_WDL, KC_INS,  NXT_WDL, XXXXXXX, _______, _______, XXXXXXX, KC_SLSH, KC_MINS, KC_UNDS, KC_GRV,  _______,
             _______, _______, _______, _______, _______,                   _______, _______, POWER,   _______, _______
  ),

  /* POWER
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       | RST  |  F1  |  F2  |  F3  |  F4  | F5   |                        | F6   |  F7  |  F8  |  F9  | F10  | F11  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |  !   |  @   |  #   |  $   |  %   |                        |   ^  |   &  |   *  |   €  |   ?  | F12  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |  |   |  (   |  [   |  {   |  <   |                        |   >  |   }  |   ]  |   )  |   |  |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |  ~   |  =   |  +   |  \   |      |      |          |      |      |   /  |   -  |   _  |   `  |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |      |      |      |      |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_POWER] = LAYOUT( /* lower and raise combined */
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_EURO, KC_QUES, KC_F12,
    _______, KC_PIPE, KC_LPRN, KC_LBRC, KC_LCBR, KC_LABK,                   KC_RABK, KC_RCBR, KC_RBRC, KC_RPRN, KC_PIPE, XXXXXXX,  
    _______, KC_TILD, KC_EQL,  KC_PLUS, KC_BSLS, XXXXXXX, _______, _______, XXXXXXX, KC_SLSH, KC_MINS, KC_UNDS, KC_GRV,  _______,
             _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
  )

};

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            if (index == 0 || index == 1) { /* Left or right encoder */
                // Next/previous track
                clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
            }
            break;

        default:
            if (index == 0 || index == 1) { /* Left or right encoder */
                // Volume up or down
                clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            }
            break;
    }
}