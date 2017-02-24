#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
//#define FUNC 1 // function, media, arrow keys
//#define NUMP 2 // numpad
//#define INTL 3 // international symbols

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |   -  |           |  =   |   6  |   7  |   8  |   9  |   0  | SYSREQ |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | DEL    |   Q  |   W  |   E  |   R  |   T  | HOME |           | PGUP |   Y  |   U  |   I  |   O  |   P  |  BKSP  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | TAB    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  ENTER |
 * |--------+------+------+------+------+------|  END |           | PGDN |------+------+------+------+------+--------|
 * | (/LSFT |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | )/RSFT |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |LGUI/LCTRL|MENU|   `  |   '  | CAPS |                                       |   [  |   ]  |   \  |MENU|RGUI/RCTRL|
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | VOL- | VOL+ |       | BRT- | BRT+ |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | ALT/ |      | MUTE |       | NUM  |      | ALT/ |
 *                                 | SPC  | LAY1 |------|       |------| LAY1 | SPC  |
 *                                 |      |      | LAY3 |       | LAY2 |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_MINS,
        KC_DEL,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_HOME,
        KC_TAB,         KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSPO,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_END,
        KC_LCTL,        KC_LGUI,KC_GRV, KC_QUOT,KC_CAPS,
                                                KC_VOLD, KC_VOLU,
                                                            KC_MUTE,
                                ALT_T(KC_SPC),  MO(BASE),   MO(BASE),
        // right hand
            KC_EQL,     KC_6,   KC_7,       KC_8,       KC_9,       KC_0,       KC_SYSREQ,
            KC_PGUP,    KC_Y,   KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
                        KC_H,   KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_ENTER,
            KC_PGDN,    KC_N,   KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSPC,
                                KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_RGUI,    KC_RCTL,
            KC_VOLD, KC_VOLU,
            KC_NLCK,
            TT(BASE),   MO(BASE),   ALT_T(KC_SPC)
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(BASE)                // FN1 - Momentary Layer 1 (Function Keys)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
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
