#include QMK_KEYBOARD_H

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(_______, _______)  }
};
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    KC_MUTE,
    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_DELETE,
    KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,     KC_PAGE_UP,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,                KC_UP,      KC_PAGE_DOWN,
    KC_LCTL,    KC_LGUI,    KC_LALT,                            KC_SPC,                             MO(1),      KC_RCTL,                            KC_LEFT,    KC_DOWN,    KC_RIGHT    
    ),
    [1] = LAYOUT(
    KC_GRV,     KC_BRID,    KC_BRIU,    _______,    KC_MYCM,    KC_MAIL,    KC_WHOM,    KC_MPRV,    KC_MPLY,    KC_MNXT,    _______,    KC_VOLD,    KC_VOLU,    _______,    _______,
    _______,    KC_BLE1,    KC_BLE2,    KC_BLE3,    KC_24G,     _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RGB_MOD,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                RGB_HUI,    _______, 
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                RGB_VAI,    _______,
    _______,    _______,     _______,                           _______,                           _______,    _______,                            RGB_SPD,    RGB_VAD,    RGB_SPI 
    )
};
                        

