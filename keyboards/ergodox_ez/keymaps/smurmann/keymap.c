#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define MDIA 1 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

bool capsOn = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |   7  |   8  |   9  |   0  |   -  |   =  |  Bksp  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  {   |           |  }   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |HyperCaps|  A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L1| Enter  |
 * |--------+------+------+------+------+------| Alt  |           |  L1  |------+------+------+------+------+--------|
 * | LShift | Z/L1 |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   ?  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |lCrtr |   [  |   ]  |   `  |   '  |                                       | Left |  Up  | Down | Right| PlayWin |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |PRTSRN| Win  |       | Home | End  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Ins  |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Enter |Space |
 *                                 |      |ace   | Del  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_LCBR,
        ALL_T(KC_CAPS), KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        LT(MDIA,KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_LALT,
        KC_LCTRL,       KC_LBRC,      KC_RBRC,        KC_GRV, KC_QUOT,
                                                     KC_PSCR, KC_LGUI,
                                                              KC_INS,
                                               KC_SPC,KC_BSPC,KC_DEL,
        // right hand
                 KC_7,    KC_8,   KC_9,  KC_0,KC_MINS, KC_EQL,             KC_BSPC,
              KC_RCBR,    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  KC_K,   KC_L,   LT(MDIA, KC_SCLN),KC_ENT,
             TG(MDIA),    KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,
                                  KC_LEFT, KC_UP,KC_DOWN,KC_RGHT,          GUI_T(KC_MPLY),
             KC_HOME,        KC_END,
             KC_PGUP,
             KC_PGDN,KC_ENT, KC_SPC
    ),
/* Keymap 1: Media and mouse keys
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |BootLoad |      | Lclk | MsUp | Rclk |      |      |           |      |      |      |  Up  |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Right|      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |MsAcl0|MsAcl1|MsAcl2|      |      |           |      |      |      | Mute | Mute |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       | Prev |VolUp |VolDn | Next |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Functions
[MDIA] = LAYOUT_ergodox(
       // left hand
          VRSN,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
         RESET,_______,KC_BTN1,KC_MS_U,KC_BTN2,_______,_______,
       _______,_______,KC_MS_L,KC_MS_D,KC_MS_R,_______,
       _______,_______,KC_ACL0,KC_ACL1,KC_ACL2,_______,_______,
        _______,_______,_______,_______,_______,
                                       _______,_______,
                                               _______,
                               _______,_______,_______,
       // right hand
         KC_F7, KC_F8,  KC_F9, KC_F10,  KC_F11, KC_F12,_______,
       _______,_______,_______, KC_UP ,_______,_______,_______,
               _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,
       _______,_______,_______,KC_MUTE,KC_MUTE,_______,_______,
                       KC_MPRV,KC_VOLU,KC_VOLD,KC_MNXT,_______,
       _______, _______,
       _______,
       _______, _______, _______
),
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
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
   uint8_t layer = get_highest_layer(layer_state);

   if(layer == 1)
   {
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();

      ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
   }

   if(capsOn)
   {
      ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_1_on ();
   }

  if(keyboard_report->mods & MOD_BIT(KC_LSFT))
  {
      ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_1_on ();
  } else {
      ergodox_right_led_1_set (LED_BRIGHTNESS_LO);

      if(!capsOn)
      {
        ergodox_right_led_1_off ();
      }
  }

  if(keyboard_report->mods & MOD_BIT(KC_LALT))
  {
      ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_2_on ();
  } else {
      ergodox_right_led_2_set (LED_BRIGHTNESS_LO);
     if(layer != 1)
     {
       ergodox_right_led_2_off ();
     }
  }

  if(keyboard_report->mods & MOD_BIT(KC_LCTRL))
  {
      ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_3_on ();
  } else {
      ergodox_right_led_3_set (LED_BRIGHTNESS_LO);
     if(layer != 1)
     {
       ergodox_right_led_3_off ();
     }
  }
};

void led_set_user(uint8_t usb_led){
 if (usb_led & (1 << USB_LED_CAPS_LOCK))
   {
      capsOn = true;
   }else {
      capsOn = false;
   }
}
