// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define FREE32KNOB_OLED_MAX_PRESSING_KEYCODES 6

typedef struct {

    uint16_t       last_kc;
    keypos_t       last_pos;

    // Buffer to indicate pressing keys.
    char pressing_keys[FREE32KNOB_OLED_MAX_PRESSING_KEYCODES + 1];
} knob_t;

typedef enum {
    FREE32KNOB_ADJUST_PENDING   = 0,
    FREE32KNOB_ADJUST_PRIMARY   = 1,
    FREE32KNOB_ADJUST_SECONDARY = 2,
} free32knob_adjust_t;

// Exported values (touch carefully)

extern knob_t knob;

//////////////////////////////////////////////////////////////////////////////
// Public API functions

/// my logo
void free32knob_oled_render_mylogo(void);

/// freeadrs32_knob_oled_render_keyinfo renders last processed key information to OLED.
/// It shows column, row, key code, and key name (if available).
void free32knob_oled_render_keyinfo(void);

/// freeadrs32_knob_oled_render_layerinfo renders current layer status information to
/// OLED.  It shows layer mask with number (1~f) for active layers and '_' for
/// inactive layers.
void free32knob_oled_render_layerinfo(void);
