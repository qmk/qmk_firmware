// Copyright 2022 Joshua Diamond josh@windowoffire.com (@spidey3)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "spidey3.h"

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    keyboard_post_init_user_rgb();
#endif
}

void eeconfig_init_user(void) {
    set_single_persistent_default_layer(_BASE);
#ifdef UNICODEMAP_ENABLE
    eeconfig_init_user_unicode();
#endif
}

#ifdef RGBLIGHT_ENABLE
void shutdown_user(void) { shutdown_user_rgb(); }
#endif
