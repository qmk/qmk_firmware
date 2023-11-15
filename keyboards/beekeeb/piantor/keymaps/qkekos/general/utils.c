
#include "../__init__.h"

bool is_shift_held(void) { return get_mods() & MOD_BIT(KC_LSFT); }
bool is_ctrl_held(void)  { return get_mods() & MOD_BIT(KC_LCTL); }
bool is_gui_held(void)   { return get_mods() & MOD_BIT(KC_LGUI); }
bool is_alt_held(void)   { return get_mods() & MOD_BIT(KC_LALT); }

bool is_os_shift_held(void) { return get_oneshot_mods() & MOD_BIT(KC_LSFT); }
bool is_os_ctrl_held(void)  { return get_oneshot_mods() & MOD_BIT(KC_LCTL); }
bool is_os_gui_held(void)   { return get_oneshot_mods() & MOD_BIT(KC_LGUI); }
bool is_os_alt_held(void)   { return get_oneshot_mods() & MOD_BIT(KC_LALT); }

bool is_alpha_layer_on(void) {
    return (get_highest_layer(layer_state) < HOTKEY);
}
