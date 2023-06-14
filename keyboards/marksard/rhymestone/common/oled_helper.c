#include "oled_helper.h"
#include "quantum.h"
#include <stdio.h>
#include <string.h>

#ifdef OLED_ENABLE

void render_logo(void) {

  static const char PROGMEM logo_buf[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};

  oled_write_P(logo_buf, false);
}

void render_lock_status(void) {

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();

  oled_write_P(PSTR("Lock:"), false);
  if (led_state.num_lock) {
    oled_write_P(PSTR("Num "), false);
  }
  if (led_state.caps_lock) {
    oled_write_P(PSTR("Caps "), false);
  }
  if (led_state.scroll_lock) {
    oled_write_P(PSTR("Scrl"), false);
  }

  oled_write_P(PSTR("\n"), false);
}

static char keylog_buf[24] = "Key state ready.\n";
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', '-', ' ', '@', ' ', ' ',
    ' ', ';', ':', ' ', ',', '.', '/', ' ', ' ', ' '};

void update_key_status(uint16_t keycode, keyrecord_t *record) {

  if (!record->event.pressed) return;

  char name = (keycode < 60) ? code_to_name[keycode] : ' ';
  snprintf(keylog_buf, sizeof(keylog_buf) - 1, "Key:%dx%d %2x %c\n",
          record->event.key.row, record->event.key.col,
          (uint16_t)keycode, name);
}

void render_key_status(void) {

  oled_write(keylog_buf, false);
}

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;

static char led_buf[24] = "LED state ready.\n";
rgblight_config_t rgblight_config_bak;
void update_led_status(void) {

  if (rgblight_config_bak.enable != rgblight_config.enable ||
      rgblight_config_bak.mode != rgblight_config.mode ||
      rgblight_config_bak.hue != rgblight_config.hue ||
      rgblight_config_bak.sat != rgblight_config.sat ||
      rgblight_config_bak.val != rgblight_config.val
  ) {
    snprintf(led_buf, sizeof(led_buf) - 1, "LED%c:%2d hsv:%2d %2d %2d\n",
      rgblight_config.enable ? '*' : '.', (uint8_t)rgblight_config.mode,
      (uint8_t)(rgblight_config.hue / RGBLIGHT_HUE_STEP),
      (uint8_t)(rgblight_config.sat / RGBLIGHT_SAT_STEP),
      (uint8_t)(rgblight_config.val / RGBLIGHT_VAL_STEP));
      rgblight_config_bak = rgblight_config;
  }
}

void render_led_status(void) {

  oled_write(led_buf, false);
}
#endif
#endif
