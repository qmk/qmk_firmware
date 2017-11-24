#include "satan.h"
#include "rgblight.h"

#define _DEFAULT 0
#define _FN 1
#define _VIM 2

enum planck_keycodes {
  DEFAULT = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

// Fillers to make layering more clear
#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty gui/alt/space/alt/gui
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift    | VIM |
 * |-----------------------------------------------------------------------------------------+
 *         | FN  | LAlt  |               Space                | RAlt   |RGUI |
 *         `-----------------------------------------------------------------'
 */
  [_DEFAULT] = KEYMAP_HHKB( /* Basic QWERTY */
      KC_GESC , KC_1    , KC_2    , KC_3   , KC_4    , KC_5    , KC_6   , KC_7     , KC_8    , KC_9   , KC_0    , KC_MINS , KC_EQL   , KC_BSLS , KC_GRV , \
      KC_TAB  , KC_Q    , KC_W    , KC_E   , KC_R    , KC_T    , KC_Y   , KC_U     , KC_I    , KC_O   , KC_P    , KC_LBRC , KC_RBRC  , KC_BSPC , \
      KC_LCTL , KC_A    , KC_S    , KC_D   , KC_F    , KC_G    , KC_H   , KC_J     , KC_K    , KC_L   , KC_SCLN , KC_QUOT , KC_ENT   , \
      KC_LSFT , KC_Z    , KC_X    , KC_C   , KC_V    , KC_B    , KC_N   , KC_M     , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT , TO(_VIM) , \
      ______  , MO(_FN) , KC_LALT , KC_SPC , KC_RALT , KC_RGUI , ______ , ______ \
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * |GRAVE| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
 * |-----------------------------------------------------------------------------------------+
 * |  CAPS  | Vol-| Mute| Vol+|MAC+ |MAC  |MAC- | PgUp| Home|     |Print| Up  |     | Del    |
 * |-----------------------------------------------------------------------------------------+
 * |  Ctrl   | End |     | PgDn|     |     | Left| Down| Up  |Right| Left|Right|    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * |  Shift    | Prev| Play| Next| BL- | BL  | BL+ |     |     |     | Down| RShift    | DEF |
 * |-----------------------------------------------------------------------------------------+
 *         |       | LAlt  |             Space               | RAlt  | Reset |
 *         `-----------------------------------------------------------------'
 */
  [_FN] = KEYMAP_HHKB( /* Layer 1 */
      KC_GRAVE , KC_F1   , KC_F2   , KC_F3   , KC_F4          , KC_F5           , KC_F6        , KC_F7    , KC_F8   , KC_F9    , KC_F10  , KC_F11  , KC_F12       , KC_INS , KC_DEL , \
      KC_CAPS  , KC_VOLD , KC_MUTE , KC_VOLU , DYN_REC_START1 , DYN_MACRO_PLAY1 , DYN_REC_STOP , KC_PGUP  , KC_HOME , ______   , KC_PSCR , KC_UP   , ______       , KC_DEL , \
      KC_LCTL  , KC_END  , ______  , KC_PGDN , ______         , ______          , KC_LEFT      , KC_DOWN  , KC_UP   , KC_RIGHT , KC_LEFT , KC_RGHT , KC_ENT       , \
      KC_LSFT  , KC_MPRV , KC_MPLY , KC_MNXT , BL_DEC         , BL_TOGG         , BL_INC       , ______   , ______  , ______   , KC_DOWN , KC_RSFT , TO(_DEFAULT) , \
      ______   , ______  , KC_LALT , KC_SPC  , KC_RALT        , RESET           , ______       , ______ \
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
 * |-----------------------------------------------------------------------------------------+
 * |        | Vol-| Mute| Vol+|     |     |     | PgUp| Home|     |Print| Up  |     | Del    |
 * |-----------------------------------------------------------------------------------------+
 * |  Ctrl   | End |     | PgDn|     |     | Left| Down| Up  |Right| Left|Right|    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * |  Shift    | Prev| Play| Next| BL- | BL  | BL+ |     |     |     | Down| RShift    | Def |
 * |-----------------------------------------------------------------------------------------+
 *         |       | LAlt  |             Space               | RAlt  | Reset |
 *         `-----------------------------------------------------------------'
 */
  [_VIM] = KEYMAP_HHKB( /* Layer 2 */
      TO(_DEFAULT) , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7    , KC_F8   , KC_F9    , KC_F10  , KC_F11  , KC_F12       , KC_INS , KC_DEL , \
      ______       , KC_VOLD , KC_MUTE , KC_VOLU , ______  , ______  , ______  , KC_PGUP  , KC_HOME , ______   , KC_PSCR , KC_UP   , ______       , KC_DEL , \
      KC_LCTL      , KC_END  , ______  , KC_PGDN , ______  , ______  , KC_LEFT , KC_DOWN  , KC_UP   , KC_RIGHT , KC_LEFT , KC_RGHT , KC_ENT       , \
      KC_LSFT      , KC_MPRV , KC_MPLY , KC_MNXT , BL_DEC  , BL_TOGG , BL_INC  , ______   , ______  , ______   , KC_DOWN , KC_RSFT , TO(_DEFAULT) , \
      ______       , ______  , KC_LALT , KC_SPC  , KC_RALT , RESET   , ______  , ______ \
      ),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    return true;
}
