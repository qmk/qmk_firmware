#include QMK_KEYBOARD_H

enum layers {
  BASE, // qwerty linux
  OSX,  // qwerty osx

  _ADJUST, // function key layer
};

enum keycodes {
  // default layout switcher
  LAY_LIN = SAFE_RANGE,
  LAY_OSX
};

/*
 * ,---------------------------------------------------------------------|
 * |Esc|▓|F1 |F2 |F3 |F4 |▓|F5 |F6 |F7 |F8 |▓|F9 |F10|F11|F12|▓|Hom|▓|End|
 * |---------------------------------------------------------------------|
 * |`  |1  |2  |3  |4  |5  |6  |7  |8  |9  |0   |-   |=   |\   |Del|▓PgU |
 * |---------------------------------------------------------------------|
 * |Tab  |Q  |W  |E  |R  |T  |Y  |U  |I  |O  |P  |[  | ]  |    BSpc|▓PgDn|
 * |---------------------------------------------------------------------|
 * |LCTRL |A  |S  |D  |F  |G  |H  |J  |K  |L  |;  |'  |  Enter   |▓▓▓▓▓▓▓|
 * |---------------------------------------------------------------------|
 * |Shft    |Z  |X  |C  |V  |B  |N  |M  |,  |.  |/  |Shift     |▓| Up |▓▓|
 * |---------------------------------------------------------------------|
 * |Ctrl|GUI |Alt |     Space                    |Alt |Fn  |▓|Lt |Dn |Rt |
 * `---------------------------------------------------------------------|'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_75_ansi_splitbs(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  KC_HOME,   LT(_ADJUST,KC_END),
		KC_GRV, KC_1,   KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_MINS, KC_EQL,  KC_BSLS,KC_DEL, KC_PGUP,
		KC_TAB, KC_Q,   KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_PGDN,
		KC_LCTL, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,  KC_QUOT,        KC_ENT,
		KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT,KC_SLSH,         KC_RSFT, KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                      KC_RALT, KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT),

  [OSX] = LAYOUT_75_ansi_splitbs(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_LCTL, KC_LALT, KC_LGUI,                  _______,                             KC_LGUI, KC_RALT, _______, _______, _______),

	[_ADJUST] = LAYOUT_75_ansi_splitbs(
		QK_BOOT, LAY_LIN, LAY_OSX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(_ADJUST),
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		BL_TOGG, BL_DEC, BL_INC, KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI,
		_______, _______, _______,                  _______,                             _______, _______, RGB_MOD, RGB_VAD, RGB_HUD),


};

extern rgblight_config_t rgblight_config;

bool edit = false;
uint32_t mode;
uint16_t hue;
uint8_t sat;
uint8_t val;

void matrix_init_user(void)
{
  mode = rgblight_config.mode;
}


void persistent_default_layer_set(uint16_t default_layer)
{
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  /* layout switcher */
  case LAY_LIN:
    if (record->event.pressed)
    {
      persistent_default_layer_set(1UL << BASE);
    }
    return false;
    break;
  case LAY_OSX:
    if (record->event.pressed)
    {
      persistent_default_layer_set(1UL << OSX);
    }
    return false;
    break;
  case RGB_MOD:
    // allows to set the rgb mode while in the ADJUST layer which uses
    // its own mode
    if (record->event.pressed)
    {
      rgblight_mode(mode);
      rgblight_step();
      mode = rgblight_config.mode;
    }
    return false;
    break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
  if (state == BASE && edit == true)
  {
    hue = rgblight_get_hue();
    sat = rgblight_get_sat();
    val = rgblight_get_val();
    edit = false;
  }

  switch (get_highest_layer(state))
  {
  case _ADJUST:
    mode = rgblight_get_mode();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(0xD3, 0x7F, 0xED);
    edit = true;
    break;
  default:
    rgblight_mode(mode);
    rgblight_sethsv(hue, sat, val);
    break;
  }
  return state;
}
