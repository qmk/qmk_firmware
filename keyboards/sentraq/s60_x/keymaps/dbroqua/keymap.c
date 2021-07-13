#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _FN 1
#define _SFX 2

// Fillers to make layering more clear
#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty gui/alt/space/alt/gui
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift    | FN  |
 * |-----------------------------------------------------------------------------------------+
 *         |LGUI | LAlt  |               Space                | RAlt   |RGUI |
 *         `-----------------------------------------------------------------'
 */
  [_DEFAULT] = LAYOUT( /* Basic QWERTY */
      KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, \
      KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,  \
      KC_LCTL, KC_A,    KC_S,    KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, ______,  KC_ENT,  \
      KC_LSFT, ______,  KC_Z,    KC_X, KC_C, KC_V,   KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(_FN), \
      ______,  KC_LGUI, KC_LALT,                     KC_SPC,                       KC_RALT, KC_RGUI, ______,  ______ \
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * | SFX | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
 * |-----------------------------------------------------------------------------------------+
 * |  CAPS  |     |     |     |     |     |     |     | Psc | Slck| Paus| Up  |     |        |
 * |-----------------------------------------------------------------------------------------+
 * |         | Vol-| Vol+| Mute|     |     | *   | /   | Home| PgUp| Left|Right|             |
 * |-----------------------------------------------------------------------------------------+
 * |           | Prev| Play| Next|     |     | +   | -   | End  |PgDn| Down|           |     |
 * |-----------------------------------------------------------------------------------------+
 *         |       |       |                                 | Stop  |       |
 *         `-----------------------------------------------------------------'
 */
  [_FN] = LAYOUT( /* Layer 1 */
      TG(_SFX),KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_INS,  KC_DEL, \
      KC_CAPS, ______,  ______,  ______,  ______, ______, ______,  ______,  KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,  ______, ______,  \
      ______,  KC_VOLD, KC_VOLU, KC_MUTE, ______, ______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,______, ______,   \
      ______,  ______,  KC_MPRV, KC_MPLY, KC_MNXT,______, ______, KC_PPLS,  KC_PMNS, KC_END,  KC_PGDN, KC_DOWN,        ______, ______,  \
      ______,  ______,  ______,                           ______,                          KC_MSTP, ______, ______, ______ \
      ),


/* SFX Layer
 * ,-----------------------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 * |-----------------------------------------------------------------------------------------+
 * |        | BL- | BL+ | BL  |     |     |     |     |     |     |     |     |     |        |
 * |-----------------------------------------------------------------------------------------+
 * |         | RGBT| RGBM|     |     |     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           | Hue+| Hue-| Sat+| Sat-| Val+| Val-|     |      |    |     |           |     |
 * |-----------------------------------------------------------------------------------------+
 *         |       |       |                                 |       |       |
 *         `-----------------------------------------------------------------'
 */
  [_SFX] = LAYOUT(
      ______,   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
      ______,   BL_TOGG,BL_STEP,BL_DEC, BL_INC, ______, ______, ______, ______, ______, ______, ______, ______, ______,  \
      ______,   F(0),   F(1),   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  \
      ______,   ______, F(2),   F(3),   F(4),   F(5),   F(6),   F(7),   ______, ______, ______, ______,         ______, ______,  \
      ______,   ______, ______,                         ______,                         ______, ______, ______, ______ \
      )
};

enum function_id {
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(RGBLED_TOGGLE),
  [1]  = ACTION_FUNCTION(RGBLED_STEP_MODE),
  [2]  = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
  [3]  = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
  [4]  = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
  [5]  = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
  [6]  = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
  [7]  = ACTION_FUNCTION(RGBLED_DECREASE_VAL)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case RGBLED_TOGGLE:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_toggle();
        #endif
      }
      break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_increase_hue();
        #endif
      }
      break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_decrease_hue();
        #endif
      }
      break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_increase_sat();
        #endif
      }
      break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_decrease_sat();
        #endif
      }
      break;
    case RGBLED_INCREASE_VAL:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_increase_val();
        #endif
      }
      break;
    case RGBLED_DECREASE_VAL:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_decrease_val();
        #endif
      }
      break;
    case RGBLED_STEP_MODE:
      if (record->event.pressed) {
        #ifdef RGB_ENABLE
        rgblight_step();
        #endif
      }
      break;
  }
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
