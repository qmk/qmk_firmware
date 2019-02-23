#include QMK_KEYBOARD_H
#include "version.h"
#include "bootmagic.h"

#define QWERTY 0    // qwerty layer
#define COLEMAK 1   // colemak layer
#define FN 2        // function layer

enum custom_keycodes {
    QWRTY = SAFE_RANGE, // can always be here
    CLMK,
    VRSN,
    FNCTN
};

/* false: Caps Lock LED is off
   true: Caps Lock LED is on */
bool CAPS_LED = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Qwerty layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Copy |           | Paste|   6  |   7  |   8  |   9  |   0  | Sleep  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  | Mute |           |  {   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |  [   |------+------+------+------+------+--------|
 * |  Esc   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| Fn1  |           |  }   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |  ]   |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | LGui | LAlt | Left | Right|                                       | Down |  Up  |   -  |   =  | RCtrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Caps | LGui |       | Ins  |  Del |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[QWERTY] = LAYOUT_ergodox(  // layer 0 : qwerty
        // left hand
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,  KC_COPY,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,  KC_MUTE,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
        KC_LSPO,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,  TT(FN),
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LEFT,  KC_RGHT,
                                                       KC_CAPS,  KC_LGUI,
                                                                 KC_HOME,
                                              KC_SPC,  KC_BSPC,  KC_END,
        // right hand
             KC_PASTE,  KC_6,  KC_7,     KC_8,     KC_9,     KC_0,      KC_SLEP,
             KC_LBRC,   KC_Y,  KC_U,     KC_I,     KC_O,     KC_P,      KC_BSLS,
                        KC_H,  KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOTE,
             KC_RBRC,   KC_N,  KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,   KC_RSPC,
                               KC_DOWN,  KC_UP,    KC_MINS,  KC_EQL,    KC_RCTL,
             KC_INS,    KC_DEL,
             KC_PGUP,
             KC_PGDN,  KC_TAB,  KC_ENT
),
/* Keymap 1: Colemak layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Copy |           | Paste|   6  |   7  |   8  |   9  |   0  | Sleep  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   F  |   P  |   B  | Mute |           |  {   |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |  [   |------+------+------+------+------+--------|
 * |  Esc   |   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  |   '    |
 * |--------+------+------+------+------+------| Fn1  |           |  }   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |      |           |  ]   |   K  |   H  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | LGui | LAlt | Left | Right|                                       | Down |  Up  |   -  |   =  | RCtrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Caps | LGui |       | Ins  |  Del |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[COLEMAK] = LAYOUT_ergodox(  // layer 1 : colemak
        // left hand
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,  KC_COPY,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,  KC_MUTE,
        KC_ESC,   KC_A,     KC_R,     KC_S,     KC_T,     KC_G,
        KC_LSPO,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,  TT(FN),
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LEFT,  KC_RGHT,
                                                       KC_CAPS,  KC_LGUI,
                                                                 KC_HOME,
                                              KC_SPC,  KC_BSPC,  KC_END,
        // right hand
             KC_PASTE,  KC_6,  KC_7,     KC_8,     KC_9,     KC_0,     KC_SLEP,
             KC_LBRC,   KC_J,  KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_BSLS,
                        KC_M,  KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOTE,
             KC_RBRC,   KC_K,  KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSPC,
                               KC_DOWN,  KC_UP,    KC_MINS,  KC_EQL,   KC_RCTL,
             KC_INS,    KC_DEL,
             KC_PGUP,
             KC_PGDN,  KC_TAB,  KC_ENT
),
/* Keymap 2: Function Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      | Prev | Play | Next |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |VolDn | VolUp|------|           |------|      |QWRTY | CLMK |     |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Functions
[FN] = LAYOUT_ergodox(
       // left hand
       VRSN,     KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_VOLD,  KC_VOLU,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,
       // right hand
       KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                 KC_TRNS,  QWRTY,    CLMK,     KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                           KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS
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
      case QWRTY:
        if (record->event.pressed) {
          set_single_persistent_default_layer(QWERTY);
        }
        return false;
        break;
      case CLMK:
        if (record->event.pressed) {
          set_single_persistent_default_layer(COLEMAK);
        }
        return false;
        break;
      case KC_CAPS:
        if (record->event.pressed) {
          // Turn LED1 On/Off for Caps Lock
          if (CAPS_LED) {
            ergodox_right_led_1_off();
            CAPS_LED = false;
          } else {
            ergodox_right_led_1_on();
            CAPS_LED = true;
          }
        }
        return true;
        break;
    }
    return true;
};

// Set LED according to the default layer
void default_layer_led_set(void) {
    switch (biton32(eeconfig_read_default_layer())) {
      case COLEMAK:
        // LED2 for COLEMAK
        ergodox_right_led_2_on();
        break;
      case QWERTY:
        // LED3 for QWERTY
        ergodox_right_led_3_on();
        break;
    };
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    default_layer_led_set();
};

uint32_t layer_state_set_user(uint32_t state) {
    ergodox_led_all_off();
    switch (biton32(state)) {
      case FN:
          // Red led on Pro Micro for Fn layer
          ergodox_board_led_on();
          break;
    };

    if (CAPS_LED) {
      ergodox_right_led_1_on();
    }

    default_layer_led_set();

    return state;
};

void suspend_power_down_user(void) {
    ergodox_led_all_off();
};

void suspend_wakeup_init_user(void) {
    default_layer_led_set();
};
