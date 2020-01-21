#pragma once
#include "quantum.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_TWINKLE)
typedef struct {
    bool     enabled;
    uint8_t  hue;
    uint16_t timer;
    uint8_t  life;
} rgblight_fadeout;
#endif

bool          process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void          keyboard_post_init_rgb(void);
void          matrix_scan_rgb(void);
layer_state_t layer_state_set_rgb(layer_state_t state);
layer_state_t default_layer_state_set_rgb(layer_state_t state);

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_TWINKLE)
void scan_rgblight_fadeout(void);
#endif
#if defined(RGBLIGHT_ENABLE)
void rgblight_sethsv_default_helper(uint8_t index);
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type);
#endif
