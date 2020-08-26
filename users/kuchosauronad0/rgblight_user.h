#pragma once
#include "kuchosauronad0.h"

typedef struct {
    bool     enabled;
    uint8_t  hue;
    uint16_t timer;
    uint8_t  life;
} rgblight_fadeout;
const uint8_t RGBLIGHT_FADE_SPEED[6] PROGMEM;

layer_state_t layer_state_set_rgb(layer_state_t state);
layer_state_t default_layer_state_set_rgb(layer_state_t state);

bool          process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void          scan_rgblight_fadeout(void);
void          keyboard_post_init_rgb(void);
void          matrix_scan_rgb(void);
void          rgblight_sethsv_default_helper(uint8_t index);
void          rgblight_savebase(void);
void          rgblight_loadbase(void);
void          rgblight_fade_helper(bool direction);
void          fadeflash_leds(uint8_t hue, uint8_t sat, uint8_t val);
