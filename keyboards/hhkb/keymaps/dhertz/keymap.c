#include "hhkb.h"
#include "dhertz.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Del|Bsp|
     * |-----------------------------------------------------------|
     * |Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter |
     * |------------------------------------------------------`    |
     * |Fn5   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |
     * |-----------------------------------------------------------|
     * |Shift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  `|Up |Shi|
     * |-----------------------------------------------------------|
     * |Fn2||  #|Gui|Alt|Fn6|   Fn0   |Fn7|Fn8|Gui|Fn3||Rig|Dow|Lef|
     * `-----------------------------------------------------------'
     */
    [0] = LAYOUT_JP(
              KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL, KC_DEL,KC_BSPC,
              KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,
        CTL_T(KC_F19),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,  KC_SCLN,KC_QUOT,KC_NUHS, KC_ENT,
              KC_LSFT,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT, KC_SLSH,KC_NUBS,  KC_UP,   KC_RSFT,
        CTL_T(KC_F18),  HSH_TLD,KC_LALT,KC_FN0, KC_FN0,  LT(1, KC_SPC) , KC_FN1, ISO_COUNTRY_CODE,KC_RGUI, CMD_SFT_L, KC_LEFT,KC_DOWN,KC_RGHT
        ),

  /* Layer 1: HHKB mode (Space)
   * ,-----------------------------------------------------------.
   * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
   * |-----------------------------------------------------------|
   * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
   * |------------------------------------------------------`    |
   * |      |VoD|VoU|Mut|   |   |   |Bsp|Del|Fn10|Lef|Rig|   |   |
   * |-----------------------------------------------------------|
   * |       |   |   |Fn9|   |   |   |   |   |   |Dow|   |PgU|   |
   * |-----------------------------------------------------------|
   * |   ||  ~|   |   |   |         |   |   |   |   ||Hom|PgD|End|
   * `-----------------------------------------------------------'
   */
  [1] = LAYOUT_JP(
            KC_PWR,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12, KC_INS,KC_DEL,
            KC_CAPS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS,  KC_UP,KC_TRNS,
            KC_TRNS,   KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,KC_TRNS,KC_TRNS,KC_BSPC, KC_DEL,CMD_SFT_L,KC_LEFT,KC_RGHT,KC_TRNS,KC_PENT,
            KC_TRNS,    KC_TRNS,KC_TRNS,CMD_ALT_C,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_DOWN,KC_TRNS,KC_PGUP,KC_TRNS,
            KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS      ,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_HOME,KC_PGDN, KC_END
  ),
};
