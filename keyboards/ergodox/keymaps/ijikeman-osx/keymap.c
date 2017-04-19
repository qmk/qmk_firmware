 #include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

#define MACRO_TMUX_ESC        10
#define MACRO_TMUX_LANG        11
#define M_TESC   M(MACRO_TMUX_ESC)
#define M_TLANG   M(MACRO_TMUX_LANG)

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
 * | `~(Esc)|   1! |   2@ |   3# |   4$ |   5% |  6^  |           |  6^  |   7& |   8* |   9( |   0) |   -_ |   =+   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \|   |
 * |--------+------+------+------+------+------|      |           |  ]}  |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |   '"   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |*(LANG)|           |  [{  |   N  |   M  |   ,< |   .> |   /? | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      | Alt  |  Cmd | Fn(1)|                         |  BS  | Fn(2)  | Alt |  \|  |      |
 *   `----------------------------------'                         `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | PGDN | PGUP |       | LEFT | RIGHT|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | UP   |        |      |
 *                                 | Space| ESC  |------|       |------|        |Enter |
 *                                 |      |      | End  |       | DOWN |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        M_TESC,         KC_1,         KC_2,       KC_3,       KC_4,       KC_5,     KC_6,
        KC_TAB,         KC_Q,         KC_W,       KC_E,       KC_R,       KC_T,     KC_NO,
        KC_LCTL,        KC_A,         KC_S,       KC_D,       KC_F,       KC_G,
        KC_LSFT,        KC_Z,         KC_X,       KC_C,       KC_V,       KC_B,     M_TLANG,
        KC_NO,          KC_NO,        KC_LALT,    KC_LGUI,    LT(1,KC_NO),
                                                  KC_PGDN,    KC_PGUP,
                                                              KC_HOME,
                                      KC_SPC,     KC_ESC,     KC_END,

        // right hand
        KC_6,           KC_7,         KC_8,       KC_9,       KC_0,        KC_MINS,   KC_EQL,
        KC_RBRC,        KC_Y,         KC_U,       KC_I,       KC_O,        KC_P,      KC_BSLS,
                        KC_H,         KC_J,       KC_K,       KC_L,        KC_SCLN,   KC_QUOT,
        KC_LBRC,        KC_N,         KC_M,       KC_COMM,    KC_DOT,      KC_SLSH,   KC_RSFT,
        KC_BSPC,        LT(2,KC_NO),  KC_RALT,    KC_BSLS,    KC_NO,
        KC_LEFT,        KC_RIGHT,
        KC_UP,
        KC_DOWN,        KC_NO,      KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | RESET   |  F1  |  F2  |  F3  |  F4  |  F5  | F6   |           |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 *  |        |      |      | MsUp |      |      |      |           |      |      | UNDO |      | REDO |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 *  |        |  BTN1|MsLeft|MsDown|MsRght|      |------|           |------| LEFT | DOWN | UP   |RIGHT |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 *  |        |      |      |      |      |      |      |           |      |      | CP   | CUT  | PST  |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      | Fn(1)|                                       | DEL  |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       RESET,     KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
       KC_TRNS,   KC_TRNS,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_NO,    KC_TRNS,
       KC_TRNS,   KC_NO,    KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_NO,
       KC_TRNS,   KC_NO,    KC_NO,    KC_NO,    KC_NO,     KCNO,    KC_TRNS,
       KC_TRNS,   KC_NO,    KC_TRNS,  KC_TRNS,  KC_TRNS,
                                      KC_TRNS,  KC_TRNS,
                                                KC_TRNS,
                        KC_TRNS, KC_TRNS,  KC_TRNS,
       // right hand
       KC_F6,     KC_F7,     KC_F8,     KC_F9,      KC_F10,      KC_F11,   KC_F12,
       KC_TRNS,   KC_NO,     LGUI(KC_Z),KC_NO,     LGUI(KC_Y),   KC_NO,    KC_TRNS,
                  KC_LEFT,   KC_DOWN,   KC_UP,      KC_RIGHT,    KC_NO,    KC_TRNS,
       KC_TRNS,   KC_NO,     LGUI(KC_C),LGUI(KC_X),LGUI(KC_V),   KC_NO,    KC_TRNS,
                  KC_DELETE,   KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,
       KC_TRNS,   KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |  F1  |  F2  |  F3  |  F4  |  F5  | F6   |           |  F6  |  F7  |  F8  |  F9  |  F10 |   F11 |  F12  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |     |   7  |   8  |   9  |       |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |   4  |   5  |   6  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |   1  |   2  |   3  |   .  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      | Fn(2)|   0  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |     ;s |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       RESET,     KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,      KC_F11,   KC_F12,
       KC_TRNS,   KC_NO,     KC_7,      KC_8,      KC_9,        KC_NO,    KC_TRNS,
                  KC_NO,     KC_4,      KC_5,      KC_6,        KC_NO,    KC_TRNS,
       KC_TRNS,  KC_NO,      KC_1,      KC_2,      KC_3,        KC_DOT,   KC_TRNS,
                          KC_TRNS,      KC_TRNS,   KC_0,        KC_NO,    KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

static uint16_t key_timer;
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
        case MACRO_TMUX_ESC:
        if (record->event.pressed) {
          key_timer = timer_read();
        } else {
          if (timer_elapsed(key_timer) >= 200) {
            return MACRO(T(ESC), END);
          } else {
            return MACRO(T(GRV), END);
          }
        }
        break;
        case MACRO_TMUX_LANG:
        if (record->event.pressed) {
          key_timer = timer_read();
        } else {
          if (timer_elapsed(key_timer) >= 200) {
            return MACRO(D(LGUI), T(SPC), U(LGUI), END);
          } else {
            return MACRO(END);
          }
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
