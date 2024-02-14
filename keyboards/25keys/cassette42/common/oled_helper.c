#include "oled_helper.h"
#include "quantum.h"
#include <stdio.h>
#include <string.h>

#ifdef OLED_ENABLE

void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0};
    oled_write_P(logo, false);
}

#    ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
static char led_buf[24] = "LED state ready.\n";
rgblight_config_t rgblight_config_bak;

void update_led_status(void) {
    if (rgblight_config_bak.enable != rgblight_config.enable || rgblight_config_bak.mode != rgblight_config.mode || rgblight_config_bak.hue != rgblight_config.hue || rgblight_config_bak.sat != rgblight_config.sat || rgblight_config_bak.val != rgblight_config.val) {
        snprintf(led_buf, sizeof(led_buf) - 1, "%c H%2d S%2d V%2d MODE%2d", rgblight_config.enable ? '*' : '.', (uint8_t)(rgblight_config.hue / RGBLIGHT_HUE_STEP), (uint8_t)(rgblight_config.sat / RGBLIGHT_SAT_STEP), (uint8_t)(rgblight_config.val / RGBLIGHT_VAL_STEP), (uint8_t)rgblight_config.mode);
        rgblight_config_bak = rgblight_config;
    }
}

void render_led_status(void) { oled_write(led_buf, false); }
#    endif
#endif
