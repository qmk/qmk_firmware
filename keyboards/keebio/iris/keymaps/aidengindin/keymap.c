#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _SYMBOL 1
#define _ADJUST 2

enum custom_keycodes {
  MS_JGL = SAFE_RANGE,
};

bool mouse_jiggle_mode = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     KC_CAPS,  KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                               KC_6,    KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
     KC_GRV,   KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                               KC_Y,    KC_U,           KC_I,           KC_O,           KC_P,           KC_MINS,
     KC_ESC,   GUI_T(KC_A),    ALT_T(KC_S),    CTL_T(KC_D),    SFT_T(KC_F),    KC_G,                               KC_H,    SFT_T(KC_J),    CTL_T(KC_K),    ALT_T(KC_L),    GUI_T(KC_SCLN), KC_QUOT,
     KC_LPRN,  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,    KC_DEL,          CW_TOGG,  KC_N,    KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RPRN,
                                                               MO(_SYMBOL),  KC_TAB,   KC_BSPC,           KC_SPC,  KC_ENT,  MO(_ADJUST)
  ),

  [_SYMBOL] = LAYOUT(
     KC_F1,   KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                              KC_F7,   KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
     KC_PGUP, KC_AT,          KC_PERC,        KC_LPRN,        KC_RPRN,        KC_EQL,                             KC_PAST, KC_P7,          KC_P8,          KC_P9,          KC_AMPR,        KC_HOME,
     KC_PGDN, GUI_T(KC_HASH), ALT_T(KC_DLR),  CTL_T(KC_LBRC), SFT_T(KC_RBRC), KC_PMNS,                            KC_PLUS, SFT_T(KC_P4),   CTL_T(KC_P5),   ALT_T(KC_P6),   GUI_T(_______), KC_END,
     KC_PIPE, KC_LABK,        KC_RABK,        KC_LCBR,        KC_RCBR,        KC_PSLS, QK_BOOT,          KC_UP,   KC_P0,   KC_P1,          KC_P2,          KC_P3,          KC_PDOT,        KC_BSLS,
                                                                     _______, KC_NUM,  _______,          KC_DOWN, KC_LEFT, KC_RGHT
  ),

  [_ADJUST] = LAYOUT(
     RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI,                            RGB_TOG, RGB_M_P, RGB_M_B, RGB_MOD, RGB_RMOD, _______,
     KC_BRIU, _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_VOLU,                            KC_MNXT, _______, KC_WH_U, _______, DM_PLY2,  DM_REC2,
     KC_BRID, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_VOLD,                            KC_MPLY, KC_WH_L, KC_WH_D, KC_WH_R, DM_PLY1,  DM_REC1,
     _______, MS_JGL,  KC_BTN3, KC_BTN3, _______, KC_MUTE, _______,          _______, KC_MPRV, _______, _______, _______, _______,  DM_RSTP,
                                         KC_WBAK, KC_WFWD, _______,          _______, _______, _______
  )
};

void matrix_scan_user(void) {
    if (mouse_jiggle_mode) {
        tap_code(KC_MS_LEFT);
        tap_code(KC_MS_RIGHT);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MS_JGL:
        if (record->event.pressed) {
            mouse_jiggle_mode = !mouse_jiggle_mode;
        }
        return false;

    default:
        break;
  }
  return true;
}
