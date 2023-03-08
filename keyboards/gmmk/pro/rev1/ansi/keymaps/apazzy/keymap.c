#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

#define KC_TASK LCTL(LSFT(KC_ESC))

enum layers{
    WIN_BASE,
    WIN_FN,
};

enum apazzy_keycodes {
  KC_WINLCK = SAFE_RANGE,
  KC_MJST,
  KC_MJCX,
  EMO_SHRUG,
  KC_RST2 // Custom RESET/QK_BOOT code, for some reason this isn't working directly on a layer
};

bool mouse_jiggle_mode = false; // Mouse Jiggle variable

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MJCX,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        MO(WIN_FN),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(WIN_FN),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [WIN_FN] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MJST,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_UP,   KC_PGDN, KC_PSCR, _______, _______, KC_RST2,          _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, KC_END,  NK_TOGG, _______, _______, _______,          _______, _______, KC_HOME,
        _______,KC_WINLCK,_______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};

#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
    };
#endif

void matrix_scan_user(void) {
    if (mouse_jiggle_mode) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
        tap_code(KC_MS_LEFT);
        tap_code(KC_MS_RIGHT);
        tap_code(KC_MS_WH_UP);
        tap_code(KC_MS_WH_DOWN);
    } else {
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_RST2:
            if (record->event.pressed) {
                reset_keyboard();
            }
            return false;
		// GUI lock toggle
        case KC_WINLCK:
            if (record->event.pressed) {
                keymap_config.no_gui = !keymap_config.no_gui; //toggle status
            }
            return false;
        // Mouse jiggle toggle
        case KC_MJST:
            if (record->event.pressed) {
                mouse_jiggle_mode = !mouse_jiggle_mode;
            }
            return false;
        case KC_MJCX:
            if (record->event.pressed) {
                mouse_jiggle_mode = false;
            }
            return false;
        case KC_ESC:
            if (record->event.pressed) {
                if (mouse_jiggle_mode) {
                    mouse_jiggle_mode = false;
                    return false;
                }
                return true;
            }
            return true;
        case EMO_SHRUG:
            if (record->event.pressed) {
                SEND_STRING("¯\\_(ツ)_/¯");
            }
            return false;
		// process all other keycodes normally
        default:
            return true;
    }
}

#ifdef RGB_MATRIX_ENABLE
    // Capslock, Scroll lock and Numlock  indicator on Left side lights.
    bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        led_t led_state = host_keyboard_led_state();
        if (layer_state_is(WIN_BASE)) {
            rgb_matrix_set_color_all(RGB_BLACK);
        }
        if (layer_state_is(WIN_FN)) {
            rgb_matrix_set_color_all(RGB_BLACK);
            for (uint8_t i=0; i<sizeof(LED_SIDE_LEFT)/sizeof(LED_SIDE_LEFT[0]); i++) {
                rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_MAGENTA);
            }
            for (uint8_t i=0; i<sizeof(LED_SIDE_RIGHT)/sizeof(LED_SIDE_RIGHT[0]); i++) {
                rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_MAGENTA);
            }
            for (uint8_t i=0; i<sizeof(LED_LIST_FNARROWS)/sizeof(LED_LIST_FNARROWS[0]); i++) {
                rgb_matrix_set_color(LED_LIST_FNARROWS[i], RGB_RED);
            }
            for (uint8_t i=0; i<sizeof(LED_LIST_FNOTHER)/sizeof(LED_LIST_FNOTHER[0]); i++) {
                rgb_matrix_set_color(LED_LIST_FNOTHER[i], RGB_MAGENTA);
            }
            rgb_matrix_set_color(LED_FN, RGB_MAGENTA);
            rgb_matrix_set_color(LED_CAPS, RGB_MAGENTA);
        }
        if (led_state.scroll_lock) {
            rgb_matrix_set_color(LED_L1, RGB_GREEN);
            rgb_matrix_set_color(LED_L2, RGB_GREEN);
        }
        if (!led_state.num_lock) {   // on if NUM lock is OFF
            rgb_matrix_set_color(LED_L3, RGB_RED);
            rgb_matrix_set_color(LED_L4, RGB_RED);
        }
        if (led_state.caps_lock) {
            rgb_matrix_set_color(LED_CAPS, RGB_RED);
            rgb_matrix_set_color(LED_L5, RGB_RED);
            rgb_matrix_set_color(LED_L6, RGB_RED);
            rgb_matrix_set_color(LED_L7, RGB_RED);
            rgb_matrix_set_color(LED_L8, RGB_RED);
        }
        if (keymap_config.no_gui) {
            rgb_matrix_set_color(LED_LWIN, RGB_RED);  //light up Win key when disabled
        }
        if (mouse_jiggle_mode) {
            rgb_matrix_set_color_all(RGB_RED);
        }
        return false;
    }

    void suspend_power_down_user(void) {
        rgb_matrix_set_suspend_state(true);
    }

    void suspend_wakeup_init_user(void) {
        rgb_matrix_set_suspend_state(false);
    }
#endif

void activate_numlock(bool turn_on) {
    if (host_keyboard_led_state().num_lock != turn_on) {
        tap_code(KC_NUM_LOCK);
    }
}

void keyboard_post_init_user(void) {
    activate_numlock(true);
}