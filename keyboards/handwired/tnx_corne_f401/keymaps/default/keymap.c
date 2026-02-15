#include QMK_KEYBOARD_H

// Home Row Mods - custom modifier order
#define HM_A LSFT_T(KC_A)           // Shift
#define HM_S LCTL_T(KC_S)           // Ctrl
#define HM_D LGUI_T(KC_D)           // Win/GUI
#define HM_F LALT_T(KC_F)           // Alt

#define HM_J LALT_T(KC_J)           // Alt
#define HM_K LGUI_T(KC_K)           // Win/GUI
#define HM_L LCTL_T(KC_L)           // Ctrl
#define HM_SCLN RSFT_T(KC_SCLN)     // Shift

// Tap-Hold Keys
#define TC_L0 LT(MO(1), KC_ESC)
#define TC_R0 LT(MO(4), KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE Layer: QWERTY */
    [0] = LAYOUT_split_3x5_3(
      //A8       B15      B14      B13      B12                                 B12      B13      B14      B15      A8 
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             /*B0*/            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        HM_A,    HM_S,    HM_D,    HM_F,    KC_G,             /*A5*/            KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             /*A4*/            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          TC_L0,   KC_SPC,  MO(3),            /*A3*/            TC_R0,   KC_BSPC, MO(2)
    ),
    [1] = LAYOUT_split_3x5_3(
        KC_ESC,  KC_F3,   KC_F6,   KC_F9,   KC_F12,                             KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,
        KC_TAB,  KC_F2,   KC_F5,   KC_F8,   KC_F11,                             KC_NO,   KC_NO,   KC_4,    KC_5,    KC_6,
        KC_DEL,  KC_F1,   KC_F4,   KC_F7,   KC_F10,                             KC_NO,   KC_0,    KC_1,    KC_2,    KC_3,
                          _______, _______, _______,                            _______, _______, _______
    ),
    [2] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE,                            KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_TILD, KC_GRV,  KC_QUOT, KC_DQUO, KC_COLN,                            KC_SCLN, KC_LT,   _______,   _______, _______,
                          _______, _______, _______,                            _______, _______, _______
    ), 
    [3] = LAYOUT_split_3x5_3(
        QK_BOOT, KC_NO,   RESET,   KC_MPRV, KC_MNXT,                            KC_MPLY, KC_MSTP, KC_MUTE, KC_PSCR, KC_NUM,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   MS_LEFT, MS_DOWN, MS_UP  , MS_RGHT,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_BRID, KC_BRIU, KC_NO,
                          _______, _______, _______,                            MS_BTN1, MS_BTN2, _______
    ),
    [4] = LAYOUT_split_3x5_3(
        KC_NO,    KC_NO,  KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,    KC_NO,  KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_NO,    KC_NO,  KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          _______, _______, _______,                            _______, _______, _______
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
        tap_code(MS_WHLU);
    } else {
        tap_code(MS_WHLD);
    }
  }
  return false;
}