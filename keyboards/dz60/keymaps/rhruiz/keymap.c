#include QMK_KEYBOARD_H

#define MISCTRL LCTL(KC_UP)
#define CMDENT LGUI_T(KC_ENT)
#define CTRLESC LCTL_T(KC_ESC)
#define FN2BSPC LT(_FN2, KC_BSPC)

#define _BL 0
#define _FN1 1
#define _FN2 2

void change_leds_to(uint16_t, rgblight_config_t);
bool state_changed = false;
static bool grave_esc_was_shifted = false;

enum custom_keycodes {
  KC_K8s = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT(
		KC_GESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,    KC_6,         KC_7,      KC_8,         KC_9,      KC_0,     KC_MINS,      KC_EQL,   KC_BSLS,   KC_GRV,
		KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,    KC_Y,         KC_U,      KC_I,         KC_O,      KC_P,     KC_LBRC,      KC_RBRC,  KC_BSPC,
		CTRLESC ,  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,    KC_H,         KC_J,      KC_K,         KC_L,      KC_SCLN,  KC_QUOT,      KC_ENT,
		KC_LSFT,   KC_NO,    KC_Z,     KC_X,    KC_C,     KC_V,    KC_B,         KC_N,      KC_M,         KC_COMM,   KC_DOT,   KC_SLSH,      KC_RSFT,  TG(_FN2),
		MO(_FN1),  KC_LALT,  KC_LGUI,  KC_SPC,  FN2BSPC,  CMDENT,  MT(MOD_LGUI,  KC_LEFT),  MT(MOD_LALT,  KC_DOWN),  KC_NO,    MT(MOD_RCTL,  KC_UP),   LT(_FN1,   KC_RIGHT)),

  [_FN1] = LAYOUT(
		KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,    KC_F11,   KC_F12,   _______,  KC_EJCT,
		_______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,   KC_UP,     KC_MRWD,  KC_MFFD,  KC_DEL,
		_______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  _______,   _______,  KC_PENT,
		_______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_ENT,   _______,   _______,   _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   TO(_BL)),

  [_FN2] = LAYOUT(
		KC_GRV,   _______,  _______,  MISCTRL,  _______,   RGB_VAD,  RGB_VAI,  KC_MRWD,  KC_MPLY,  KC_MFFD,   KC_MUTE,  KC__VOLDOWN,  KC__VOLUP,  KC_K8s,  KC_EJCT,
		_______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_ACL0,   KC_ACL1,  KC_ACL2,  _______,  _______,  _______,   KC_UP,    _______,      _______,    KC_DEL,
		_______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_RIGHT,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  _______,  _______,      KC_PENT,
		_______,  _______,  _______,  _______,  _______,   _______,  KC_LEFT,  KC_DOWN,  KC_ENT,   _______,   _______,  _______,      _______,    _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   RESET)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	// keyevent_t event = record->event;
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  uint16_t hue = 1;

  switch(biton32(layer_state)) {
    case _FN1:
      hue = 255;
      break;

    case _FN2:
      hue = 0;
      break;
  }

  if (hue != 1) {
    rgblight_config_t eeprom_config;
    eeprom_config.raw = eeconfig_read_rgblight();
    change_leds_to(hue, eeprom_config);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_K8s: {
      if (record->event.pressed) {
        SEND_STRING("kubectl ");
        return false;
      }
      break;
    }

    case GRAVE_ESC: {
      uint8_t shifted = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)
                                      |MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)
                                      |MOD_BIT(KC_LALT)));

      if (record->event.pressed) {
        grave_esc_was_shifted = shifted;
        add_key(shifted ? KC_GRAVE : KC_ESCAPE);
      }
      else {
        del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
      }

      send_keyboard_report();
      return false;
    }
  }

  return true;
}

void change_leds_to(uint16_t hue, rgblight_config_t eeprom_config) {
  if (state_changed) {
    if (!eeprom_config.enable) {
      rgblight_enable_noeeprom();
      rgblight_mode_noeeprom(1);
      for (uint8_t i = RGBLED_NUM ; i-- > 0 ; ) {
        if (i == 8 || i == 15) {
          continue;
        }

        rgblight_sethsv_at(0, 0, 0, i);
      }
    }

    state_changed = false;
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
        state_changed = false;
        break;

      case _FN1:
      case _FN2:
        state_changed = true;
        break;

      default:
        break;
    }

    last_state = state;
  }

  return state;
}
