#include QMK_KEYBOARD_H
#include "rgblight.h"

#define _DEFAULT 0
#define _FN 1
#define _VIM 10
#define _VIM_SHIFT 11
#define _VIM_CONTROL 12

enum custom_keycodes {
  DYNAMIC_MACRO_RANGE = SAFE_RANGE,
  a_MACRO,
  A_MACRO,
  I_MACRO,
  O_MACRO,
};

#define KC_PREV_WORD LCTL(KC_LEFT)
#define KC_NEXT_WORD LCTL(KC_RIGHT)
#define KC_UNDO LCTL(KC_Z)
#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)

#include "dynamic_macro.h"

static uint8_t old_layer = 0;

// Fillers to make layering more clear
#define ______ KC_TRNS
#define XXXXXX KC_NO

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
  [_DEFAULT] = LAYOUT_60_ansi_split_bs_rshift( /* Basic QWERTY */
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
  [_FN] = LAYOUT_60_ansi_split_bs_rshift( /* Layer 2 */
      KC_GRAVE , KC_F1   , KC_F2   , KC_F3   , KC_F4          , KC_F5           , KC_F6        , KC_F7    , KC_F8   , KC_F9    , KC_F10  , KC_F11  , KC_F12       , KC_INS , KC_DEL , \
      KC_CAPS  , KC_VOLD , KC_MUTE , KC_VOLU , DYN_REC_START1 , DYN_MACRO_PLAY1 , DYN_REC_STOP , KC_PGUP  , KC_HOME , ______   , KC_PSCR , KC_UP   , ______       , KC_DEL , \
      KC_LCTL  , KC_END  , ______  , KC_PGDN , ______         , ______          , KC_LEFT      , KC_DOWN  , KC_UP   , KC_RIGHT , KC_LEFT , KC_RGHT , KC_ENT       , \
      KC_LSFT  , KC_MPRV , KC_MPLY , KC_MNXT , BL_DEC         , BL_TOGG         , BL_INC       , ______   , ______  , ______   , KC_DOWN , KC_RSFT , TO(_DEFAULT) , \
      ______   , ______  , KC_LALT , KC_SPC  , KC_RALT        , QK_BOOT           , ______       , ______ \
      ),

/* VIM Layer
 * ,-----------------------------------------------------------------------------------------.
 * | DEF |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * |        |     | WORD| WORD|     |     | COPY| UNDO| DEF |ENTER|PASTE|     |     | Del    |
 * |-----------------------------------------------------------------------------------------+
 * | V_Ctrl  |a_ins|     |     |     |     | Left| Down| Up  |Right|     |     |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * |  V_Shift  |     |     |     |     | PREV|     |     |     |     |     | RShift    | Def |
 * |-----------------------------------------------------------------------------------------+
 *         |       | LAlt  |             Space               | RAlt  |       |
 *         `-----------------------------------------------------------------'
 */
  [_VIM] = LAYOUT_60_ansi_split_bs_rshift( /* Layer 10 */
      TO(_DEFAULT)     , KC_1    , KC_2         , KC_3         , KC_4    , KC_5         , KC_6    , KC_7     , KC_8         , KC_9     , KC_0     , KC_MINS , KC_EQL       , KC_BSLS , KC_GRV , \
      XXXXXX           , XXXXXX  , KC_NEXT_WORD , KC_NEXT_WORD , XXXXXX  , XXXXXX       , KC_COPY , KC_UNDO  , TO(_DEFAULT) , KC_ENTER , KC_PASTE , XXXXXX  , XXXXXX       , KC_DEL  , \
      MO(_VIM_CONTROL) , a_MACRO , XXXXXX       , XXXXXX       , XXXXXX  , XXXXXX       , KC_LEFT , KC_DOWN  , KC_UP        , KC_RIGHT , XXXXXX   , XXXXXX  , KC_ENTER     , \
      MO(_VIM_SHIFT)   , XXXXXX  , XXXXXX       , XXXXXX       , XXXXXX  , KC_PREV_WORD , XXXXXX  , XXXXXX   , XXXXXX       , XXXXXX   , XXXXXX   , KC_RSFT , TO(_DEFAULT) , \
      XXXXXX           , XXXXXX  , KC_LALT      , KC_SPC       , KC_RALT , XXXXXX       , XXXXXX  , XXXXXX \
      ),

/* VIM Layer
 * ,-----------------------------------------------------------------------------------------.
 * | DEF |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * |        |     | WORD| WORD|     |     |     |     |I_ins|ENTER|     |     |     | Del    |
 * |-----------------------------------------------------------------------------------------+
 * |         |A_ins|     |     |     |     | Left| Down| Up  |Right|     |     |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     | PREV|     |     |     |     |     | RShift    | Def |
 * |-----------------------------------------------------------------------------------------+
 *         |       | LAlt  |             Space               | RAlt  |       |
 *         `-----------------------------------------------------------------'
 */
  [_VIM_SHIFT] = LAYOUT_60_ansi_split_bs_rshift( /* Layer 11 */
      TO(_DEFAULT) , KC_1    , KC_2         , KC_3         , KC_4    , KC_5         , KC_6    , KC_7     , KC_8    , KC_9     , KC_0   , KC_MINS , KC_EQL       , KC_BSLS , KC_GRV , \
      XXXXXX       , XXXXXX  , KC_NEXT_WORD , KC_NEXT_WORD , XXXXXX  , XXXXXX       , XXXXXX  , XXXXXX   , I_MACRO , O_MACRO  , XXXXXX , XXXXXX  , XXXXXX       , KC_DEL  , \
      XXXXXX       , A_MACRO , XXXXXX       , KC_PGDN      , XXXXXX  , XXXXXX       , KC_LEFT , KC_DOWN  , KC_UP   , KC_RIGHT , XXXXXX , XXXXXX  , KC_ENTER     , \
      XXXXXX       , XXXXXX  , XXXXXX       , XXXXXX       , XXXXXX  , KC_PREV_WORD , XXXXXX  , XXXXXX   , XXXXXX  , XXXXXX   , XXXXXX , KC_RSFT , TO(_DEFAULT) , \
      XXXXXX       , XXXXXX  , KC_LALT      , KC_SPC       , KC_RALT , QK_BOOT        , XXXXXX  , XXXXXX \
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
 * |-----------------------------------------------------------------------------------------+
 * |        | Vol-| Mute| Vol+|     |     |     | PgUp| Ins |     |Print| Up  |     | Del    |
 * |-----------------------------------------------------------------------------------------+
 * |  Ctrl   | App |     | PgDn|     |     | Left| Down| Up  |Right| Left|Right|    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * |  Shift    | Prev| Play| Next| BL- | BL  | BL+ |     |     |     | Down| RShift    | Def |
 * |-----------------------------------------------------------------------------------------+
 *         |       | LAlt  |             Space               | RAlt  | Reset |
 *         `-----------------------------------------------------------------'
 */
  [_VIM_CONTROL] = LAYOUT_60_ansi_split_bs_rshift( /* Layer 12 */
      TO(_DEFAULT) , KC_1    , KC_2         , KC_3         , KC_4    , KC_5         , KC_6    , KC_7     , KC_8    , KC_9     , KC_0   , KC_MINS , KC_EQL       , KC_BSLS , KC_GRV , \
      XXXXXX       , XXXXXX  , KC_NEXT_WORD , KC_NEXT_WORD , XXXXXX  , XXXXXX       , XXXXXX  , XXXXXX   , I_MACRO , O_MACRO  , XXXXXX , XXXXXX  , XXXXXX       , KC_DEL  , \
      XXXXXX       , A_MACRO , XXXXXX       , KC_PGDN      , XXXXXX  , XXXXXX       , KC_LEFT , KC_DOWN  , KC_UP   , KC_RIGHT , XXXXXX , XXXXXX  , KC_ENTER     , \
      XXXXXX       , XXXXXX  , XXXXXX       , XXXXXX       , XXXXXX  , KC_PREV_WORD , XXXXXX  , XXXXXX   , XXXXXX  , XXXXXX   , XXXXXX , KC_RSFT , TO(_DEFAULT) , \
      XXXXXX       , XXXXXX  , KC_LALT      , KC_SPC       , KC_RALT , QK_BOOT        , XXXXXX  , XXXXXX \
      )            ,
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    if (record->event.pressed) {
        switch(keycode) {
            case a_MACRO:
                SEND_STRING(SS_TAP(X_RIGHT));
                layer_off(_VIM);
                return false;
                break;
            case A_MACRO:
                SEND_STRING(SS_TAP(X_END));
                layer_off(_VIM_SHIFT);
                layer_off(_VIM);
                return false;
                break;
            case I_MACRO:
                SEND_STRING(SS_TAP(X_HOME));
                layer_off(_VIM_SHIFT);
                layer_off(_VIM);
                return false;
                break;
            case O_MACRO:
                SEND_STRING(SS_TAP(X_ENTER));
                layer_off(_VIM_SHIFT);
                layer_off(_VIM);
                return false;
                break;
        }
    }
    return true;
}

void matrix_scan_user(void) {
  uint8_t layer = get_highest_layer(layer_state);

  if (old_layer != layer) {
    switch (layer) {
      case _DEFAULT:
      case _FN:
        backlight_set(1);
      break;
      case _VIM:
      case _VIM_SHIFT:
      case _VIM_CONTROL:
        backlight_set(4);
      break;
    }
    old_layer = layer;
  }
};
