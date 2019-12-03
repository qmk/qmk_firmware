#include QMK_KEYBOARD_H

/**
 * Custom Keycodes for advanced functionality
 */
bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

enum custom_keycodes {            // Make sure have the awesome keycode ready 
  ALT_TAB = SAFE_RANGE,
};
