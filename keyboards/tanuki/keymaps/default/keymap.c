#include QMK_KEYBOARD_H

// custom type to store stuff in EEPROM
typedef union {
    uint32_t raw;
    struct {
        bool layer_rgb :1;
    };
} user_config_t;

user_config_t user_config;

// Layer definitions
#define _BL 0
#define _DL 1
#define _UL 2
#define _GL 3
#define _BK 4

// Custom keycode to toggle normal RGB or per-layer RGB
enum custom_keycodes {
    CUSTRGB = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BL] = LAYOUT(
    KC_ESC,   KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,     KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,   KC_A,     KC_S,     KC_D,    KC_F,    KC_G,     KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN, TG(_GL),
    KC_LSFT,  KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,     KC_N,       KC_M,    KC_QUOT, KC_SLSH, KC_ENT,
    KC_LCTL,  KC_LALT,  KC_COMMA, LT(_DL,KC_SPC), LT(_UL,KC_SPC),         KC_DOT,  KC_LGUI),

[_DL] = LAYOUT(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,  KC_F12,
    KC_TRNS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_TRNS,
    KC_TRNS,  KC_PSCR,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  QK_BOOT,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS),

[_UL] = LAYOUT(
    KC_GRV,   KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_BSLS,  KC_PLUS,  KC_UNDS,  KC_MINS,  KC_EQL,  KC_DEL,
    KC_TRNS,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN, KC_TRNS,
    KC_TRNS,  CUSTRGB,  RGB_TOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_SAD,  RGB_VAD,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  RGB_MOD,  RGB_HUI,  KC_TRNS,  KC_TRNS,            RGB_SAI,  RGB_VAI),

[_GL] = LAYOUT(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_SPC,   KC_SPC,             KC_TRNS,  KC_TRNS)
  
};

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    if(user_config.layer_rgb) {
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(1);
        rgblight_sethsv_noeeprom(0,10,255);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // This code switches underglow color by active layer, if the user has enabled the feature
    if(user_config.layer_rgb) {
        switch (get_highest_layer(state)) {
            case _BL:
                rgblight_sethsv_noeeprom(0,10,255);
                rgblight_mode_noeeprom(1);
                break;
            case _DL:
                rgblight_sethsv_noeeprom(130,200,255);
                rgblight_mode_noeeprom(1);
                break;
            case _UL:
                rgblight_sethsv_noeeprom(170,200,255);
                rgblight_mode_noeeprom(1);
                break;
            case _GL:
                rgblight_sethsv_noeeprom(0,180,255);
                rgblight_mode_noeeprom(1);
                break;
        }
    }
    return state;
}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CUSTRGB: // if the user toggled per-layer RGB, update the config and refresh the RGB color
            if(record->event.pressed) {
                user_config.layer_rgb ^= 1;
                eeconfig_update_user(user_config.raw);
                if (user_config.layer_rgb) {
                    layer_state_set(layer_state);
                }
            }
            return false;
            break;
        case RGB_MOD:
        case RGB_SAD:
        case RGB_SAI:
        case RGB_HUI:
        case RGB_VAD:
        case RGB_VAI:
            if(user_config.layer_rgb && record->event.pressed) {
                return false; // if layer RGB is on, ignore attempts to change RGB settings
            }
            break;
    }
    return true;
}

void eeconfig_init_user(void) { // in case EEPROM is reset, set up our custom config
    user_config.raw = 0;
    user_config.layer_rgb = true; // enable per-layer RGB by default
    eeconfig_update_user(user_config.raw);
    rgblight_enable();
    rgblight_sethsv(0,10,255);
    rgblight_mode(1);
}
