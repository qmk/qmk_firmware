#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "string.h"

#ifdef SUBPROJECT_infinity
#include "visualizer/lcd_backlight.h"
#endif


#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

#define EPRM M(1) // Macro 1: Reset EEPROM
#define HTML_LI M(10)
#define HTML_UL M(11)
#define HTML_OL M(12)
#define HTML_CODE M(13)
#define HTML_BR M(14)

#define SEND_TAG(TAG) do {\
    send_key(KC_NONUS_BSLASH); \
    SEND_STRING(TAG); \
    send_larger_than(); \
    send_key(KC_NONUS_BSLASH); \
    SEND_STRING("&"); \
    SEND_STRING(TAG); \
    send_larger_than(); \
    go_back_based_on_tag(TAG); \
  } while (0)

#define SEND_SHORT_TAG(TAG) do {\
    send_key(KC_NONUS_BSLASH); \
    SEND_STRING(TAG); \
    SEND_STRING("&"); \
    send_larger_than();	       \
  } while (0)

void send_key(uint16_t keycode);
void go_back_based_on_tag(char* tag);
void send_larger_than(void);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   §    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   '    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Z  |   U  |   I  |   O  |   P  |   ü    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   | A /L2|   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |ö / L2|ä / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Y/Ctrl|X/Alt |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |./Alt |-/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |< / L1|   ^  |   $  | Left | Right|                                       |  Up  | Down |AltGr |   ¨  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_DEL,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(SYMB),
        KC_BSPC,        LT(MDIA, KC_A),KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  ALT_T(KC_X),   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        LT(SYMB,KC_NONUS_BSLASH), KC_EQL, KC_BSLS,  KC_LEFT,KC_RGHT,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
	KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
	TG(SYMB),    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_LBRC,
	KC_H,   KC_J,   KC_K,   KC_L,   LT(MDIA, KC_SCLN),GUI_T(KC_QUOT),
	MEH_T(KC_NO),KC_N,   KC_M,   KC_COMM,ALT_T(KC_DOT), CTL_T(KC_SLSH),   KC_RSFT,
                             KC_UP,  KC_DOWN,KC_RALT,KC_RBRC, TT(SYMB),
             KC_LALT,CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | EPRM |      |      |      |                                       |   ?  |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
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
       M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,ACTION_MODS_KEY(MOD_LSFT, KC_RBRC), ACTION_MODS_KEY(MOD_RALT, KC_2),  ACTION_MODS_KEY(MOD_RALT, KC_QUOT), ACTION_MODS_KEY(MOD_RALT, KC_BSLS),ACTION_MODS_KEY(MOD_RALT,KC_7),KC_TRNS,
       KC_TRNS,ACTION_MODS_KEY(MOD_RALT,KC_3),KC_BSLS, ACTION_MODS_KEY(MOD_LSFT, KC_8), ACTION_MODS_KEY(MOD_RSFT, KC_9),ACTION_MODS_KEY(MOD_LSFT,KC_EQL),
       KC_TRNS,ACTION_MODS_KEY(MOD_LSFT,KC_5),KC_EQL, ACTION_MODS_KEY(MOD_RALT, KC_LBRC), ACTION_MODS_KEY(MOD_RALT, KC_RBRC),ACTION_MODS_KEY(MOD_RALT,KC_EQL),KC_TRNS,
          KC_TRNS,EPRM,KC_TRNS,KC_NONUS_BSLASH, ACTION_MODS_KEY(MOD_LSFT, KC_NONUS_BSLASH)/*KC_TRNS,KC_TRNS*/,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    ACTION_MODS_KEY(MOD_RSFT,KC_3), KC_F12,
       KC_DOWN, KC_4,   KC_5,    KC_6,    ACTION_MODS_KEY(MOD_RSFT,KC_1), KC_TRNS,
       KC_TRNS, ACTION_MODS_KEY(MOD_RSFT,KC_6), KC_1,   KC_2,    KC_3,  ACTION_MODS_KEY(MOD_RALT,KC_NONUS_BSLASH), KC_TRNS,
       ACTION_MODS_KEY(MOD_RSFT,KC_MINS),KC_DOT,  KC_0,   KC_EQL, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |      |      |      |      |      |      |           |      |      |      |      |      |      | RESET  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |H_UL  |      |H_OL  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |H_LI  |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |H_CODE|      |H_BR  |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Enter |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, HTML_CODE, KC_TRNS, HTML_BR, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_ENT, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
       KC_TRNS,  KC_TRNS, HTML_UL, KC_TRNS, HTML_OL, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, HTML_LI, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
      case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      case 10:
	if (record->event.pressed) {
	  SEND_TAG("li");
	}
	break;
      case 11:
	if (record->event.pressed) {
	  SEND_TAG("ul");
	}
	break;
      case 12:
	if (record->event.pressed) {
	  SEND_TAG("ol");
	}
	break;
      case 13:
	if (record->event.pressed) {
	  SEND_TAG("code");
	}
	break;
      case 14:
	if (record->event.pressed) {
	  SEND_SHORT_TAG("br");
	}
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
    case 0:
      ergodox_board_led_off();
      ergodox_right_led_1_off();
      ergodox_right_led_2_off();
      ergodox_right_led_3_off();

      #ifdef SUBPROJECT_infinity
      lcd_backlight_hal_color(0, 0, 0);
      #endif
      break;
    case 1:
      ergodox_right_led_1_on();

      ergodox_board_led_off();
      ergodox_right_led_2_off();
      ergodox_right_led_3_off();
      #ifdef SUBPROJECT_infinity
      lcd_backlight_hal_color(5000, 0, 0);
      #endif
      break;
    case 2:
      ergodox_right_led_2_on();

      ergodox_board_led_off();
      ergodox_right_led_1_off();
      ergodox_right_led_3_off();
      #ifdef SUBPROJECT_infinity
      lcd_backlight_hal_color(0, 5000, 0);
      #endif
      break;
    default:
            // none
            break;
    }

};

void send_key(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

void go_back_based_on_tag(char* tag) {
  const int BRACKETS_AND_SLASH_LENGTH = 3;

  for (int i=0; i < strlen(tag) + BRACKETS_AND_SLASH_LENGTH; i++) {
    send_key(KC_LEFT);
  }
}

void send_larger_than() {
  register_code(KC_LSFT);
  send_key(KC_NONUS_BSLASH);
  unregister_code(KC_LSFT);
}
