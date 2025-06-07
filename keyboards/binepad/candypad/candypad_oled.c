// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later
// Portions of this code are based on [Andrew Kannan](https://github.com/awkannan1)'s
//  work on the Satisfaction75

#include "quantum.h"
#include "keymap_introspection.h"

#ifdef OLED_ENABLE

static char *get_enc_mode(uint8_t encoder) {
#    ifdef ENCODER_MAP_ENABLE

    static char s_u_d[4] = {24, 38, 25, 0}; // Up and down
    static char s_l_r[4] = {27, 38, 26, 0}; // Left and right

    uint8_t  layer   = get_highest_layer(layer_state);
    uint16_t keycode = KC_TRNS;

    while (keycode == KC_TRNS) {
        keycode = keycode_at_encodermap_location(layer, encoder, true); // only reads ENCODER_CW
        if (keycode == KC_TRNS) {
            if (layer > 0) {
                layer--;
            } else {
                keycode = KC_NO;
            }
        }
    }

    switch (keycode) {
        case KC_NO:
            return " - ";
            break;

        case KC_WH_U:
        case KC_WH_D:
            return "MWL";
            break;

        case KC_VOLD:
        case KC_VOLU:
            return "VOL";
            break;

        case KC_MEDIA_NEXT_TRACK:
        case KC_MEDIA_PREV_TRACK:
            return "MED";
            break;

        case KC_UP:
        case KC_DOWN:
            return (char *)&s_u_d;
            break;

        case KC_LEFT:
        case KC_RIGHT:
            return (char *)&s_l_r;
            break;

        default:
            return "Usr";
            break;
    }

#    else

    return "Err";

#    endif
}

static void __draw_line_h(uint8_t x, uint8_t y, uint8_t len, bool on) {
    for (uint8_t i = 0; i < len; i++) {
        oled_write_pixel(i + x, y, on);
    }
}

static void __draw_line_v(uint8_t x, uint8_t y, uint8_t len, bool on) {
    for (uint8_t i = 0; i < len; i++) {
        oled_write_pixel(x, i + y, on);
    }
}

// Weak so that user keymaps can make their own
__attribute__((weak)) bool candypad_render_default_user(void) {
    return false; // Return true if your user keymap renders its own
}

__attribute__((weak)) bool candypad_render_default_kb(void) {
    if (candypad_render_default_user()) {
        return true; // Was handled by user code
    }

    bool on;

    // --- Show Layer ---

    oled_set_cursor(0, 1);
    oled_write_P(PSTR("LAYER"), false);

    oled_set_cursor(6, 1);
    oled_write_char(get_highest_layer(layer_state) + 0x30, true);

    __draw_line_h((OLED_FONT_WIDTH * 6) - 1, OLED_FONT_HEIGHT - 1, OLED_FONT_WIDTH + 1, true);
    __draw_line_v((OLED_FONT_WIDTH * 6) - 1, OLED_FONT_HEIGHT, OLED_FONT_HEIGHT, true);

    // --- Show Encoder 1 ---

    oled_set_cursor(13, 1);
    oled_write_P(PSTR("ENC1"), false);

    oled_set_cursor(18, 1);
    oled_write(get_enc_mode(0), true);

    __draw_line_h((OLED_FONT_WIDTH * 18) - 1, OLED_FONT_HEIGHT - 1, (OLED_FONT_WIDTH * 3) + 1, true);
    __draw_line_v((OLED_FONT_WIDTH * 18) - 1, OLED_FONT_HEIGHT, OLED_FONT_HEIGHT, true);

    // --- Show Encoder 2 ---

    oled_set_cursor(13, 3);
    oled_write_P(PSTR("ENC2"), false);

    oled_set_cursor(18, 3);
    oled_write(get_enc_mode(1), true);

    __draw_line_h((OLED_FONT_WIDTH * 18) - 1, (OLED_FONT_HEIGHT * 3) - 1, (OLED_FONT_WIDTH * 3) + 1, true);
    __draw_line_v((OLED_FONT_WIDTH * 18) - 1, OLED_FONT_HEIGHT * 3, OLED_FONT_HEIGHT, true);

    // --- Keyboard Modifiers ---

    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(4, 3);
    if (led_state.caps_lock && !led_state.num_lock) { // Caps-Lock transcends keyboards, so show it if on if num-lock is off
        oled_write_P(PSTR("CAP"), true);
    } else {
        oled_write_P(PSTR("NUM"), led_state.num_lock);
    }
    on = led_state.num_lock || led_state.caps_lock;
    __draw_line_h((OLED_FONT_WIDTH * 4) - 1, (OLED_FONT_HEIGHT * 3) - 1, (OLED_FONT_WIDTH * 3) + 1, on);
    __draw_line_v((OLED_FONT_WIDTH * 4) - 1, OLED_FONT_HEIGHT * 3, OLED_FONT_HEIGHT, on);

    // --- Show keymap matrix ---

#    define MXDS_X 2
#    define MXDS_Y (OLED_FONT_HEIGHT * 3)

    // matrix
    for (uint8_t x = 0; x < MATRIX_ROWS - 1; x++) {
        for (uint8_t y = 0; y < MATRIX_COLS; y++) {
            on = (matrix_get_row(x) & (1 << y)) > 0;
            oled_write_pixel(MXDS_X + y, MXDS_Y + x + 1, on);
        }
    }

    on = (matrix_get_row(1) & (1 << 3)) > 0; // `+`
    oled_write_pixel(MXDS_X + 3, MXDS_Y + 1 + 2, on);

    on = (matrix_get_row(3) & (1 << 3)) > 0; // `Enter`
    oled_write_pixel(MXDS_X + 3, MXDS_Y + 3 + 2, on);

    on = (matrix_get_row(4) & (1 << 0)) > 0; // `0`
    oled_write_pixel(MXDS_X + 0 + 1, MXDS_Y + 4 + 1, on);

    on = (matrix_get_row(5) & (1 << 0)) > 0; // Enc 1 press
    oled_write_pixel(MXDS_X + 2, MXDS_Y, on);

    on = (matrix_get_row(5) & (1 << 1)) > 0; // Enc 2 press
    oled_write_pixel(MXDS_X + 3, MXDS_Y, on);

    // outline
    __draw_line_h(MXDS_X - 2, MXDS_Y - 2, 8, true);
    __draw_line_h(MXDS_X - 2, MXDS_Y + 7, 8, true);
    __draw_line_v(MXDS_X - 2, MXDS_Y - 1, 8, true);
    __draw_line_v(MXDS_X + 5, MXDS_Y - 1, 8, true);

    return true; // Was handled here
}

void oled_request_repaint(void) {
    oled_clear();
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    candypad_render_default_kb();
    return false;
}

#endif // OLED_ENABLE
