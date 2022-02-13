#include QMK_KEYBOARD_H
#include "keymap_swedish.h"


enum layer_number {
  _QWERTY = 0,
  _COLEMAK,
  _EMOJI,
  _FUNCTION,
  _SWE
};

enum custom_keycodes {
  M_NAME = SAFE_RANGE,
  M_CD_DOT,
  COMM,     // , | <
  DOT,      // . | >
  SLSH,     // / | ?
  SCLN,     // ; | :
  QUOT,     // ' | "
  KC_SE_MYEQUAL,  // 0 | *
  LAY_QWE,
  LAY_COL,
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
#define FN_KC_N LT(_FUNCTION, KC_N)
#define FN_KC_T LT(_FUNCTION, KC_T)
#define SW_KC_E LT(_SWE, KC_E)
#define SW_KC_K LT(_SWE, KC_K)
#define WIN_KC_K WIN_T(KC_K)

#define CTL_KC_I RCTL_T(KC_I)
#define CTL_KC_R LCTL_T(KC_R)

#define SHFT_KC_A LSFT_T(KC_A)
#define SHFT_KC_O RSFT_T(KC_O)

#define CTLZ LCTL(KC_Z)
#define CTLX LCTL(KC_X)
#define CTLC LCTL(KC_C)
#define CTLV LCTL(KC_V)


#define EM_TAB LT(_EMOJI,KC_TAB)

// SWEDISH LETTERS AND SYMBOLS
// Letters
#define KC_SE_AA KC_LBRC               // Å
#define KC_SE_AE KC_QUOT               // Ä
#define KC_SE_OE KC_SCLN               // Ö
#define KC_SE_QUO KC_BSLS              // '
#define KC_SE_COL S(KC_DOT)            // :
#define KC_SE_SEMI S(KC_COMM)          // ;
#define KC_SE_EXCL S(KC_1)             // !
#define KC_SE_DQUO S(KC_2)             // "
#define KC_SE_HASH S(KC_3)             // #
#define KC_SE_PERC S(KC_5)             // %
#define KC_SE_AMPR S(KC_6)             // &
#define KC_SE_SLSH S(KC_7)             // /
#define KC_SE_LPRN S(KC_8)             // (
#define KC_SE_RPRN S(KC_9)             // )
#define KC_SE_EQAL S(KC_0)             // =
#define KC_SE_CIRC S(KC_RBRACKET)      // ^
#define KC_SE_AT RALT(KC_2)            // @
#define KC_SE_DLR RALT(KC_4)           // $
#define KC_SE_LCBR RALT(KC_7)          // {
#define KC_SE_LBRC RALT(KC_8)          // [
#define KC_SE_RBRC RALT(KC_9)          // ]
#define KC_SE_RCBR RALT(KC_0)          // }
#define KC_SE_TILD RALT(KC_RBRACKET)   // ~
#define KC_SE_DIAE KC_RBRACKET         // ¨
#define KC_SE_ACUT KC_EQL              // ´
#define KC_SE_MINS KC_SLASH            // -
#define KC_SE_GRAV KC_PLUS             // `
#define KC_SE_LESS KC_NUBS             // <
#define KC_SE_MORE S(KC_NUBS)          // >
#define KC_SE_PLUS KC_MINS             // +
#define KC_SE_ASTR S(KC_BSLS)          // *
#define KC_SE_QUES S(KC_MINS)          // ?
#define KC_SE_BSLH RALT(KC_MINS)       /* \ */
#define KC_SE_PIPE RALT(KC_NUBS)       // |


//Tap Dance Declarations
enum {
  TD_1 = 0,
  TD_2,
  TD_3,
  TD_4,
  TD_5,
  TD_6,
  TD_7,
  TD_8,
  TD_9,
  TD_0,
  TD_EQL,
  TD_DASH,
  TD_GRAV,
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_1]  = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_SE_EXCL),
  [TD_2]  = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_SE_AT),
  [TD_3]  = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_SE_HASH),
  [TD_4]  = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_SE_DLR),
  [TD_5]  = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_SE_PERC),
  [TD_6]  = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_SE_CIRC),
  [TD_7]  = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_SE_AMPR),
  [TD_8]  = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_SE_ASTR),
  [TD_9]  = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_SE_LPRN),
  [TD_0]  = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_SE_RPRN),
  [TD_EQL]  = ACTION_TAP_DANCE_DOUBLE(KC_SE_EQAL, KC_SE_PLUS),
  [TD_DASH]  = ACTION_TAP_DANCE_DOUBLE(KC_SE_MINS, S(SE_MINS)),
  [TD_GRAV]  = ACTION_TAP_DANCE_DOUBLE(KC_SE_GRAV, KC_SE_TILD),


// Other declarations would go here, separated by commas, if you have them
};



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap _QWERTY: Base Qwerty
   * ,----------------------------------------------------------------.---
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
    KC_ESC , TD(TD_1)   , TD(TD_2),  TD(TD_3),    TD(TD_4),   TD(TD_5),    TD(TD_6),   TD(TD_7),    TD(TD_8),    TD(TD_9),    TD(TD_0),    KC_MINS , TD(TD_DASH),  KC_BSPC, TD(TD_GRAV),  \
    EM_TAB , KC_Q   , KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
    FN_BSPC, KC_A   , KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    SW_KC_K,    KC_L,    SCLN, QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    COMM,  DOT,  SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FUNCTION), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),


  /* Keymap _COLEMAK: Base Colemak
   * ,----------------------------------------------------------------.
   * | Esc  | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa |  ´|
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  F|  P|  B|  J|  L|  U|  Y|  ;|  [|  ]|  Ent|Del |
   * |------------------------------------------------------|  er|----|
   * |Backspa| A|  R|  S|  T|  G|  M|  N|  E|  I|  O| '| \  |    |PgUp|
   * |----------------------------------------------------------------|
   * |Shif| \|  Z|  X|  C|  D|  V|  K|  H|  ,|  .|  / | Shift| Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_iso(
    KC_ESC , TD(TD_1)   , TD(TD_2)   ,    TD(TD_3),    TD(TD_4),    TD(TD_5),    TD(TD_6),    TD(TD_EQL),  TD(TD_7),    TD(TD_8),    TD(TD_9),    TD(TD_0),    TD(TD_DASH), KC_BSPC,     TD(TD_GRAV),  \
    EM_TAB , KC_Q   , KC_W   ,    KC_F,    KC_P,    KC_B,    KC_SE_LBRC, KC_J,    KC_L,    KC_U,    KC_Y,    SCLN, SLSH,              KC_DEL,  \
    FN_BSPC, SHFT_KC_A   , CTL_KC_R   ,    KC_S,    FN_KC_T,    KC_G,    KC_SE_RBRC, KC_M,    FN_KC_N,    SW_KC_E,    CTL_KC_I,    SHFT_KC_O,    QUOT, KC_ENT,      KC_PGUP, \
    KC_LSPO, KC_Z   , KC_X   ,    KC_C,    KC_D,    KC_V,    KC_SE_BSLH, KC_SE_HASH, WIN_KC_K,    KC_H,    COMM, DOT,  KC_RSPC, KC_UP,       KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                       KC_RALT, MO(_FUNCTION), KC_RCTL, KC_LEFT, KC_DOWN,        KC_RGHT
  ),


  /* Keymap _EMOJI: Layer Upper
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
  [_EMOJI] = LAYOUT_iso(
    _______, _______, _______, _______, _______, _______, _______,  _______,   _______, _______, _______, _______, _______,  _______, _______,  \
    _______, _______, _______, _______, _______, X(USMIL),  X(UKB), X(UCOFFEE), X(UVOLT), X(UBEER), X(UTHMUP),XP(SE_AA_L, SE_AA_H) , _______,           _______,  \
    _______, _______, _______, _______, _______, X(UORHEART), X(UBIC), X(UNERD),   X(UBUG), X(UPARTY), XP(SE_OE_L, SE_OE_H), XP(SE_AE_L, SE_AE_H) , _______,           _______,  _______, \
    _______, BL_TOGG, BL_DEC, _______, _______, _______, X(UWHALE), X(UBOMB), X(UFACE_ROLLING_EYES), X(THNK), _______, _______, _______, _______,  _______, \
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
    _______, KC_F1  ,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7  , KC_F8   , KC_F9 ,  KC_F10,   KC_F11,  KC_F12,    RESET,   KC_PSCR, \
    _______, LAY_QWE, LAY_COL, M_NAME, _______, _______,_______, KC_PGUP, KC_HOME, KC_UP   , KC_END,  KC_DEL ,KC_INS ,           _______  ,  \
    _______, _______ , _______ , KC_LSHIFT, KC_LCTRL , KC_DEL ,_______ ,KC_PGDN ,  KC_LEFT ,KC_DOWN, KC_RIGHT, KC_BSPC ,_______  , _______,   KC_HOME, \
    _______, CTLZ ,CTLX , CTLC, CTLV,_______,KC_MPRV, KC_MPLY, KC_MNXT,  KC_VOLD, KC_MUTE,  KC_VOLU, _______, M_CD_DOT,    BL_INC,  \
    _______, _______, _______,                   KC_ENT ,                             _______, _______,   KC_APP, _______,  _______,    _______
  ),


  [_SWE] = LAYOUT_iso(
    _______, _______, _______, _______, _______, _______, _______,  _______,   _______, _______, _______, _______, _______,  _______, _______,  \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,_______, _______ , _______,           _______,  \
    _______, XP(SE_AA_L, SE_AA_H), XP(SE_AE_L, SE_AE_H), XP(SE_OE_L, SE_OE_H),   _______, _______,  _______, _______, _______, _______,  _______, _______,           _______,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, \
    _______, _______, _______,                   _______,                             _______,_______, _______, _______, _______, _______
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
          case COMM:    // , | <
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
            unregister_code16(KC_LSFT);  // Remove shift before sending the keycode
            register_code16(SE_LABK);
            register_code16(KC_LSFT);
        } else {
          register_code16(KC_COMM);
        }
      } else {
        unregister_code16(KC_GRV);
        unregister_code16(SE_LABK);
        unregister_code16(KC_COMM);
      }
      return false;
      break;

    case DOT:    // . | >
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
            register_code16(SE_RABK);
        } else {
          register_code16(KC_DOT);
        }
      } else {
        unregister_code16(KC_GRV);
        unregister_code16(SE_RABK);
        unregister_code16(KC_DOT);
      }
      return false;
      break;

    case SLSH:    // / | ?
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(KC_SE_QUES);
        } else {
          register_code16(KC_SE_SLSH);
        }
      } else {
        unregister_code16(KC_SE_QUES);
        unregister_code16(KC_SE_SLSH);
      }
      return false;
      break;

    case SCLN:    // ; | :
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(SE_COLN);
        } else {
          register_code16(SE_SCLN);
        }
      } else {
        unregister_code16(SE_COLN);
        unregister_code16(SE_SCLN);
      }
      return false;
      break;

    case QUOT:    // ' | "
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(SE_DQUO);
        } else {
          register_code16(SE_QUOT);
        }
      } else {
        unregister_code16(SE_DQUO);
        unregister_code16(SE_QUOT);
      }
      return false;
      break;
  case KC_SE_MYEQUAL:   // ' | "
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(KC_SE_PLUS);
        } else {
          register_code16(KC_SE_EQAL );
        }
      } else {
        unregister_code16(KC_SE_EQAL);
        unregister_code16(KC_SE_PLUS);
      }
      return false;
      break;
          }
    return true;
}
