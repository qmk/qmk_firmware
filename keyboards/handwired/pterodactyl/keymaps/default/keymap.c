#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // ensure these codes start after the highest keycode defined in Quantum
  VRSN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,------------------------------------------------.                    .------------------------------------------------.
 * |   =  |   1  |   2  |   3  |   4  |   5  |  _2_ |                    |  _2_ |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * | Del  |   Q  |   W  |   E  |   R  |   T  |  _3_ |                    |  _3_ |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * | BkSp |   A  |   S  |   D  |   F  |   G  |  _4_ |                    |  _4_ |   H  |   J  |   K  |   L  |; / L2|'/Cmd |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |LShift|Z/Ctrl|   X  |   C  |   V  |   B  |  _5_ |                    |  _5_ |   N  |   M  |   ,  |   .  |//Ctrl|RShift|
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |Grv/L1|  '"  |AltShf| Left | Right|  _1_ |  _6_ |                    |  _6_ |  _1_ |  Up  | Down |   [  |   ]  | ~L1  |
 * `------------------------------------------------'                    '------------------------------------------------'
 *                                            ,--------------.  ,---------------.
 *                                            |2 App | 4 LGui|  | 4 Alt  | 2 ^/Esc|
 *                                     ,------|------|-------|  |--------+--------+------.
 *                                     |  1   |  3   | 5 Home|  | 5 PgUp | 3      |  1   |
 *                                     | Space|Backsp|-------|  |--------|  Tab   |Enter |
 *                                     |      |ace   | 6 End |  | 6 PgDn |        |      |
 *                                     `---------------------'  `------------------------'
 */
[BASE] = LAYOUT_pterodactyl(  // layer 0 : default
        // left hand
          KC_EQL,          KC_1,           KC_2,     KC_3,     KC_4,  KC_5,   ALT_T(KC_APP),
          KC_DEL,          KC_Q,           KC_W,     KC_E,     KC_R,  KC_T,   KC_BSPC,
          KC_BSPC,         KC_A,           KC_S,     KC_D,     KC_F,  KC_G,   KC_LGUI,
          KC_LSFT,  CTL_T(KC_Z),           KC_X,     KC_C,     KC_V,  KC_B,   KC_HOME,
  LT(SYMB,KC_GRV),      KC_QUOT,  LALT(KC_LSFT),  KC_LEFT,  KC_RGHT,  KC_SPC, KC_END,

        // right hand
         CTL_T(KC_ESC),    KC_6,   KC_7,     KC_8,     KC_9,               KC_0,         KC_MINS,
                KC_TAB,    KC_Y,   KC_U,     KC_I,     KC_O,               KC_P,         KC_BSLS,
               KC_RALT,    KC_H,   KC_J,     KC_K,     KC_L,  LT(MDIA, KC_SCLN),  GUI_T(KC_QUOT),
               KC_PGUP,    KC_N,   KC_M,  KC_COMM,   KC_DOT,     CTL_T(KC_SLSH),         KC_RSFT,
               KC_PGDN,  KC_ENT,  KC_UP,  KC_DOWN,  KC_LBRC,            KC_RBRC,        TT(SYMB),
    ),
/* Keymap 1: Symbol Layer
 *
 * ,------------------------------------------------.                    .------------------------------------------------.
 * |Versn |  F1  |  F2  |  F3  |  F4  |  F5  |  _2_ |                    |  _2_ |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |  _3_ |                    |  _3_ |  Up  |   7  |   8  |   9  |   *  |  F12 |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |      |   #  |   $  |   (  |   )  |   `  |  _4_ |                    |  _4_ | Down |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   ~  |  _5_ |                    |  _5_ |   &  |   1  |   2  |   3  |   \  |      |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |RESET |      |      |      |      |  _1_ |  _6_ |                    |  _6_ | _1_  |      |   .  |   0  |   =  |      |
 * `------------------------------------------------'                    '------------------------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |  2   |  4   |  |   4  |  2   |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |  5   |  |   5  |      |      |
 *                               |  1   |  3   |------|  |------|  3   |  1   |
 *                               |      |      |  6   |  |   6  |      |      |
 *                               `--------------------'  `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_pterodactyl(
       // left hand
          VRSN,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5, KC_TRNS,
       KC_TRNS,  KC_EXLM,    KC_AT,  KC_LCBR,  KC_RCBR,  KC_PIPE, KC_TRNS,
       KC_TRNS,  KC_HASH,   KC_DLR,  KC_LPRN,  KC_RPRN,   KC_GRV, KC_TRNS,
       KC_TRNS,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD, KC_TRNS,
         RESET,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
       // right hand
           KC_TRNS,      KC_F6,      KC_F7,   KC_F8,    KC_F9,    KC_F10,   KC_F11,
           KC_TRNS,      KC_UP,       KC_7,    KC_8,     KC_9,   KC_ASTR,   KC_F12,
           KC_TRNS,    KC_DOWN,       KC_4,    KC_5,     KC_6,   KC_PLUS,  KC_TRNS,
           KC_TRNS,    KC_AMPR,       KC_1,    KC_2,     KC_3,   KC_BSLS,  KC_TRNS,
           KC_TRNS,    KC_TRNS,      KC_DOT,   KC_0,   KC_EQL,   KC_TRNS,  KC_TRNS,
),

/* Keymap 2: Media and mouse keys
 * ,------------------------------------------------.                    .------------------------------------------------.
 * |      |      |      |      |      |      |  _2_ |                    |  _2_ |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |      |      |      | MsUp |      |      |  _3_ |                    |  _3_ |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |      |      |MsLeft|MsDown|MsRght|      |  _4_ |                    |  _4_ |      |      |      |      |      | Play |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  _5_ |                    |  _5_ |      |      | Prev | Next |      |      |
 * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
 * |      |      |      | Lclk | Rclk | _1_  |  _6_ |                    |  _6_ | _1_  | VolUp| VolDn| Mute |      |      |
 * `------------------------------------------------'                    '------------------------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |  2   |  4   |  |  4   |  2   |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |  5   |  |  5   |      |  1   |
 *                               |  1   |  3   |------|  |------|  3   |Brwser|
 *                               |      |      |  6   |  |  6   |      | Back |
 *                               `--------------------'  `--------------------'
 *
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_pterodactyl(
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_BTN2,  KC_TRNS, KC_TRNS,
    // right hand
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MPLY, KC_TRNS,
                KC_TRNS,  KC_TRNS,  KC_MPRV,  KC_MNXT,  KC_TRNS,  KC_TRNS, KC_TRNS,
                KC_WBAK,  KC_VOLU,  KC_VOLD,  KC_MUTE,  KC_TRNS,  KC_TRNS, KC_TRNS,
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
