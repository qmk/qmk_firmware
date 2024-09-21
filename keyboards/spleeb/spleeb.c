// Copyright 2022 Chris Hoage (@chrishoage)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "spleeb.h"
#include "transactions.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

#if defined(POINTING_DEVICE_ENABLE) || defined(SPLEEB_ENCODER_MODE_MAP_ENABLE)
typedef union {
    uint16_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        uint8_t enc_modes[NUM_ENCODERS];
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
    } __attribute__((packed));
} spleeb_config_t;

static spleeb_config_t g_spleeb_config = {0};

/**
 * \brief Set the value of `config` from EEPROM.
 *
 * Note that `is_dragscroll_enabled` and `is_sniping_enabled` are purposefully
 * ignored since we do not want to persist this state to memory.  In practice,
 * this state is always written to maximize write-performances.  Therefore, we
 * explicitly set them to `false` in this function.
 */
static void read_spleeb_config_from_eeprom(spleeb_config_t* config) {
    config->raw                   = eeconfig_read_kb() & 0xffff;
    config->is_dragscroll_enabled = false;
    config->is_sniping_enabled    = false;
}

/**
 * \brief Save the value of `config` to eeprom.
 *
 * Note that all values are written verbatim, including whether drag-scroll
 * and/or sniper mode are enabled.  `read_spleeb_config_from_eeprom(…)`
 * resets these 2 values to `false` since it does not make sense to persist
 * these across reboots of the board.
 */
static void write_spleeb_config_to_eeprom(spleeb_config_t* config) {
    eeconfig_update_kb(config->raw);
}

void eeconfig_init_kb(void) {
    g_spleeb_config.raw                 = 0;
    g_spleeb_config.pointer_default_dpi = 4;

#    ifdef SPLEEB_ENCODER_MODE_MAP_ENABLE
    for (size_t i = 0; i < NUM_ENCODERS; i++) {
        if (spleeb_encoder_mode_map[i][0].initalized) {
            spleeb_enc_mode_t* first_enc_mode = &spleeb_encoder_mode_map[i][0];
            g_spleeb_config.enc_modes[i]      = first_enc_mode->mode;
        }
    }
#    endif // SPLEEB_ENCODER_MODE_MAP_ENABLE

    write_spleeb_config_to_eeprom(&g_spleeb_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_spleeb_config_from_eeprom(&g_spleeb_config);
    matrix_init_user();
}

void spleeb_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(g_spleeb_config)) {
        memcpy(&g_spleeb_config, initiator2target_buffer, sizeof(g_spleeb_config));
    }
}

void keyboard_post_init_kb(void) {
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, spleeb_config_sync_handler);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave.
        static spleeb_config_t last_spleeb_config = {0};
        static uint32_t        last_sync          = 0;
        bool                   needs_sync         = false;

        // Check if the state values are different.
        if (memcmp(&g_spleeb_config, &last_spleeb_config, sizeof(g_spleeb_config))) {
            needs_sync = true;
            memcpy(&last_spleeb_config, &g_spleeb_config, sizeof(g_spleeb_config));
        }
        // Send to slave every 500ms regardless of state change.
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested.
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KB_CONFIG_SYNC, sizeof(g_spleeb_config), &g_spleeb_config)) {
                last_sync = timer_read32();
            }
        }
    }
    // No need to invoke the user-specific callback, as it's been called
    // already.
}
#endif // defined(POINTING_DEVICE_ENABLE) || defined(SPLEEB_ENCODER_MODE_MAP_ENABLE)

#ifdef SPLEEB_ENCODER_MODE_MAP_ENABLE

/**
 * \brief Handle the encoder mode action when triggered by encoder_update_kb
 *
 * Weakly defined fuction intended to be overridden in a users keymap
 */
__attribute__((weak)) void spleeb_encoder_mode_trigger(uint8_t mode, bool clockwise) {}

typedef struct {
    uint8_t            index;
    spleeb_enc_mode_t* enc_mode;
} spleeb_found_enc_mode_t;

static spleeb_found_enc_mode_t spleeb_get_found_encoder_mode(spleeb_config_t* config, uint8_t index) {
    spleeb_found_enc_mode_t found_enc_mode;

    for (size_t i = 0; i < SPLEEB_ENCODER_MODE_COUNT; i++) {
        spleeb_enc_mode_t* cur_enc_mode = &spleeb_encoder_mode_map[index][i];
        if (cur_enc_mode->mode == config->enc_modes[index]) {
            found_enc_mode.index    = i;
            found_enc_mode.enc_mode = cur_enc_mode;
            break;
        }
    }

    return found_enc_mode;
}

/**
 * \brief Step through the defined encoder modes for the encoder at the given
 * index
 *
 * Step though the modes defined in spleeb_encoder_mode_map at the users keymap.
 * Use a null terminator at the first character on the name property for the
 * enc_mode struct to determine if we've reached the end of the defined encoder
 * modes. When this happens loop back to the beginning.
 */
static void spleeb_step_encoder_mode(spleeb_config_t* config, uint8_t index) {
    spleeb_found_enc_mode_t cur_enc_mode  = spleeb_get_found_encoder_mode(config, index);
    spleeb_enc_mode_t*      next_enc_mode = &spleeb_encoder_mode_map[index][(cur_enc_mode.index + 1) % SPLEEB_ENCODER_MODE_COUNT];

    if (!next_enc_mode->initalized) {
        next_enc_mode = &spleeb_encoder_mode_map[index][0];
    }

    if (next_enc_mode->initalized) {
        config->enc_modes[index] = next_enc_mode->mode;
        write_spleeb_config_to_eeprom(config);
    }
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    spleeb_encoder_mode_trigger(g_spleeb_config.enc_modes[index], clockwise);

    return true;
}
#endif // SPLEEB_ENCODER_MODE_MAP_ENABLE

#ifdef POINTING_DEVICE_ENABLE

/** \brief Return the current value of the pointer's default DPI. */
static uint16_t get_pointer_default_dpi(spleeb_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * SPLEEB_DEFAULT_DPI_CONFIG_STEP + SPLEEB_MINIMUM_DEFAULT_DPI;
}

/** \brief Return the current value of the pointer's sniper-mode DPI. */
static uint16_t get_pointer_sniping_dpi(spleeb_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * SPLEEB_SNIPING_DPI_CONFIG_STEP + SPLEEB_MINIMUM_SNIPING_DPI;
}

/** \brief Return the current value of the pointer's default DPI. */
static uint16_t get_pointer_current_dpi(spleeb_config_t* config) {
    if (config->is_sniping_enabled) {
        return get_pointer_sniping_dpi(config);
    } else {
        return get_pointer_default_dpi(config);
    }
}

/** \brief Set the appropriate DPI for the input config. */
static void maybe_update_pointing_device_cpi(spleeb_config_t* config) {
    if (config->is_sniping_enabled) {
        pointing_device_set_cpi(get_pointer_sniping_dpi(config));
    } else {
        pointing_device_set_cpi(get_pointer_default_dpi(config));
    }
}

/**
 * \brief Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to SPLEEB_DEFAULT_DPI_CONFIG_STEP.
 */
static void step_pointer_default_dpi(spleeb_config_t* config, bool forward) {
    config->pointer_default_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

/**
 * \brief Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to SPLEEB_SNIPING_DPI_CONFIG_STEP.
 */
static void step_pointer_sniping_dpi(spleeb_config_t* config, bool forward) {
    config->pointer_sniping_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

uint16_t spleeb_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_spleeb_config);
}

uint16_t spleeb_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_spleeb_config);
}

void spleeb_cycle_pointer_default_dpi_noeeprom(bool forward) {
    step_pointer_default_dpi(&g_spleeb_config, forward);
}

void spleeb_cycle_pointer_default_dpi(bool forward) {
    step_pointer_default_dpi(&g_spleeb_config, forward);
    write_spleeb_config_to_eeprom(&g_spleeb_config);
}

void spleeb_cycle_pointer_sniping_dpi_noeeprom(bool forward) {
    step_pointer_sniping_dpi(&g_spleeb_config, forward);
}

void spleeb_cycle_pointer_sniping_dpi(bool forward) {
    step_pointer_sniping_dpi(&g_spleeb_config, forward);
    write_spleeb_config_to_eeprom(&g_spleeb_config);
}

bool spleeb_get_pointer_sniping_enabled(void) {
    return g_spleeb_config.is_sniping_enabled;
}

void spleeb_set_pointer_sniping_enabled(bool enable) {
    g_spleeb_config.is_sniping_enabled = enable;
    maybe_update_pointing_device_cpi(&g_spleeb_config);
}

bool spleeb_get_pointer_dragscroll_enabled(void) {
    return g_spleeb_config.is_dragscroll_enabled;
}

void spleeb_set_pointer_dragscroll_enabled(bool enable) {
    g_spleeb_config.is_dragscroll_enabled = enable;
    cirque_pinnacle_enable_cursor_glide(enable);
    maybe_update_pointing_device_cpi(&g_spleeb_config);
}
#endif // POINTING_DEVICE_ENABLE

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_spleeb_config);

    // only glide on drag scroll
    cirque_pinnacle_enable_cursor_glide(false);

    set_auto_mouse_enable(true);
    pointing_device_init_user();
}

/**
 * \brief Augment the pointing device behavior.
 *
 * Drag-scroll implementation borrowed from https://github.com/qmk/qmk_firmware/pull/18218
 */
static void pointing_device_task_spleeb(report_mouse_t* mouse_report) {
    static int16_t scroll_x = 0;
    static int16_t scroll_y = 0;
    if (g_spleeb_config.is_dragscroll_enabled) {
        scroll_x -= mouse_report->x;
        scroll_y += mouse_report->y;
        mouse_report->h = scroll_x / SPLEEB_DRAGSCROLL_DIVISOR;
        mouse_report->v = scroll_y / SPLEEB_DRAGSCROLL_DIVISOR;
        mouse_report->x = 0;
        mouse_report->y = 0;
        scroll_x -= (int16_t)mouse_report->h * SPLEEB_DRAGSCROLL_DIVISOR;
        scroll_y -= (int16_t)mouse_report->v * SPLEEB_DRAGSCROLL_DIVISOR;
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_keyboard_master()) {
        pointing_device_task_spleeb(&mouse_report);

        mouse_report = pointing_device_task_user(mouse_report);
    }

    return mouse_report;
}

/**
 * \brief Outputs the Spleeb configuration to console.
 *
 * Prints the in-memory configuration structure to console, for debugging.
 * Includes:
 *   - raw value
 *   - drag-scroll: on/off
 *   - sniping: on/off
 *   - default DPI: internal table index/actual DPI
 *   - sniping DPI: internal table index/actual DPI
 */
static void debug_spleeb_config_to_console(spleeb_config_t* config) {
#    ifdef CONSOLE_ENABLE
    pd_dprintf("(spleeb) process_record_kb: config = {\n"
               "\traw = 0x%u,\n"
               "\t{\n"
               "\t\tis_dragscroll_enabled=%u\n"
               "\t\tis_sniping_enabled=%u\n"
               "\t\tdefault_dpi=0x%X (%u)\n"
               "\t\tsniping_dpi=0x%X (%u)\n"
               "\t}\n"
               "}\n",
               config->raw, config->is_dragscroll_enabled, config->is_sniping_enabled, config->pointer_default_dpi, get_pointer_default_dpi(config), config->pointer_sniping_dpi, get_pointer_sniping_dpi(config));
#    endif // CONSOLE_ENABLE
}
#endif // POINTING_DEVICE_ENABLE

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
#ifdef POINTING_DEVICE_ENABLE

        debug_spleeb_config_to_console(&g_spleeb_config);
#endif // POINTING_DEVICE_ENABLE
        return false;
    }
#ifdef POINTING_DEVICE_ENABLE
    switch (keycode) {
        case POINTER_DEFAULT_DPI_FORWARD:
            if (record->event.pressed) {
                spleeb_cycle_pointer_default_dpi(true);
            }
            break;
        case POINTER_DEFAULT_DPI_REVERSE:
            if (record->event.pressed) {
                spleeb_cycle_pointer_default_dpi(false);
            }
            break;
        case POINTER_SNIPING_DPI_FORWARD:
            if (record->event.pressed) {
                spleeb_cycle_pointer_sniping_dpi(true);
            }
            break;
        case POINTER_SNIPING_DPI_REVERSE:
            if (record->event.pressed) {
                spleeb_cycle_pointer_sniping_dpi(false);
            }
            break;
        case SNIPING_MODE:
            spleeb_set_pointer_sniping_enabled(record->event.pressed);
            break;
        case SNIPING_MODE_TOGGLE:
            if (record->event.pressed) {
                spleeb_set_pointer_sniping_enabled(!spleeb_get_pointer_sniping_enabled());
            }
            break;
        case DRAGSCROLL_MODE:
            spleeb_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
        case DRAGSCROLL_MODE_TOGGLE:
            if (record->event.pressed) {
                spleeb_set_pointer_dragscroll_enabled(!spleeb_get_pointer_dragscroll_enabled());
            }
            break;
    }
#endif // POINTING_DEVICE_ENABLE

#ifdef SPLEEB_ENCODER_MODE_MAP_ENABLE
    switch (keycode) {
        case ENC_MODE_STEP_LEFT:
            if (record->event.pressed) {
                spleeb_step_encoder_mode(&g_spleeb_config, 0);
            }
            break;
        case ENC_MODE_STEP_RIGHT:
            if (record->event.pressed) {
                spleeb_step_encoder_mode(&g_spleeb_config, 1);
            }
            break;
    }
#endif // SPLEEB_ENCODER_MODE_MAP_ENABLE

#ifdef POINTING_DEVICE_ENABLE
    if ((keycode >= POINTER_DEFAULT_DPI_FORWARD && keycode <= ENC_MODE_STEP_RIGHT) || IS_MOUSEKEY(keycode)) {
        debug_spleeb_config_to_console(&g_spleeb_config);
    }
#endif // POINTING_DEVICE_ENABLE

    return true;
}

#ifdef POINTING_DEVICE_ENABLE

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case DRAGSCROLL_MODE:
        case SNIPING_MODE:
            return true;
        default:
            return false;
    }

    return is_mouse_record_user(keycode, record);
}

#endif // POINTING_DEVICE_ENABLE

#ifdef OLED_ENABLE

static void render_layer(void) {
    oled_write_P(PSTR("LAYER: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("\xC0\xC1"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("\xC2\xC3"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("\xC4\xC5"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("\xC6\xC7"), false);
            break;
        case 4:
            oled_write_ln_P(PSTR("\xC8\xC9"), false);
            break;
        case 5:
            oled_write_ln_P(PSTR("\xCA\xCB"), false);
            break;
        default:
            oled_write_ln_P(get_u8_str(get_highest_layer(layer_state) + 0x30, ' '), true);
    }

    oled_write_ln_P("", false);
}

static void render_mods(void) {
    uint8_t modifiers = get_mods();

    oled_write_ln_P(PSTR("MODS:"), false);
    oled_write_ln_P("", false);
    oled_write_P(PSTR("\325\326"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("\327\330"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("\331\332"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("\333\334"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P("", false);
}

static void render_lock(void) {
    led_t led_state = host_keyboard_led_state();

    oled_write_P(PSTR("LOCK: "), false);
    oled_write_P(PSTR("\235\236"), led_state.caps_lock);
    oled_write_ln_P(PSTR("\275\276"), led_state.num_lock);
}

static void render_pointer(void) {
#    ifdef POINTING_DEVICE_ENABLE
    oled_write_ln_P(PSTR("POINTER:"), false);
    oled_write_ln_P("", false);
    oled_write_P(PSTR("dpi:"), false);
    oled_write_ln_P(get_u16_str(get_pointer_current_dpi(&g_spleeb_config), ' '), false);
    oled_write_ln_P("", false);
#    endif // POINTING_DEVICE_ENABLE
}

#    ifdef SPLEEB_ENCODER_MODE_MAP_ENABLE
static uint8_t spleeb_get_encoder_mode(spleeb_config_t* config, uint8_t index) {
    spleeb_found_enc_mode_t found_enc_mode = spleeb_get_found_encoder_mode(config, index);
    return found_enc_mode.enc_mode->mode;
}

/**
 * \brief Map an encoder mode to a string to be displayed on the OLED
 *
 * Weakly defined fuction intended to be overridden in a users keymap. My be
 * omitted if no OLED is used.
 */
__attribute__((weak)) const char* spleeb_encoder_mode_string(uint8_t mode) {
    return get_u8_str(mode, ' ');
}
#    endif //  SPLEEB_ENCODER_MODE_MAP_ENABLE

static void render_encoder(void) {
#    ifdef SPLEEB_ENCODER_MODE_MAP_ENABLE
    oled_write_ln_P(PSTR("ENCODER:"), false);
    oled_write_ln_P("", false);
    oled_write_P(PSTR("R: "), false);
    oled_write_ln_P(spleeb_encoder_mode_string(spleeb_get_encoder_mode(&g_spleeb_config, 1)), false);
    oled_write_P(PSTR("L: "), false);
    oled_write_ln_P(spleeb_encoder_mode_string(spleeb_get_encoder_mode(&g_spleeb_config, 0)), false);
#    endif //  SPLEEB_ENCODER_MODE_MAP_ENABLE
}

static void render_status(void) {
    render_layer();
    render_mods();
    render_lock();
    render_pointer();
    render_encoder();
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_task_kb(void) {
    if (is_keyboard_master()) {
        return false;
    }

    if (!oled_task_user()) {
        return false;
    }

    render_status();
    return false;
}
#endif // OLED_ENABLE
