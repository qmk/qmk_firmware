#pragma once

typedef struct {
    bool     enabled;
    uint8_t  hue;
    uint16_t timer;
    uint8_t  life;
} rgblight_fadeout;

bool          process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void          keyboard_post_init_rgb(void);
void          matrix_scan_rgb(void);
layer_state_t layer_state_set_rgb(layer_state_t state);
layer_state_t default_layer_state_set_rgb(layer_state_t state);
void          rgblight_sethsv_default_helper(uint8_t index);

#if defined(RGBLIGHT_TWINKLE)
void scan_rgblight_fadeout(void);
#endif
