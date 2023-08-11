// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <hal.h>
#include <string.h>
#include <ctype.h>
#include <printf.h>
#include "qp.h"
#include "backlight.h"
#include "transactions.h"
#include "split_util.h"

#include "djinn.h"
#include "theme_djinn_default.h"

#include "djinn.qgf.h"
#include "lock-caps-ON.qgf.h"
#include "lock-scrl-ON.qgf.h"
#include "lock-num-ON.qgf.h"
#include "lock-caps-OFF.qgf.h"
#include "lock-scrl-OFF.qgf.h"
#include "lock-num-OFF.qgf.h"
#include "thintel15.qff.h"

static painter_image_handle_t djinn_logo;
static painter_image_handle_t lock_caps_on;
static painter_image_handle_t lock_caps_off;
static painter_image_handle_t lock_num_on;
static painter_image_handle_t lock_num_off;
static painter_image_handle_t lock_scrl_on;
static painter_image_handle_t lock_scrl_off;
static painter_font_handle_t  thintel;

//----------------------------------------------------------
// RGB Matrix naming
#if defined(RGB_MATRIX_ENABLE)
#    include <rgb_matrix.h>

#    if defined(RGB_MATRIX_EFFECT)
#        undef RGB_MATRIX_EFFECT
#    endif // defined(RGB_MATRIX_EFFECT)

#    define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
};

#    define RGB_MATRIX_EFFECT(x)    \
        case RGB_MATRIX_EFFECT_##x: \
            return #x;
const char *rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
        default:
            return "UNKNOWN";
    }
}
#endif // defined(RGB_MATRIX_ENABLE)

//----------------------------------------------------------
// UI Initialisation
void keyboard_post_init_display(void) {
    djinn_logo    = qp_load_image_mem(gfx_djinn);
    lock_caps_on  = qp_load_image_mem(gfx_lock_caps_ON);
    lock_caps_off = qp_load_image_mem(gfx_lock_caps_OFF);
    lock_num_on   = qp_load_image_mem(gfx_lock_num_ON);
    lock_num_off  = qp_load_image_mem(gfx_lock_num_OFF);
    lock_scrl_on  = qp_load_image_mem(gfx_lock_scrl_ON);
    lock_scrl_off = qp_load_image_mem(gfx_lock_scrl_OFF);
    thintel       = qp_load_font_mem(font_thintel15);
}

//----------------------------------------------------------
// UI Drawing
void draw_ui_user(bool force_redraw) {
    bool            hue_redraw = force_redraw;
    static uint16_t last_hue   = 0xFFFF;
#if defined(RGB_MATRIX_ENABLE)
    uint16_t curr_hue = rgb_matrix_get_hue();
#else  // defined(RGB_MATRIX_ENABLE)
    uint16_t curr_hue = 0;
#endif // defined(RGB_MATRIX_ENABLE)
    if (last_hue != curr_hue) {
        last_hue   = curr_hue;
        hue_redraw = true;
    }

    bool            layer_state_redraw = false;
    static uint32_t last_layer_state   = 0;
    if (last_layer_state != layer_state) {
        last_layer_state   = layer_state;
        layer_state_redraw = true;
    }

    bool                     power_state_redraw = false;
    static usbpd_allowance_t last_current_state = (usbpd_allowance_t)(~0);
    if (last_current_state != kb_state.current_setting) {
        last_current_state = kb_state.current_setting;
        power_state_redraw = true;
    }

    bool            scan_redraw      = false;
    static uint32_t last_scan_update = 0;
    if (timer_elapsed32(last_scan_update) > 125) {
        last_scan_update = timer_read32();
        scan_redraw      = true;
    }

    bool            wpm_redraw      = false;
    static uint32_t last_wpm_update = 0;
    if (timer_elapsed32(last_wpm_update) > 125) {
        last_wpm_update = timer_read32();
        wpm_redraw      = true;
    }

#if defined(RGB_MATRIX_ENABLE)
    bool            rgb_effect_redraw = false;
    static uint16_t last_effect       = 0xFFFF;
    uint8_t         curr_effect       = rgb_matrix_config.mode;
    if (last_effect != curr_effect) {
        last_effect       = curr_effect;
        rgb_effect_redraw = true;
    }
#endif // defined(RGB_MATRIX_ENABLE)

    // Show the Djinn logo and two vertical bars on both sides
    if (hue_redraw) {
        qp_drawimage_recolor(lcd, 120 - djinn_logo->width / 2, 32, djinn_logo, curr_hue, 255, 255, curr_hue, 255, 0);
        qp_rect(lcd, 0, 0, 8, 319, curr_hue, 255, 255, true);
        qp_rect(lcd, 231, 0, 239, 319, curr_hue, 255, 255, true);
    }

    int ypos = 4;

    // Show layer info on the left side
    if (is_keyboard_left()) {
        char buf[64] = {0};
        int  xpos    = 16;

#if defined(RGB_MATRIX_ENABLE)
        if (hue_redraw || rgb_effect_redraw) {
            static int max_rgb_xpos = 0;
            xpos                    = 16;
            snprintf(buf, sizeof(buf), "rgb: %s", rgb_matrix_name(curr_effect));

            for (int i = 5; i < sizeof(buf); ++i) {
                if (buf[i] == 0)
                    break;
                else if (buf[i] == '_')
                    buf[i] = ' ';
                else if (buf[i - 1] == ' ')
                    buf[i] = toupper(buf[i]);
                else if (buf[i - 1] != ' ')
                    buf[i] = tolower(buf[i]);
            }

            xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_rgb_xpos < xpos) {
                max_rgb_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_rgb_xpos, ypos + thintel->line_height, 0, 0, 0, true);
        }

        ypos += thintel->line_height + 4;
#endif // defined(RGB_MATRIX_ENABLE)

        if (hue_redraw || layer_state_redraw) {
            extern const char *current_layer_name(void);
            const char        *layer_name = current_layer_name();

            static int max_layer_xpos = 0;
            xpos                      = 16;
            snprintf(buf, sizeof(buf), "layer: %s", layer_name);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_layer_xpos < xpos) {
                max_layer_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_layer_xpos, ypos + thintel->line_height, 0, 0, 0, true);
        }

        ypos += thintel->line_height + 4;

        if (hue_redraw || power_state_redraw) {
            static int max_power_xpos = 0;
            xpos                      = 16;
            snprintf(buf, sizeof(buf), "power: %s", usbpd_str(kb_state.current_setting));
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_power_xpos < xpos) {
                max_power_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_power_xpos, ypos + thintel->line_height, 0, 0, 0, true);
        }

        ypos += thintel->line_height + 4;

        if (hue_redraw || scan_redraw) {
            static int max_scans_xpos = 0;
            xpos                      = 16;
            snprintf(buf, sizeof(buf), "scans: %d", (int)theme_state.scan_rate);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_scans_xpos < xpos) {
                max_scans_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_scans_xpos, ypos + thintel->line_height, 0, 0, 0, true);
        }

        ypos += thintel->line_height + 4;

        if (hue_redraw || wpm_redraw) {
            static int max_wpm_xpos = 0;
            xpos                    = 16;
            snprintf(buf, sizeof(buf), "wpm: %d", (int)get_current_wpm());
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_wpm_xpos < xpos) {
                max_wpm_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_wpm_xpos, ypos + thintel->line_height, 0, 0, 0, true);
        }

        ypos += thintel->line_height + 4;
    }

    // Show LED lock indicators on the right side
    if (!is_keyboard_left()) {
        static led_t last_led_state = {0};
        if (hue_redraw || last_led_state.raw != host_keyboard_led_state().raw) {
            last_led_state.raw = host_keyboard_led_state().raw;
            qp_drawimage_recolor(lcd, 239 - 12 - (32 * 3), 0, last_led_state.caps_lock ? lock_caps_on : lock_caps_off, curr_hue, 255, last_led_state.caps_lock ? 255 : 32, curr_hue, 255, 0);
            qp_drawimage_recolor(lcd, 239 - 12 - (32 * 2), 0, last_led_state.num_lock ? lock_num_on : lock_num_off, curr_hue, 255, last_led_state.num_lock ? 255 : 32, curr_hue, 255, 0);
            qp_drawimage_recolor(lcd, 239 - 12 - (32 * 1), 0, last_led_state.scroll_lock ? lock_scrl_on : lock_scrl_off, curr_hue, 255, last_led_state.scroll_lock ? 255 : 32, curr_hue, 255, 0);
        }
    }
}

//----------------------------------------------------------
// Sync

theme_runtime_config theme_state;

void rpc_theme_sync_callback(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    if (m2s_size == sizeof(theme_state)) {
        memcpy(&theme_state, m2s_buffer, m2s_size);
    }
}

void theme_init(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(THEME_DATA_SYNC, rpc_theme_sync_callback);

    // Reset the initial shared data value between master and slave
    memset(&theme_state, 0, sizeof(theme_state));
}

void theme_state_update(void) {
    if (is_keyboard_master()) {
        // Keep the scan rate in sync
        theme_state.scan_rate = get_matrix_scan_rate();
    }
}

void theme_state_sync(void) {
    if (!is_transport_connected()) return;

    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static theme_runtime_config last_theme_state;
        static uint32_t             last_sync;
        bool                        needs_sync = false;

        // Check if the state values are different
        if (memcmp(&theme_state, &last_theme_state, sizeof(theme_runtime_config))) {
            needs_sync = true;
            memcpy(&last_theme_state, &theme_state, sizeof(theme_runtime_config));
        }

        // Send to slave every 125ms regardless of state change
        if (timer_elapsed32(last_sync) > 125) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(THEME_DATA_SYNC, sizeof(theme_runtime_config), &theme_state)) {
                last_sync = timer_read32();
            } else {
                dprint("Failed to perform rpc call\n");
            }
        }
    }
}
