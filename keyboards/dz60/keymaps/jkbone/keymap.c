#include QMK_KEYBOARD_H

#define ____ KC_TRNS
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define FL_ESC  LT(_FL, KC_ESC)
#define FL      MO(_FL)

enum layers_idx {
    _BL, // Base Layer
    _ML, // Mac Modifiers (Switched around LGUI, LALT, LCTL)
    _FL  // Functions
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_60_iso_5x1u(
    KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,    KC_BSPC,
    KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_ENT,
    FL_ESC,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_BSLS,
    KC_LSFT,    KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,        KC_RSFT,
    KC_LCTL,     KC_LGUI,     KC_LALT,                      KC_SPC,                         FL, KC_LEFT, KC_DOWN,  KC_UP,  KC_RIGHT
  ),
  [_ML] = LAYOUT_60_iso_5x1u(
    ____,      ____,     ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,         ____,
    ____,        ____,     ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,     ____,     ____,     ____,
    ____,         ____,     ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,     ____,     ____,
    ____,       ____,     ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,     ____,          ____,
    KC_LGUI,     KC_LALT,     KC_LCTL,                      ____,                             ____,    ____,    ____,    ____,    ____
  ),
  [_FL] = LAYOUT_60_iso_5x1u(
    RESET,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,     KC_DEL,
    ____,        ____,   DF(_BL),   DF(_ML),    ____,    ____,    ____,    ____,    ____,    ____,    ____,     ____,     ____,    ____,
    ____,         ____,    ____,    ____,    ____,    ____,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,    ____,     ____,     ____,
    ____,       F(3),     F(2),    F(1),    F(0),    ____,    ____,    ____, KC_MUTE, KC_MPRV, KC_MNXT, KC_MPLY,          ____,
    ____,        ____,      ____,                          ____,                             ____,    ____,    ____,    ____,    ____
  )
};

enum function_id {
    RGB_VAZ,
    RGB_OAZ,
    RGB_WAN,
    RGB_000
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(RGB_VAZ),
  [1]  = ACTION_FUNCTION(RGB_OAZ),
  [2]  = ACTION_FUNCTION(RGB_WAN),
  [3]  = ACTION_FUNCTION(RGB_000)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case RGB_VAZ:
        rgblight_enable();
        rgblight_setrgb(0, 204, 33);
        break;
    case RGB_OAZ:
        rgblight_enable();
        rgblight_setrgb(229, 65, 0);
        break;
    case RGB_WAN:
        rgblight_enable();
        rgblight_setrgb(255, 255, 255);
        break;
    case RGB_000:
        rgblight_disable();
        break;
  }
}
