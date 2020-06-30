
#include QMK_KEYBOARD_H
#include "keymap_hungarian.h"

enum preonic_layers {
  _QWERTY,
  _SHIFT,
  _LOWER,
  _SHIFTED_LOWER,
  _RAISE,
  _SHIFTED_RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  SHIFT,
  LOWER,
  RAISE,
};

enum {
  TD_A_AA,
  TD_S_A_AA,
  TD_E_EE,
  TD_S_E_EE,
  TD_I_II,
  TD_S_I_II,
  TD_O_OO,
  TD_S_O_OO,
  TD_OE_OEE,
  TD_S_OE_OEE,
  TD_U_UU,
  TD_S_U_UU,
  TD_UE_UEE,
  TD_S_UE_UEE,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_A_AA]     = ACTION_TAP_DANCE_DOUBLE(HU_A, HU_AA),
  [TD_S_A_AA]   = ACTION_TAP_DANCE_DOUBLE(S(HU_A), S(HU_AA)),
  [TD_E_EE]     = ACTION_TAP_DANCE_DOUBLE(HU_E, HU_EE),
  [TD_S_E_EE]   = ACTION_TAP_DANCE_DOUBLE(S(HU_E), S(HU_EE)),
  [TD_I_II]     = ACTION_TAP_DANCE_DOUBLE(HU_I, HU_II),
  [TD_S_I_II]   = ACTION_TAP_DANCE_DOUBLE(S(HU_I), S(HU_II)),
  [TD_O_OO]     = ACTION_TAP_DANCE_DOUBLE(HU_O, HU_OO),
  [TD_S_O_OO]   = ACTION_TAP_DANCE_DOUBLE(S(HU_O), S(HU_OO)),
  [TD_OE_OEE]   = ACTION_TAP_DANCE_DOUBLE(HU_OE, HU_OEE),
  [TD_S_OE_OEE] = ACTION_TAP_DANCE_DOUBLE(S(HU_OE), S(HU_OEE)),
  [TD_U_UU]     = ACTION_TAP_DANCE_DOUBLE(HU_U, HU_UU),
  [TD_S_U_UU]   = ACTION_TAP_DANCE_DOUBLE(S(HU_U), S(HU_UU)),
  [TD_UE_UEE]   = ACTION_TAP_DANCE_DOUBLE(HU_UE, HU_UEE),
  [TD_S_UE_UEE] = ACTION_TAP_DANCE_DOUBLE(S(HU_UE), S(HU_UEE)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   =  |   '  | GUI  | Alt  |Lower |    Space    |Raise |   -  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_ESC,   HU_1,        HU_2,    HU_3,        HU_4,    HU_5,    HU_6,    HU_7,        HU_8,        HU_9,        HU_0,    KC_BSPC, \
  KC_TAB,   HU_Q,        HU_W,    TD(TD_E_EE), HU_R,    HU_T,    HU_Z,    TD(TD_U_UU), TD(TD_I_II), TD(TD_O_OO), HU_P,    HU_BSLS, \
  KC_LCTL,  TD(TD_A_AA), HU_S,    HU_D,        HU_F,    HU_G,    HU_H,    HU_J,        HU_K,        HU_L,        HU_SCLN, KC_ENT,  \
  SHIFT,    HU_Y,        HU_X,    HU_C,        HU_V,    HU_B,    HU_N,    HU_M,        HU_COMM,     HU_DOT,      KC_UP,   HU_SLSH, \
  HU_EQL,   HU_QUOT,     KC_LGUI, KC_LALT,     LOWER,   KC_SPC,  KC_SPC,  RAISE,       HU_MINS,     KC_LEFT,     KC_DOWN, KC_RGHT  \
),

/* Shift
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   :  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   <  |   >  |  Up  |  ?   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   +  |   "  | GUI  | Alt  |Lower |    Space    |Raise |   _  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
@ */
[_SHIFT] = LAYOUT_preonic_grid( \
  S(KC_ESC),  HU_EXLM,      HU_AT,      HU_HASH,      HU_DLR,  HU_PERC,  HU_CIRC,    HU_AMPR,      HU_ASTR,      HU_LPRN,       HU_RPRN,    S(KC_BSPC), \
  S(KC_TAB),  S(HU_Q),      S(HU_W),    TD(TD_S_E_EE),S(HU_R), S(HU_T),  S(HU_Z),    TD(TD_S_U_UU),TD(TD_S_I_II),TD(TD_S_O_OO), S(HU_P),    HU_PIPE,    \
  S(KC_LCTL), TD(TD_S_A_AA),S(HU_S),    S(HU_D),      S(HU_F), S(HU_G),  S(HU_H),    S(HU_J),      S(HU_K),      S(HU_L),       HU_COLN,    S(KC_ENT),  \
  SHIFT,      S(HU_Y),      S(HU_X),    S(HU_C),      S(HU_V), S(HU_B),  S(HU_N),    S(HU_M),      HU_LESS,      HU_MORE,       S(KC_UP),   HU_QST,     \
  HU_PLUS,    HU_DQOT,      S(KC_LGUI), S(KC_LALT),   LOWER,   S(KC_SPC), S(KC_SPC), RAISE,        HU_UNDS,      S(KC_LEFT),    S(KC_DOWN), S(KC_RGHT) \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  HU_TILD, HU_EXLM, HU_AT,   HU_HASH, HU_DLR,  HU_PERC, HU_CIRC, HU_AMPR,   HU_ASTR,   HU_LPRN, HU_RPRN, KC_DEL,  \
  HU_TILD, HU_EXLM, HU_AT,   HU_HASH, HU_DLR,  HU_PERC, HU_CIRC, HU_AMPR,   HU_ASTR,   HU_LPRN, HU_RPRN, KC_DEL,  \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   HU_UNDS,   HU_PLUS,   HU_LCBR, HU_RCBR, HU_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,   KC_MNXT,   KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Lower + Shift
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_SHIFTED_LOWER] = LAYOUT_preonic_grid( \
  HU_TILD,   HU_EXLM,  HU_AT,    HU_HASH,  HU_DLR,    HU_PERC,   HU_CIRC,   HU_AMPR, HU_ASTR, HU_LPRN, HU_RPRN, S(KC_DEL), \
  HU_TILD,   HU_EXLM,  HU_AT,    HU_HASH,  HU_DLR,    HU_PERC,   HU_CIRC,   HU_AMPR, HU_ASTR, HU_LPRN, HU_RPRN, S(KC_DEL), \
  S(KC_DEL), S(KC_F1), S(KC_F2), S(KC_F3), S(KC_F4),  S(KC_F5),  S(KC_F6),  HU_UNDS, HU_PLUS, HU_LCBR, HU_RCBR, HU_PIPE,   \
  _______,   S(KC_F7), S(KC_F8), S(KC_F9), S(KC_F10), S(KC_F11), S(KC_F12), KC_NUHS, KC_NUBS, _______, _______, _______,   \
  _______,   _______,  _______,  _______,  _______,   _______,   _______,   _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY    \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   U  |   8  |   O  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | Ins  | PgUp | PrSc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  HU_GRV,  HU_1,    HU_2,    HU_3,    HU_4,    HU_5,    HU_6,    HU_7,          HU_8,    HU_9,          HU_0,    KC_DEL,     \
  HU_GRV,  HU_1,    HU_2,    HU_3,    HU_4,    HU_5,    HU_6,    TD(TD_UE_UEE), HU_8,    TD(TD_OE_OEE), HU_0,    KC_DEL,     \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   HU_MINS,       HU_EQL,  HU_LBRC,       HU_RBRC, HU_BSLS,    \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS,       KC_NUBS, KC_INSERT,     KC_PGUP, KC_PSCREEN, \
  _______, _______, _______, _______, _______, _______, _______, _______,       _______, KC_HOME,       KC_PGDN, KC_END      \
),

/* Raise + Shift
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   U  |   8  |   O  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | Ins  | PgUp | PrSc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_SHIFTED_RAISE] = LAYOUT_preonic_grid( \
  HU_GRV,    S(HU_1),  S(HU_2),  S(HU_3),  S(HU_4),   S(HU_5),   S(HU_6),   S(HU_7),         S(HU_8), S(HU_9),         S(HU_0),    S(KC_DEL),     \
  HU_GRV,    S(HU_1),  S(HU_2),  S(HU_3),  S(HU_4),   S(HU_5),   S(HU_6),   TD(TD_S_UE_UEE), S(HU_8), TD(TD_S_OE_OEE), S(HU_0),    S(KC_DEL),     \
  S(KC_DEL), S(KC_F1), S(KC_F2), S(KC_F3), S(KC_F4),  S(KC_F5),  S(KC_F6),  HU_MINS,         HU_EQL,  HU_LBRC,         HU_RBRC,    HU_BSLS,       \
  _______,   S(KC_F7), S(KC_F8), S(KC_F9), S(KC_F10), S(KC_F11), S(KC_F12), KC_NUHS,         KC_NUBS, S(KC_INSERT),    S(KC_PGUP), S(KC_PSCREEN), \
  _______,   _______,  _______,  _______,  _______,   _______,   _______,   _______,         _______, S(KC_HOME),      S(KC_PGDN), S(KC_END)      \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case SHIFT:
          if (record->event.pressed) {
            layer_on(_SHIFT);
          } else {
            layer_off(_SHIFT);
          }
          update_tri_layer(_SHIFT, _RAISE, _SHIFTED_RAISE);
          update_tri_layer(_SHIFT, _LOWER, _SHIFTED_LOWER);
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
          } else {
            layer_off(_LOWER);
          }
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
          update_tri_layer(_SHIFT, _LOWER, _SHIFTED_LOWER);
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
          } else {
            layer_off(_RAISE);
          }
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
          update_tri_layer(_SHIFT, _RAISE, _SHIFTED_RAISE);
          return false;
          break;
      }
    return true;
};
