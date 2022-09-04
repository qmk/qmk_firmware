#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

/******************************************************************************************
 * SPANISH DVORAK LAYOUT (see http://djelibeibi.unex.es/dvorak/)
 * Layer 1: auxiliary keys
 * Layer 2: full qwerty layout
 ******************************************************************************************
 * IMPORTANT: Software layout must be set to SPANISH QWERTY to work properly
 *****************************************************************************************/

// LAYERS
#define BASE    0 // dvorak layout (default)
#define AUX     1 // auxiliary keys
#define QWERTY  2 // qwerty layout

// MACROS
#define OBRACE 0 // key { or shift
#define CBRACE 1 // key } or shift
#define OBRACK 2 // key [ or left alt
#define CBRACK 3 // key ] or left alt
#define CAPS   4 // caps lock

// LEDS
#define USB_LED_NUM_LOCK    0
#define USB_LED_CAPS_LOCK   1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE     3
#define USB_LED_KANA        4

// TIMERS
#define KEY_TAP_FAST 85
#define KEY_TAP_SLOW 95

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 * Keys with double values (like Esc/Ctrl) correspond to the 'tapped' key and the 'held' key, respectively
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   \    |   1  |   2  |   3  |   4  |   5  |  <>  |           |   ¡  |   6  |   7  |   8  |   9  |   0  |   '    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | F1/~L1 |   .  |   ,  |   Ñ  |   P  |   Y  |MEH_T |           |  L1  |   F  |   G  |   C  |   H  |   L  |ALL_T/+ |
 * |--------+------+------+------+------+------| DEL  |           | ~L1  |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   R  |   T  |   N  |   S  |'/RCtrl |
 * |--------+------+------+------+------+------| LGUI |           | RALT |------+------+------+------+------+--------|
 * | {/LSft |   -  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | }/RSft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |[/LALT| HOME |PGDOWN| PGUP | END  |                                       | LEFT | DOWN |  UP  |RIGHT |]/LALT|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |F5/CAG|F6/~L1|       |F7/~L1|F8/CAG|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |F4/CA |       |F11/CA|        |      |
 *                                 | ENTER| TAB  |------|       |------|  BSPC  | SPACE|
 *                                 |      |      |F3/SA |       |F12/SA|        |      |
 *                                 `--------------------'       `----------------------'
 *  CAG = CTRL-ALT-GUI
 *   CA = CTRL-ALT
 *   SA = SHIFT-ALT
 *
 */
[BASE] = LAYOUT_ergodox(
        // left hand
        KC_GRAVE,       KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_NONUS_BSLASH,
        LT(AUX, KC_F1), KC_DOT, KC_COMM,KC_SCLN,KC_P,   KC_Y,   MEH_T(KC_DEL),
        CTL_T(KC_ESC),  KC_A,   KC_O,   KC_E,   KC_U,   KC_I,
        M(OBRACE),      KC_SLSH,KC_Q,   KC_J,   KC_K,   KC_X,   KC_LGUI,
        M(OBRACK),      KC_HOME,KC_PGDN,KC_PGUP,KC_END,
                                                           LCAG_T(KC_F5),  LT(AUX, KC_F6),
                                                           MT((MOD_LALT | MOD_LCTL), KC_F4),
                                           KC_ENT,KC_TAB,MT((MOD_LALT | MOD_LSFT), KC_F3),
        // right hand
                    KC_EQL,    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
                    TT(AUX),   KC_F,   KC_G,   KC_C,   KC_H,   KC_L,   ALL_T(KC_RBRACKET),
                               KC_D,   KC_R,   KC_T,   KC_N,   KC_S,   CTL_T(KC_QUOTE),
                    KC_RALT,   KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   M(CBRACE),
                                       KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,M(CBRACK),
        LT(AUX, KC_F7), LCAG_T(KC_F8),
        MT((MOD_LALT | MOD_LCTL), KC_F11),
        MT((MOD_LALT | MOD_LSFT), KC_F12),KC_BSPC, KC_SPC
    ),
/* Keymap 1: Aux layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  | SLEEP            | PWR  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  <   |  >   | MsUp |      |      |      |           | ~L0  |      |   7  |   8  |   9  |   *  |  `^    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |   4  |   5  |   6  |   +  |   Ç    |
 * |--------+------+------+------+------+------|      |           |PSCR  |------+------+------+------+------+--------|
 * |CAPSLOCK|      |      |      |      |      |      |           |      |      |   1  |   2  |   3  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |CTRL-S|CTRL-Z|CTRL-X|CTRL-C|CTRL-V|                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      | Play |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | VolUp|      |      |
 *                                 | Lclk | Rclk |------|       |------| Prev | Next |
 *                                 |      |      |  L2  |       | VolDn|      |      |
 *                                 `--------------------'       `--------------------'
 */
[AUX] = LAYOUT_ergodox(
       // left hand
       KC_NO  , KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_SLEP,
       KC_TRNS, KC_NONUS_BSLASH, LSFT(KC_NONUS_BSLASH), KC_MS_U, KC_NO, KC_NO, KC_NO,
       KC_NO  , KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO  ,
       M(CAPS), KC_NO, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO,
       LCTL(KC_S), LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
                                                            KC_NO  , KC_TRNS,
                                                                       KC_NO,
                                                KC_BTN1, KC_BTN2, TG(QWERTY),
       // right hand
            KC_PWR,  KC_F6,   KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,
            KC_TRNS, KC_NO,   KC_7,   KC_8,   KC_9,    KC_PAST, KC_LBRACKET,
                     KC_NO,   KC_4,   KC_5,   KC_6,    KC_PPLS, KC_BSLASH,
            KC_PSCR, KC_NO,   KC_1,   KC_2,   KC_3,    KC_PSLS, KC_NO,
                              KC_NO  ,KC_DOT, KC_0,    KC_PEQL, KC_NO,
       KC_TRNS, KC_MPLY,
       KC_VOLU,
       KC_VOLD, KC_MPRV, KC_MNXT
),
/* Keymap 2: QWERTY layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   \    |   1  |   2  |   3  |   4  |   5  |  <>  |           |   ¡  |   6  |   7  |   8  |   9  |   0  |   '    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TRANS |   Q  |   W  |   E  |   R  |   T  |MEH_T |           | TRANS|   Y  |   U  |   I  |   O  |   P  |ALL_T/+ |
 * |--------+------+------+------+------+------| DEL  |           |      |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ñ  |'/RCtrl |
 * |--------+------+------+------+------+------| LGUI |           | RALT |------+------+------+------+------+--------|
 * | {/LSft |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   -  | }/RSft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |[/LALT| HOME |PGDOWN| PGUP | END  |                                       | LEFT | DOWN |  UP  |RIGHT |]/LALT|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |F5/CAG| TRANS|       | TRANS|F8/CAG|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |F4/CA |       |F11/CA|        |      |
 *                                 | ENTER| TAB  |------|       |------|  BSPC  | SPACE|
 *                                 |      |      | TRANS|       |F12/SA|        |      |
 *                                 `--------------------'       `----------------------'
 *  CAG = CTRL-ALT-GUI
 *   CA = CTRL-ALT
 *   SA = SHIFT-ALT
 *
 */
[QWERTY] = LAYOUT_ergodox(
        // left hand
        KC_GRAVE,       KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_NONUS_BSLASH,
        KC_TRNS,        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   MEH_T(KC_DEL),
        CTL_T(KC_ESC),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        M(OBRACE),      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LGUI,
        M(OBRACK),      KC_HOME,KC_PGDN,KC_PGUP,KC_END,
                                                                  LCAG_T(KC_F5),  KC_TRNS,
                                                           MT((MOD_LALT | MOD_LCTL), KC_F4),
                                                                    KC_ENT,KC_TAB,KC_TRNS,
        // right hand
                    KC_EQL,    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,
                    KC_TRNS,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   ALL_T(KC_RBRACKET),
                               KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,CTL_T(KC_QUOTE),
                    KC_RALT,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,M(CBRACE),
                                       KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,M(CBRACK),
        KC_TRNS, LCAG_T(KC_F8),
        MT((MOD_LALT | MOD_LCTL), KC_F11),
        MT((MOD_LALT | MOD_LSFT), KC_F12),KC_BSPC, KC_SPC
),
};

static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case OBRACE: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                    register_code(KC_RALT);
                    register_code(KC_QUOTE);
                    unregister_code(KC_QUOTE);
                    unregister_code(KC_RALT);
                }
            }
            break;
        }
        case CBRACE: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                    register_code(KC_RALT);
                    register_code(KC_BSLS);
                    unregister_code(KC_BSLS);
                    unregister_code(KC_RALT);
                }
            }
            break;
        }
        case OBRACK: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                    register_code(KC_RALT);
                    register_code(KC_LBRACKET);
                    unregister_code(KC_LBRACKET);
                    unregister_code(KC_RALT);
                }
            }
            break;
        }
        case CBRACK: {
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
                if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
                    register_code(KC_RALT);
                    register_code(KC_RBRACKET);
                    unregister_code(KC_RBRACKET);
                    unregister_code(KC_RALT);
                }
            }
            break;
        }
        case CAPS: {
            if (record->event.pressed) {
                register_code(KC_CAPSLOCK);
            } else {
                unregister_code(KC_CAPSLOCK);
            }
            break;
        }
      }
    return MACRO_NONE;
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
        case 1:
            ergodox_right_led_3_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

    // Turn the caps lock led on
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    }

}
