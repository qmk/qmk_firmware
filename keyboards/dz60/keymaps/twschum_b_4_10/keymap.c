#include QMK_KEYBOARD_H
#include "twschum.h"

/* DZ60 layout using following options (from layouts diagram on KBDfans):
 *  - plate B (2.25u lshift)
 *  - opt 4 (1.75, 1, 1 on rshift)
 *  - opt 10 (2.75, 1.25, 2.25 on space, 5x1u bottom right keys)
 * http://www.keyboard-layout-editor.com/#/gists/225f0f4dcf6671405f744fabe314627c
 */


#define LAYOUT_b_4_10( \
        K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, \
        K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
        K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       \
        K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310,       K312, K313, K314, \
        K400, K401,       K403,       K404, K406,       K408,       K410, K411, K412, K413, K414  \
        ) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  XXXXXXX, K014 }, \
    { K100,  XXXXXXX, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { K200,  XXXXXXX, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  XXXXXXX }, \
    { K300,  XXXXXXX, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  XXXXXXX, K312,  K313,  K314 }, \
    { K400,  K401,  XXXXXXX, K403,  K404,  XXXXXXX, K406,  XXXXXXX, K408,  XXXXXXX, K410,  K411,  K412,  K413,  K414 }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* base 60% qwerty */
  LAYOUT_b_4_10(
    // |--------|----1---|----2---|----3---|---4----|---5----|---6----|---7----|---8----|---9----|---0----|-- - ---|-- = ---||------2.0-------|
         KC_ESC,   KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS, KC_EQL,      KC_BSPC,
    // |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------||----------------|
    //
    // |----1.5-----||---Q----|---W----|---E----|---R----|---T----|---Y----|---U----|---I----|---O----|---P----|---[----|---]----|----1.5-----|
          KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_LBRC, KC_RBRC,   KC_BSLS,
    // |------------||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|------------|
    //
    // |----1.75------||---A----|---S----|---D----|---F----|---G----|---H----|---J----|---K----|---L----|---;----|---'----|------2.25--------||
          KC_LCTL,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,     KC_ENT,
    // |--------------||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|------------------||
    //
    // |------2.25--------|---Z----|---X----|---C----|---V----|---B----|---N----|---M----|---,----|---.----||----1.75------|--------|--------||
          KC_LSHIFT,        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,  /*SFT_T*/KC_SLSH, KC_UP,  VIM_START,
    // |------------------|--------|--------|--------|--------|--------|--------|--------|--------|--------||--------------|--------|--------||
    //
    // |---1.25---|---1.25---||---1.25---||--------2.75----------||---1.25---|------2.25--------||--------|--------|--------|--------|--------|
          MO(_Fn),  KC_LALT,    KC_LGUI,         KC_SPC,           TT(_Nav),      MO(_Fn),       TG(_Num), TT(_Cfg), KC_LEFT, KC_DOWN, KC_RGHT
    // |----------|----------||----------||----------------------||----------|------------------||--------|--------|--------|--------|--------|
  ),

  /* vim mode */
  LAYOUT_b_4_10(
    VIM_ESC,   _______, _______, _______, _______, _______, _______, _______, _______,   _______,    _______, _______, _______, _______,
    _______,   _______, VIM_W,   VIM_E,   KC_R,    _______, VIM_Y,   VIM_U,   VIM_I,     VIM_O,      VIM_P,   _______, _______, _______,
    _______,   VIM_A,   VIM_S,   VIM_D,   _______, VIM_G,   VIM_H,   VIM_J,   VIM_K,     VIM_L,      _______, _______, _______,
    VIM_SHIFT, _______, VIM_X,   VIM_C,   VIM_V,   VIM_B,   _______, _______, VIM_COMMA, VIM_PERIOD, _______, _______, VIM_ESC,
    _______,   _______, _______, _______, _______, _______, _______, _______, _______,   _______,    _______
  ),

  /* primary fn layer */
  LAYOUT_b_4_10(
    // |--------|----1---|----2---|----3---|---4----|---5----|---6----|---7----|---8----|---9----|---0----|-- - ---|-- = ---||------2.0-------|
         KC_GRV,   KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_DEL,
    // |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------||----------------|
    //
    // |----1.5-----||---Q----|---W----|---E----|---R----|---T----|---Y----|---U----|---I----|---O----|---P----|---[----|---]----|----1.5-----|
          KC_TAB,   CODE_PASTE, KC_HOME, KC_UP,   KC_END, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, LESS_PD, XXXXXXX, XXXXXXX,  CODE_PASTE,
    // |------------||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|------------|
    //
    // |----1.75------||---A----|---S----|---D----|---F----|---G----|---H----|---J----|---K----|---L----|---;----|---'----|------2.25--------||
          KC_CAPS,     SALT_CMD, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, XXXXXXX, XXXXXXX,     KC_ENT,
    // |--------------||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|------------------||
    //
    // |------2.25--------|---Z----|---X----|---C----|---V----|---B----|---N----|---M----|---,----|---.----||----1.75------|--------|--------||
          KC_LSHIFT,       KC_MPRV, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______, XXXXXXX, XXXXXXX,     KC_LOCK,     KC_PGUP,  KC_INS,
    // |------------------|--------|--------|--------|--------|--------|--------|--------|--------|--------||--------------|--------|--------||
    //
    // |---1.25---|---1.25---||---1.25---||--------2.75----------||---1.25---|------2.25--------||--------|--------|--------|--------|--------|
          KC_MEH,   KC_LALT,    KC_LGUI,    KC_MEDIA_PLAY_PAUSE,    _______,       _______,       _______, _______,  KC_HOME, KC_PGDN, KC_END
    // |----------|----------||----------||----------------------||----------|------------------||--------|--------|--------|--------|--------|
  ),

  /* mouse navigation */
  LAYOUT_b_4_10(
    TO(_Base), KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, XXXXXXX,     XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,   XXXXXXX,      KC_MS_BTN2,   KC_MS_UP,     KC_MS_BTN1,  XXXXXXX, XXXXXXX,       KC_SLEP,       KC_PGDN,     KC_PGUP,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LCTL,   KC_MS_BTN3,   KC_MS_LEFT,   KC_MS_DOWN,   KC_MS_RIGHT, XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LSHIFT, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,     XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, _______, XXXXXXX,
    XXXXXXX,   XXXXXXX,      XXXXXXX,      KC_MS_BTN1,   _______,     _______, _______,       _______,       _______,     _______,        _______
  ),

  /* numpad layer */
  LAYOUT_b_4_10(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX, KC_BSPC,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, KC_KP_PLUS,     XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_SLASH, KC_KP_ASTERISK, XXXXXXX, KC_ENT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT,   KC_KP_ENTER,    XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_0, _______, _______, XXXXXXX, XXXXXXX,     XXXXXXX
  ),


  /* RGB lighting controls and keyboard config, reset */
  LAYOUT_b_4_10(
    _______,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      TG_L0_RGB,      XXXXXXX,          XXXXXXX,   TO(_None),
    XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,        XXXXXXX,          XXXXXXX,   RGB_HUD,
    EN_CTRL_SHORTCUTS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_LAYER_RGB, RGB_MODE_PLAIN, RGB_MODE_FORWARD, KC_RSHIFT,
    XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MAKE, XXXXXXX, XXXXXXX,      RGB_TOG,        RGB_VAI,          RGB_HUI,
    XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, RGB_SAD, RGB_VAD,      RGB_SAI
  ),

  /* soft "off" state where none of the keystroke register */
  LAYOUT_b_4_10(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_Base),
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

uint8_t vim_cmd_layer(void) {
    return _Vim;
}
