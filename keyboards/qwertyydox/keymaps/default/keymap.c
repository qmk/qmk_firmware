#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layer_names {
    _QWERTY,
    _NUM,
    _NAV
};

enum custom_keycodes {
  qwerty = SAFE_RANGE,
  nav,
  num,
  EQL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_LGUI, KC_LALT, qwerty,  KC_ENT,  KC_DEL,  TO(1),            TO(2),   KC_SPC,  KC_BSPC, KC_LEFT, KC_RALT, KC_RGUI, KC_RCTL
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_NUM] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,            KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                      KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_PPLS, KC_PMNS, EQL,     KC_PAST, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL,  KC_ESC, KC_NO,   num,     KC_ENT,  KC_LSFT, TO(2),            TO(0),   KC_SPC,  KC_BSPC, KC_LEFT, KC_RALT, KC_RGUI, KC_RCTL
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

    [_NAV] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_ESC,  KC_NO,   KC_ACL0, KC_ACL1, KC_ACL2, KC_WH_L, KC_WH_R,          KC_ESC,  KC_NO,   KC_UP,   KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_WH_U,                   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_INS,  KC_HOME, KC_PGUP, KC_BTN1, KC_BTN2, KC_WH_D,                            KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_DEL,  KC_END,  KC_PGDN, nav,     KC_LCTL, KC_SPC,  TO(0),            TO(1),   KC_LSFT, KC_BSPC, KC_NO,   KC_NO,   KC_NO,   RESET
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case qwerty:
                SEND_STRING("-QWERTY");
                return false;
            case nav:
                SEND_STRING("-NAV"); // selects all and copies
                return false;
            case num:
                SEND_STRING("-NUM"); // selects all and copies
                return false;
            case EQL:
                SEND_STRING("="); // selects all and copies
                return false;
        }
    }
    return true;
};
