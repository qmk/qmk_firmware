#include "kageurufu.h"
#include "quantum.h"
#include "process_records.h"

#ifdef RGBLIGHT_ENABLE
  //Following line allows macro to read current RGB settings
  extern rgblight_config_t rgblight_config;
  rgblight_config_t backup_rgblight_config;

  __attribute__((weak))
  uint8_t RGBLIGHT_MODS[] = {0};
#endif
