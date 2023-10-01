#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"
#include "debug.h"
#include "action_layer.h"

/******************************************************************************************
 * DVORAK LAYOUT (see http://djelibeibi.unex.es/dvorak/)
 * Layer 1: auxiliary keys
 *****************************************************************************************/

// LAYERS
#define BASE 0 // dvorak layout (default)
#define AUX 1  // auxiliary keys

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 * Keys with double values (like Esc/Ctrl) correspond to the 'tapped' key and the 'held' key, respectively
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |  Esc |           |  Esc |   6  |   7  |   8  |   9  |   0  | = / +  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   ~    |" / ' |, / < |. / > |   P  |   Y  |   [  |           |   ]  |   F  |   G  |   C  |   H  |   L  | / / ?  |
 * |--------+------+------+------+------+------|   {  |           |   }  |------+------+------+------+------+--------|
 * |  Tab   |   A  |   O  |   E  |U/LSft| I/L1 |------|           |------|  D/L1|R/RSft|   T  |   N  |   S  | - / _  |
 * |--------+------+------+------+------+------| LGUI |           | LGUI |------+------+------+------+------+--------|
 * | {/LSft |; / : |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | }/RSft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | L1   | CAPS | SCRL | INS  | ~L1  |                                       | ~L1  |      |      | \ / || L1     |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | HOME |  END |       | LEFT | RIGHT|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | BSPC |  DEL | PGUP |       |  UP  | SPACE  |RETURN|
 *                                 |  /   |  /   |------|       |------|   /    |  /   |
 *                                 | LCTL | LALT |PGDWN |       | DOWN | LALT   | LCTL |
 *                                 `--------------------'       `----------------------'
 *
 */
[BASE] = LAYOUT_ergodox(
        // left hand
        KC_GRV,         KC_1,     KC_2,    KC_3,   KC_4,          KC_5,           KC_ESC,
        KC_TILD,        DV_QUOT,  DV_COMM, DV_DOT, DV_P,          DV_Y,           DV_LBRC,
        KC_TAB,         DV_A,     DV_O,    DV_E,   SFT_T(DV_U),   LT(AUX, DV_I),
        SFT_T(DV_LBRC), DV_SCLN,  DV_Q,    DV_J,   DV_K,          DV_X,           KC_LGUI,
        TG(AUX),        CW_TOGG,  KC_SCRL, KC_INS, MO(AUX),
                                                            KC_HOME, KC_END,
                                                                     KC_PGUP,
                                      CTL_T(KC_BSPC), ALT_T(KC_DEL), KC_PGDN,
        // right hand
        KC_ESC,         KC_6,           KC_7,         KC_8,    KC_9,   KC_0,    DV_EQL,
        DV_RBRC,        DV_F,           DV_G,         DV_C,    DV_R,   DV_L,    DV_SLSH,
                        LT(AUX, DV_D),  SFT_T(DV_H),  DV_T,    DV_N,   DV_S,    DV_MINS,
        KC_LGUI,        DV_B,           DV_M,         DV_W,    DV_V,   DV_Z,    SFT_T(DV_RBRC),
                                        MO(AUX),      KC_NO,   KC_NO,  KC_BSLS, TG(AUX),
        KC_LEFT, KC_RIGHT,
        KC_UP,
        KC_DOWN, ALT_T(KC_ENT), CTL_T(KC_SPC)
    ),
/* Keymap 1: Aux layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  VolUp |      |      |      |      |      | SLEEP            | PWR  |      |      |      |      |      | Brigh+ |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  VolDn |  F1  |  F2  |  F3  |  F4  |      |      |           |      |      |   7  |   8  |   9  |   *  | Brigh- |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Mute  |  F5  |  F6  |  F7  |  F8  | TRANS|------|           |------|TRANS |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |PSCR  |------+------+------+------+------+--------|
 * |  TRANS |  F9  |  F10 |  F11 |  F12 |      |      |           |      |      |   1  |   2  |   3  |   /  |  TRANS |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | TRANS|CTRL-Z|CTRL-X|CTRL-C|CTRL-S|                                       | TRANS|    . |   0  |   =  |  TRANS |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | TRANS| TRANS|       | TRANS| TRANS|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | TRANS|       | TRANS|      |      |
 *                                 | Prev | Next |------|       |------| Stop | Play |
 *                                 |      |      | TRANS|       | TRANS|      |      |
 *                                 `--------------------'       `--------------------'
 */
[AUX] = LAYOUT_ergodox(
       // left hand
       KC_VOLU, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_SLEP,
       KC_VOLD, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_NO,   KC_NO,
       KC_MUTE, KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_TRNS,
       KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,   KC_NO,
       KC_TRNS, LCTL(DV_Z), LCTL(DV_X), LCTL(DV_C), LCTL(DV_S),
                                                         KC_TRNS, KC_TRNS,
                                                                  KC_TRNS,
                                                KC_MPRV, KC_MNXT, KC_TRNS,
       // right hand
            KC_PWR,  KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_BRIU,
            KC_NO,   KC_NO,   KC_7,   KC_8,   KC_9,    KC_PAST, KC_BRID,
                     KC_TRNS, KC_4,   KC_5,   KC_6,    KC_PPLS, KC_NO,
            KC_PSCR, KC_NO,   KC_1,   KC_2,   KC_3,    KC_PSLS, KC_TRNS,
                              KC_TRNS,KC_DOT, KC_0,    KC_PEQL, KC_TRNS,
       KC_TRNS  , KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_MSTP, KC_MPLY
),
};

// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case AUX:
            ergodox_right_led_1_on();
            break;
        default: // on any other layer
            ergodox_right_led_1_off();
            break;
    }

    return state;
}

bool led_update_user(led_t led_state) {
    led_state.scroll_lock ? ergodox_right_led_3_on() : ergodox_right_led_3_off();
    return true;
}

void caps_word_set_user(bool active) {
    active ? ergodox_right_led_2_on() : ergodox_right_led_2_off();
}

/* Modified to behave correctly with the DV_* keys that map to special
 * characters. */
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case DV_MINS:                        /* KC_QUOT */
        case DV_S:                           /* KC_SCLN */
        case DV_V:                           /* KC_DOT */
        case DV_W:                           /* KC_COMM */
        case DV_Z:                           /* KC_SLSH */
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case DV_UNDS: /* S(KC_QUOT) */
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
