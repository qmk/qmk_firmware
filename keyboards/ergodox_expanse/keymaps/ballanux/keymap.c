#include "ergodox_expanse.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
//#include "visualizer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

static uint16_t idle_timer;
static uint16_t sec_cnt;

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  OBRACE, // key {
  CBRACE, // key }
  OBRACK, // key [
  CBRACK, // key ]
  OPAREN, // key (
  CPAREN  // key )
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | º ª \  |   1  |   2  |   3  |   4  |   5  | ESC  |           |   '  |   6  |   7  |   8  |   9  |   0  |  DEL   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |  BkSp  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CAPS   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCTRL|  <>  | App  |alt F | LAlt |                                       | Left | Down |  Up  | Right | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | App  | LGui |       | Home |End/RAlt|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Ins  |       | PgUp |        |      |
 *                                 | Space|Enter |------|       |------| Enter  |Space |
 *                                 |      |      | PrtS |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRAVE, KC_1,           KC_2,   KC_3,   KC_4,   KC_5,   KC_ESC,
        KC_TAB,   KC_Q,           KC_W,   KC_E,   KC_R,   KC_T,   TT(SYMB),
        KC_CAPS,  KC_A,           KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,  RCTL_T(KC_Z),    KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        KC_LCTL,  KC_NONUS_BSLASH,KC_APP, LALT(TT(SYMB)), KC_LALT,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_INS,
                                               KC_SPC,KC_ENT, KC_PSCR,
        // right hand
             KC_MINS,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_DELT,
             TT(SYMB),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSPC,
                          KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          GUI_T(KC_QUOT),
             MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,          KC_FN1,
             KC_HOME,     RALT_T(KC_END),
             KC_PGUP,
             KC_PGDN,KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           | NLCK |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  | ¡ ¿  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   <  |   >  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   /  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  OBRACE, CBRACE, KC_EQL, KC_TRNS,
       KC_TRNS,KC_LT,  KC_GT,  OPAREN, CPAREN, KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,OBRACK, CBRACK, KC_TILD,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_NLCK, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_P7,  KC_P8,   KC_P9,   KC_PAST, KC_F12,
                KC_DOWN, KC_P4,  KC_P5,   KC_P6,   KC_PPLS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_P1,  KC_P2,   KC_P3,   KC_PSLS, KC_TRNS,
                         KC_TRNS,KC_PDOT, KC_P0,   KC_PEQL, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
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
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
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
    case OBRACE:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_QUOTE);
        unregister_code(KC_QUOTE);
        unregister_code(KC_RALT);
      }
      return false;
      break;
    case CBRACE:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_BSLS);
        unregister_code(KC_BSLS);
        unregister_code(KC_RALT);
      }
      return false;
      break;
   case OBRACK:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_LBRACKET);
        unregister_code(KC_LBRACKET);
        unregister_code(KC_RALT);
      }
      return false;
      break;
    case CBRACK:
      if (record->event.pressed) {
        register_code(KC_RALT);
        register_code(KC_RBRACKET);
        unregister_code(KC_RBRACKET);
        unregister_code(KC_RALT);
      }
      return false;
      break;
    case OPAREN:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        register_code(KC_8);
        unregister_code(KC_8);
        unregister_code(KC_LSFT);
      }
      return false;
      break;
    case CPAREN:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        register_code(KC_9);
        unregister_code(KC_9);
        unregister_code(KC_LSFT);
      }
      break;
  }
  idle_timer = timer_read();
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
	idle_timer = timer_read();
	sec_cnt = 0;
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);
/*
    visualizer_keyboard_status_t initial_status = {
        .default_layer = 0xFFFFFFFF,
        .layer = 0xFFFFFFFF,
        .mods = 0xFF,
        .leds = 0xFFFFFFFF,
        .suspended = false,
        .backlight_level = 0,
        .user_data = {0},
    };

    visualizer_state_t state = {
        .status = initial_status,
        .current_lcd_color = 0,
        .font_fixed5x8 = gdispOpenFont("fixed_5x8"),
        .font_dejavusansbold12 = gdispOpenFont("DejaVuSansBold12")
    };
*/
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
            //user_visualizer_suspend(&state);
            break;
        default:
            // none
            break;
    }

    if (timer_elapsed(idle_timer) > 1000) {
        sec_cnt++;
        idle_timer = timer_read();
    }

    if (sec_cnt >= 30) {
        ergodox_led_all_off();
        //user_visualizer_suspend(&state);
        sec_cnt = 0;
    }

};

