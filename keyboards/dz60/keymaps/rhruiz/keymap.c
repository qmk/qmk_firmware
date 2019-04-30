#include QMK_KEYBOARD_H

#include "rhruiz.h"

typedef union {
  uint32_t raw;
  struct {
    bool     version_1_1 :1;
  };
} user_config_t;

enum rhruiz_keys {
  KC_KBVSN = SAFE_RANGE
};

user_config_t user_config;
const hue_sat_pair hue_sat_pairs[][2] = {
  [_FN1] = {
    [false] = { 2, 255 },
    [true] = { 3, 255 }
  },

  [_FN2] = {
    [false] = { 275, 255 },
    [true] = { 272, 255 }
  },

  [_CFG] = {
    [false] = { 110, 255 },
    [true] = { 110, 255 }
  }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT(
		KC_GESC,   KC_1,     KC_2,     KC_3,    KC_4,      KC_5,    KC_6,    KC_7,    KC_8,   KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,   KC_GRV,
		KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,      KC_T,    KC_Y,    KC_U,    KC_I,   KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,
		KC_LCTL,   KC_A,     KC_S,     KC_D,    KC_F,      KC_G,    KC_H,    KC_J,    KC_K,   KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
		KC_LSFT,   KC_NO,    KC_Z,     KC_X,    KC_C,      KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  MO(_FN2),
		MO(_FN1),  KC_LALT,  KC_LGUI,  KC_SPC,  MO(_FN2),  BKSFN1,  CLLEFT,  CLDOWN,  KC_NO,  CLUP,     CLRIGHT
  ),

  [_VIM_EMACS] = LAYOUT(
		_______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,   KC_UP,    _______,  _______,  _______,
		_______,  _______,  _______,  _______,  KC_RIGHT,   _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  _______,  _______,  _______,
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
		KC_GRV,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_INS,  KC_EJCT,
		KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PENT,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  KC_DEL,   _______,  _______,  _______,  _______,  _______
  ),

  [_FN1] = LAYOUT(
		_______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,   _______,
		_______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  MO(_CFG),
		_______,  _______,  _______,  MO(_CFG),  MO(_CFG),  _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_FN2] = LAYOUT(
		_______,   KC_SLCK,  KC_PAUS,  MISCTRL,  _______,  RGB_VAD,   RGB_VAI,  KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_MUTE,  KC__VOLDOWN,  KC__VOLUP,  _______,  _______,
		_______,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,      _______,    _______,
		_______,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,      _______,
		_______,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,      _______,    _______,
		MO(_CFG),  _______,  _______,  _______,  _______,  MO(_CFG),  _______,  _______,  _______,  _______,  MO(_CFG)
  ),

  [_CFG] = LAYOUT(
		_______,  RGB_M_P,    RGB_M_B,      RGB_M_R,  RGB_M_SW,  RGB_M_SN,  RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,  _______,  RGB_SPD,  RGB_SPI,  _______,  KC_KBVSN,
		_______,  RGB_TOG,    RGB_MOD,      RGB_HUI,  RGB_HUD,   RGB_SAI,   RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  RESET,
		_______,  KC__VOLUP,  KC__VOLDOWN,  KC_MUTE,  KC_EJCT,   _______,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,  _______,
		_______,  _______,    BL_TOGG,      BL_STEP,  BL_BRTG,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,    _______,      _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______
  ),
};

void rhruiz_update_layer_colors() {
  if (biton32(layer_state) < 1UL)  {
    return;
  }

  uint16_t hue = 1;
  uint8_t sat = 0;

  const hue_sat_pair hue_sat = hue_sat_pairs[biton32(layer_state)][user_config.version_1_1];
  hue = hue_sat.hue;
  sat = hue_sat.sat;

  rhruiz_change_leds_to(hue, sat);
}

void keyboard_post_init_user(void) {
  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();
}

void matrix_scan_user(void) {
  rhruiz_update_layer_colors();
}

bool rhruiz_is_layer_indicator_led(uint8_t index) {
  if (user_config.version_1_1) {
    return index == 0 || index == RGBLED_NUM / 2 - 1;
  } else {
    return index == RGBLED_NUM / 2 || index == RGBLED_NUM - 1;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_KBVSN: {
      if (record->event.pressed) {
        user_config.version_1_1 ^= 1; // Toggles the version
        eeconfig_update_user(user_config.raw); // Writes version to EEPROM
      }
      return false;
    }
  }

  return true;
}

void eeconfig_init_user(void) {
  user_config.version_1_1 = false;
  eeconfig_update_user(user_config.raw);
}

uint32_t layer_state_set_user(uint32_t state) {
  return rhruiz_layer_state_set_user(state);
}
