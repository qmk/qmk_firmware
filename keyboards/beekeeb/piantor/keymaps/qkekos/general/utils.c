
#include "../__init__.h"

bool is_shift_held_core(int mods) { return mods & MOD_BIT(KC_LSFT); }
bool is_ctrl_held_core(int mods)  { return mods & MOD_BIT(KC_LCTL); }
bool is_gui_held_core(int mods)   { return mods & MOD_BIT(KC_LGUI); }
bool is_alt_held_core(int mods)   { return mods & MOD_BIT(KC_LALT); }

bool is_shift_held(void) { return is_shift_held_core(get_mods()); }
bool is_ctrl_held(void)  { return is_ctrl_held_core(get_mods());  }
bool is_gui_held(void)   { return is_gui_held_core(get_mods());   }
bool is_alt_held(void)   { return is_alt_held_core(get_mods());   }

bool is_os_shift_held(void) { return is_shift_held_core(get_oneshot_mods()); }
bool is_os_ctrl_held(void)  { return is_ctrl_held_core(get_oneshot_mods());  }
bool is_os_gui_held(void)   { return is_gui_held_core(get_oneshot_mods());   }
bool is_os_alt_held(void)   { return is_alt_held_core(get_oneshot_mods());   }

bool is_alpha_layer_on(void) {
    return (get_highest_layer(layer_state) <= QWERTY);
}

uint16_t normalize_keycode(uint16_t keycode) {
    if (IS_QK_MOD_TAP(keycode))   return QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    if (IS_QK_LAYER_TAP(keycode)) return QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);

    return keycode;
}
