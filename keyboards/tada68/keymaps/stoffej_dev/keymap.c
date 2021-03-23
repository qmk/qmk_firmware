#include QMK_KEYBOARD_H


enum layer_number {
  _QWERTY = 0,
  _COLEMAK,
  _EMOJI,
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

#define FN_BSPC LT(_FUNCTION, KC_BSPC)
#define FN_SCLN LT(_FUNCTION, KC_SCLN)
#define EM_TAB LT(_EMOJI,KC_TAB)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap _QWERTY: Base Qwerty
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
    EM_TAB , KC_Q   , KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
    FN_BSPC, KC_A   , KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    FN_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FUNCTION), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),


  /* Keymap _COLEMAK: Base Colemak
   * ,----------------------------------------------------------------.
   * | Esc  | 1|  2|  3|   |   |   |   |   |   |   |   |   |Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  F|  P|  B|  J|  L|  U|  Y|  P|  [|  Ent|Del |
   * |------------------------------------------------------|  er|----|
   * |Backspa| A|  R|  S|  T|  G|  M|  N|  E|  I|  I|  O| '| \   |PgUp|
   * |----------------------------------------------------------------|
   * |Shif| \|  Z|  X|  C|  D|  V|  K|  H|  ,|  .|  / | Shift| Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_iso(
    KC_ESC , KC_1   , KC_2   ,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,  \
    EM_TAB , KC_Q   , KC_W   ,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
    FN_BSPC, KC_A   , KC_R   ,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z   ,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FUNCTION), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),


  /* Keymap _EMOJI: Layer Upper
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  +|  '|Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  Å|  ¨| Ent|Del |
   * |------------------------------------------------------| er|----|
   * |Backspa| A|  S|  D|  F|  G|  H|  J|  K|  L|  Ø|  Æ| @ |   |PgUp|asdasdad
   * |----------------------------------------------------------------|
   * |Shif| <>|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  -| Shift| Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_EMOJI] = LAYOUT_iso(
    _______, _______, _______, _______, _______, _______, _______,  _______,   _______, _______, _______, _______, _______,  _______, _______,  \
    _______, _______, _______, _______, _______, _______,  X(UKB), X(UCOFFEE), X(UVOLT), X(UBEER), X(UTHMUP), X(USMIL), _______,           _______,  \
    _______, _______, _______, _______, _______, _______, X(UBIC), X(UNERD),   X(UBUG), X(UPARTY), X(UORHEART), _______, _______, _______,  _______, \
    _______, _______, _______, _______, _______, _______, X(UWHALE), X(UBOMB), X(UFACE_ROLLING_EYES), X(THNK), _______, _______, _______, _______,  _______, \
    _______, _______, _______,                   _______,                             _______,_______, _______, _______, _______, _______
  ),


  /* Keymap _FUNCTION: (Base Layer) Default Layer qwerty
   * ,----------------------------------------------------------------.
   * |Esc |F1|F2|F3|F4|F5| F6| F7| F8| F9| F10| F11| F12|Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  | CM | QW | NM |   |   |   |   |   |   |   |  å|  ¨| Ent|Del |
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
    _______, LAY_COL, LAY_QWE ,  M_NAME, _______, _______, KC_END, KC_HOME, _______, _______,  BL_INC, XP(SE_AA_L, SE_AA_H) , _______,              KC_INS,  \
    _______, OS_WIN , OS_LIN , VM2WIN , WIN2VM, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,   XP(SE_OE_L, SE_OE_H) ,  XP(SE_AE_L, SE_AE_H) , _______,  _______,   KC_HOME, \
    _______, BL_TOGG, BL_DEC , _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLD, KC_MUTE,  KC_VOLU, _______, M_CD_DOT,    KC_END,  \
    _______, _______, _______,                   KC_ENT,                             _______, _______,   KC_APP, _______,  _______,    _______
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
            set_unicode_input_mode(UC_WINC);
        }
        return false;
        break;
    case WIN2VM:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LGUI) SS_TAP(X_RIGHT) SS_UP(X_LCTL) SS_UP(X_LGUI) SS_DELAY(300) SS_TAP(X_BTN1));
            set_unicode_input_mode(UC_LNX);
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
