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


// Debug
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

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

#ifdef SHIFT_ENABLE
bool lshift = false;
bool rshift = false;
bool lctrl = false;
bool rctrl = false;
bool lalt = false;
bool ralt = false;
bool lgui = false;
bool rgui = false;
#endif

// Tap dance configuration

// Mouse
#ifdef MOUSEKEY_ENABLE
#ifdef TAP_DANCE_ENABLE

// Define a type containing the tapdance states to be tested
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Global instacne of the tapdacne state type
static td_state_t td_state;

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if(state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN;
}

void cps_ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            if (caps_lock) {
                register_code16(KC_CAPS);
            }
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            register_code16(KC_CAPS);
            break;
        default:
            break;
    }
}

void cps_ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state)  {
        case TD_SINGLE_TAP:
            if (caps_lock) {
                unregister_code16(KC_CAPS);
            }
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_CAPS);
            break;
        default:
            break;
    }
}

// Tap Dance definition
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once or Shift, twice for mouse layer
    [TD_LSHIFT_MOUSE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LSFT, _EX_MOUSE),
    [TD_ADJ_M_NUM] = ACTION_TAP_DANCE_LAYER_TOGGLE(ADJ_M, _NUM),
    [TD_ADJ_L_NUM] = ACTION_TAP_DANCE_LAYER_TOGGLE(ADJ_L, _NUM),
    [TD_ADJ_W_NUM] = ACTION_TAP_DANCE_LAYER_TOGGLE(ADJ_W, _NUM),
//    [TD_CTRL_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS),
    [TD_CTRL_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cps_ctl_finished, cps_ctl_reset),
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
    switch(cur_layer) {
        case _DEF_L:
            if (caps_lock) {
                set_caps_rgb();
            } else {
                reset_rgb();
            }
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

    // Board specific handling
    rgb_matrix_indicators_keymap();
}
#endif

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case S_SHIFT:
        case A_SHIFT:
        case R_SHIFT:
        case S_MOUSE:
        case SFT_MSE:
        case SPC_LWR:
        case SPC_RSE:
        case SLS_SFT:
        case A_MOUSE:
        case M_NAV_1:
        case L_NAV_1:
        case W_NAV_1:
        case M_F_NAV:
        case L_F_NAV:
        case W_F_NAV:
#ifdef DYNAMIC_TAPPING_TERM_ENABLE
            return g_tapping_term;
#else
            return TAPPING_TERM;
#endif
        case CPS_CTL:
        case TAB_CTL:
#ifdef DYNAMIC_TAPPING_TERM_ENABLE
            return g_tapping_term * 0.75;
#else
            return TAPPING_TERM * 0.75;
#endif
        default:
#ifdef DYNAMIC_TAPPING_TERM_ENABLE
            return g_tapping_term / 2;
#else
            return TAPPING_TERM / 2;
#endif
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case TAB_CTL:
        // case CPS_CTL:
        case ADM_BSL:
        case ADL_BSL:
        case ADW_BSL:
        case END_F_M:
        case END_F_L:
        case END_F_W:
        case PGDN_FM:
        case PGDN_FL:
        case PGDN_FW:
        // case SPC_LWR:
        // case SPC_RSE:
        // case M_NAV_1:
        // case L_NAV_1:
        // case W_NAV_1:
        // case M_F_NAV:
        // case L_F_NAV:
        // case W_F_NAV:
        case R_SHIFT:
            // Immediately select the hold action when another key is tapped.
            // return true;
            return true;
        default:
            // Do not select the hold action for other keys
            return false;
    }
}
#endif

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TAB_CTL:
        case QUT_SFT:
        case CPS_CTL:
        case SFT_MSE:
            // Immediately select the hold action when another key is pressed
            // return true;
            return true;
        default:
            // Do not select the hold action when another key is pressed
            return false;
    }
}
#endif

#ifdef IGNORE_MOD_TAP_INTERRUPT_PER_KEY
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Do not force the mod-tap key press to be handled as a modifier
        // if any other key was pressed while the mod-tap key is held down.
        // return true;
        default:
            // Force the mod-tap key press to e handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return false;
    }
}
#endif

#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* case A_MOUSE:
        case M_NAV_1:
        case L_NAV_1:
        case W_NAV_1:
        case M_F_NAV:
        case L_F_NAV:
        case W_F_NAV:
            return true; */
        default:
            return false;
    }
}
#endif

#ifdef RETRO_TAPPING_PER_KEY
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}
#endif

// Handling of layer color
layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (caps_lock) {
        set_caps_rgb();
    } else if (mouse_layer) {
        set_mse_rgb();
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
            mouse_layer = false;
            set_nav_1_rgb();
            break;
        case _MAC_NAV_2:
        case _LINUX_NAV_2:
        case _WIN_NAV_2:
            cur_layer = _NAV2_L;
            def_layer = false;
            mouse_layer = false;
            set_nav_2_rgb();
            break;
        case _ADJUST_MAC:
        case _ADJUST_WIN:
        case _ADJUST_LINUX:
            cur_layer = _ADJ_L;
            def_layer = false;
            mouse_layer = false;
            set_adj_rgb();
            break;
        case _MOUSE:
        case _EX_MOUSE:
            cur_layer = _MSE_L;
            def_layer = false;
            mouse_layer = true;
            set_mse_rgb();
            break;
        default:
            cur_layer = _DEF_L;
            def_layer = true;
            mouse_layer = false;
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
#ifdef SHIFT_ENABLE
        /* Monitor shift state */
        case SFT_MSE:
        case KC_LSFT:
            if (record->event.pressed) {
                lshift = true;
            } else {
                lshift = false;
            }

            break;
        case QUT_SFT:
        case R_SHIFT:
        case KC_RSFT:
            if (record->event.pressed) {
                rshift = true;
            } else {
                rshift = false;
            }
            break;
        case TAB_CTL:
        case CPS_CTL:
        case KC_LCTL:
            if (record->event.pressed) {
                lctrl = true;
            } else {
                lctrl = false;
            }
            break;
        case KC_RCTL:
            if (record->event.pressed) {
                rctrl = true;
            } else {
                rctrl = false;
            }
            break;
        case KC_LALT:
            if (record->event.pressed) {
                lalt = true;
            } else {
                lalt = false;
            }
            break;
        case KC_RALT:
            if (record->event.pressed) {
                ralt = true;
            } else {
                ralt = false;
            }
            break;
        case KC_LGUI:
            if (record->event.pressed) {
                lgui = true;
            } else {
                lgui = false;
            }
            break;
        case KC_RGUI:
            if (record->event.pressed) {
                rgui = true;
            } else {
                rgui = false;
            }
            break;
        case CU_BSPC:
            // SHIFT_NO(KC_BSPC, KC_DEL)
            CTRL_NO(KC_BSPC, KC_DEL)
#endif
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

