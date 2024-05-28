#pragma once

void rgb_matrix_init_user(void);
void rgb_matrix_set_color_by_keycode(
    uint8_t led_min,
    uint8_t led_max,
    uint8_t layer,
    bool (*is_keycode)(uint16_t),
    uint8_t red,
    uint8_t green,
    uint8_t blue
);
