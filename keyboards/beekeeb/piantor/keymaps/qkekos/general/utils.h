
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

uint16_t normalize_keycode(uint16_t keycode);
void multi_tap(uint16_t keycode, int count);
const char* to_upper_case(const char *str);
uint16_t char_to_keycode(char symbol);
bool is_uppercase_letter(char symbol);
bool is_lowercase_letter(char symbol);
bool is_alpha_layer_on(void);

#define execute_without_mods(x) \
    { \
        int mod_state = get_mods(); \
        clear_mods(); \
        { x; } \
        set_mods(mod_state); \
    }

#define tap_clear_code(code) execute_without_mods(tap_code16(code))
#define IS_ALPHA_KEY(keycode) (KC_A <= keycode && keycode <= KC_Z)

#define MAX_STR_LEN 100
