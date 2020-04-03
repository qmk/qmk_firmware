#pragma once

#ifdef RGBLIGHT_ENABLE
  extern rgblight_config_t rgblight_config;
  rgblight_config_t RGB_current_config;
#endif

#ifdef RGB_MATRIX_ENABLE
  extern rgb_matrix_config_t rgb_matrix_config;
  rgb_config_t RGB_current_config;
#endif


void save_rgb_config(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_config.enable = rgblight_config.enable;
    RGB_current_config.mode = rgblight_get_mode();
    RGB_current_config.speed = rgblight_get_speed();
    RGB_current_config.hue = rgblight_get_hue();
    RGB_current_config.sat = rgblight_get_sat();
    RGB_current_config.val = rgblight_get_val();
  #elif RGB_MATRIX_ENABLE
    RGB_current_config.enable = rgb_matrix_config.enable;
    RGB_current_config.mode = rgb_matrix_get_mode();
    RGB_current_config.speed  = rgb_matrix_config.speed;
    RGB_current_config.hsv.h = rgb_matrix_config.hsv.h;
    RGB_current_config.hsv.s = rgb_matrix_config.hsv.s;
    RGB_current_config.hsv.v = rgb_matrix_config.hsv.v;
  #endif
}

void restore_rgb_config(void) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_set_speed_noeeprom(RGB_current_config.speed);
    if (rgblight_config.mode != RGB_current_config.mode) {
      rgblight_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hue != rgblight_config.hue) ||
      (RGB_current_config.sat != rgblight_config.sat) ||
      (RGB_current_config.val != rgblight_config.val)) {
      rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
    }
    if (rgblight_config.enable) {
      rgblight_enable_noeeprom();
    } else {
      rgblight_disable_noeeprom();
    }
  #elif RGB_MATRIX_ENABLE
    rgb_matrix_config.speed = RGB_current_config.speed;
    if (rgb_matrix_config.mode != RGB_current_config.mode) {
      rgb_matrix_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hsv.h != rgb_matrix_config.hsv.h) ||
      (RGB_current_config.hsv.s != rgb_matrix_config.hsv.s) ||
      (RGB_current_config.hsv.v != rgb_matrix_config.hsv.v)) {
      rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
    }
    if (rgb_matrix_config.enable) {
      rgb_matrix_enable_noeeprom();
    } else {
      rgb_matrix_disable_noeeprom();
    }
  #endif
}

void rgb_by_layer(int layer) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  #elif RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  #endif

  switch (layer) {
    case _ADJUST:
      rgblight_sethsv_noeeprom(9, 255, 255);
      break;
    case _RAISE:
      rgblight_sethsv_noeeprom(HSV_CYAN);
      break;
    case _LOWER:
      rgblight_sethsv_noeeprom(HSV_MAGENTA);
      break;
    default:
      rgblight_sethsv_noeeprom(HSV_RED);
  }
}
