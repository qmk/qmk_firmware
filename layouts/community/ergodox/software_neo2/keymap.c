#include QMK_KEYBOARD_H
#include "debug.h"
#include "led.h"
#include "action_layer.h"
#include "keymap_extras/keymap_neo2.h"

// Layer names
#define BASE 0 // default layer
#define MDIA 1 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Del   |   1  |   2  |   3  |   4  |   5  | Play |           | Next |   6  |   7  |   8  |   9  |   0  |   ß    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   X  |   V  |   L  |   C  |   W  | Esc  |           | Esc  |   K  |   H  |   G  |   F  |   Q  |   Y    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | NeoL1  |   U  |   I  |   A  |   E  |   O  |------|           |------|   S  |   N  |   R  |   T  |   D  | NeoR1  |
 * |--------+------+------+------+------+------| L1   |           | L1   |------+------+------+------+------+--------|
 * | LShift |Ü/Ctrl| Ö/Win| Ä/Alt|   P  |   Z  |      |           |      |   B  |   M  |   ,  |   .  |   J  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |NeoL2 | Home | PgDn | PgUp | End  |                                       | Right| Down |  Up  | Left | NeoR2|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      | Enter|       |Delete|        |      |
 *                                 | Space|Backsp|------|       |------|  Enter |Space |
 *                                 |      |ace   | Tab  |       | Esc  |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_DEL,          NE_1,         NE_2,         NE_3,         NE_4,   NE_5,   KC_MPLY,
        KC_TAB,          NE_X,         NE_V,         NE_L,         NE_C,   NE_W,   KC_ESC,
        NE_L3L,        NE_U,         NE_I,         NE_A,         NE_E,   NE_O,
        KC_LSFT,         CTL_T(NE_UDIA), GUI_T(NE_ODIA), ALT_T(NE_ADIA), NE_P,   NE_Z,   TG(1),
        NE_L4L,        KC_HOME,       KC_PGDN,       KC_PGUP,       KC_END,
                                                C_S_T(KC_ESC),KC_LGUI,
                                                              KC_ENT,
                                               KC_SPC,KC_BSPC,KC_TAB,
        // right hand
        KC_MNXT,     NE_6,   NE_7,   NE_8,   NE_9,   NE_0,   NE_SS,
        KC_ESC,      NE_K,   NE_H,   NE_G,   NE_F,   NE_Q,   NE_Y,
                     NE_S,   NE_N,   NE_R,   NE_T,   NE_D,   NE_L3R,
        TG(1),       NE_B,   NE_M,   NE_COMM, NE_DOT, NE_J,   KC_RSFT,
                              KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, NE_L4R,
        KC_LALT,KC_RGUI,
        KC_DEL,
        KC_ESC,KC_ENT, KC_SPC
    ),
/* Keymap 1: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      |VolDwn| Mute |VolUp |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Btn4 |MsLeft|MsDown|MsRght| Btn5 |------|           |------|      | Prev | Stop | Play | Next |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |WhRght|WhDown| WhUp |WhLeft|WhClk |      |           |      |BwSrch|BwBack|BwHome|BwRefr|BwFwd |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |MsAcl0|MsAcl1|MsAcl2|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |Brwser|Brwser|
 *                                 | Lclk | Rclk |------|       |------|Back  |Forwd |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5,
       KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_BTN3, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,
       KC_TRNS, KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_F12,
                KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,
       KC_TRNS, KC_WSCH, KC_WBAK, KC_WHOM, KC_WREF, KC_WFWD, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_WBAK, KC_WFWD
),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    ergodox_board_led_off();

    if (host_keyboard_led_state().caps_lock) {
        ergodox_right_led_3_on();
    }

    switch (layer) {
        case MDIA:
            ergodox_right_led_2_on();
            break;
    }

};
