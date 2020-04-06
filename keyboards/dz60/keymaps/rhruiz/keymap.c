#include QMK_KEYBOARD_H

#include "rhruiz.h"
#define KC__FN1 MO(_FN1)
#define KC__FN2 MO(_FN2)
#define _DELFN1 LT(_FN1, KC_DEL)

typedef union {
    uint32_t raw;
    struct {
        bool version_1_1 : 1;
    };
} user_config_t;

enum rhruiz_keys { KC_KBVSN = SAFE_RANGE };

user_config_t      user_config;
const hue_sat_pair hue_sat_pairs[][2] = {[_FN1] = {[false] = {2, 255}, [true] = {2, 255}},

                                         [_FN2] = {[false] = {200, 255}, [true] = {200, 255}},

                                         [_CFG] = {[false] = {80, 255}, [true] = {80, 255}}};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT(
		KC_GRV,    KC_1,     KC_2,     KC_3,    KC_4,      KC_5,    KC_6,    KC_7,    KC_8,   KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,   KC_PIPE,
		KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,      KC_T,    KC_Y,    KC_U,    KC_I,   KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,
		CTRLESC,   KC_A,     KC_S,     KC_D,    KC_F,      KC_G,    KC_H,    KC_J,    KC_K,   KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
		KC_LSFT,   KC_NO,    KC_Z,     KC_X,    KC_C,      KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC__FN2,
		KC__FN1,   KC_LALT,  KC_LGUI,  KC_SPC,  KC__FN2,   BKSFN1,  CLLEFT,  CLDOWN,  KC_NO,  CLUP,     CLRIGHT
  ),

  [_NUM] = LAYOUT(
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_ACL0,  KC_ACL1,  KC_ACL2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_KEY_OVERRIDE] = LAYOUT(
		KC_GRV,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_INS,  KC_EJCT,
		KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL,
		_______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,  KC_PENT,
		_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,  _DELFN1,  _______,  _______,  _______,  _______,  _______
  ),

  [_FN1] = LAYOUT(
		_______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,   _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_FN2] = LAYOUT(
		_______,   KC_SLCK,  KC_PAUS,  MISCTRL,  _______,  RGB_VAD,   RGB_VAI,  KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_MUTE,  KC__VOLDOWN,  KC__VOLUP,  _______,  _______,
		_______,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,      _______,    _______,
		_______,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,      _______,
		_______,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,      _______,    _______,
		_______,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______
  ),

  [_CFG] = LAYOUT(
		_______,  RGB_M_P,    RGB_M_B,      RGB_M_R,  RGB_M_SW,  RGB_M_SN,  RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,  _______,  RGB_SPD,  RGB_SPI,  KC_MAKE,  KC_KBVSN,
		_______,  RGB_TOG,    RGB_MOD,      RGB_HUI,  RGB_HUD,   RGB_SAI,   RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  RESET,
		_______,  KC__VOLUP,  KC__VOLDOWN,  KC_MUTE,  KC_EJCT,   _______,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,  _______,
		_______,  _______,    BL_TOGG,      BL_STEP,  BL_BRTG,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
		_______,  _______,    _______,      _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______
  ),
};

// clang-format on

void rhruiz_update_layer_colors(layer_state_t state) {
    if (biton32(state) < _FN1) {
        rhruiz_rgblight_reset();
        return;
    }

    uint16_t hue = 1;
    uint8_t  sat = 0;

    const hue_sat_pair hue_sat = hue_sat_pairs[biton32(state)][user_config.version_1_1];
    hue                        = hue_sat.hue;
    sat                        = hue_sat.sat;

    rhruiz_change_leds_to(hue, sat);
}

void keyboard_post_init_keymap(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
}

bool rhruiz_is_layer_indicator_led(uint8_t index) {
    if (user_config.version_1_1) {
        return index == 0 || index == RGBLED_NUM / 2 - 1;
    } else {
        return index == RGBLED_NUM / 2 || index == RGBLED_NUM - 1;
    }
}

bool rhruiz_process_record(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_KBVSN: {
            if (record->event.pressed) {
                user_config.version_1_1 ^= 1;           // Toggles the version
                eeconfig_update_user(user_config.raw);  // Writes version to EEPROM
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
