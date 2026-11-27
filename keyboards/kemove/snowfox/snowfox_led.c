// Copyright 2021 Yaotian Feng / Codetector
// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>
#include "snowfox.h"
#include "snowfox_led.h"
#include "sled17341.h"
#include "snowfox_power.h"

// LED positions and flags. Defined here rather than in keyboard.json so it can live
// in flash: QMK's generated table is writable and would take 255 bytes of RAM.
led_config_t g_led_config __attribute__((section(".rodata.g_led_config"))) = {
    {
        {     0,      1,      2,      3,      4,      5,      6,      7,      8},
        {    14,     15,     16,     17,     18,     19,     20,     21,     22},
        {    28,     29,     30,     31,     32,     33,     34,     35,     36},
        {    41, NO_LED,     42,     43,     44,     45,     46,     47,     48},
        {    53, NO_LED,     54,     50,     51,     55, NO_LED,     59, NO_LED},
        {     9,     10,     11,     12,     13, NO_LED,     56,     58,     57},
        {    23,     24,     25,     27,     38, NO_LED, NO_LED,     60, NO_LED},
        {    39,     37,     26,     49,     52, NO_LED, NO_LED,     40, NO_LED},
    },
    {
        {0, 0}, {16, 0}, {32, 0}, {48, 0}, {65, 0}, {81, 0}, {97, 0}, {113, 0},
        {129, 0}, {145, 0}, {161, 0}, {178, 0}, {194, 0}, {218, 0}, {4, 16}, {24, 16},
        {40, 16}, {57, 16}, {73, 16}, {89, 16}, {105, 16}, {121, 16}, {137, 16}, {153, 16},
        {170, 16}, {186, 16}, {202, 16}, {222, 16}, {6, 32}, {28, 32}, {44, 32}, {61, 32},
        {77, 32}, {93, 32}, {109, 32}, {125, 32}, {141, 32}, {157, 32}, {174, 32}, {190, 32},
        {216, 32}, {10, 48}, {36, 48}, {52, 48}, {69, 48}, {85, 48}, {101, 48}, {117, 48},
        {133, 48}, {149, 48}, {165, 48}, {182, 48}, {212, 48}, {2, 64}, {22, 64}, {42, 64},
        {103, 64}, {163, 64}, {184, 64}, {204, 64}, {224, 64}
    },
    {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 1, 1, 1,
        1
    },
};

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = sled_init,
    .flush         = sled_flush,
    .set_color     = sled_set_color,
    .set_color_all = sled_set_color_all,
};

#define LED_CAPS_LOCK 28
#define LED_FN 60
static const uint8_t led_ble_slot[BLE_KEYBOARD_SIZE] = {42, 43, 44}; // Z, X, C

#define BLINK_MS 250
// After connecting, the slot key shows blue this long and then returns to normal.
#define BLE_CONNECTED_SHOW_MS 3000

#define LED_NUMBER_ROW 1 // keys 1 to 0 are LEDs 1 to 10

// Switching profile lights the whole keyboard in its colour for a moment.
#define PROFILE_FLASH_MS 800
static const uint8_t profile_colours[SF_PROFILE_COUNT][3] = {
    {255, 255, 255}, // 0 white
    {255, 0, 0},     // 1 red
    {0, 255, 0},     // 2 green
    {0, 0, 255},     // 3 blue
    {255, 160, 0},   // 4 yellow
};

static uint8_t        flash_profile;
static uint16_t       flash_from;
static bool           flash_pending;
static bool           show_battery;
static uint8_t        fn_keys[(RGB_MATRIX_LED_COUNT + 7) / 8];
static uint8_t        gui_keys[(RGB_MATRIX_LED_COUNT + 7) / 8];

// Marks the keys that send Win/Cmd with the active base layout and profile, Fn
// aside, so Win lock blinks the keys it actually disables. Worked out again only
// when the active layers change.
static void update_gui_keys(void) {
    static layer_state_t done = (layer_state_t)~0;
    layer_state_t        active = (layer_state | default_layer_state) & ~((layer_state_t)1 << SF_LAYER_FN);
    if (active == done) {
        return;
    }
    done = active;
    memset(gui_keys, 0, sizeof(gui_keys));
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED) {
                continue;
            }
            for (int8_t layer = MAX_LAYER - 1; layer >= 0; layer--) {
                if (!(active & ((layer_state_t)1 << layer))) {
                    continue;
                }
                uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){.row = row, .col = col});
                if (keycode != KC_TRNS) {
                    if (keycode == KC_LGUI || keycode == KC_RGUI) {
                        gui_keys[led / 8] |= 1 << (led % 8);
                    }
                    break;
                }
            }
        }
    }
}

// Reads the Fn layer from the keymap (with VIA, from EEPROM) once per Fn press.
layer_state_t layer_state_set_kb(layer_state_t state) {
    static bool fn_was_on;
    bool        fn_on = state & ((layer_state_t)1 << SF_LAYER_FN);
    if (fn_on && !fn_was_on) {
        memset(fn_keys, 0, sizeof(fn_keys));
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t led = g_led_config.matrix_co[row][col];
                if (led != NO_LED && keymap_key_to_keycode(SF_LAYER_FN, (keypos_t){.row = row, .col = col}) > KC_TRNS) {
                    fn_keys[led / 8] |= 1 << (led % 8);
                }
            }
        }
    }
    fn_was_on = fn_on;
    return layer_state_set_user(state);
}
static bool           ble_show_connected;
static ble_state_t    ble_state = STANDBY;
static ble_keyboard_t ble_slot  = BLE_KEYBOARD1;
static uint16_t       ble_changed_at;

void snowfox_led_show_profile(uint8_t profile) {
    flash_profile = profile < SF_PROFILE_COUNT ? profile : 0;
    flash_from    = timer_read();
    flash_pending = true;
}

void snowfox_led_show_battery(bool show) {
    show_battery = show;
}

// The indicators follow state changes only. The module can repeat an event for a
// state it is already in, which would otherwise restart the 3 s connected blue.
bool ble_update_kb(ble_handle_t *ble_handle) {
    if (ble_handle->state != ble_state || ble_handle->keyboard != ble_slot) {
        ble_changed_at     = timer_read();
        ble_show_connected = ble_handle->state == CONNECTED;
    }
    ble_state = ble_handle->state;
    ble_slot  = ble_handle->keyboard;
    return true;
}

// Draws the indicators over whatever is in the frame. Returns whether any is showing.
static bool draw_indicators(uint8_t led_min, uint8_t led_max) {
    bool shown = false;
    bool blink = (timer_read() / BLINK_MS) % 2;

    if (flash_pending) {
        if (timer_elapsed(flash_from) < PROFILE_FLASH_MS) {
            const uint8_t *c = profile_colours[flash_profile];
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, c[0], c[1], c[2]);
            }
            return true;
        }
        flash_pending = false;
    }

    // While Fn is held, only the keys that do something on the Fn layer stay lit:
    // in the current effect, so lighting changes show, or white with lighting off.
    if (layer_state_is(SF_LAYER_FN)) {
        bool effect = rgb_matrix_is_enabled();
        for (uint8_t i = led_min; i < led_max; i++) {
            bool fn_key = fn_keys[i / 8] & (1 << (i % 8));
            if (!fn_key) {
                rgb_matrix_set_color(i, 0, 0, 0);
            } else if (!effect) {
                rgb_matrix_set_color(i, 255, 255, 255);
            }
        }
        shown = true;
    }

    // Holding the reset keys fills the number row in red over the 3 seconds.
    uint8_t reset = snowfox_factory_reset_progress();
    if (reset > 0) {
        for (uint8_t i = 0; i < 10; i++) {
            if (i * 10 < reset) {
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_NUMBER_ROW + i, 255, 0, 0);
            } else {
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_NUMBER_ROW + i, 0, 0, 0);
            }
        }
        shown = true;
    }

    if (show_battery) {
        // One key per 10%: red up to 20%, yellow up to 50%, then green.
        uint8_t percent = snowfox_battery_percent();
        uint8_t keys    = (percent + 9) / 10;
        uint8_t r       = percent <= 50 ? 255 : 0;
        uint8_t g       = percent > 20 ? 255 : 0;
        for (uint8_t i = 0; i < 10; i++) {
            if (i < keys) {
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_NUMBER_ROW + i, r, g, 0);
            } else {
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_NUMBER_ROW + i, 0, 0, 0);
            }
        }
        shown = true;
    }

    // Win lock blinks the keys it disables, Fn lock the Fn key, in red.
    if (keymap_config.no_gui) {
        update_gui_keys();
        for (uint8_t i = led_min; i < led_max; i++) {
            if (gui_keys[i / 8] & (1 << (i % 8))) {
                rgb_matrix_set_color(i, blink ? 255 : 0, 0, 0);
            }
        }
        shown = true;
    }
    if (layer_state_is(SF_LAYER_FN_LOCK)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_FN, blink ? 255 : 0, 0, 0);
        shown = true;
    }

    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS_LOCK, 255, 0, 0);
        shown = true;
    }

    if (ble_slot < BLE_KEYBOARD_SIZE) {
        uint8_t led = led_ble_slot[ble_slot];
        switch (ble_state) {
            case DISCOVERING:
                RGB_MATRIX_INDICATOR_SET_COLOR(led, 0, blink ? 255 : 0, blink ? 255 : 0);
                shown = true;
                break;
            case CONNECTING:
                RGB_MATRIX_INDICATOR_SET_COLOR(led, blink ? 255 : 0, 0, blink ? 255 : 0);
                shown = true;
                break;
            case CONNECTED:
                // Shown once per connection. A 16-bit timestamp would come round again every 65 s.
                if (ble_show_connected && timer_elapsed(ble_changed_at) < BLE_CONNECTED_SHOW_MS) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(led, 0, 255, 255);
                    shown = true;
                } else {
                    ble_show_connected = false;
                }
                break;
            default:
                break;
        }
    }
    return shown;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    draw_indicators(led_min, led_max);
    return true;
}

// RGB Matrix draws nothing while it is off, so indicators are drawn here then.
// The flush only writes changed frames, and also shuts the chips down once dark.
void snowfox_led_task(void) {
    static uint16_t last;

    if (rgb_matrix_is_enabled() || snowfox_power_asleep() || timer_elapsed(last) < RGB_MATRIX_LED_FLUSH_LIMIT) {
        return;
    }
    last = timer_read();

    sled_set_color_all(0, 0, 0);
    draw_indicators(0, RGB_MATRIX_LED_COUNT);
    sled_flush();
}
