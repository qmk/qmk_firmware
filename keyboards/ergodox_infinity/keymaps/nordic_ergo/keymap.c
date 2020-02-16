// Nordic layout for Ergodox infinity
#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_nordic.h"
#include "keymap_german.h"

enum layer_names {
    BASE,
    FUNCL,
    SYMB,
    MDIA
};

enum custom_keycodes {
    VRSN = SAFE_RANGE,
    RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   |   1  |   2  |   3  |   4  |   5  |  §½  |           | PRSC |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Caps  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------|  L2  |           |  L2  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  -   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  ¨^  |  <|>  | LGui | Alt  |                                       | Ctrl |  Alt  |  ´`  |   +  | RGui |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LEFT |RIGHT |       | DOWN | UP   |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Del   |------|       |------|  Enter | Bkspc|
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */

[BASE] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
    KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,  KC_5,   KC_GRV,
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,  KC_T,   TG(1),
    KC_CAPS,  KC_A,   KC_S,   KC_D,   KC_F,  KC_G,
    KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,  KC_B,   MO(2),
    KC_LCTRL, MO(3),  KC_EQL, KC_LGUI, KC_LALT,
                                            KC_NLCK,  KC_SLCK,
                                            KC_HOME,
                                            KC_SPC,   KC_DEL, KC_END,

    // right hand
    KC_BSLS,  KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
    TG(1),    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,
              KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    MO(2),    KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_NONUS_BSLASH,
    KC_LEFT,  KC_DOWN, KC_UP, KC_RIGHT, KC_RBRC,
    KC_RGUI,  KC_RALT,
    KC_PGUP,
    KC_PGDN,  KC_ENT, KC_BSPC
),
/* Keymap 1: Basic layer with functions
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |  ¨   |       |     |       |                                       |      |       |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */

[FUNCL] = LAYOUT_ergodox(  // layer 1 : functions
    // left hand
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,
                                            _______,  _______,
                                            _______,
                                            _______,  _______,  _______,
    // right hand
    KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,
    _______,  _______,
    _______,
    _______,  _______,  _______
),

/* Keymap 2: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat| BLTOG|       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|  BL+ |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |  BL- |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
   // left hand
   _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,
   _______,  DE_EXLM,  DE_AT,    DE_LCBR,  DE_RCBR,  DE_PIPE,  _______,
   _______,  DE_HASH,  DE_DLR,   DE_LPRN,  DE_RPRN,  DE_GRV,
   _______,  DE_PERC,  DE_CIRC,  DE_LBRC,  DE_RBRC,  DE_TILD,  _______,
   _______,  _______,  _______,  _______,  _______,
                                           RGB_MOD,  BL_TOGG,
                                           BL_INC,
                                           RGB_VAD,  RGB_VAI,  BL_DEC,
   // right hand
   KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
   _______,  KC_UP,    KC_7,     KC_8,     KC_9,     DE_ASTR,  _______,
             KC_DOWN,  KC_4,     KC_5,     KC_6,     DE_PLUS,  _______,
   _______,  DE_AMPR,  KC_1,     KC_2,     KC_3,     DE_BSLS,  _______,
   _______,  KC_DOT,   KC_0,     DE_EQL,   _______,
   RGB_TOG,  RGB_SLD,
   _______,
   _______,  RGB_HUD,  RGB_HUI
),

/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
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
   RESET,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,
   _______,  _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  _______,  _______,
   _______,  KC_BTN4,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_BTN5,
   _______,  KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  KC_BTN3,  _______,
   _______,  _______,  KC_ACL0,  KC_ACL1,  KC_ACL2,
                                           _______,  _______,
                                           _______,
                                           KC_BTN1,  KC_BTN2,  _______,
   // right hand
   KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
   _______, _______,   KC_VOLD,  KC_MUTE,  KC_VOLU,  _______,  _______,
            _______,   KC_MPRV,  KC_MSTP,  KC_MPLY,  KC_MNXT,  _______,
   _______, KC_WSCH,   KC_WBAK,  KC_WHOM,  KC_WREF,  KC_WFWD,  _______,
   _______, _______,   _______,  _______,  _______,
   _______, _______,
   _______,
   _______, KC_WBAK, KC_WFWD
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    // MACRODOWN only works in this function
    switch (id) {
        case 0:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            break;
        case 1:
            if (record->event.pressed) {  // For resetting EEPROM
                eeconfig_init();
            }
            break;
    }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
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
void matrix_init_user(void){

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }
};
