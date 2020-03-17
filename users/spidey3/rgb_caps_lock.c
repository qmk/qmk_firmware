#include QMK_KEYBOARD_H

#include <spidey3.h>

extern rgblight_config_t rgblight_config;

uint32_t rgb_mode;
uint16_t rgb_hue;
uint8_t rgb_sat;
uint8_t rgb_val;
bool rgb_saved = 0;

void spidey_swirl(void) {
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
  rgblight_sethsv(213, 255, 128);
}

void eeconfig_init_user_rgb(void)
{
  spidey_swirl();
}

void matrix_init_user_rgb(void)
{
  rgb_mode = rgblight_config.mode;
  rgb_hue = rgblight_config.hue;
  rgb_sat = rgblight_config.sat;
  rgb_val = rgblight_config.val;
  rgb_saved = 1;

#ifdef CONSOLE_ENABLE
  uprintf("matrix_init_user: Saved mode: %u, hue: %u, sat: %u, val: %u\n", rgb_mode, rgb_hue, rgb_sat, rgb_val);
#endif 
}

bool led_update_user(led_t led_state) {
  if (led_state.caps_lock) {
    rgb_mode = rgblight_get_mode();

    rgb_hue = rgblight_get_hue();
    rgb_sat = rgblight_get_sat();
    rgb_val = rgblight_get_val();
    rgb_saved = 1;

    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(HSV_AZURE);

#ifdef CONSOLE_ENABLE
    if (debug_enable) { uprintf("CAPS_LOCK ON: Saved mode: %u, hue: %u, sat: %u, val: %u\n", rgb_mode, rgb_hue, rgb_sat, rgb_val); }
#endif 

  } else if (rgb_saved) {
    rgblight_mode(rgb_mode);
    rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
    rgb_saved = 0;

#ifdef CONSOLE_ENABLE
    if (debug_enable) { uprintf("CAPS_LOCK OFF: Restored mode: %u, hue: %u, sat: %u, val: %u\n", rgb_mode, rgb_hue, rgb_sat, rgb_val); }
#endif 
  }

  return true; // Continue to process the led state change
}

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case SPI_GLO:
      if (record->event.pressed) {
        spidey_swirl();
#ifdef CONSOLE_ENABLE                                                                                                                                                                                 
        if (debug_enable) { print("process_record_user_rgb: FAV_GLO\n"); }
#endif       
      }
      break;
  }

  return true;
}

