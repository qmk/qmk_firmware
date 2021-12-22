#include "chrisgve.h"

/*****************************************
 *
 *   Placeholder functions implementable in the respective keymaps
 *
 *****************************************/

__attribute__ ((weak))
    bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
        return true;
    }

__attribute__ ((weak))
    void keyboard_post_init_keymap(void) {
    }

__attribute__ ((weak))
    layer_state_t default_layer_state_set_keymap(layer_state_t state) {
        return state;
    }

__attribute__ ((weak))
    void led_set_keymap(uint8_t usb_led) { }

__attribute__ ((weak))
    layer_state_t layer_state_set_keymap(layer_state_t state) {
        return state;
    }

#ifdef RGB_MATRIX_ENABLE
__attribute__ ((weak))
    void rgb_matrix_indicators_keymap(void) { }
#endif

/*****************************************
 *
 *   Common code
 *
 *****************************************/

// EEPROM user configuration

typedef union {
    uint8_t raw; // 8 bit configuration
    struct {
        bool apple_mode :1;
    };
} user_config_t;

user_config_t user_config;

// Global variables

enum generic_layer_t {
    _DEF_L,
    _NAV1_L,
    _NAV2_L,
    _ADJ_L,
    _NUM_L,
    _MSE_L, 
};

bool apple_mode = false;
bool caps_lock = false;
bool def_layer = true;
uint8_t cur_layer = _DEF_L;
bool apple_fn_pressed = false;
bool mouse_layer = false;

// Tap dance configuration

// Mouse
#ifdef MOUSEKEY_ENABLE
#ifdef TAP_DANCE_ENABLE

// Tap Dance definition
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once or Shift, twice for mouse layer
    [TD_LSHIFT_MOUSE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LSFT, _MOUSE),
    [TD_CTRL_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS),
};

#endif
#endif


// RGB Handling

void reset_rgb(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_disable_noeeprom();
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_disable_noeeprom();
#endif
}

void set_rgb(uint8_t red, uint8_t green, uint8_t blue) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(red, green, blue);
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(red, green, blue);
#endif
}

void set_nav_1_rgb(void) {
    set_rgb(RGB_NAV1_R, RGB_NAV1_G, RGB_NAV1_B);
}

void set_nav_2_rgb(void) {
    set_rgb(RGB_NAV2_R, RGB_NAV2_G, RGB_NAV2_B);
}

void set_caps_rgb(void) {
    set_rgb(RGB_CAPS_R, RGB_CAPS_G, RGB_CAPS_B); // Warm white
}

void set_adj_rgb(void) {
    set_rgb(RGB_ADJ_R, RGB_ADJ_G, RGB_ADJ_B);
}

void set_mse_rgb(void) {
    set_rgb(RGB_MSE_R, RGB_MSE_G, RGB_MSE_B);
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    if (caps_lock) {
        set_caps_rgb();
    } else {
        switch(cur_layer) {
            case _DEF_L:
                reset_rgb();
                break;
            case _NAV1_L:
                set_nav_1_rgb();
                break;
            case _NAV2_L:
                set_nav_2_rgb();
                break;
            case _ADJ_L:
                set_adj_rgb();
                break;
            case _MSE_L:
                set_mse_rgb();
                break;
            default:
                break;
        }
    }

    // Board specific handling
    rgb_matrix_indicators_keymap();
}
#endif

// Handling of layer color
layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (caps_lock) {
        set_caps_rgb();
    } else {
        reset_rgb();
    }
    
    // Board specific handling
    return default_layer_state_set_keymap(state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case _MAC_NAV_1:
        case _LINUX_NAV_1:
        case _WIN_NAV_1:
            cur_layer = _NAV1_L;
            def_layer = false;
            set_nav_1_rgb();
            break;
        case _MAC_NAV_2:
        case _LINUX_NAV_2:
        case _WIN_NAV_2:
            cur_layer = _NAV2_L;
            def_layer = false;
            set_nav_2_rgb();
            break;
        case _ADJUST_MAC:
        case _ADJUST_WIN:
        case _ADJUST_LINUX:
            cur_layer = _ADJ_L;
            def_layer = false;
            set_adj_rgb();
            break;
        case _MOUSE:
            cur_layer = _MSE_L;
            def_layer = false;
            set_adj_rgb();
        default:
            cur_layer = _DEF_L;
            def_layer = true;
            if (caps_lock) {
                set_caps_rgb();
            } else {
                reset_rgb();
            }
    }

    // Board specific handling
    return layer_state_set_keymap(state);
}

// Handling of CAPS LOCK
void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        set_caps_rgb();
        caps_lock = true;
    } else {
        if (def_layer) {
            reset_rgb();
        }
        caps_lock = false;
    }
}


// Keyboard post init
void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    apple_mode = user_config.apple_mode;

    // Init RGB
    reset_rgb();

    // Call specific board initialization
    keyboard_post_init_keymap();
}

// Key handling 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* Set the default persistent layer */
        case DF_M_P:
            if (!record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY_MAC);
                return false;
            }
            break;
        case DF_L_P:
            if (!record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY_LINUX);
                return false;
            }
            break;
        case DF_W_P:
            if (!record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY_WIN);
                return false;
            }
            break;
#ifdef APPLE_FN_ENABLE
        /* Detect if KC_APPLE_FN is pressed */
        case INV_AFN:
            apple_fn_pressed = record->event.pressed;
            break;
        /* Set the default Fn-behavior */
        case WIN_SWT:
            if (!record->event.pressed) {
                if (apple_mode) {
                    apple_mode = false;
                    user_config.apple_mode = apple_mode;
                    eeconfig_update_user(user_config.raw); 
                }
                return false;
            }
            break;
        case MAC_SWT:
            if (!record->event.pressed) {
                if (!apple_mode) {
                    apple_mode = true;
                    user_config.apple_mode = apple_mode;
                    eeconfig_update_user(user_config.raw);
                }
                return false;
            }
            break;
        /* Inject generic function keys */
        case KC_WF1:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F1);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F1);
                }
                // return false;
            }
            break;
        case KC_WF2:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F2);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F2);
                }
                // return false;
            }
            break;
        case KC_WF3:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F3);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F3);
                }
                // return false;
            }
            break;
        case KC_WF4:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F4);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F4);
                }
                // return false;
            }
            break;
        case KC_WF5:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F5);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F5);
                }
                // return false;
            }
            break;
        case KC_WF6:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F6);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F6);
                }
                // return false;
            }
            break;
        case KC_WF7:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F7);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F7);
                }
                // return false;
            }
            break;
        case KC_WF8:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F8);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F8);
                }
                // return false;
            }
            break;
        case KC_WF9:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F9);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F9);
                }
                // return false;
            }
            break;
        case KC_WF10:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F10);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F10);
                }
                // return false;
            }
            break;
        case KC_WF11:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F11);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F11);
                }
                // return false;
            }
            break;
        case KC_WF12:
            if (!record->event.pressed) {
                if (apple_mode && !apple_fn_pressed) {
                    register_code(KC_APPLE_FN);
                    add_key(KC_F12);
                    unregister_code(KC_APPLE_FN);
                } else {
                    tap_code(KC_F12);
                }
                // return false;
            }
            break;
#endif
#ifdef MACROS_ENABLED
        /* Standard macros */
#endif
        default:
            break;
    }

    // Board specific handling
    return process_record_keymap(keycode, record);
}

