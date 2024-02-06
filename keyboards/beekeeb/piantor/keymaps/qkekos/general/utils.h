
#pragma once
#include "../__init__.h"

bool is_shift_held_core(int mods);
bool is_ctrl_held_core(int mods);
bool is_gui_held_core(int mods);
bool is_alt_held_core(int mods);

bool is_shift_held(void);
bool is_ctrl_held(void);
bool is_gui_held(void);
bool is_alt_held(void);

bool is_os_shift_held(void);
bool is_os_ctrl_held(void);
bool is_os_gui_held(void);
bool is_os_alt_held(void);

bool is_alpha_layer_on(void);
void multi_tap(uint16_t keycode, int count);
uint16_t normalize_keycode(uint16_t keycode);

#define execute_without_mods(x) \
    { \
        int mod_state = get_mods(); \
        clear_mods(); \
        { x; } \
        set_mods(mod_state); \
    }

#define tap_clear_code(code) execute_without_mods(tap_code16(code))
#define IS_ALPHA_KEY(keycode) (KC_A <= keycode && keycode <= KC_Z)
