#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define GAME 1 // gaming layer
#define NUMP 2 // number pad

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // ensure these codes start after the highest keycode defined in Quantum
  VRSN,
};

//BASE TEMPLATE
/* Keymap N: Template Layer
 *
 * ,-------------------------------------------------------.    ,-------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |    |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |    |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |    |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |    |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------'    `------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |                  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------'                  `------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                |      |      |      |      |      |      |
 * `-----------------------------------------'                                `-----------------------------------------'
 *                                            ,-------------.  ,-------------.
 *                                            |      |      |  |      |      |
 *                                     ,------|------|------|  |------+------+------.
 *                                     |      |      |      |  |      |      |      |
 *                                     |      |      |------|  |------|      |      |
 *                                     |      |      |      |  |      |      |      |
 *                                     `--------------------'  `--------------------'
 */
/*
        // left hand
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
                                                                  KC_NO,   KC_NO,
                                                                           KC_NO,
                                                         KC_NO,   KC_NO,   KC_NO,
        // right hand
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,
            KC_NO,
            KC_NO,   KC_NO,   KC_NO,
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------------------.    ,-------------------------------------------------------.
 * |  ESC |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |    |  F7  |  F8  |  F9  | F10  | F11  | F12  |      | GAME |
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBHUI|   `  |   1  |   2  |   3  |   4  |   5  |   6  |    |  5   |  6   |  7   |  8   |  9   |  1O  |  -   |RGBVAI|
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBHUD|      |   Q  |   W  |   E  |   R  |   T  |      |    |      |  Y   |  U   |  I   |  O   |  P   |  \   |RGBVAD|
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBSAI|      |   A  |   S  |   D  |   F  |   G  |      |    |      |  H   |  J   |  K   |  L   |  ;   |  '   |RGBSPI|
 * |------+------+------+------+------+------+------+------'    `------+------+------+------+------+------+------+------|
 * |RGBSAD| LSPO |   Z  |   X  |   C  |   V  |   B  |                  |  N   |  M   |  ,   |  .   |  /   | RSPC |RGBSPD|
 * |------+------+------+------+------+------+------'                  `------+------+------+------+------+------+------|
 * |RGBTOG|RGBMOD|      | NUMP | LALT | LCTL |                                | RCTL | RALT | NUMP |      |      |      |
 * `-----------------------------------------'                                `-----------------------------------------'
 *                                            ,-------------.  ,-------------.
 *                                            |      |      |  |      |      |
 *                                     ,------|------|------|  |------+------+------.
 *                                     |      |      | CAPS |  | INS  |      |      |
 *                                     |BSPACE|  Tab |------|  |------|ENTER |SPACE |
 *                                     |      |      |  DEL |  | WIN  |      |      |
 *                                     `--------------------'  `--------------------'
 */
[BASE] = LAYOUT_albatross(  // layer 0 : default
        // left hand
           KC_ESC,   KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
          RGB_HUI,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
          RGB_HUD,   KC_NO,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_NO,
          RGB_SAI,   KC_NO,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_NO,
          RGB_SAD, KC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, 
          RGB_TOG, RGB_MOD,   KC_NO,   KC_NO, KC_LALT, KC_LCTL, 
                                                                  KC_NO,   KC_NO,
                                                                         KC_CAPS,
                                                       KC_BSPC,  KC_TAB,  KC_DEL,
        // right hand
                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_NO, TG(GAME),
                      KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS, RGB_VAI,
                     KC_NO,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, RGB_VAD,
                     KC_NO,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, RGB_SPI,
                               KC_N,    KC_M,  KC_COM,  KC_DOT, KC_SLSH, KC_RSPC, RGB_SPD,
                                     KC_RCTL, KC_RALT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,
            KC_NO,
          KC_LWIN,  KC_ENT,  KC_SPC,
    ),
/* Keymap 1: Gaming Level
 *
 * ,-------------------------------------------------------.    ,-------------------------------------------------------.
 * |  ESC |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |    |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |  TO  |
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBHUI|   `  |   1  |   2  |   3  |   4  |   5  |   6  |    |  5   |  6   |  7   |  8   |  9   |  1O  |  -   |RGBVAI|
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBHUD|      |  TAB |   Q  |   W  |   E  |   R  |   T  |    |      |  Y   |  U   |  I   |  O   |  P   |  \   |RGBVAD|
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBSAI|      | CAPS |   A  |   S  |   D  |   F  |   G  |    |  B   |  H   |  J   |  K   |  L   |  ;   |  '   |RGBSPI|
 * |------+------+------+------+------+------+------+------'    `------+------+------+------+------+------+------+------|
 * |RGBSAD|      |LSHIFT|   Z  |   X  |   C  |   V  |                  |  N   |  M   |  ,   |  .   |  /   | RSPC |RGBSPD|
 * |------+------+------+------+------+------+------'                  `------+------+------+------+------+------+------|
 * |RGBTOG|RGBMOD|      |      | LAlt | LCtrl|                                |RCtrl | RAlt |      |      |      |      |
 * `-----------------------------------------'                                `-----------------------------------------'
 *                                            ,-------------.  ,-------------.
 *                                            |      |      |  |      |      |
 *                                     ,------|------|------|  |------+------+------.
 *                                     |      |      | CAPS |  |      |      |      |
 *                                     |BSPACE| SPACE|------|  |------|ENTER |SPACE |
 *                                     |      |      |  DEL |  | WIN  |      |      |
 *                                     `--------------------'  `--------------------'
 */
// GAMING
[GAME] = LAYOUT_albatross(
        // left hand
           KC_ESC,   KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
          RGB_HUI,  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
          RGB_HUD,   KC_NO,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
          RGB_SAI,   KC_NO, KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
          RGB_SAD,   KC_NO, KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,
          RGB_TOG, RGB_MOD,   KC_NO,   KC_NO, KC_LALT, KC_LCTL, 
                                                                  KC_NO,   KC_NO,
                                                                           KC_NO,
                                                        KC_SPC, KC_BSPC,  KC_DEL,
        // right hand
                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_NO, TO(BASE),
                      KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS, RGB_VAI,
                     KC_NO,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, RGB_VAD,
                     KC_NO,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, RGB_SPI,
                               KC_N,    KC_M,  KC_COM,  KC_DOT, KC_SLSH, KC_RSPC, RGB_SPD,
                                     KC_RCTL, KC_RALT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,
            KC_NO,
          KC_LWIN,  KC_ENT,  KC_SPC,
),
/* Keymap 2: NumPad
 *
 * ,-------------------------------------------------------.    ,-------------------------------------------------------.
 * |  ESC |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |    |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |      |
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBHUI|   `  |   1  |   2  |   3  |   4  |   5  |   6  |    |  5   |  6   |  7   |  8   |  9   |  1O  |  -   |RGBVAI|
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBHUD|      |   Q  |   W  |   E  |   R  |   T  |      |    |      |  Y   |  U   |  I   |  O   |  P   |  \   |RGBVAD|
 * |------+------+------+------+------+------+------+------|    |------+------+------+------+------+------+------+------|
 * |RGBSAI|      |   A  |   S  |   D  |   F  |   G  |      |    |      |  H   |  J   |  K   |  L   |  ;   |  '   |RGBSPI|
 * |------+------+------+------+------+------+------+------'    `------+------+------+------+------+------+------+------|
 * |RGBSAD| LSPO |   Z  |   X  |   C  |   V  |   B  |                  |  N   |  M   |  ,   |  .   |  /   | RSPC |RGBSPD|
 * |------+------+------+------+------+------+------'                  `------+------+------+------+------+------+------|
 * |RGBTOG|RGBMOD|      |      | LAlt | LCtrl|                                |RCtrl | RAlt |      |      |      |      |
 * `-----------------------------------------'                                `-----------------------------------------'
 *                                            ,-------------.  ,-------------.
 *                                            |      |      |  |      |      |
 *                                     ,------|------|------|  |------+------+------.
 *                                     |      |      |      |  |      |      |      |
 *                                     |Backsp|  Tab |------|  |------|Enter |Space |
 *                                     |ace   |      |  Del |  | Win  |      |      |
 *                                     `--------------------'  `--------------------'
 */
// NUMBER PAD
[NUMP] = LAYOUT_albatross(
        // left hand
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
                                                                  KC_NO,   KC_NO,
                                                                           KC_NO,
                                                         KC_NO,   KC_NO,   KC_NO,
        // right hand
                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,
            KC_NO,
            KC_NO,   KC_NO,   KC_NO,
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {};
