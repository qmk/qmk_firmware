#ifdef RGBLIGHT_ENABLE

#include "quantum.h"
#include <stdio.h>

extern rgblight_config_t rgblight_config;
char rbf_info_str[24];
const char *read_rgb_info(void) {

  snprintf(rbf_info_str, sizeof(rbf_info_str), "%s %2d h%3d s%3d v%3d",
    rgblight_config.enable ? "on" : "- ", rgblight_config.mode,
    rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
  return rbf_info_str;
}
#endif
