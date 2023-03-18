// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/** \brief 5-bit packed modifiers
 *
 * Mod bits:    43210
 *   bit 0      ||||+- Control
 *   bit 1      |||+-- Shift
 *   bit 2      ||+--- Alt
 *   bit 3      |+---- Gui
 *   bit 4      +----- LR flag(Left:0, Right:1)
 */
enum mods_5bit {
    MOD_LCTL = 0x01,
    MOD_LSFT = 0x02,
    MOD_LALT = 0x04,
    MOD_LGUI = 0x08,
    MOD_RCTL = 0x11,
    MOD_RSFT = 0x12,
    MOD_RALT = 0x14,
    MOD_RGUI = 0x18,
};
#define MOD_HYPR (MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI)
#define MOD_MEH (MOD_LCTL | MOD_LSFT | MOD_LALT)

/** \brief 8-bit packed modifiers
 */
enum mods_8bit {
    MOD_BIT_LCTRL  = 0b00000001,
    MOD_BIT_LSHIFT = 0b00000010,
    MOD_BIT_LALT   = 0b00000100,
    MOD_BIT_LGUI   = 0b00001000,
    MOD_BIT_RCTRL  = 0b00010000,
    MOD_BIT_RSHIFT = 0b00100000,
    MOD_BIT_RALT   = 0b01000000,
    MOD_BIT_RGUI   = 0b10000000,
};
#define MOD_MASK_CTRL (MOD_BIT_LCTRL | MOD_BIT_RCTRL)
#define MOD_MASK_SHIFT (MOD_BIT_LSHIFT | MOD_BIT_RSHIFT)
#define MOD_MASK_ALT (MOD_BIT_LALT | MOD_BIT_RALT)
#define MOD_MASK_GUI (MOD_BIT_LGUI | MOD_BIT_RGUI)
#define MOD_MASK_CS (MOD_MASK_CTRL | MOD_MASK_SHIFT)
#define MOD_MASK_CA (MOD_MASK_CTRL | MOD_MASK_ALT)
#define MOD_MASK_CG (MOD_MASK_CTRL | MOD_MASK_GUI)
#define MOD_MASK_SA (MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_SG (MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_AG (MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSA (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_CSG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_CAG (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_SAG (MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSAG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)
