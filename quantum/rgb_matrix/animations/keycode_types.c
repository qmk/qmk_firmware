#include "keycode_types.h"

bool is_arrow_keycode(uint16_t keycode) {
    return (KC_RGHT <= keycode && keycode <= KC_UP);
}

bool is_modifier_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_LCTL ... KC_RGUI:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return true;
        default:
            return false;
    }
}

bool is_media_keycode(uint8_t keycode) {
    switch (keycode) {
        case KC_MUTE ... KC_MPLY:
            return true;
        default:
            return false;
    }
}

bool is_base_character_keycode(uint8_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINUS ... KC_SLSH:
        case KC_KP_SLASH ... KC_KP_PLUS:
        case KC_KP_1 ... KC_NONUS_BACKSLASH:
            return true;
        default:
            return false;
    }
}

bool is_character_keycode(uint16_t keycode) {
    if (IS_QK_BASIC(keycode)) return is_base_character_keycode(keycode);
    if (!IS_QK_MODS(keycode)) return false;
    if (HAS_CTRL_OR_GUI_MOD(keycode)) return false;
    if (HAS_ALT_MOD(keycode) && !HAS_RIGHT_ALT_MOD(keycode)) return false;
    return is_base_character_keycode(keycode & 0xff);
}
