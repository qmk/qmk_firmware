#include "custom_rgb.h"

#if defined(RGBLIGHT_ENABLE)
  extern rgblight_config_t rgblight_config;
  rgblight_config_t _pushed_rgblight_config;
  #define push_rgb_config() { if (_pushed_rgblight_config.raw == 0) { _pushed_rgblight_config.raw = rgblight_config.raw; } }
  #define pop_rgb_config() { if (_pushed_rgblight_config.raw == 0) { rgblight_config.raw = _pushed_rgblight_config.raw; _pushed_rgblight_config.raw = 0; } }
#elif defined(RGB_MATRIX_ENABLE)
  extern rgb_config_t rgb_matrix_config;
  rgb_config_t _pushed_rgb_matrix_config;
  #define push_rgb_config() _pushed_rgb_matrix_config.raw = rgb_matrix_config.raw
  #define pop_rgb_config() rgb_matrix_config.raw = _pushed_rgb_matrix_config.raw
#endif


bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
  return true;
}
