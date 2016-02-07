/* TypeMatrix-2030-like keymap  */
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "led.h"
#include "keymap_extras/keymap_bepo.h"

#define BASE 0 // default layer
#define NUMR 8 // numeric layer
#define FNLR 9 // fn layer

#define MDBL0 1
#define MFNLR 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   $    |   "  |   «  |   »  |   (  |   )  | Del  |           | Del  |   @  |   +  |   -  |   /  |   *  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   B  |   É  |   P  |   O  |   È  |Backsp|           |Backsp|   ^  |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
 * |   W    |   A  |   U  |   I  |   E  |   ,  |------|           |------|   C  |   T  |   S  |   R  |   N  |   M    |
 * |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
 * | LShift |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |  fn  | LGui | Play |App/Alt|                                      |Alt Gr|   %  | Home |   Ç  |End/Ctl|
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
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        BP_DLR,     KC_1,      KC_2,    KC_3,    KC_4,          KC_5,    KC_DELT,
        KC_TAB,     BP_B,      BP_ECUT, BP_P,    BP_O,          BP_EGRV, KC_BSPC,
        BP_W,       BP_A,      BP_U,    BP_I,    BP_E,          BP_COMM,
        KC_LSFT,    BP_AGRV,   BP_Y,    BP_X,    BP_DOT,        BP_K,    KC_ENT,
        KC_LCTL,    M(MFNLR),  KC_LGUI, KC_MPLY, ALT_T(KC_APP),

                                              ALT_T(KC_ESC),  TG(NUMR),
                                                              KC_PGUP,
                                            KC_SPC, KC_LSFT,  KC_PGDN,

        // right hand
        KC_DELT,   KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     BP_EQL,
        KC_BSPC,   BP_DCRC,  BP_V,    BP_D,    BP_L,    BP_J,     BP_Z,
                   BP_C,     BP_T,    BP_S,    BP_R,    BP_N,     BP_M,
        KC_ENT,    BP_APOS,  BP_Q,    BP_G,    BP_H,    BP_F,     KC_RSFT,
                             BP_ALGR, BP_PERC, KC_HOME, BP_CCED,  CTL_T(KC_END),

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
[NUMR] = KEYMAP(
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
[FNLR] = KEYMAP(
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
void * matrix_init_user(void) {
    return NULL;
};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    // led 1: numeric layer
    if (layer_state & (1 << NUMR)) {
        ergodox_right_led_1_on();
    }
    // led 3: caps lock
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      ergodox_right_led_3_on();
    }
    return NULL;
};
