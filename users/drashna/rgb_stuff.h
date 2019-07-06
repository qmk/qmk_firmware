#pragma once
#include "quantum.h"
#ifdef RGB_MATRIX_ENABLE
  #include "rgb_matrix.h"
#endif

typedef struct {
    bool enabled;
    uint8_t hue;
    uint16_t timer;
    uint8_t life;
} rgblight_fadeout;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void scan_rgblight_fadeout(void);
void keyboard_post_init_rgb(void);
void matrix_scan_rgb(void);
layer_state_t layer_state_set_rgb(layer_state_t state);
layer_state_t default_layer_state_set_rgb(layer_state_t state);
void rgblight_sethsv_default_helper(uint8_t index);
void rgb_matrix_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
