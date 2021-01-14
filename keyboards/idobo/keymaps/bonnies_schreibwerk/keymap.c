// qmk compile -kb idobo -km bonnies_schreibwerk


//  .----------------.  .----------------.  .-----------------. .-----------------. .----------------.
//  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
//  | |   ______     | || |     ____     | || | ____  _____  | || | ____  _____  | || |  ____  ____  | |
//  | |  |_   _ \    | || |   .'    `.   | || ||_   \|_   _| | || ||_   \|_   _| | || | |_  _||_  _| | |
//  | |    | |_) |   | || |  /  .--.  \  | || |  |   \ | |   | || |  |   \ | |   | || |   \ \  / /   | |
//  | |    |  __'.   | || |  | |    | |  | || |  | |\ \| |   | || |  | |\ \| |   | || |    \ \/ /    | |
//  | |   _| |__) |  | || |  \  `--'  /  | || | _| |_\   |_  | || | _| |_\   |_  | || |    _|  |_    | |
//  | |  |_______/   | || |   `.____.'   | || ||_____|\____| | || ||_____|\____| | || |   |______|   | |
//  | |              | || |              | || |              | || |              | || |              | |
//  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
//  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'

#include QMK_KEYBOARD_H

// Keyboard Layers
enum layer_names {
    BASE,
    LAYER1,
    LAYER2,
    LAYER3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Default Layout
 [BASE] = LAYOUT_ortho_5x15(
    KC_ESC,  KC_GRV,  KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,      KC_0,    KC_MINS, KC_EQL,  KC_INS,  \
    KC_TAB,  KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  \
    KC_BSPC, KC_A,    KC_S,      KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_ENT,  KC_ENT,  KC_HOME, \
    KC_LSFT, KC_Y,    KC_X,      KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT, KC_RSFT, KC_UP,   KC_END, \
    KC_LCTL, KC_LALT, MO(LAYER1),KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  MO(LAYER1),KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT  \
  ),
// Fn Reihe, kleine Umlaute, Capslock, media Controls
  [LAYER1] = LAYOUT_ortho_5x15(
             KC_NO,  KC_NO,     KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,              KC_F11,  KC_F12,      KC_NO,  \
             KC_NO,  KC_NO,     KC_NO,     KC_F20,   KC_NO,    KC_NO,    KC_NO,    KC_F17,   KC_NO,    KC_F15,   KC_NO,   KC_NO,               KC_NO,   KC_NO,       KC_NO,  \
            KC_DEL,  KC_F13,    KC_F19,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,               KC_NO,   KC_NO,       KC_NO, \
LT(LAYER2, KC_CAPS), KC_NO,     KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   LT(LAYER2, KC_CAPS), KC_NO,   KC_VOLU,     KC_NO, \
         MO(LAYER3), KC_NO,     KC_NO,     KC_MPLY,  KC_MPLY,  KC_MPLY,  KC_MPLY,  KC_MPLY,  KC_MPLY,  KC_MPLY,  KC_NO,   KC_NO,               KC_MPRV, KC_VOLD,     KC_MNXT  \
  ),
// große Umlaute
  [LAYER2] = LAYOUT_ortho_5x15(
     KC_NO,  KC_NO,   KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,     KC_F10,  KC_F11,  KC_F12,  KC_NO,  \
     KC_NO,  KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F18,  KC_NO,   KC_F16,  KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,  \
     KC_NO,  KC_F14,  KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO, \
     KC_NO,  KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO, \
     KC_NO,  KC_NO,   KC_NO,     KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO  \
  ),
// Numpad
  [LAYER3] = LAYOUT_ortho_5x15(
     KC_NO,   KC_NO,   KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,     KC_F10,    KC_F11,  KC_F12,  KC_NO,  \
     KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,      KC_NO,     KC_NO,   KC_NO,   KC_NO,  \
     KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_4,    KC_5,    KC_6,      KC_NO,     KC_NO,   KC_NO,   KC_NO, \
     KC_LSFT, KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,      KC_RSFT,   KC_NO,   KC_NO,   KC_NO, \
     KC_NO,   KC_NO,   KC_NO,     KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_0,    KC_NO,     KC_NO,     KC_NO,   KC_NO,   KC_RST  \
  ),
};
