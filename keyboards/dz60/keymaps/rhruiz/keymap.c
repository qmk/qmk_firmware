#include QMK_KEYBOARD_H

#define X___X KC_TRNS
#define MISCTRL LCTL(KC_UP)
#define CTRLESC LCTL_T(KC_ESC)

#define _BL 0
#define _FN1 1
#define _FN2 2
#define _FN3 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT(
		KC_GESC,   KC_1,     KC_2,     KC_3,    KC_4,      KC_5,    KC_6,     KC_7,     KC_8,   KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSLS,   KC_GRV,
		KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,      KC_T,    KC_Y,     KC_U,     KC_I,   KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSPC,
		CTRLESC ,  KC_A,     KC_S,     KC_D,    KC_F,      KC_G,    KC_H,     KC_J,     KC_K,   KC_L,     KC_SCLN,    KC_QUOT,  KC_ENT,
		KC_LSFT,   KC_NO,    KC_Z,     KC_X,    KC_C,      KC_V,    KC_B,     KC_N,     KC_M,   KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,  TG(_FN3),
		MO(_FN1),  KC_LALT,  KC_LGUI,  KC_SPC,  MO(_FN2),  KC_ENT,  KC_LGUI,  KC_LALT,  KC_NO,  KC_APP,   TO(_FN1)),

  [_FN1] = LAYOUT(
		KC_GRV,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,    KC_F11,   KC_F12,   X___X,   KC_EJCT,
		X___X,   RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  X___X,     KC_UP,     KC_MRWD,  KC_MFFD,  KC_DEL,
		X___X,   X___X,    X___X,    X___X,    X___X,    X___X,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  X___X,     X___X,    KC_PENT,
		X___X,   X___X,    X___X,    X___X,    X___X,    X___X,    KC_LEFT,  KC_DOWN,  KC_ENT,   X___X,     X___X,     X___X,    X___X,    X___X,
		X___X,   X___X,    X___X,    X___X,    X___X,    X___X,    X___X,    X___X,    X___X,    X___X,     TO(_BL)),

  [_FN2] = LAYOUT(
		KC_GRV,  X___X,    X___X,    MISCTRL,  X___X,     RGB_VAD,  RGB_VAI,  KC_MRWD,  KC_MPLY,  KC_MFFD,   KC_MUTE,  KC__VOLDOWN,  KC__VOLUP,  X___X,   KC_EJCT,
		X___X,   KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_ACL0,   KC_ACL1,  KC_ACL2,  X___X,    X___X,    X___X,     KC_UP,    X___X,        X___X,      KC_DEL,
		X___X,   KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_RIGHT,  X___X,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  X___X,    X___X,        KC_PENT,
		X___X,   X___X,    X___X,    X___X,    X___X,     X___X,    KC_LEFT,  KC_DOWN,  KC_ENT,   X___X,     X___X,    X___X,        X___X,      X___X,
		X___X,   X___X,    X___X,    X___X,    X___X,     X___X,    X___X,    X___X,    X___X,    X___X,     RESET),

  [_FN3] = LAYOUT(
		X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,    X___X,  X___X,    X___X,     X___X,  X___X,  X___X,     X___X,
		X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,    X___X,  X___X,    X___X,     X___X,  X___X,  X___X,
		X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,    X___X,  X___X,    X___X,     X___X,  X___X,
		X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,    X___X,  X___X,    X___X,     X___X,  KC_UP,  TG(_FN3),
		X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  X___X,  KC_LEFT,  X___X,  KC_DOWN,  KC_RIGHT)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	// keyevent_t event = record->event;
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void change_leds_to(uint16_t hue, rgblight_config_t eeprom_config) {
  if (!eeprom_config.enable) {
    rgblight_enable_noeeprom();
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
      rgblight_sethsv_at(0, 0, 0, i);
    }
  }

  rgblight_sethsv_at(hue, 255, eeprom_config.val, 8);
  rgblight_sethsv_at(hue, 255, eeprom_config.val, 15);
}

uint32_t layer_state_set_user(uint32_t state) {
  static uint32_t last_state = 0;
  rgblight_config_t eeprom_config;
  eeprom_config.raw = eeconfig_read_rgblight();

  if (state != last_state) {
    switch(biton32(state)) {
      case _BL:
        if (!eeprom_config.enable) {
          rgblight_disable_noeeprom();
        }
        rgblight_mode_noeeprom(eeprom_config.mode);
        rgblight_sethsv_noeeprom(eeprom_config.hue, eeprom_config.sat, eeprom_config.val);
        break;

      case _FN1:
        change_leds_to(255, eeprom_config);
        break;

      case _FN2:
        change_leds_to(0, eeprom_config);
        break;

      case _FN3:
        change_leds_to(120, eeprom_config);
        break;

      default:
        break;
    }

    last_state = state;
  }

  return state;
}
