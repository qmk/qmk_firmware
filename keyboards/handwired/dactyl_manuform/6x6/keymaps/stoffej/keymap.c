#include QMK_KEYBOARD_H


enum layers { BASE, LAY0, LAY1, LAY2, LAY3, LAY4, LAY5 };

enum custom_keycodes {
  M_NAME = SAFE_RANGE,
  M_CD_DOT,
  VM2WIN,
  WIN2VM,
};

#define U_RDO KC_AGIN
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO



enum unicode_names {
  SE_AA_H,
  SE_AE_H,
  SE_OE_H,
  SE_AA_L,
  SE_AE_L,
  SE_OE_L,
  UKB,
  UCOFFEE,
  UVOLT,
  UBEER,
  UTHMUP,
  USMIL,
  UBIC,
  UNERD,
  UBUG,
  UPARTY,
  UORHEART,
  UWHALE,
  UBOMB,
  UFACE_ROLLING_EYES,
  THNK
};

const uint32_t PROGMEM unicode_map[] = {
  [SE_AA_H] = 0x00C5,
  [SE_AE_H] = 0x00C4,
  [SE_OE_H] = 0x00D6,
  [SE_AA_L] = 0x00E5,
  [SE_AE_L] = 0x00E4,
  [SE_OE_L] = 0x00F6,
  [UKB]     = 0x2328,   // ⌨
  [UCOFFEE] = 0x2615,   // ☕
  [UVOLT]   = 0x26A1,   // ⚡
  [UBEER]   = 0x1F37B,  // 🍻
  [UTHMUP]  = 0x1F44D,  // 👍
  [USMIL]   = 0x1F642,  // 🙂
  [UBIC]    = 0x1F6B2,  // 🚲
  [UNERD]   = 0x1F913,  // 🤓
  [UBUG]    = 0x1F41B,  // 🐛
  [UPARTY]  = 0x1F389,  // 🎉
  [UORHEART] = 0x1F9E1, // 🧡
  [UWHALE] = 0x1F433,   // 🐳
  [UBOMB] = 0x1F4A3,    // 💣
  [UFACE_ROLLING_EYES] = 0x1F644, // 🙄
  [THNK] = 0x1F914, // 🤔
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_6x6(
    KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,          KC_J, KC_L,         KC_U,         KC_Y,           KC_QUOT,
    LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,          KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I),   LGUI_T(KC_O),
    KC_Z,         ALGR_T(KC_X), KC_C,         KC_D,         KC_V,          KC_K, KC_H,         KC_COMM,      ALGR_T(KC_DOT), KC_SLSH,
    LT(LAY0, KC_DEL),LT(LAY1, KC_BSPC),LT(LAY2, KC_ENT),                   LT(LAY3, KC_TAB), LT(LAY5, KC_SPC), LT(LAY4, KC_ESC)
),


[LAY0] = LAYOUT_6x6(
    _______, _______,  _______,      _______,    _______,                  KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,
    _______,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,                            KC_4,    KC_5,    KC_6,    KC_EQL,  KC_SCLN,
    _______,  KC_ALGR, _______,    _______,    _______,                    KC_1,    KC_2,    KC_3,    KC_GRV,  KC_BSLS,
                               _______,  _______, _______,                 KC_DOT,  KC_0,    KC_MINS
),

[LAY1] = LAYOUT_6x6(
    _______,   _______,  _______,    _______,    _______,               U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    _______,  KC_LGUI,   KC_LALT, KC_LCTL, KC_LSFT,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,
    _______,  KC_ALGR, _______,    _______,    _______,                 KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,
                            _______,    KC_UNDS, KC_LPRN,               KC_RPRN, _______, _______
),

[LAY2] = LAYOUT_6x6(
    _______, _______,  _______, _______,  _______,                  KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_PSCR,
    _______,  KC_LGUI, KC_LALT, KC_LCTL,  KC_LSFT,                            KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_EQL,
    _______,  KC_ALGR, _______, _______,  _______,                    KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_BSLS,
                       _______, _______,  _______,                 KC_TAB,  KC_SPC,    KC_APP
),

[LAY3] = LAYOUT_6x6(
    _______, _______, _______, WIN2VM, VM2WIN,                                              _______,  _______, _______, _______, _______,
    _______, _______,XP(SE_AA_L, SE_AA_H), XP(SE_AE_L, SE_AE_H), XP(SE_OE_L, SE_OE_H),      _______,  _______, _______, _______, _______,
    _______, _______, _______, _______, M_CD_DOT,                                           _______,  _______, _______, _______, _______,
                      _______, _______, _______,                                            _______,  _______, _______
),


[LAY4] = LAYOUT_6x6(
    KC_LCBR,   KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,               KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,
    KC_COLN,   KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                         KC_PLUS, KC_DLR,  KC_PERC, KC_CIRC, KC_COLN,
    KC_TILD,   KC_EXLM, KC_AT,   KC_HASH,    KC_PIPE,                 KC_PIPE, KC_EXLM, KC_AT,   KC_HASH, KC_TILD,
                        KC_LPRN, KC_RPRN, KC_UNDS,                 KC_RPRN, _______, _______
),


[LAY5] = LAYOUT_6x6(
    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,                            _______,    _______,    _______,    _______,   _______,
    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,                           _______,    KC_LSFT,    KC_LCTL,    KC_LALT,   KC_LGUI,
    U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,                             _______,    _______,    _______,    KC_ALGR,   _______,
                _______,    _______,    KC_DEL,                            KC_BSPC, KC_ENT,  _______
),

// [MBO] = LAYOUT_6x6(
//     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
//     KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
//     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//     _______,    _______,    KC_BTN2, KC_BTN3, KC_BTN1, KC_BTN1
// ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   #ifdef CONSOLE_ENABLE
//     uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
//   #endif
switch (keycode) {
    case M_NAME:
      if (record->event.pressed) {
          SEND_STRING("Kristoffer");
      }
      return false;
      break;
    case M_CD_DOT:
      if (record->event.pressed) {
          SEND_STRING("cd .."SS_TAP(X_ENTER)"");
      }
      return false;
      break;
    case VM2WIN:
        if (record->event.pressed) {
            SEND_STRING( SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_UP(X_LCTL) SS_UP(X_LALT) SS_DOWN(X_LCTL) SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_UP(X_LCTL) SS_UP(X_LGUI));
            //_delay_ms(1500);
            //set_unicode_input_mode(UC_WINC);
            //_delay_ms(100);
            //set_unicode_input_mode(UC_WINC);
            _delay_ms(200);
            //set_unicode_input_mode(UC_WINC);
            //_delay_ms(100);
        }
        return false;
        break;
    case WIN2VM:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LGUI) SS_TAP(X_RIGHT) SS_UP(X_LCTL) SS_UP(X_LGUI) SS_DELAY(300) SS_TAP(X_BTN1));
            //set_unicode_input_mode(UC_LNX);
        }
        return false;
        break;
    }


    return true;
}




// SEND_STRING(".............................................\n"
//             "...#######################################...\n"
//             "...#######################################...\n"
//             "...###'''##'''##'''##'''##'''##'''##'''###...\n"
//             "...###...##...##...##...##...##...##...###...\n"
//             "...#######################################...\n"
//             "...###'''##'''##'''##'''##'''##'''##'''###...\n"
//             "...###...##...##...##...##...##...##...###...\n"
//             "...#######################################...\n"
//             "...######'''''''''''''''''''''''''''######...\n"
//             "...######...........................######...\n"
//             "...#######################################...\n"
//             "...#######################################...\n"
//             ".................__............._............\n"
//             "................/ /............| |...........\n"
//             "...... _ __ .../ /.._ __ ___...| |.__........\n"
//             "......| '__|../ /..| '_ ` _ \\..| |/ /........\n"
//             "......| |..../ /...| | | | | |.|   < ........\n"
//             "......|_|.../_/....|_| |_| |_|.|_|\\_\\........\n"
//             ".............................................\n"
//             );