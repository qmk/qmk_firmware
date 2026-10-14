// Copyright 2020 Yaotian Feng / Codetector
// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "snowfox.h"
#include "snowfox_ble.h"
#include "snowfox_led.h"
#include "snowfox_power.h"
#include "eeprom_lpc11uxx.h"
#ifdef DYNAMIC_KEYMAP_ENABLE
#    include "dynamic_keymap.h"
#endif

// The switch on the back is on in its Windows position. What it does is a setting:
// 0 picks the Windows or Mac layout, as the stock firmware. 1 and 2 pick the layout
// from the operating system seen over USB, and the switch in its Mac position
// locks the Win key (1) or the F keys (2).
static bool switch_on = true;

uint8_t snowfox_switch_mode(void) {
    snowfox_config_t config = snowfox_config_read();
    return config.switch_mode < SF_SWITCH_MODES ? config.switch_mode : 0;
}

// The lock a mode hands to the switch is left alone in the other modes, so Fn+Win
// and Fn+Space keep working there. Leaving a mode gives the lock back.
static void apply_switch(void) {
    static uint8_t   applied = 0;
    snowfox_config_t config  = snowfox_config_read();
    uint8_t          mode    = config.switch_mode < SF_SWITCH_MODES ? config.switch_mode : 0;
    bool             mac     = mode == 0 ? !switch_on : config.host_is_mac;

    default_layer_set(1UL << (mac ? SF_LAYER_MAC : SF_LAYER_WIN));

    if (applied == 1 && mode != 1) {
        eeconfig_read_keymap(&keymap_config);
    }
    if (applied == 2 && mode != 2) {
        layer_off(SF_LAYER_FN_LOCK);
    }
    if (mode == 1) {
        keymap_config.no_gui = !switch_on;
    }
    if (mode == 2) {
        if (switch_on) {
            layer_off(SF_LAYER_FN_LOCK);
        } else {
            layer_on(SF_LAYER_FN_LOCK);
        }
    }
    applied = mode;
}

void snowfox_set_switch_mode(uint8_t mode) {
    snowfox_config_t config = snowfox_config_read();
    config.switch_mode      = mode < SF_SWITCH_MODES ? mode : 0;
    snowfox_config_write(config);
    apply_switch();
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        switch_on = active;
        apply_switch();
    }
    return true;
}

bool process_detected_host_os_kb(os_variant_t os) {
    if (!process_detected_host_os_user(os)) {
        return false;
    }
    if (os != OS_UNSURE) {
        snowfox_config_t config = snowfox_config_read();
        bool             mac    = os == OS_MACOS || os == OS_IOS;
        if (config.host_is_mac != mac) {
            config.host_is_mac = mac;
            snowfox_config_write(config);
        }
        apply_switch();
    }
    return true;
}

// Lighting effects call rand(). This small generator replaces the C library's,
// which drags in stdio and about 400 bytes of RAM.
static uint32_t rand_state = 2463534242UL;

int rand(void) {
    rand_state ^= rand_state << 13;
    rand_state ^= rand_state >> 17;
    rand_state ^= rand_state << 5;
    return (int)(rand_state & 0x7FFFFFFF);
}

void srand(unsigned int seed) {
    rand_state = seed ? seed : 2463534242UL;
}

// The C library's abort() brings in its reentrancy data (84 bytes of RAM).
void abort(void) {
    chSysHalt("abort");
    while (true) {
    }
}

void housekeeping_task_kb(void) {
    snowfox_power_task();
    snowfox_led_task();
}

void mcu_reset(void) {
    eeprom_lpc11uxx_flush();
    NVIC_SystemReset();
}

void bootloader_jump(void) {
    eeprom_lpc11uxx_flush();
    // The OpenKemove bootloader stays in DFU mode when it finds this word after a reset.
    *((volatile uint32_t *)0x100001F0) = 0xDEADBEEF;
    NVIC_SystemReset();
}

// Settings are read once and then kept in RAM, so frequent reads cost no EEPROM access.
static snowfox_config_t config_cache;
static bool             config_cached;

snowfox_config_t snowfox_config_read(void) {
    if (!config_cached) {
        eeconfig_read_kb_datablock(&config_cache.raw, 0, sizeof(config_cache.raw));
        config_cached = true;
    }
    return config_cache;
}

void snowfox_config_write(snowfox_config_t config) {
    config_cache  = config;
    config_cached = true;
    eeconfig_update_kb_datablock(&config.raw, 0, sizeof(config.raw));
}

// Each profile keeps its own lighting in the keyboard data block.
#define PROFILE_LAYERS ((layer_state_t)((1UL << SF_LAYER_PROFILE1) | (1UL << SF_LAYER_PROFILE2) | (1UL << SF_LAYER_PROFILE3) | (1UL << SF_LAYER_PROFILE4)))

uint8_t snowfox_profile(void) {
    snowfox_config_t config = snowfox_config_read();
    return config.profile < SF_PROFILE_COUNT ? config.profile : 0;
}

static void profile_apply_layers(uint8_t profile) {
    layer_and((layer_state_t)~PROFILE_LAYERS);
    if (profile > 0) {
        layer_on(SF_LAYER_PROFILE1 + profile - 1);
    }
}

void snowfox_profile_select(uint8_t profile) {
    if (profile >= SF_PROFILE_COUNT) {
        return;
    }
    uint8_t current = snowfox_profile();
    if (profile != current) {
        eeconfig_update_kb_datablock(&rgb_matrix_config, SF_LIGHTING_OFFSET(current), sizeof(rgb_config_t));

        rgb_config_t lighting;
        eeconfig_read_kb_datablock(&lighting, SF_LIGHTING_OFFSET(profile), sizeof(rgb_config_t));
        // A profile used for the first time keeps the current lighting.
        if (lighting.mode != 0) {
            rgb_matrix_mode(lighting.mode);
            rgb_matrix_sethsv(lighting.hsv.h, lighting.hsv.s, lighting.hsv.v);
            rgb_matrix_set_speed(lighting.speed);
            if (lighting.enable) {
                rgb_matrix_enable();
            } else {
                rgb_matrix_disable();
            }
        }

        snowfox_config_t config = snowfox_config_read();
        config.profile          = profile;
        snowfox_config_write(config);
    }
    profile_apply_layers(profile);
    snowfox_led_show_profile(profile);
}

// Restores the current profile's default lighting and, with VIA, clears the key
// changes on its layer. Profile 0 has no layer of its own.
void snowfox_profile_reset(void) {
    uint8_t profile = snowfox_profile();

    eeconfig_update_rgb_matrix_default();
    eeconfig_update_kb_datablock(&rgb_matrix_config, SF_LIGHTING_OFFSET(profile), sizeof(rgb_config_t));

#ifdef DYNAMIC_KEYMAP_ENABLE
    if (profile > 0) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                dynamic_keymap_set_keycode(SF_LAYER_PROFILE1 + profile - 1, row, col, KC_TRNS);
            }
        }
    }
#endif
    snowfox_led_show_profile(profile);
}

void keyboard_post_init_kb(void) {
    profile_apply_layers(snowfox_profile());
    apply_switch();
    keyboard_post_init_user();
}

// Connects to, or with pair set starts pairing with, Bluetooth host 0 to 2, and remembers it.
void snowfox_ble_select(uint8_t host, bool pair) {
    ble_cmdq->put(PICK_KEYBOARD1 + host);
    ble_cmdq->put(pair ? DISCOVER : CONNECT);

    snowfox_config_t config = snowfox_config_read();
    if (config.ble_slot != host + 1) {
        config.ble_slot = host + 1;
        snowfox_config_write(config);
    }
}

// Hold a Bluetooth slot key at least this long to pair instead of switching.
#define SNOWFOX_BLE_PAIR_HOLD_MS 3000

static bool process_ble_slot_key(uint16_t keycode, keyrecord_t *record) {
    static uint16_t pressed_at[BLE_KEYBOARD_SIZE];
    uint8_t         slot = keycode - SF_BT1;

    if (record->event.pressed) {
        pressed_at[slot] = timer_read();
        return false;
    }

    snowfox_ble_select(slot, timer_elapsed(pressed_at[slot]) >= SNOWFOX_BLE_PAIR_HOLD_MS);
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    // Only keys that send something to the computer reconnect. Fn, lighting and the
    // host keys do not, so Fn+X does not first reconnect to the previous host.
    if (record->event.pressed && keycode <= QK_BASIC_MAX) {
        snowfox_ble_key_pressed();
    }

    switch (keycode) {
        case SF_BT1 ... SF_BT3:
            return process_ble_slot_key(keycode, record);
        case SF_BATT:
            snowfox_led_show_battery(record->event.pressed);
            return false;
        case SF_FRST:
            snowfox_factory_reset_key(record->event.pressed);
            return false;
        case SF_PRF0 ... SF_PRF4:
            if (record->event.pressed) {
                snowfox_profile_select(keycode - SF_PRF0);
            }
            return false;
        case SF_FNLK:
            if (record->event.pressed) {
                layer_invert(SF_LAYER_FN_LOCK);
            }
            return false;
    }

    return true;
}

