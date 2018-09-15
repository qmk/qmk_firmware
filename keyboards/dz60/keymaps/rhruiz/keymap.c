#include QMK_KEYBOARD_H

#define MISCTRL LCTL(KC_UP)
#define CTRLESC LCTL_T(KC_ESC)

// arrow cluster
#define CLLEFT MT(MOD_LGUI, KC_LEFT)
#define CLDOWN MT(MOD_LALT, KC_DOWN)
#define CLUP MT(MOD_RCTL, KC_UP)
#define CLRIGHT LT(_FN1, KC_RIGHT)

void change_leds_to(uint16_t, uint8_t, rgblight_config_t);
bool state_changed = false;
static bool grave_esc_was_shifted = false;

enum rhruiz_layers {
  _BL,
  _VIM_EMACS,
  _MOUSE,
  _KEY_OVERRIDE,
  _FN1,
  _FN2,
  _CFG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT(
		KC_GRV,   KC_1,     KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,   KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_GRV,
		KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,   KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,
		CTRLESC,  KC_A,     KC_S,     KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,   KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
		KC_LSFT,  KC_NO,    KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_FN2,
		KC_FN1,   KC_LALT,  KC_LGUI,  KC_SPC,  KC_FN2,  KC_BSPC,  CLLEFT,  CLDOWN,  KC_NO,  CLUP,     CLRIGHT
  ),

  [_VIM_EMACS] = LAYOUT(
		_______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,   KC_UP,    _______,  _______,  _______,
		_______,  _______,  _______,  _______,  KC_RIGHT,   _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  _______,  _______,  KC_PENT,
		_______,  _______,  _______,  _______,  _______,    _______,  KC_LEFT,  KC_DOWN,  KC_ENT,   _______,   _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,   _______
  ),

  [_MOUSE] = LAYOUT(
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_ACL0,  KC_ACL1,  KC_ACL2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_KEY_OVERRIDE] = LAYOUT(
		KC_GRV,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_EJCT,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PENT,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  KC_DEL,   _______,  _______,  _______,  _______,  _______
  ),

  [_FN1] = LAYOUT(
		_______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,   _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  MO(_CFG),
		_______,  _______,  _______,  _______,  MO(_CFG),  _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_FN2] = LAYOUT(
		_______,   KC_SLCK,  KC_PAUS,  MISCTRL,  _______,  RGB_VAD,  RGB_VAI,  KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_MUTE,  KC__VOLDOWN,  KC__VOLUP,  _______,  _______,
		_______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,      _______,    _______,
		_______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,      _______,
		_______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,      _______,    _______,
		MO(_CFG),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  MO(_CFG)
  ),

  [_CFG] = LAYOUT(
		_______,  RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW,  RGB_M_SN,  RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,  RGB_SPI,  RGB_SPD,  _______,  _______,  RESET,
		_______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,   RGB_SAI,   RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  RESET,
		_______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______
  ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	// keyevent_t event = record->event;
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  uint16_t hue = 1;
  uint8_t sat = 0;

  switch(biton32(layer_state)) {
    case _FN1:
      hue = 2;
      sat = 225;
      break;

    case _FN2:
      hue = 275;
      sat = 255;
      break;

    case _CFG:
      hue = 110;
      sat = 255;
      break;
  }

  if (hue != 1) {
    rgblight_config_t eeprom_config;
    eeprom_config.raw = eeconfig_read_rgblight();
    change_leds_to(hue, sat, eeprom_config);
  }
}

void rhruiz_layer_on(uint8_t layer) {
  layer_on(_VIM_EMACS);
  layer_on(_MOUSE);
  layer_on(_KEY_OVERRIDE);
  layer_on(layer);
}

void rhruiz_layer_off(uint8_t layer) {
  layer_off(_VIM_EMACS);
  layer_off(_MOUSE);
  layer_off(_KEY_OVERRIDE);
  layer_off(layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_FN1: {
      if (record->event.pressed) {
        rhruiz_layer_on(_FN1);
      } else {
        rhruiz_layer_off(_FN1);
      }

      return false;
    }

    case KC_FN2: {
      if (record->event.pressed) {
        rhruiz_layer_on(_FN2);
      } else {
        rhruiz_layer_off(_FN2);
      }

      return false;
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

void change_leds_to(uint16_t hue, uint8_t sat, rgblight_config_t eeprom_config) {
  if (state_changed) {
    if (!eeprom_config.enable) {
      rgblight_enable_noeeprom();
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      for (uint8_t i = RGBLED_NUM ; i-- > 0 ; ) {
        if (i == 8 || i == 15) {
          continue;
        }

        rgblight_sethsv_at(0, 0, 0, i);
      }
    }

    state_changed = false;
  }

  rgblight_sethsv_at(hue, sat, eeprom_config.val, 8);
  rgblight_sethsv_at(hue, sat, eeprom_config.val, 15);
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
      case _CFG:
        state_changed = true;
        break;

      default:
        break;
    }

    last_state = state;
  }

  return state;
}
