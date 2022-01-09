#include QMK_KEYBOARD_H

enum alt_keycodes {
    SWITCH_USB = SAFE_RANGE,
};

#ifdef RGB_MATRIX_ENABLE
    //static uint32_t idle_timer;
    //static bool led_on = true;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
        SWITCH_USB, _______, _______, _______, _______, _______, _______, _______,_______,_______, _______, _______, _______, _______, _______, \
        RESET, _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PGUP, _______, \
        _______, _______, _______,                            _______,                            KC_RCTL, _______, _______, KC_PGDN, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

/*
void switch_usb(void) {
    if (usb_host_port == USB_HOST_PORT_2) {USB_set_host_by_port_num(1); }
    else {USB_set_host_by_port_num(2); }
}
*/

void matrix_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        rgblight_sethsv(COLOR);
    #endif
}

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        #ifdef RGB_MATRIX_ENABLE
            if (!led_on) {
                rgblight_enable_noeeprom();
                led_on = true;
            }
        idle_timer = timer_read();
        #endif
    }
    switch (keycode) {
        case SWITCH_USB:
            switch_usb();
            return false;
        default:
            return true; //Process all other keycodes normally
  }
}

void matrix_scan_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        if ( led_on && timer_elapsed(idle_timer) > BACKLIGHT_TIMEOUT * 60000) {
            rgblight_disable_noeeprom();
            led_on = false;
        }
    #endif
}

*/
