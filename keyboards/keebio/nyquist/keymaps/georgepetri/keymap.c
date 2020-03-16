#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _BASE 0
#define _L 1
#define _R 2

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
    KC_CAPS, KC_LCTL, KC_LGUI, KC_LALT, MO(_L) , KC_SPC ,   KC_RSFT, TG(_R) , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  
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

const rgblight_segment_t PROGMEM base[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM left[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM right[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_RED}
);

const rgblight_segment_t PROGMEM capslock[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_GOLD},
    {9, 3, HSV_GOLD}
);

// HSV_SPRINGGREEN //YES //YES
// HSV_GREEN //YES
// HSV_GOLD //YES
// HSV_RED //YES
// HSV_ORANGE //YES
// HSV_WHITE //YES
// HSV_MAGENTA //YES
// todo add shift colors
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base, left, right, capslock
);

//docs.qmk.fm/#/custom_quantum_functions?id=keyboard-idlingwake-code/
//todo idea: impl hjkl as compose or leader 
//github.com/qmk/qmk_firmware/pull/5338/files  //might not work on split kbs
//todo idea use TT on left layer
void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
    rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _L));
    rgblight_set_layer_state(2, layer_state_cmp(state, _R));
    return state;
}

bool is_shift_pressed = false;

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, is_shift_pressed ^ led_state.caps_lock);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            is_shift_pressed = record->event.pressed;
            rgblight_set_layer_state(3, is_shift_pressed ^ host_keyboard_led_state().caps_lock);
        default:
            return true;
    }
}
