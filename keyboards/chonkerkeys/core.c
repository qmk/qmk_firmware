#include "quantum.h"
#include "keyconfig.h"
#include "rgb_strands/rgb_strands.h"

// This file is not meant to be compiled directly, but included in keymap.c
// LAYER_COUNT, keymaps etc are defined in config.c

bool is_connected = false;

uint8_t get_layer_count() {
    return LAYER_COUNT;
}

uint8_t get_layer_type(uint8_t index) {
    return layers[index];
}

uint8_t get_key_size_and_ordinal(uint8_t layer, uint8_t x, uint8_t y) {
    return key_size_and_ordinals[layer][y][x];
}

uint8_t get_key_action_type(uint8_t layer, uint8_t x, uint8_t y) {
    return pgm_read_byte(&keymaps[layer][y][x]) - CH_CUSTOM;
}

uint32_t get_key_icon(uint8_t layer, uint8_t x, uint8_t y) {
    // TODO: Confirm with client.
    return 0;
}

bool is_windows(uint8_t layer) {
    return layer % 2 == 0;
}

uint8_t get_current_layer(void) {
    uint16_t current_layer = 0;
    for (uint16_t i = 0; i < LAYER_COUNT; ++i) {
        if (IS_LAYER_ON(i)) {
            current_layer = i;
            break;
        }
    }
    return current_layer;
}

void switch_layer(void) {
    uint8_t current_layer = get_current_layer();
    layer_clear();
    uint16_t next_layer = current_layer + 1;
    if (next_layer >= LAYER_COUNT) {
        next_layer = 0;
    }
    layer_on(next_layer);
}

void virtser_recv(uint8_t c) {
    process_protocol(c);
}

void send_protocol(uint8_t c) {
    virtser_send(c);
}

void on_connected() {
    is_connected = true;
}

uint8_t from_x_y_to_index(uint8_t x, uint8_t y) {
    return (y * MATRIX_COLS) + x;
}

void from_app_to_firmware_origin(uint8_t *x, uint8_t *y) {
    // TODO: Flip x as well once w use top-right as origin
    *x = MATRIX_COLS - 1 - *x;
    *y = MATRIX_ROWS - 1 - *y;
}

void from_firmware_to_app_origin(uint8_t *x, uint8_t *y) {
    // app to firmware is the reverse op of itself, so just call it once more
    from_app_to_firmware_origin(x, y);
}

void start_key_anim(uint8_t x, uint8_t y, rgb_strands_anim_t anim) {
    from_app_to_firmware_origin(&x, &y);
    uint8_t rgb_strand = from_x_y_to_index(x, y);
    rgb_strand_animation_start(rgb_strand, anim,
        get_default_rgb_strand_anim_config(anim),
        RGB_STRAND_ANIM_STATE_STEADY);
    rgb_strand_animation_set_state(rgb_strand, RGB_STRAND_ANIM_STATE_START);
}

void set_led_off(uint8_t key_x, uint8_t key_y) {
    start_key_anim(key_x, key_y, RGB_STRAND_EFFECT_NONE);
}

void set_led_steady(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b) {
    // Seems STATIC isn't working, use momentary for now
    // TODO: Fix STATIC
    start_key_anim(key_x, key_y, RGB_STRAND_EFFECT_MOMENTARY);
}

void set_led_blink(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b, uint8_t frequency_tbc) {
    start_key_anim(key_x, key_y, RGB_STRAND_EFFECT_BLINKY);
}

void set_led_like(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b) {
    start_key_anim(key_x, key_y, RGB_STRAND_EFFECT_LIKE);
}

void set_led_leave_meeting(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b) {
    start_key_anim(key_x, key_y, RGB_STRAND_EFFECT_DRAINSWIRL);
}

void set_led_momentary(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b, uint32_t duration_ms) {
    start_key_anim(key_x, key_y, RGB_STRAND_EFFECT_MOMENTARY);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_either_pressed = false;
    uint8_t app_x = record->event.key.col;
    uint8_t app_y = record->event.key.row;
    // QMK uses top left as origin, but the app uses KU origin (i.e. bottom left) for switching layer
    from_firmware_to_app_origin(&app_x, &app_y);
    // Requirement is, use the bottom row and left-most keys as key-switching hotkey
    if (app_y == 0 && app_x <= 1) {
        if (record->event.pressed) {   
            if (is_either_pressed) {
                switch_layer();
                return false;
            }
        }
        is_either_pressed = record->event.pressed;
    }

    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    uint8_t key_strand = from_x_y_to_index(col, row);
    if (record->event.pressed) {
        if (is_connected) {
            key_down(get_current_layer(), app_x, app_y);
        } else {
            if (keycode > CH_CUSTOM && keycode < CH_LAST_KEYCODE) {
                uint16_t key_config_index = keycode - CH_CUSTOM;
                uint16_t current_layer = get_current_layer();
                uint16_t const* keyMacros = is_windows(current_layer) ? windows_configs[key_config_index] : macos_configs[key_config_index];
                for (uint32_t i = 0; i < KEY_MACROS_MAX_COUNT; ++i) {
                    uint16_t code = keyMacros[i];
                    if (code == KC_NO) continue;
                    register_code(code);
                }
                for (int32_t i = KEY_MACROS_MAX_COUNT - 1; i >= 0; --i) {
                    uint16_t code = keyMacros[i];
                    if (code == KC_NO) continue;
                    unregister_code(code);
                }
            } else {
                register_code(keycode);
                unregister_code(keycode);
            }
            uint8_t current_layer = get_current_layer();
            rgb_strands_anim_t anim = key_anim[current_layer][row][col];
            rgb_strand_animation_start(key_strand, anim,
                    get_default_rgb_strand_anim_config(anim),
                    RGB_STRAND_ANIM_STATE_STEADY);
        }
    } else { // released
        rgb_strand_animation_set_state(key_strand, RGB_STRAND_ANIM_STATE_START);
    }
    return false;
}
