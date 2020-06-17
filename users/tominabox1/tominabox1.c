#include "tominabox1.h"
#include "meme_modes.c"
#include "combos.c"
#include "tap_dancing.c"

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

layer_state_t layer_state_set_user (layer_state_t state) {
  return layer_state_set_keymap (state);
}

// __attribute__ ((weak))
// void led_update_kb (led_t led_state) {
//   return led_state;
// }
// bool led_update_user(led_t led_state){
//   return led_update_kb (led_state);

// __attribute__((weak)) void keyboard_pre_init_keymap(void) {}
//
// void keyboard_pre_init_user(void) {
// 	keyboard_pre_init_keymap();
// }
//
// __attribute__((weak)) void keyboard_post_init_keymap(void) {}
//
// void keyboard_post_init_user(void) {
// 	keyboard_post_init_keymap();
// }
