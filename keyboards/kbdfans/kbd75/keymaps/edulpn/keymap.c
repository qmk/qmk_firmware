#include QMK_KEYBOARD_H

#define WINDOWS_LAYER 0
#define WINDOWS_FN_LAYER 1
#define MAC_LAYER 2
#define MAC_FN_LAYER 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [WINDOWS_LAYER] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,                 KC_F11,   KC_F12,   KC_PSCR,  TO(MAC_LAYER),  KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,                   KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,        KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,                   KC_LBRC,  KC_RBRC,  KC_BSLS,                  KC_END,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,                KC_QUOT,                      KC_ENT,         KC_PGUP,
    KC_LSFT,  KC_TRNS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,                 KC_SLSH,  KC_RSFT,            KC_UP,          KC_PGDN,
    KC_LCTL,  KC_LWIN,  KC_LALT,                      KC_SPC,   KC_SPC,   KC_SPC,                       MO(WINDOWS_FN_LAYER),   KC_TRNS,  KC_RCTL,  KC_LEFT,  KC_DOWN,        KC_RGHT
  ),

  [WINDOWS_FN_LAYER] = LAYOUT(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_TRNS,  KC_INS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [MAC_LAYER] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,             KC_F11,   KC_F12,   KC_PSCR,  TO(WINDOWS_LAYER),  KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,               KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,            KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,               KC_LBRC,  KC_RBRC,  KC_BSLS,                      KC_END,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,            KC_QUOT,                      KC_ENT,             KC_PGUP,
    KC_LSFT,  KC_TRNS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,             KC_SLSH,  KC_RSFT,            KC_UP,              KC_PGDN,
    KC_LCTL,  KC_LALT,  KC_LCMD,                      KC_SPC,   KC_SPC,   KC_SPC,                       MO(MAC_FN_LAYER),   KC_TRNS,  KC_RCTL,  KC_LEFT,  KC_DOWN,            KC_RGHT
  ),

  [MAC_FN_LAYER] = LAYOUT(
    QK_BOOT,  KC_BRID,  KC_BRIU,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_MUTE,    KC_VOLD,      KC_VOLU,    KC_TRNS,  KC_TRNS,  KC_INS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS,            KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,                            KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,      KC_TRNS,              KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,    KC_TRNS,      KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case WINDOWS_LAYER:
        rgblight_setrgb(RGB_BLUE);
        break;
    case WINDOWS_FN_LAYER:
        rgblight_setrgb(RGB_BLUE);
        break;
    case MAC_LAYER:
        rgblight_setrgb(RGB_WHITE);
        break;
    case MAC_FN_LAYER:
        rgblight_setrgb(RGB_WHITE)
        break;
    default:
        rgblight_setrgb (0x00,  0xFF, 0xFF);
        break;
    }
    return state;
}
