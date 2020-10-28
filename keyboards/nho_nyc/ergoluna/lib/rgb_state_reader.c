#include QMK_KEYBOARD_H
#include <stdio.h>

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
char rbf_info_str[24];
const char *read_rgb_info(void) {

  snprintf(rbf_info_str, sizeof(rbf_info_str), "%s %2d h%3d s%3d v%3d",
    rgblight_config.enable ? "on " : "off", rgblight_config.mode,
    rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
  return rbf_info_str;
}
#endif

#ifdef RGB_MATRIX_ENABLE
char rbf_matrix_info_str[24];
const char *read_rgb_matrix_info(void) {
  snprintf(rbf_matrix_info_str, sizeof(rbf_matrix_info_str), "Status:%s|Mode:%2d",
    rgb_matrix_is_enabled() ? "on " : "off", rgb_matrix_get_mode());
  return rbf_matrix_info_str;
}
#endif
