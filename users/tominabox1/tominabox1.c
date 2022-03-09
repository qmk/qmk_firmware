#include "tominabox1.h"

#ifdef KEYBOARD_lazydesigners_dimple
#ifdef RGBLIGHT_ENABLE
__attribute__ ((weak))
void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) { // sets the backlighting to come on upon successful load then turn off
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(RGB_RED);
  rgblight_mode_noeeprom(0);
  wait_ms(700);
  rgblight_disable_noeeprom();
}
#endif // RGBLIGHT
#endif // Dimple


#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type);
static bool is_suspended;
static bool rgb_matrix_enabled;

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
    if (!is_suspended) {
        is_suspended = true;
        rgb_matrix_enabled = (bool)rgb_matrix_config.enable;
        rgb_matrix_disable_noeeprom();
    }
}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
    is_suspended = false;
    if (rgb_matrix_enabled) {
        rgb_matrix_enable_noeeprom();
    }
}

#    include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(g_rgb_counters.tick, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}
#endif //RGB_MATRIX_ENABLE

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(S(KC_2));
    } else {
        SEND_STRING("tom.campie@gmail.com");
    }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(S(KC_2));
    } else {
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [KC_EMAIL] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset),
    [TD_SFT_CPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef KEYBOARD_crkbd_rev1

#endif // CRKBD

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_CAPS):
            return 250;
        case KC_ENT_LOW:
            return 150;
        case KC_SPC_RSE:
            return(250);
        case LCTL_T(KC_TAB):
            return 300;
        default:
            return TAPPING_TERM;
    }
};

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (biton32(state)) {
        case _LOWER:
            break;
        case _RAISE:
            break;
        case _ADJUST:
            break;
        default:
            break;
    }
    return state;
}

#ifdef KEYBOARD_crkbd_rev1

__attribute__((weak))
void matrix_scan_keymap(void) {}

extern bool oled_initialized;
void matrix_scan_user(void) {
  if(!oled_initialized) {
    wait_ms(200);
    oled_init(0);
    return;
  }
  matrix_scan_keymap();
  }

extern uint8_t is_master;
#endif // CRKBD

uint16_t        oled_timer;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
      uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif

    if (record->event.pressed) {
      #ifdef OLED_ENABLE
        oled_timer = timer_read();
        oled_on();
        #endif // OLED_ENABLE
    switch (keycode) {
            case KC_BBB:
                if (record->event.pressed) {
                    SEND_STRING(":b:");
                } else {}
                break;
            case KC_BEPIS:
                if (record->event.pressed) {
                    SEND_STRING("BEPIS");
                } else {}
                break;
        }
    }
    return true;

}
#ifdef KEYBOARD_crkbd_rev1
#ifdef OLED_ENABLE
void render_logo(void) {
    static const char PROGMEM logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(logo, false);
}

void render_status_main(void) {
    // Host Keyboard USB Status
    oled_write_P(PSTR("USB: "), false);
    switch (USB_DeviceState) {
        case DEVICE_STATE_Unattached:
            oled_write_P(PSTR("Unattached\n"), false);
            break;
        case DEVICE_STATE_Suspended:
             oled_write_P(PSTR("Suspended\n"), false);
            break;
        case DEVICE_STATE_Configured:
             oled_write_P(PSTR("Connected\n"), false);
            break;
        case DEVICE_STATE_Powered:
             oled_write_P(PSTR("Powered\n"), false);
            break;
        case DEVICE_STATE_Default:
             oled_write_P(PSTR("Default\n"), false);
            break;
        case DEVICE_STATE_Addressed:
             oled_write_P(PSTR("Addressed\n"), false);
            break;
        default:
             oled_write_P(PSTR("Invalid\n"), false);
        }

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (biton32(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case _ARROW:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _FKEY:
            oled_write_P(PSTR("Function\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status

    oled_write_ln_P(IS_HOST_LED_ON(USB_LED_CAPS_LOCK) ? PSTR("Caps Lock\n") : PSTR("         \n"), false);
}
__attribute__ ((weak))
void oled_task_keymap(void) {}

bool oled_task_user(void) {

    if (timer_elapsed(oled_timer) > 20000) {
        oled_off();
        return;
    }
        if (is_master) {
            render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        } else {
            render_logo();
            oled_scroll_left();
        }
        oled_task_keymap();
        return false;
    }

#endif // OLED_Driver
#endif // crkbd
