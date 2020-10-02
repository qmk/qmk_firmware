#pragma once
#include "quantum.h"

#if defined(RGBLIGHT_TWINKLE)
typedef struct {
    bool     enabled;
    uint8_t  hue;
    uint16_t timer;
    uint8_t  life;
} rgblight_fadeout;
#endif

bool          process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record);
void          keyboard_post_init_rgb_light(void);
void          matrix_scan_rgb_light(void);
layer_state_t layer_state_set_rgb_light(layer_state_t state);
layer_state_t default_layer_state_set_rgb_light(layer_state_t state);
void          rgblight_sethsv_default_helper(uint8_t index);

#if defined(RGBLIGHT_TWINKLE)
void scan_rgblight_fadeout(void);
#endif
