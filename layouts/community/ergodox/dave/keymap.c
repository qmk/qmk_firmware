#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define PROG 1 // programming
#define NAVI 2 // navigation

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |   6  |   7  |   8  |   9  |   0  |   -  | BkSpce |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   Y  |           |   G  |   Y  |   U  |   I  |   O  |   P  | Enter  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | Enter  |
 * |--------+------+------+------+------+------|   H  |           |   B  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |`/Ctrl|   \  |      |      | LAlt |                                       | RAlt |   [  |   ]  |      |'/Ctrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | PrtS | PrtS |       | CtAl | CtAl |
 *                                 ,------+------+------|       |------+------+------.
 *                                 |      |      |  L1  |       |  L1  |      |      |
 *                                 | Spce | ~L2  +------|       |------+  ~L1 | Spce |
 *                                 |      |      | LGui |       | RGui |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,   KC_1,     KC_2,    KC_3,    KC_4,    KC_5,   KC_6,
        KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,
        KC_LCTRL, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,   KC_H,
        CTL_T(KC_GRV),KC_NUBS,KC_NO, KC_NO,   KC_LALT,
                                                  KC_PSCREEN, KC_PSCREEN,
                                                      TO(PROG),
                                               KC_SPC, MO(NAVI), KC_LGUI,
        // right hand
             KC_6,    KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_BSPC,
             KC_G,    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_ENTER,
                      KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_ENTER,
             KC_B,    KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,
                              KC_RALT,KC_LBRC,KC_RBRC,KC_NO,   CTL_T(KC_QUOT),
             MT(0x5, KC_NO), MT(0x5, KC_NO),
             TO(PROG),
             KC_RGUI, MO(PROG), KC_SPC
    ),

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |  K/  |  K*  |  K-  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   (  |   )  |   |  |      |           |      |      |  K7  |  K8  |  K9  |  K+  |   #    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   {  |   }  |   `  |------|           |------|      |  K4  |  K5  |  K6  |  K+  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |      |  K1  |  K2  |  K3  |  K=  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  K0  |  K0  |  K.  |  K=  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  L2  |       |  L2  |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// PROGRAMMING
[PROG] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
       KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
       KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,
                                      TO(NAVI),
                               KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_NO,  KC_PSLS, KC_PAST, KC_PMNS, KC_EQUAL,
       KC_TRNS, KC_TRNS, KC_P7,  KC_P8,   KC_P9,   KC_PPLS, KC_NUHS,
                KC_TRNS, KC_P4,  KC_P5,   KC_P6,   KC_PPLS, KC_QUOT,
       KC_TRNS, KC_TRNS, KC_P1,  KC_P2,   KC_P3,   KC_PENT, KC_TRNS,
                         KC_P0,  KC_P0,   KC_PDOT, KC_PENT, KC_TRNS,
       KC_TRNS, KC_TRNS,
       TO(NAVI),
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Navigation and system keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | Home |  Up  | End  | Ins  | PgUp |      |           |      |      |      | Ins  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Left | Down | Rght | Del  | PgDn |------|           |------|      | Back | Del  | Fwrd |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Lclk | MsUp | Rclk |      |      |      |           |      |      | Prev | Play | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | MsLt | MsDn | MsRt |      |                                       |VolDn | Mute |VolUp |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  L0  |       |  L0  |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NAVIGATION
[NAVI] = LAYOUT_ergodox(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
       KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_INS,  KC_PGUP, KC_TRNS,
       KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_PGDN,
       KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                         TO(BASE),
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_WBAK, KC_DEL,  KC_WFWD, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       TO(BASE),
       KC_TRNS, KC_TRNS, KC_TRNS
),
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
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    /* leds is a static array holding the current brightness of each of the
     * three keyboard LEDs. It's 4 long simply to avoid the ugliness of +1s and
     * -1s in the code below, and because wasting a byte really doesn't matter
     * that much (no, it *doesn't*, stop whinging!). Note that because it's
     * static it'll maintain state across invocations of this routine.
     */
    static uint8_t leds[4];
    uint8_t led;
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();

    /* Loop over each LED/layer */
    for (led = 1; led <= 3; ++led) {
        /* If the current layer matches the current LED, increment its
         * brightness by 1 up to a maximum of 255. If the current layer doesn't
         * match, decrement its brightness by 1 down to a minimum of zero.
         */
        leds[led] += (layer == led) ?
            (leds[led] < 255 ? 1 : 0):
            (leds[led] > 0 ? -1 : 0);
        /* Set LED state according to the new brightness */
        if (leds[led]) {
            ergodox_right_led_on(led);
            ergodox_right_led_set(led, leds[led]);
        }
        else {
            ergodox_right_led_off(led);
        }
    }


};
