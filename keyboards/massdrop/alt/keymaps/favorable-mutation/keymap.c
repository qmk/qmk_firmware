#include QMK_KEYBOARD_H

enum alt_keycodes {
    HK_COSL = SAFE_RANGE,  //Clear held-down keys
};

#define TG_NKRO  MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode
#define CTL_ESC  LCTL_T(KC_ESC)
#define TP_LSFT  OSM(MOD_LSFT)
#define TP_RSFT  OSM(MOD_RSFT)
#define TP_LALT  OSM(MOD_LALT)
#define TP_RALT  OSM(MOD_RALT)
#define KC_YBAI  LCTL(KC_SPC)
#define GUI_SPC  LGUI_T(KC_SPC)
#define KC_SPOT  LGUI(KC_SPC)

//TODO default layer vim-like binds that work with WM, i to type??? this leads
//to layers of vim modes - what's the best way to deal with that?
//also need to deal with shift not working for other mods, add to shift layer
//most likely
//
//TODO tap/toggle for layers

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_SPOT,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_MUTE,
        TP_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_VOLU, KC_MPLY,
        TP_LALT, TG(2),   KC_YBAI,                            GUI_SPC,                            TP_RALT, TG(1),   KC_MRWD, KC_VOLD, KC_MFFD
    ),
    [1] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_HOME,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, KC_MRWD, KC_MFFD, _______, _______, _______,          _______, KC_PGUP,
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, TG_NKRO, DBG_TOG, _______, _______, _______, _______,          KC_UP,   KC_PGDN,
        _______, _______, _______,                            HK_COSL,                            _______, TG(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HK_COSL:
            clear_keyboard();
            reset_oneshot_layer();
            return true;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}
