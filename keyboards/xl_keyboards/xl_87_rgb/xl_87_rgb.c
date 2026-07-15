// Copyright 2026 Hiiwwy
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "eeconfig.h"

#ifdef VIA_ENABLE
#    include "via.h"
#endif

enum xl_87_rgb_led_index {
    XL_87_RGB_SCROLL_LOCK_LED = 14,
    XL_87_RGB_CAPS_LOCK_LED   = 62,
};

// The high 24 bits identify this keyboard's configuration. The low two bits
// store the ordinary-lighting state for the keylight and underglow groups.
#define XL_87_RGB_LEGACY_CONFIG_MAGIC      0x584C8700UL
#define XL_87_RGB_CONFIG_MAGIC             0x584C8800UL
#define XL_87_RGB_CONFIG_MAGIC_MASK        0xFFFFFF00UL
#define XL_87_RGB_KEYLIGHT_ENABLED_BIT     (1UL << 0)
#define XL_87_RGB_UNDERGLOW_ENABLED_BIT    (1UL << 1)

static uint32_t xl_87_rgb_config;

static bool xl_87_rgb_lighting_is_enabled(uint32_t enabled_bit) {
    return (xl_87_rgb_config & enabled_bit) != 0;
}

static void xl_87_rgb_save_config(void) {
    eeconfig_update_kb(xl_87_rgb_config);
}

static void xl_87_rgb_set_lighting_enabled(uint32_t enabled_bit, bool enabled) {
    if (enabled) {
        xl_87_rgb_config |= enabled_bit;
    } else {
        xl_87_rgb_config &= ~enabled_bit;
    }

    // Keep RGB Matrix rendering active so lock indicators can still be drawn.
    rgb_matrix_enable_noeeprom();
}

static void xl_87_rgb_set_default_config(void) {
    xl_87_rgb_config = XL_87_RGB_CONFIG_MAGIC | XL_87_RGB_KEYLIGHT_ENABLED_BIT | XL_87_RGB_UNDERGLOW_ENABLED_BIT;
}

void eeconfig_init_kb(void) {
    xl_87_rgb_set_default_config();
    xl_87_rgb_save_config();

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    xl_87_rgb_config = eeconfig_read_kb();

    if ((xl_87_rgb_config & XL_87_RGB_CONFIG_MAGIC_MASK) == XL_87_RGB_LEGACY_CONFIG_MAGIC) {
        bool lighting_was_enabled = xl_87_rgb_lighting_is_enabled(XL_87_RGB_KEYLIGHT_ENABLED_BIT);

        xl_87_rgb_set_default_config();
        xl_87_rgb_set_lighting_enabled(XL_87_RGB_KEYLIGHT_ENABLED_BIT, lighting_was_enabled);
        xl_87_rgb_set_lighting_enabled(XL_87_RGB_UNDERGLOW_ENABLED_BIT, lighting_was_enabled);
        xl_87_rgb_save_config();
    } else if ((xl_87_rgb_config & XL_87_RGB_CONFIG_MAGIC_MASK) != XL_87_RGB_CONFIG_MAGIC) {
        xl_87_rgb_set_default_config();
        xl_87_rgb_save_config();
    }

    // A previously stored RGB Matrix off-state must not stop the indicators.
    rgb_matrix_enable_noeeprom();

    keyboard_post_init_user();
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    led_t led_state = host_keyboard_led_state();

    // This runs after the regular effect, so it can independently clear either
    // ordinary-lighting group before restoring active lock indicators.
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        led_flags_t flags = g_led_config.flags[i];

        if ((!xl_87_rgb_lighting_is_enabled(XL_87_RGB_KEYLIGHT_ENABLED_BIT) && HAS_FLAGS(flags, LED_FLAG_KEYLIGHT)) ||
            (!xl_87_rgb_lighting_is_enabled(XL_87_RGB_UNDERGLOW_ENABLED_BIT) && HAS_FLAGS(flags, LED_FLAG_UNDERGLOW))) {
            rgb_matrix_set_color(i, RGB_OFF);
        }
    }

    if (led_state.caps_lock) {
        rgb_matrix_set_color(XL_87_RGB_CAPS_LOCK_LED, RGB_WHITE);
    }

    if (led_state.scroll_lock) {
        rgb_matrix_set_color(XL_87_RGB_SCROLL_LOCK_LED, RGB_WHITE);
    }

    return true;
}

// Do not allow RM_TOGG to stop RGB Matrix itself: it only controls ordinary
// lighting, leaving the lock indicators available.
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (keycode == RM_TOGG) {
        if (record->event.pressed) {
            bool ordinary_lighting_is_enabled = xl_87_rgb_lighting_is_enabled(XL_87_RGB_KEYLIGHT_ENABLED_BIT) || xl_87_rgb_lighting_is_enabled(XL_87_RGB_UNDERGLOW_ENABLED_BIT);

            xl_87_rgb_set_lighting_enabled(XL_87_RGB_KEYLIGHT_ENABLED_BIT, !ordinary_lighting_is_enabled);
            xl_87_rgb_set_lighting_enabled(XL_87_RGB_UNDERGLOW_ENABLED_BIT, !ordinary_lighting_is_enabled);
            xl_87_rgb_save_config();
        }

        return false;
    }

    return true;
}

#ifdef VIA_ENABLE

enum xl_87_rgb_via_value {
    id_xl_87_rgb_keylight_enabled  = 1,
    id_xl_87_rgb_underglow_enabled = 2,
};

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [command_id, channel_id, value_id, value_data]
    uint8_t *command_id = &data[0];
    uint8_t *channel_id = &data[1];
    uint8_t *value_id   = &data[2];
    uint8_t *value_data = &data[3];

    (void)length;

    if (*channel_id != id_custom_channel) {
        *command_id = id_unhandled;
        return;
    }

    switch (*command_id) {
        case id_custom_set_value:
            if (*value_id == id_xl_87_rgb_keylight_enabled) {
                xl_87_rgb_set_lighting_enabled(XL_87_RGB_KEYLIGHT_ENABLED_BIT, *value_data != 0);
                return;
            }

            if (*value_id == id_xl_87_rgb_underglow_enabled) {
                xl_87_rgb_set_lighting_enabled(XL_87_RGB_UNDERGLOW_ENABLED_BIT, *value_data != 0);
                return;
            }
            break;

        case id_custom_get_value:
            if (*value_id == id_xl_87_rgb_keylight_enabled) {
                *value_data = xl_87_rgb_lighting_is_enabled(XL_87_RGB_KEYLIGHT_ENABLED_BIT);
                return;
            }

            if (*value_id == id_xl_87_rgb_underglow_enabled) {
                *value_data = xl_87_rgb_lighting_is_enabled(XL_87_RGB_UNDERGLOW_ENABLED_BIT);
                return;
            }
            break;

        case id_custom_save:
            xl_87_rgb_save_config();
            return;

        default:
            break;
    }

    *command_id = id_unhandled;
}

#endif
