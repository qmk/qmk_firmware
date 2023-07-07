// Copyright 2022 Arturo Avila (@ADPenrose), Christopher Courtney/Drashna Jael're (@drashna)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "animation_process.h"

/* Structure that helps store settings in memory and write to the EEPROM: */
typedef union {
  uint32_t raw;
  struct {
    bool     split_zero :1;
    bool     split_enter :1;
    bool     split_plus :1;
  };
} via_layout_t;

via_layout_t via_layouts;

/* Keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                  MO(1),    MO(2),     MO(3),     CK_TOGG,
                  KC_NUM,   KC_PSLS,   KC_PAST,   KC_PMNS,
                  KC_P7,    KC_P8,     KC_P9,     KC_PPLS,
                  KC_P4,    KC_P5,     KC_P6,     KC_PPLS,
                  KC_P1,    KC_P2,     KC_P3,     KC_PENT,
        KC_MUTE,  KC_P0,    KC_P0,     KC_PDOT,   KC_PENT 
    ),
    [1] = LAYOUT_all(
                  KC_TRNS,  CK_DOWN,   CK_UP,     CK_RST,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [2] = LAYOUT_all(
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [3] = LAYOUT_all(
                  QK_BOOT,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [2] = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif

/* Setting layout options and debuggin text */
void via_set_layout_options_kb(uint32_t value) { 
  via_layouts.raw = value;
  #ifdef CONSOLE_ENABLE
    if (via_layouts.split_zero && via_layouts.split_enter && via_layouts.split_plus){
      xprintf("All three layouts are active with a value of: %d\n", value);
    } else if (!(via_layouts.split_zero) && via_layouts.split_enter && via_layouts.split_plus){
      xprintf("SE and SP layouts are active with a value of: %d\n", value);
    } else if (via_layouts.split_zero && !(via_layouts.split_enter) && via_layouts.split_plus){
      xprintf("SZ and SP layouts are active with a value of: %d\n", value);
    } else if (!(via_layouts.split_zero) && !(via_layouts.split_enter) && via_layouts.split_plus){
      xprintf("SP is the only layout active with a value of: %d\n", value);
    } else if (via_layouts.split_zero && via_layouts.split_enter && !(via_layouts.split_plus)){
      xprintf("SE and SZ layouts are active with a value of: %d\n", value);
    } else if (!(via_layouts.split_zero) && via_layouts.split_enter && !(via_layouts.split_plus)) {
      xprintf("SE is the only layout active with a value of: %d\n", value);
    } else if (via_layouts.split_zero && !(via_layouts.split_enter) && !(via_layouts.split_plus)){
      xprintf("SZ is the only layout active with a value of: %d\n", value); 
    } else {
      xprintf("The base layout is active with a value of: %d\n", value);
    }
  #endif
}

/* Turing LEDs on/off depending on the layout selected on VIA */
bool rgb_matrix_indicators_user(void){
  if (via_layouts.split_zero && via_layouts.split_enter && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
  } else if (!(via_layouts.split_zero) && via_layouts.split_enter && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
  } else if (via_layouts.split_zero && !(via_layouts.split_enter) && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  } else if (!(via_layouts.split_zero) && !(via_layouts.split_enter) && via_layouts.split_plus){
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  } else if (via_layouts.split_zero && via_layouts.split_enter && !(via_layouts.split_plus)){
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
  } else if (!(via_layouts.split_zero) && via_layouts.split_enter && !(via_layouts.split_plus)) {
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(21, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
  } else if (via_layouts.split_zero && !(via_layouts.split_enter) && !(via_layouts.split_plus)){
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(23, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  } else {
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(16, 0, 0, 0);
    rgb_matrix_set_color(20, 0, 0, 0);
    rgb_matrix_set_color(22, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0, 0);
    rgb_matrix_set_color(26, 0, 0, 0);
  }
  return false;
}

/* OLED stuff */
#ifdef OLED_ENABLE
bool oled_task_user(void) { 
    render_anim();
    
    // WPM render
    oled_set_cursor(1, 0);
    oled_write_P(PSTR(">"), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0,14);
    oled_write_P(led_state.caps_lock ? PSTR("CPSLK") :"    ", true);
    oled_set_cursor(0,15);
    oled_write_P(led_state.num_lock ? PSTR("NUMLK") :"    ", true);
    
  return false;
}

/* WPM calculation considerations */
bool wpm_keycode_user(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
      (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
    keycode = keycode & 0xFF;
  } else if (keycode > 0xFF) {
    keycode = 0;
  }

  // Include keys in WPM calculation
  if ((keycode >= KC_TAB && keycode <= KC_SLASH) || // Tab - Slash (Symbols, Punctuation, Space)
      (keycode >= KC_KP_SLASH && keycode <= KC_KP_COMMA) ||  // Keypad numbers - Keypad Dot
      (keycode >= KC_F1 && keycode <= KC_F12)) { // F1 - F12
    return true;
  }

  return false;
}
#endif
