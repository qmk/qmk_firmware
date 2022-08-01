/*
 * About this keymap:
 *
 * The Dvorak layout shown here stems from my early Kinesis years, using the Contour PS/2 with a Dvorak
 * software layout. Because of this, the RBRC and LBRC were on opposite sides of the board in the corner
 * keys. When I originally set up this keymap, I'd decided to continue using this layout with my ErgoDox.
 * I've since modified my layout to be more effective for me and to more closely match my other ortho
 * keyboard layouts
 *
 * The QWERTY layout shown here is based entirely on the Kinesis Advantage layout, with the additional
 * keys as shown in the diagrams. The Colemak layout is merely an adaptation of that.
 *
 * I've enabled persistent keymaps for Qwerty, Dvorak and Colemak layers, similar to the default Planck
 * layouts.
 *
 * What's New:
 *
 * I've overhauled this Dvorak layout a bit to more match what I've got on my other Ortho boards. For
 * some keys, I'm moving away from my old Kinesis keymap and adding the brackets and braces to the
 * inner column vertical keys. I figure this will help me have better ease of use. In this update, I
 * have also removed the keypad layer since I no longer use that at all, and have remapped the MEDIA
 * layer a bit.
 *
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _DVORAK,
    _QWERTY,
    _COLEMAK,
    _MEDIA,
};

enum custom_keycodes { DVORAK = SAFE_RANGE, QWERTY, COLEMAK };

// Aliases to make the keymap more uniform
#define GUI_END GUI_T(KC_END)
#define MEDIA MO(_MEDIA)
#define MACLOCK LGUI(LCTL(KC_Q))

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 0 : Dvorak
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |      | |      |   6  |   7  |   8  |   9  |   0  |  ~     |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   '  |   ,  |   .  |   P  |   Y  |      | |      |   F  |   G  |   C  |   R  |   L  |   \    |
 * |--------+------+------+------+------+------|  [   | |   ]  |------+------+------+------+------+--------|
 * | CapsLk |   A  |   O  |   E  |   U  |   I  |------| |------|   D  |   H  |   T  |   N  |   S  |   -    |
 * |--------+------+------+------+------+------|  {   | |   }  |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K  |   X  |      | |      |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |MEDIA |   `  |   ~  | Left | Rght |                             |  Up  |  Dn  |   /  |   =  | MEDIA|
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

[_DVORAK] = LAYOUT_ergodox(
        // left hand
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_LBRC,
        KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_LCBR,
        MEDIA,   KC_GRV,  KC_TILD, KC_LEFT, KC_RGHT,
        // left thumb
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_BSPC, KC_DEL,  GUI_END,
        // right hand
        XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH,
        KC_RBRC, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,
                 KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
        KC_RCBR, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                          KC_UP,   KC_DOWN, KC_SLSH, KC_EQL,  MEDIA,
        // right thumb
        KC_RGUI, KC_RCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT,  KC_SPC
  ),

/* Layer 1: QWERTY
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |      | |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      | |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|  [   | |   ]  |------+------+------+------+------+--------|
 * | CapsLk |   A  |   S  |   D  |   F  |   G  |------| |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  {   | |   }  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |MEDIA |   `  |   =  | Left | Rght |                             |  Up  |  Dn  |   [  |   ]  | MEDIA|
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | LCTL | LALT | | RGUI | RCTL |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | Home | | PgUp |      |      |
 *                               | BkSp | Del  |------| |------| Enter| Space|
 *                               |      |      | End  | | PgDn |      |      |
 *                               `--------------------' `--------------------'
 */
[_QWERTY] = LAYOUT_ergodox(
        // left hand
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR,
        MEDIA,   KC_GRV,  KC_EQL,  KC_LEFT, KC_RGHT,
        // left thumb
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH,
        KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_RCBR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, MEDIA,
        // right thumb
        KC_RGUI, KC_RCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
  ),


/* Layer 2 : Colemak
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |      | |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |      | |      |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|  [   | |   ]  |------+------+------+------+------+--------|
 * | BkSpc  |   A  |   R  |   S  |   T  |   D  |------| |------|   H  |   N  |   E  |   I  |   O  |   '    |
 * |--------+------+------+------+------+------|  {   | |   }  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   K  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   | MEDIA|   `  |   =  | Left | Rght |                             |  Up  |  Dn  |   [  |   ]  | MEDIA|
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      | LCTL | LALT | | RGUI | RCTL |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      | Home | | PgUp |      |      |
 *                               | BkSp | Del  |------| |------| Enter| Space|
 *                               |      |      | End  | | PgDn |      |      |
 *                               `--------------------' `--------------------'
 */
[_COLEMAK] = LAYOUT_ergodox(
        // left hand
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,
        KC_DEL,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_LBRC,
        KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR,
        MEDIA,   KC_GRV,  KC_EQL,  KC_LEFT, KC_RGHT,
        // left thumb
                                            KC_LCTL, KC_LALT,
                                                     KC_HOME,
                                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
                 KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_RCBR, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, MEDIA,
        // right thumb
        KC_RGUI, KC_RCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
  ),


/* Layer 3 : Media layer
 * ,--------------------------------------------------. ,--------------------------------------------------.
 * |   F11  |  F1  |  F2  |  F3  |  F4  |  F5  |TEENSY| |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 * |--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      | |      |      | PrSc | ScLk | Paus |      |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * | CapsLk |      | Mute | Vol- | Vol+ |      |------| |------|      |Dvorak|Qwerty|Colmak|      |        |
 * |--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 * |        | Stop | Prev | Play | Next | Sel  |      | |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                             |      |      |      |      |      |
 *   `----------------------------------'                             `----------------------------------'
 *                                      ,-------------. ,-------------.
 *                                      |      |MacLck| |MacLck|      |
 *                               ,------|------|------| |------+------+------.
 *                               |      |      |      | |      |      |      |
 *                               |      |      |------| |------|      |      |
 *                               |      |      |      | |      |      |      |
 *                               `--------------------' `--------------------'
 */
[_MEDIA] = LAYOUT_ergodox(
        // left hand
        KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   RESET,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
        KC_CAPS, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, _______,
        _______, _______, _______, _______, _______,
                                            _______, MACLOCK,
                                                     _______,
                                   _______, _______, _______,
        // right hand
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
        _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
                 _______, DVORAK,  QWERTY,  COLEMAK, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,
        MACLOCK, _______,
        _______,
        _______, _______, KC_INS
  ),

};

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case DVORAK:
                set_single_persistent_default_layer(_DVORAK);
                return false;
            case QWERTY:
                set_single_persistent_default_layer(_QWERTY);
                return false;
            case COLEMAK:
                set_single_persistent_default_layer(_COLEMAK);
                return false;
        }
    }
    return true;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

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
