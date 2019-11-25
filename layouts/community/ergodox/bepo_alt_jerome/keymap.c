#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_bepo.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MOUSE 2 // media keys

enum macros {
    // Characters that do not exist in CSA and must be implemented based on unicode support
    // Note: these are intentionally declared first to be used as indexes in spec_chars below

    // macros for characters that don't have a simple key combination in LR_CA_MULT_ALTGR
    M_CRC,
    // other layer macros
    M_DBL0, // double 0
    M_FNLR, // fn layer
    M_NMAL, // num+alt
    M_MAIL, // mail pro.
    M_SKCC, // Copié collé en une touche
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   "  |   «  |   »  |   (  |   )  |  $   |           |  %   |   @  |   +  |   -  |   /  |   *  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   B  |   É  |   P  |   O  |   È  |  Ç   |           | Tab  |   ^  |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | W      |   A  |   U  |   I  |   E  |   ,  |------|           |------|   C  |   T  |   S  |   R  |   N  |   M    |
 * |--------+------+------+------+------+------|  Del |           | BkSp |------+------+------+------+------+--------|
 * | Ctrl   |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  |  Ctrl  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGui | Home | Pgup |Pgdown| End  |                                       | Left | Down |  Up  |Right | RGui |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Ctrl+C|Ctrl+V|       |  L1  |  L2  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | ~L1  |       | App  |        |      |
 *                                 | Space|Shift |------|       |------|  Shift |Enter |
 *                                 |      |      |Alt/Enter|    | AltGr|        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,       BP_DOUBLE_QUOTE, BP_LEFT_GUILLEMET, BP_RIGHT_GUILLEMET, BP_LEFT_PAREN, BP_RIGHT_PAREN, BP_DOLLAR,
        KC_TAB, BP_B,            BP_E_ACUTE,        BP_P,               BP_O,          BP_E_GRAVE,     BP_C_CEDILLA,
        BP_W,         BP_A,            BP_U,              BP_I,               BP_E,          BP_COMMA,
        KC_LCTL,      BP_A_GRAVE,      BP_Y,              BP_X,               BP_DOT,        BP_K,           KC_DELT,
          KC_LGUI,    KC_HOME,         KC_PGUP,           KC_PGDN,            KC_END,

					           LCTL(BP_C), LCTL(BP_V),
                                                               MO(SYMB),
                                              KC_SPC, KC_LSFT, ALT_T(KC_ENT),
        // right hand
             BP_PERCENT, BP_AT,              BP_PLUS, BP_MINUS, BP_SLASH, BP_ASTERISK, BP_EQUAL,
             KC_TAB,     BP_DEAD_CIRCUMFLEX, BP_V,    BP_D,     BP_L,     BP_J,        BP_Z,
                         BP_C,               BP_T,    BP_S,     BP_R,     BP_N,        BP_M,
             KC_BSPC,    BP_APOSTROPHE,      BP_Q,    BP_G,     BP_H,     BP_F,        KC_RCTL,
                                             KC_LEFT, KC_DOWN,  KC_UP,    KC_RGHT,     KC_LGUI,
             TG(SYMB), TG(MOUSE),
             KC_APP,
             KC_RALT,KC_RSFT, KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |P.Scr|NumLock|   +  |  -   |  /   |  *   |    =   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | VolUp  |   F7 |  F8  |  F9  |  F10 | F11  |  F12 |           |      |   ^  |   7  |   8  |   9  |   +  |ScrLock |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Mute  | Prev | Play | Stop | Next | Calc |------|           |------|   ˇ  |   4  |   5  |   6  |   +  | Pause  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | VolDn  | Undo | Cut  | Copy | Paste| Redo |      |           |      |  Ins |   1  |   2  |   3  |Enter |  ,     |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |@mail |     |LCTL(BP_B)|LCTL(BP_U)|      |                               |   0   |  00  |   .  |Enter |LCTL(BP_L)|
 *   `------------------------------------------'                               `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,
       KC_VOLU,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,
       KC_MUTE,   KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT,  KC_CALC,
       KC_VOLD,   KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE, KC_CALC, KC_TRNS,
         M(M_MAIL), M(M_SKCC), LCTL(BP_B),LCTL(BP_U), LCTL(BP_B),

                                       KC_TRNS, KC_TRNS,
                                                KC_TRNS,
                               KC_TRNS,KC_TRNS, KC_TRNS,
       // right hand
       KC_PSCR, KC_LNUM,            KC_KP_PLUS,KC_KP_MINUS,KC_KP_SLASH,KC_KP_ASTERISK,KC_KP_EQUAL,
       KC_TRNS, BP_DEAD_CIRCUMFLEX, KC_KP_7,   KC_KP_8,    KC_KP_9,    KC_KP_PLUS,    KC_SLCK,
                RALT(BP_V),         KC_KP_4,   KC_KP_5,    KC_KP_6,    KC_KP_PLUS,    KC_PAUS,
       KC_TRNS, KC_INS,             KC_KP_1,   KC_KP_2,    KC_KP_3,    KC_KP_ENTER,   KC_KP_COMMA,
                                    KC_KP_0,   M(M_DBL0),KC_KP_DOT,  KC_KP_ENTER,   RGUI(KC_L),
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |RGB_M_X |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | WhUp | Lclk | MsUp | Rclk | Acc0 |      |           |      | Acc0 | WhLft| WhUp | WhRgh|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | WhDwn|MsLeft|MsDown|MsRght| Acc1 |------|           |------| Acc1 | Lclk | Cclk | Rclk |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Btn4 | Cclk | Btn5 | Acc2 |      |           |      | Acc2 | Btn4 | WhDwn| Btn5 |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MOUSE
[MOUSE] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_MS_WH_UP,   KC_BTN1, KC_MS_U, KC_BTN2, KC_ACL0, KC_TRNS,
       KC_TRNS, KC_MS_WH_DOWN, KC_MS_L, KC_MS_D, KC_MS_R, KC_ACL1,
       KC_TRNS, KC_TRNS,       KC_BTN4, KC_BTN3, KC_BTN5, KC_ACL2, KC_TRNS,
       KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS,       KC_TRNS,       KC_TRNS, RGB_M_X,
       KC_TRNS,  KC_ACL0, KC_MS_WH_UP, KC_MS_WH_UP,   KC_MS_WH_DOWN, KC_TRNS, KC_TRNS,
                 KC_ACL1, KC_BTN1,     KC_BTN3,       KC_BTN2,       KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_ACL2, KC_BTN4,     KC_MS_WH_DOWN, KC_BTN5,       KC_TRNS, KC_TRNS,
                          KC_TRNS,     KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

rgblight_config_t rgblight_config;
bool disable_layer_color = 0;

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
	case M_DBL0:
            if (record->event.pressed) {
                return MACRO( I(25), T(P0), T(P0), END );
            }
        break;
    case M_MAIL:
            if (record->event.pressed) {
                return MACRO( I(25), T(P0), END );
            }
        break;
    case M_SKCC:
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(C), U(LCTL), END  );
            } else {
                return MACRO( D(LCTL), T(V), U(LCTL), END  );
            }
            break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

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
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    rgblight_disable();
    switch (layer) {
      case 1:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(77,248,240);
        }
        break;
      case 2:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(0,48,254);
        }
        break;
      case 3:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(42,221,248);
        }
        break;
      case 4:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(249,241,170);
        }
        break;
      case 6:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(11,255,255);
        }
        break;
      default:
        if(!disable_layer_color) {
          rgblight_config.raw = eeconfig_read_rgblight();
          if(rgblight_config.enable == true) {
            rgblight_enable();
            rgblight_mode(rgblight_config.mode);
            rgblight_sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
          }
          else {
            rgblight_disable();
          }
        }
        break;
    }
    return state;

};
