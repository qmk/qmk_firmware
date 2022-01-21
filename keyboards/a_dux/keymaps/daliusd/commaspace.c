#include "commaspace.h"

void swap_layout(void) {
    uint8_t saved_mods = get_mods();
    clear_mods();
    tap_code16(LCTL(KC_SPC));
    set_mods(saved_mods);
}

void press_with_layout_swap(uint16_t keycode) {
    tap_code16(KC_BSPC);
    swap_layout();
    tap_code16(keycode);
    swap_layout();
}

bool comma_pressed = false;

bool update_commaspace(
    uint16_t keycode,
    bool pressed
) {
    if (keycode == KC_COMM) {
        if (!(get_mods() & MOD_MASK_SHIFT)) {
            comma_pressed = true;
        }
    } else if (comma_pressed) {
        if (keycode != KC_LSFT) {
            comma_pressed = false;
        }

        switch(keycode) {
            case KC_Q:
                if (pressed) {
                    press_with_layout_swap(KC_1);
                    return false;
                }
                break;
            case KC_W:
                if (pressed) {
                    press_with_layout_swap(KC_2);
                    return false;
                }
                break;
            case KC_E:
                if (pressed) {
                    press_with_layout_swap(KC_3);
                    return false;
                }
                break;
            case KC_R:
                if (pressed) {
                    press_with_layout_swap(KC_4);
                    return false;
                }
                break;
            case KC_T:
                if (pressed) {
                    press_with_layout_swap(KC_5);
                    return false;
                }
                break;
            case KC_Y:
                if (pressed) {
                    press_with_layout_swap(KC_6);
                    return false;
                }
                break;
            case KC_U:
                if (pressed) {
                    press_with_layout_swap(KC_7);
                    return false;
                }
                break;
            case KC_I:
                if (pressed) {
                    press_with_layout_swap(KC_8);
                    return false;
                }
                break;
            case KC_O:
                if (pressed) {
                    press_with_layout_swap(KC_EQL);
                    return false;
                }
                break;
        }
    }

    return true;
};
