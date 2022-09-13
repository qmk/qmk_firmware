#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _FUNC,
    _NUM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        
    /* Keymap (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |ENu|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   BS  |Del |
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  {|  }| Ent |PgUp|
     * |------------------------------------------------------.    |----|
     * |CapsFn|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  #|    |PgDn|
     * |----------------------------------------------------------------|
     * |Shift| \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |Fn  |
     * |----------------------------------------------------------------|
     * |Ctrl|Win |Alt |          Space        |Alt |Ctrl|  |Lef|Dow|Rig |
     * `------------------------------------------------'  `------------'
     */
    [_QWERTY] = LAYOUT_all(
        LT(_NUM,KC_ESC),KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC, KC_BSPC, KC_DEL, 
        KC_TAB,           KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_PGUP, 
        LT(_FUNC,KC_CAPS), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT,             KC_PGDN, 
        KC_LSFT, KC_NUBS,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,         KC_UP,        MO(_FUNC), 
        KC_LCTL, KC_LGUI, KC_LALT,        KC_SPC,         KC_SPC,          KC_SPC,          KC_RALT, KC_RCTL, XXXXXXX, KC_LEFT, KC_DOWN,      KC_RGHT),

    /* Keymap Fn Layer
     * ,----------------------------------------------------------------.
     * | ` | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       |Ins |
     * |----------------------------------------------------------------|
     * |     |TOG|M+ |H+ |S+ |V+ |Sp+|   |Prt|SLk|Pau|   |   |     |Home|
     * |------------------------------------------------------.    |----|
     * |      |VLK|M- |H- |S- |V+ |Sp-|   |   |   |   |   |   |    |End |
     * |----------------------------------------------------------------|
     * |       |BL |BL-|BL+|BRTG|   |   |   |   |   |   |      |PUp|    |
     * |----------------------------------------------------------------|
     * |Sleep|Reset|    |         C+A+D      |C+A+I|Menu|  |Hom|PDn|End |
     * `------------------------------------------------'  `------------'
     */
    [_FUNC] = LAYOUT_all(
         KC_GRV,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,KC_INS, 
         _______,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______,_______,_______,      KC_HOME, 
         _______,     VLK_TOG, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,_______,_______,_______,_______,_______,      _______,      KC_END, 
         _______,_______,BL_TOGG, BL_DEC, BL_INC, BL_BRTG,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,_______, 
         KC_SLEP,QK_BOOT,_______,      LCA(KC_DEL),     LCA(KC_DEL),    LCA(KC_DEL),  LCA(KC_INS),KC_APP, _______,KC_HOME,KC_PGDN,KC_END),
       
    /* Keymap Numpad Layer
     * ,----------------------------------------------------------------.
     * |   |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  /|   |       |    |
     * |----------------------------------------------------------------|
     * |     |   |   |   |   |   |   |  4|  5|  6|  *|   |   |     |    |
     * |------------------------------------------------------.    |----|
     * |      |   |   |   |   |   |   |  1|  2|  3|  -|   |   |    |    |
     * |----------------------------------------------------------------|
     * |     |  |NLk|   |   |   |   |   |  0|   |   |  +|      |   |    |
     * |----------------------------------------------------------------|
     * |    |    |    |                       |    |    |  |   |   |    |
     * `------------------------------------------------'  `------------'
     */
    [_NUM] = LAYOUT_all(
        _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, KC_KP_SLASH, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS, _______, _______,             _______, 
        _______, _______, KC_NLCK, _______, _______, _______, _______, _______, KC_KP_0, _______, _______, KC_KP_PLUS, _______,   _______, _______, 
        _______, _______, _______,       _______,        _______,         _______,          _______, _______, XXXXXXX, _______, _______, _______),
    };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void matrix_init_user(void) {
    
}

void matrix_scan_user(void) {
    
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
      rgblight_enable_noeeprom();
    } else {
      rgblight_disable_noeeprom();
    }
}
