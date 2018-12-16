/* TypeMatrix-2030-like keymap  */
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "led.h"

#define BASE 0 // default layer
#define DVRK 1 // Dvorak layer
#define NUMR 8 // numeric layer
#define FNLR 9 // fn layer

#define MDBL0 1
#define MFNLR 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Del  |           | Del  |   6  |   7  |   8  |   9  |   0  |   ]    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |Backsp|           |Backsp|   Y  |   U  |   I  |   O  |   P  |   [    |
 * |--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '/Shift|
 * |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | \/Shift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |  fn  | LGui | Play |App/Alt|                                      | RAlt |   -  | Home |   =  |End/Ctl|
 *   `-----------------------------------'                                      `-----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |Esc/Alt| num  |       | Left |Right |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       | PgUp |       |  Up  |      |      |
 *                                |Space |LShift |------|       |------|RShift|Space |
 *                                |      |       | PgDn |       | Down |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_DELT,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_BSPC,
        KC_LSFT,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   KC_ENT,
        KC_LCTL,        M(MFNLR),     KC_LGUI,KC_MPLY,ALT_T(KC_APP),

                                              ALT_T(KC_ESC),  TG(NUMR),
                                                              KC_PGUP,
                                            KC_SPC, KC_LSFT,  KC_PGDN,

        // right hand
             KC_DELT,     KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     KC_RBRC,
             KC_BSPC,     KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,
                          KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  SFT_T(KC_QUOT),
             KC_ENT,      KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  SFT_T(KC_BSLS),
                                  KC_RALT, KC_MINS, KC_HOME, KC_EQL,   CTL_T(KC_END),

             KC_LEFT, KC_RGHT,
             KC_UP,
             KC_DOWN, KC_RSFT,  KC_SPC
    ),
/* Dvorak layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Del  |           | Del  |   6  |   7  |   8  |   9  |   0  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   '  |   ,  |   .  |   P  |   Y  |Backsp|           |Backsp|   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
 * | LShift |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  | -/Shift|
 * |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | \/Shift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |  fn  | LGui | Play |App/Alt|                                      | RAlt |   [  | Home |   ]  |End/Ctl|
 *   `-----------------------------------'                                      `-----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |Esc/Alt| num  |       | Left |Right |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       | PgUp |       |  Up  |      |      |
 *                                |Space |LShift |------|       |------|RShift|Space |
 *                                |      |       | PgDn |       | Down |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[DVRK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,   KC_1,      KC_2,    KC_3,    KC_4,   KC_5,   KC_DELT,
        KC_TAB,   KC_QUOT,   KC_COMM, KC_DOT,  KC_P,   KC_Y,   KC_BSPC,
        KC_LSFT,  KC_A,      KC_O,    KC_E,    KC_U,   KC_I,
        KC_LSFT,  KC_SCLN,   KC_Q,    KC_J,    KC_K,   KC_X,   KC_ENT,
        KC_LCTL,  M(MFNLR),  KC_LGUI, KC_MPLY, ALT_T(KC_APP),

                                              ALT_T(KC_ESC),  TG(NUMR),
                                                              KC_PGUP,
                                            KC_SPC, KC_LSFT,  KC_PGDN,

        // right hand
             KC_DELT,     KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     KC_EQL,
             KC_BSPC,     KC_F,   KC_G,    KC_C,    KC_R,    KC_L,     KC_SLSH,
                          KC_D,   KC_H,    KC_T,    KC_N,    KC_S,     SFT_T(KC_MINS),
             KC_ENT,      KC_B,   KC_M,    KC_W,    KC_V,    KC_Z,     SFT_T(KC_BSLS),
                                  KC_RALT, KC_LBRC, KC_HOME, KC_RBRC,  CTL_T(KC_END),

             KC_LEFT, KC_RGHT,
             KC_UP,
             KC_DOWN, KC_RSFT,  KC_SPC
    ),
/* Numeric Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |  Tab |   /  |   *  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  |  F10 |      |           |      |      | Home |   7  |   8  |   9  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F11 |  F12 |      |      |      |------|           |------|  Up  | End  |   4  |   5  |   6  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           | Left | Down | Right|   1  |   2  |   3  |KpEnter |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |   0  |  00  |   .  |Etr/Ctl|
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |n.lock|c.lock|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[NUMR] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                                               KC_TRNS, KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,   KC_TAB,  KC_PSLS, KC_PAST, KC_PMNS,
       KC_TRNS, KC_TRNS, KC_HOME, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
                KC_UP,   KC_END,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
       KC_LEFT, KC_DOWN, KC_RGHT, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                         KC_TRNS, KC_P0,   M(MDBL0),KC_PDOT, CTL_T(KC_PENT),

       KC_NLCK, KC_CAPS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* fn layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |Insert|           |Insert|Eject |Power |Sleep | Wake |PrtScr|ScrollLk|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |VolUp |           |      |      |      |      |      |      | Pause  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      | Calc | Mail |Browsr|------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | cut  | copy |paste | Mute |VolDn |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | Next |      |      |
 *                                 | Mute |      |------|       |------|      |      |
 *                                 |      |      |      |       | Prev |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[FNLR] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_INS,
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_VOLU,
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_CALC,     KC_MAIL,      KC_WHOM,
       KC_TRNS, KC_TRNS, LSFT(KC_DELT),LCTL(KC_INS),LSFT(KC_INS), KC_MUTE, KC_VOLD,
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,

                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_MUTE, KC_TRNS, KC_TRNS,
    // right hand
       KC_INS,   KC_EJCT, KC_PWR,  KC_SLEP, KC_WAKE, KC_PSCR, KC_SLCK,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS,
       KC_MPRV,
       KC_MNXT, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
        case MDBL0:
            if (record->event.pressed) {
              return MACRO( I(25), T(P0), T(P0), END );
            }
        break;
        case MFNLR:
            layer_invert(NUMR);
            layer_invert(FNLR);
            break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    // led 1: numeric layer
    if (layer_state & (1 << NUMR)) {
        ergodox_right_led_1_on();
    }
    // led 2: Dvorak layer
    if (default_layer_state == 1 << DVRK) {
        ergodox_right_led_2_on();
    }
    // led 3: caps lock
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      ergodox_right_led_3_on();
    }

};
