// Copyright 2026 Scramble Tools
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// Keymaps name their layers per side by defining this; unnamed layers show a
// number. Each half shows the name for its own side, the layer state is
// synced to the secondary.
__attribute__((weak)) const char *layer_name_klaw(uint8_t layer, bool left) {
    return NULL;
}

#    ifndef __AVR__
static const char *current_name(char *fallback, size_t size, uint8_t *layer) {
    *layer           = get_highest_layer(layer_state | default_layer_state);
    const char *name = layer_name_klaw(*layer, is_keyboard_left());
    if (name == NULL) {
        snprintf(fallback, size, "Layer %u", *layer);
        name = fallback;
    }
    return name;
}

// Text at twice the size of the built-in font: the driver renders the line
// at normal size on the bottom line, that line is read back and every pixel
// expanded into a 2x2 block on the two target lines. Ten characters fit.
#        define BIG_CHARS (OLED_DISPLAY_WIDTH / (2 * OLED_FONT_WIDTH))
#        define LINES (OLED_DISPLAY_HEIGHT / 8)
#        define SCRATCH_LINE (LINES - 1)

static uint8_t stretch(uint8_t nibble) {
    uint8_t out = 0;
    for (uint8_t bit = 0; bit < 4; bit++) {
        if (nibble & (1 << bit)) {
            out |= 3 << (2 * bit);
        }
    }
    return out;
}

static void blank_line(uint8_t line) {
    for (uint8_t x = 0; x < OLED_DISPLAY_WIDTH; x++) {
        oled_write_raw_byte(0, line * OLED_DISPLAY_WIDTH + x);
    }
}

// line is the upper of the two 8 pixel lines, the text is centred on it
static void oled_write_big(uint8_t line, const char *text) {
    char clipped[BIG_CHARS + 1];
    strlcpy(clipped, text, sizeof(clipped));
    oled_set_cursor(0, SCRATCH_LINE);
    oled_write(clipped, false);

    uint8_t              small[OLED_DISPLAY_WIDTH];
    oled_buffer_reader_t reader = oled_read_raw(SCRATCH_LINE * OLED_DISPLAY_WIDTH);
    memcpy(small, reader.current_element, sizeof(small));
    blank_line(SCRATCH_LINE);

    uint8_t  used = strlen(clipped) * OLED_FONT_WIDTH;
    uint8_t  x0   = (OLED_DISPLAY_WIDTH - 2 * used) / 2;
    uint16_t top = line * OLED_DISPLAY_WIDTH, bottom = top + OLED_DISPLAY_WIDTH;
    blank_line(line);
    blank_line(line + 1);
    for (uint8_t x = 0; x < used; x++) {
        uint8_t hi = stretch(small[x] & 0x0F), lo = stretch(small[x] >> 4);
        oled_write_raw_byte(hi, top + x0 + 2 * x);
        oled_write_raw_byte(hi, top + x0 + 2 * x + 1);
        oled_write_raw_byte(lo, bottom + x0 + 2 * x);
        oled_write_raw_byte(lo, bottom + x0 + 2 * x + 1);
    }
}

// Only the layer name, centred, redrawn when the layer changes
static void render(void) {
    static uint8_t shown = 0xFF;
    char           fallback[BIG_CHARS + 1];
    uint8_t        layer;
    const char    *name = current_name(fallback, sizeof(fallback), &layer);
    if (layer == shown) {
        return;
    }
    shown = layer;
    for (uint8_t line = 0; line < LINES; line++) {
        blank_line(line);
    }
    oled_write_big(LINES / 2 - 1, name);
}
#    else
static void render(void) {
    uint8_t     layer = get_highest_layer(layer_state | default_layer_state);
    const char *name  = layer_name_klaw(layer, is_keyboard_left());
    oled_set_cursor(0, 3);
    if (name == NULL) {
        oled_write_P(PSTR("Layer "), false);
        oled_write_ln(get_u8_str(layer, ' '), false);
    } else {
        oled_write_ln(name, false);
    }
}
#    endif

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    render();
    return false;
}
#endif
