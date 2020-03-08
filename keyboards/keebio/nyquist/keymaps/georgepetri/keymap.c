#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _BASE 0
#define _L 1
#define _R 2

enum custom_keycodes { QWERTY = SAFE_RANGE };

#define KC_TL LCTL(KC_PGUP)
#define KC_TR LCTL(KC_PGDN)
#define KC_TC LCTL(KC_W)
#define KC_TRO LCTL(LSFT(KC_T))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL ,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT ,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    KC_CAPS, KC_LCTL, KC_LGUI, KC_LALT, MO(_L) , KC_SPC ,   KC_SPC , TG(_R) , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  
//└────────┴────────┴────────┴────────┴────────┴────────┘ └────────┴────────┴────────┴────────┴────────┴────────┘
  ),
  
  [_L] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┐
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, KC_F11 , KC_F12 , _______, _______, _______,   _______, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, _______, _______, _______,   _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END , _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______
//└────────┴────────┴────────┴────────┴────────┴────────┘ └────────┴────────┴────────┴────────┴────────┴────────┘
  ),
  
  [_R] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┐
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, KC_TL  , KC_TR  , KC_TC  , KC_TRO , _______,   _______, KC_TL  , KC_TR  , KC_TC  , KC_TRO , _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END , _______,   _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END , _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤ ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______
//└────────┴────────┴────────┴────────┴────────┴────────┘ └────────┴────────┴────────┴────────┴────────┴────────┘
  )
};

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_BLUE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSFT:
            if (record->event.pressed) {
                rgblight_sethsv_range(HSV_WHITE, 0, 3);
            } else {
                rgblight_sethsv_range(HSV_BLUE, 0, 3);
            }
            return true;
        default:
            return true;
    }
}

void update_led(void) {
    switch (biton32(layer_state)) {
        case _BASE:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _L:
            rgblight_sethsv_noeeprom(HSV_CORAL);
            break;
        case _R:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
    }
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgblight_sethsv_range(HSV_WHITE, 0, 3);
        rgblight_sethsv_range(HSV_WHITE, 9, 12);
    }
    //rgblight_sethsv_range(HSV_RED, 0, 6); //YES
    //rgblight_sethsv_range(HSV_ORANGE, 6, 12); //YES

    //rgblight_sethsv_range(HSV_CORAL, 0, 6);  //NO
    //rgblight_sethsv_range(HSV_GOLDENROD, 6, 12); //NO
    
    //rgblight_sethsv_range(HSV_GOLD, 0, 6); //YES
    //rgblight_sethsv_range(HSV_YELLOW, 6, 12); //NO
    
    //rgblight_sethsv_range(HSV_CHARTREUSE, 0, 6); //NO
    //rgblight_sethsv_range(HSV_GREEN, 6, 12); //YES
    
    //rgblight_sethsv_range(HSV_SPRINGGREEN, 0, 6); //YES //YES
    //rgblight_sethsv_range(HSV_TURQUOISE, 6, 12); //NO
    
    //rgblight_sethsv_range(HSV_TEAL, 0, 6); //NO
    //rgblight_sethsv_range(HSV_CYAN, 6, 12); //NO
    
    //rgblight_sethsv_range(HSV_AZURE, 0, 6); //NO
    //rgblight_sethsv_range(HSV_BLUE, 6, 12); //NO
    
    //rgblight_sethsv_range(HSV_PURPLE, 0, 6); //NO
    //rgblight_sethsv_range(HSV_MAGENTA, 6, 12); //NO
    
    rgblight_setrgb_range(RGB_PINK, 0, 6); //NO
}

uint32_t layer_state_set_user(uint32_t state) {
    update_led();
    return state;
}

void led_set_user(uint8_t usb_led) {
    update_led();
}
