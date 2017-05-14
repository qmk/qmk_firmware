/*
 * About this keymap:
 * 
 * The Dvorak layout shown herestems from my early Kinesis years, using the Contour PS/2 with a Dvorak
 * software layout. Because of this, the RBRC and LBRC were on opposite sides of the board in the corner
 * keys. I've decided to continue using this layout with my ErgoDox.
 *
 * The QWERTY layout shown here is based entirely on the Kinesis Advantage layout, with the additional
 * keys as shown in the diagrams. The Colemak layout is merely an adaptation of that.
 *
 * I've enabled persistent keymaps for Qwerty, Dvorak and Colemak layers, similar to the default Planck
 * layouts.
 *
 */

#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DV 0 // Dvorak layer
#define _QW 1 // Qwerty layer
#define _CM 2 // Colemak layer
#define _MD 3 // Media Layer
#define _KP 4 // Keypad Layer

// Macro name shortcuts
#define DVORAK M(_DV)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 0 : Dvorak
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | ESC  | | ESC  |   6  |   7  |   8  |   9  |   0  |   /    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   '  |   ,  |   .  |   P  |   Y  |      | |      |   F  |   G  |   C  |   R  |   L  |   \    |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | CapsLk |   A  |   O  |   E  |   U  |   I  |------| |------|   D  |   H  |   T  |   N  |   S  |   -    |
 * |--------+------+------+------+------+------| _MD  | | _KP  |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K  |   X  |      | |      |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   | LGUI |   `  |  INS | Left | Rght |                             |  Up  |  Dn  |   [  |   ]  | RGUI |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | LCTL | LALT | | RALT | RCTL |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | Home | | PgUp |      |      |
 *                               | BkSp | Del  |------| |------| Enter| Space|
 *                               |      |      | End  | | PgDn |      |      |
 *                               `--------------------' `--------------------'
 *
 */
[_DV] = KEYMAP(
        // left hand
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_ESC,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    XXXXXXX,
        KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    MO(_MD),
        KC_LGUI, KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        KC_ESC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH,
        XXXXXXX, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,
                 KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
        MO(_KP), KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                          KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_RGUI,
        KC_RALT, KC_RCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT,  KC_SPC
  ),


/* Layer 1: QWERTY
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | ESC  | | ESC  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      | |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | CapsLk |   A  |   S  |   D  |   F  |   G  |------| |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| _MD  | | _KP  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   | LGUI |   `  |  INS | Left | Rght |                             |  Up  |  Dn  |   [  |   ]  | RGUI |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | LCTL | LALT | | RALT | RCTL |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | Home | | PgUp |      |      |
 *                               | BkSp | Del  |------| |------| Enter| Space|
 *                               |      |      | End  | | PgDn |      |      |
 *                               `--------------------' `--------------------'
 */
[_QW] = KEYMAP(
        // left hand
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,
        KC_DELT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_MD),
        KC_LGUI, KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        KC_ESC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        MO(_KP), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_RGUI,
        KC_LALT, KC_LCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
  ),


/* Layer 2 : Colemak
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | ESC  | | ESC  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |      | |      |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | BkSpc  |   A  |   R  |   S  |   T  |   D  |------| |------|   H  |   N  |   E  |   I  |   O  |   '    |
 * |--------+------+------+------+------+------| _MD  | | _KP  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   K  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   | LGUI |   `  |  INS | Left | Rght |                             |  Up  |  Dn  |   [  |   ]  | RGUI |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | LCTL | LALT | | RALT | RCTL |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | Home | | PgUp |      |      |
 *                               | BkSp | Del  |------| |------| Enter| Space|
 *                               |      |      | End  | | PgDn |      |      |
 *                               `--------------------' `--------------------'
 */
[_CM] = KEYMAP( 
        // left hand
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,
        KC_DELT, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    XXXXXXX,
        KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_MD),
        KC_LGUI, KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        KC_ESC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
                 KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        MO(_KP), KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_RGUI,
        KC_LALT, KC_LCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
  ),


/* Layer 3 : Media layer
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * | TEENSY |  F1  |  F2  |  F3  |  F4  |  F5  | F11  | |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * |        |      | PrSc | ScLk | Paus |      |      | |      |      | Mute | Vol- | Vol+ |      |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------| |------| Stop | Prev | Play | Next | Sel  |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * |        |      |Dvorak|Qwerty|Colemk|      |      | |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                             |      |      |      |      |      |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      |      |      | |      |      |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      |      | |      |      |      |
 *                               |      |      |------| |------|      |      |
 *                               |      |      |      | |      |      |      |
 *                               `--------------------' `--------------------'
 */
[_MD] = KEYMAP(
        // left hand
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
        _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, DVORAK,  QWERTY,  COLEMAK, _______, _______,
        _______, _______, _______, _______, _______,
                                            _______, _______,
                                                     _______,
                                   _______, _______, _______,
        // right hand
        KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
                 KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, _______,
        _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,
        _______, _______,
        _______,
        _______, _______, _______
  ),


/* Layer 4 : Keypad layer
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * | Power  |      |      |      |      |      |      | |      |      | NmLk | KP = | KP / | KP * |        |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Sleep  |      |      |      |      |      |      | |      |      | KP 7 | KP 8 | KP 9 | KP - |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | Wake   |      |      |      |      |      |------| |------|      | KP 4 | KP 5 | KP 6 | KP + |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      | |      |      | KP 1 | KP 2 | KP 3 |KP Ent|        |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                             | KP 0 |      | KP . |KP Ent|      |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      |      |      | |      |      |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      |      | |      |      |      |
 *                               |      |      |------| |------|      |      |
 *                               |      |      |      | |      |      |      |
 *                               `--------------------' `--------------------'
 */
[_KP] = KEYMAP(
        // left hand
        KC_PWR,  _______, _______, _______, _______, _______, _______,
        KC_SLEP, _______, _______, _______, _______, _______, _______,
        KC_WAKE, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
                                            _______, _______,
                                                     _______,
                                   _______, _______, _______,
        // right hand
        _______, _______, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
        _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
                 _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
        _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                          KC_P0,   _______, KC_PDOT, KC_PENT, _______,
        _______, _______,
        _______,
        _______, _______, _______
  ),

};

const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _DV:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DV);
          }
          break;
        case _QW:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QW);
          }
          break;
        case _CM:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_CM);
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
