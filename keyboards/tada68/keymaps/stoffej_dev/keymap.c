#include QMK_KEYBOARD_H


enum layer_number {
  _QWERTY = 0,
  _COLEMAK,
  _UPPER,
  _FUNCTION,
};

enum custom_keycodes {
  M_NAME = SAFE_RANGE,
  M_CD_DOT,
  VM2WIN,
  WIN2VM,
  LAY_QWE,
  LAY_COL,
  OS_LIN,
  OS_WIN,
};


enum unicode_names {
  SE_AA_H,
  SE_AE_H,
  SE_OE_H,
  SE_AA_L,
  SE_AE_L,
  SE_OE_L,
};

const uint32_t PROGMEM unicode_map[] = {
  [SE_AA_H] = 0x00C5,
  [SE_AE_H] = 0x00C4,
  [SE_OE_H] = 0x00D6,
  [SE_AA_L] = 0x00E5,
  [SE_AE_L] = 0x00E4,
  [SE_OE_L] = 0x00F6,
};

/*#define U_AA (XP(SE_AA_L, SE_AA_H))
#define U_AE (XP(SE_AE_L, SE_AE_H))
#define U_OE (XP(SE_OE_L, SE_OE_H))*/

#define FN_BSPC LT(_FUNCTION, KC_BSPC)
#define FN_SCLN LT(_FUNCTION, KC_SCLN)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap _BL: (Base Layer) Default Layer qwerty
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  +|  '|Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  Å|  ¨| Ent|Del |
   * |------------------------------------------------------| er|----|
   * |Backspa| A|  S|  D|  F|  G|  H|  J|  K|  L|  Ø|  Æ| @ |   |PgUp|
   * |----------------------------------------------------------------|
   * |Shif| <>|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  -| Shift| Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_iso(
    KC_ESC , KC_1   , KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,  \
    KC_TAB , KC_Q   , KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
    FN_BSPC, KC_A   , KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    FN_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_UPPER), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),


  /* Keymap _BL: (Base Layer) Default Layer qwerty
   * ,----------------------------------------------------------------.
   * |   |  |   |   |   |   |   |   |   |   |   |   |   |Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  Å|  ¨| Ent|Del |
   * |------------------------------------------------------| er|----|
   * |Backspa| A|  S|  D|  F|  G|  H|  J|  K|  L|  Ø|  Æ| @ |   |PgUp|
   * |----------------------------------------------------------------|
   * |Shif| <>|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  -| Shift| Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_iso(
    KC_ESC , KC_1   , KC_2   ,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,  \
    KC_TAB , KC_Q   , KC_W   ,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
    FN_BSPC, KC_A   , KC_S   ,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    FN_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z   ,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_UPPER), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),


  /* Keymap _BL: (Base Layer) Default Layer qwerty
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  +|  '|Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  Å|  ¨| Ent|Del |
   * |------------------------------------------------------| er|----|
   * |Backspa| A|  S|  D|  F|  G|  H|  J|  K|  L|  Ø|  Æ| @ |   |PgUp|
   * |----------------------------------------------------------------|
   * |Shif| <>|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  -| Shift| Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_UPPER] = LAYOUT_iso(
    _______,     KC_1, KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,  \
    _______,     KC_Q, KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
    _______,  KC_A , KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT,_______, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),


  /* Keymap _BL: (Base Layer) Default Layer qwerty
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  +|  '|Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  |   |   |   |   |   |   |   |   |   |   |  å|  ¨| Ent|Del |
   * |----------------------------------------------------- | er|----|
   * |Backs  |  |   |   |   |   |   |   |   |   |  ö| ä  |   |   |PgUp|
   * |----------------------------------------------------------------|
   * |Shif| <>|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  -| Shift| Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_FUNCTION] = LAYOUT_iso(
    _______, KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12,    RESET,   KC_PSCR, \
    _______, _______, _______,  M_NAME, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, _______ ,  BL_INC, XP(SE_AA_L, SE_AA_H) , _______,              KC_INS,  \
    _______, OS_WIN , OS_LIN , VM2WIN , WIN2VM, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,   XP(SE_OE_L, SE_OE_H) ,  XP(SE_AE_L, SE_AE_H) , _______,  _______,   KC_HOME, \
    _______, BL_TOGG, BL_DEC , _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLD, KC_MUTE,  KC_VOLU, _______, M_CD_DOT,    KC_END,  \
    _______, _______, _______,                   _______,                             _______, _______,   KC_APP, _______,  _______,    _______
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
            SEND_STRING( SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_UP(X_LCTL) SS_UP(X_LALT) SS_DOWN(X_LCTL) SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_UP(X_LCTL) SS_UP(X_LGUI) );
        }
        return false;
        break;
    case WIN2VM:
        if (record->event.pressed) {
            SEND_STRING( SS_DOWN(X_LCTL) SS_DOWN(X_LGUI) SS_TAP(X_RIGHT) SS_UP(X_LCTL) SS_UP(X_LGUI) SS_TAP(X_MS_L));
        }
        return false;
        break;

    /* layout switcher */
    case LAY_QWE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LAY_COL:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;

    /* os switcher */
    case OS_LIN:
      set_unicode_input_mode(UC_LNX);
      return false;
      break;
    case OS_WIN:
      set_unicode_input_mode(UC_WINC);
      return false;
      break;
    }
    return true;
}

/*
kolla om hopp fungerar mellan win i vm
sätt upp colemak o qwerty tangenterna
lägg till att byta input när en hoppar mellan de olika miljöerna
*/