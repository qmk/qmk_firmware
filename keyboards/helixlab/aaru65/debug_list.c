// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "debug_list.h"
#include "version.h"
#include "i2c_master.h"

void debug_custom(void) {
    dprintf("[DEVICE INFO]\n");
    dprintf("General\n");
    dprintf("   VID: %s\n", STR(VENDOR_ID));
    dprintf("   PID: %s\n", STR(PRODUCT_ID));
    dprintf("   VER: %s\n", STR(DEVICE_VER));
    dprintf("   Manufacturer: %s\n", STR(MANUFACTURER));
    dprintf("   Product: %s\n", STR(PRODUCT));
    dprintf("Firmware\n");
    dprintf("   QMK Ver: %s\n", STR(QMK_VERSION));
    dprintf("   Build Date: %s\n", STR(QMK_BUILDDATE));
    dprintf("   Keyboard: %s\n", STR(QMK_KEYBOARD));
    dprintf("   Keymap: %s\n", STR(QMK_KEYMAP));
    dprintf("Keyboard\n");
    dprintf("   NKRO: %s\n", YN(keymap_config.nkro));
    dprintf("   Win Lock : %s\n", YN(keymap_config.no_gui));
    dprintf("   Alt_Win Swap : %s\n", YN(keymap_config.swap_lalt_lgui));
    dprintf("   Ctrl_Caps Swap : %s\n", YN(keymap_config.swap_control_capslock));
#ifdef RGB_INDICATOR_ENABLE
    dprintf("RGB Indicator\n");
    dprintf("   RGB Indicator Enable: %s\n", YN(rgb_indicator_config.enable));
    dprintf("   RGB Indicator Selection: %s\n", YN(rgb_indicator_config.select));
    dprintf("   RGB Indicator Mode: %d\n", rgb_indicator_config.mode);
    dprintf("   RGB Indicator HSV: %d %d %d\n", rgb_indicator_config.hsv.h, rgb_indicator_config.hsv.s, rgb_indicator_config.hsv.v);
#endif
#ifdef RGB_MATRIX_ENABLE
    dprintf("RGB Matrix\n");
    dprintf("   RGB Matrix Enable: %s\n", YN(rgb_matrix_is_enabled()));
    dprintf("   RGB Matrix Mode: %d\n", rgb_matrix_get_mode());
    dprintf("   RGB Matrix HSV: %d %d %d\n", rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val());
    dprintf("   RGB Matrix Speed: %d\n", rgb_matrix_get_speed());
    dprintf("   RGB Matrix Indicator Only: %s\n", YN(rgb_matrix_get_mode() == 41 ? 1 : 0));
#endif
#ifdef FADER_ENABLE
    dprintf("Fader\n");
    dprintf("   Fader Enable: %s\n", YN(fader_config.enable));
    dprintf("   Fader Reverse: %s\n", YN(fader_config.reverse));
    dprintf("   Fader Channel: %d\n", fader_config.channel);
    dprintf("   Fader CC: %d\n", fader_config.cc);
    dprintf("   Fader Value: %d\n", fader_get_val());
#endif
    dprintf("[END]\n");
}