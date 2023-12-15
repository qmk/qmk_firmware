#pragma once

#include <stdint.h>
#include "action.h"

#ifdef OLED_ENABLE

void render_logo(void);
void render_lock_status(void);
void update_key_status(uint16_t keycode, keyrecord_t *record);
void render_key_status(void);

#define RENDER_LOGO() render_logo()
#define RENDER_LOCK_STATUS() render_lock_status()
#define UPDATE_KEY_STATUS(a, b) update_key_status(a, b)
#define RENDER_KEY_STATUS() render_key_status()

#ifdef RGBLIGHT_ENABLE
  void update_led_status(void);
  void render_led_status(void);
  #define UPDATE_LED_STATUS() update_led_status()
  #define RENDER_LED_STATUS() render_led_status()
#else
  #define UPDATE_LED_STATUS()
  #define RENDER_LED_STATUS()
#endif

#else

#define RENDER_LOGO()
#define RENDER_LOCK_STATUS()
#define UPDATE_KEY_STATUS(a, b)
#define RENDER_KEY_STATUS()
#define UPDATE_LED_STATUS()
#define RENDER_LED_STATUS()

#endif
