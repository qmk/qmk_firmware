#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

// TODO: Define layer names that make sense for the ErgoDox EZ.
#define DEFAULT_LAYER 0
#define COLEMAK_LAYER 1
#define DVORAK_LAYER 2
#define LOWER_LAYER 1
#define RAISE_LAYER 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEFAULT_LAYER] = KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_ESC,
        KC_BSLS,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_FN2,
        KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_FN1,
        KC_LGUI,KC_GRV, KC_BSLS,KC_LEFT,KC_RGHT,
                                      KC_LCTL,KC_LALT,
                                           KC_HOME,
                                 KC_BSPC,KC_DEL, KC_END,
        // right hand
             KC_FN3, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
             KC_LBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_RBRC,
                  KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
             KC_FN1, KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                       KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_RGUI,
        KC_RALT,KC_RCTL,
        KC_PGUP,
        KC_PGDN,KC_ENT, KC_SPC
    ),
[LOWER_LAYER] = KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL, KC_1,   KC_2,   KC_3,   LALT(KC_TAB),   KC_5,   KC_ESC,
        KC_BSLS,KC_Q,   S(KC_W),   KC_E,   KC_R,   KC_T,   KC_FN2,
        KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_FN1,
        KC_LGUI,KC_GRV, KC_BSLS,KC_LEFT,KC_RGHT,
                                      KC_LCTL,KC_LALT,
                                           KC_HOME,
                                 KC_BSPC,KC_DEL, KC_END,
        // right hand
             KC_FN3, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
             KC_LBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_RBRC,
             KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
             KC_FN1, KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                       KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_RGUI,
        KC_RALT,KC_RCTL,
        KC_PGUP,
        KC_PGDN,KC_ENT, KC_SPC
    )
};

const uint16_t PROGMEM fn_actions[] = {

    [1] = ACTION_LAYER_MOMENTARY(LOWER_LAYER),  // to RAISE
    [2] = ACTION_LAYER_MOMENTARY(LOWER_LAYER),  // to LOWER

    [3] = ACTION_DEFAULT_LAYER_SET(DEFAULT_LAYER),
    [4] = ACTION_DEFAULT_LAYER_SET(COLEMAK_LAYER),
    [5] = ACTION_DEFAULT_LAYER_SET(DVORAK_LAYER),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_left_led_1_off();
    ergodox_left_led_2_off();
    ergodox_left_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            // all
            ergodox_left_led_1_on();
            ergodox_left_led_2_on();
            ergodox_left_led_3_on();
            break;
        case 2:
            // blue
            ergodox_left_led_2_on();
            break;
        case 8:
            // blue and green
            ergodox_left_led_2_on();
            // break missed intentionally
        case 3:
            // green
            ergodox_left_led_3_on();
            break;
        case 6:
            ergodox_board_led_on();
            // break missed intentionally
        case 4:
        case 5:
        case 7:
            // white
            ergodox_left_led_1_on();
            break;
        case 9:
            // white+green
            ergodox_left_led_1_on();
            ergodox_left_led_3_on();
            break;
        default:
            // none
            break;
    }

    mcp23018_status = ergodox_left_leds_update();
};
