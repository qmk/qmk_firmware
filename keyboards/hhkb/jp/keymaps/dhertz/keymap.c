#include QMK_KEYBOARD_H
#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Del|Bsp|
     * |-----------------------------------------------------------|
     * |Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter |
     * |------------------------------------------------------`    |
     * |SrCtl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |
     * |-----------------------------------------------------------|
     * |Shift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  `|Up |Shi|
     * |-----------------------------------------------------------|
     * |NCt||  #|Alt|CmT|CmT|  LyrSpc |CGv|Iso|Gui|CSL||Rig|Dow|Lef|
     * `-----------------------------------------------------------'
     */
    [0] = LAYOUT_JP(
              KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL, KC_DEL,KC_BSPC,
              KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,
             SRCH_CTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,  KC_SCLN,KC_QUOT,KC_NUHS, KC_ENT,
              KC_LSFT,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT, KC_SLSH,KC_NUBS,  KC_UP,   KC_RSFT,
              NC_CTL, HSH_TLD,KC_LALT,CMD_TAB_CMD,CMD_TAB_CMD, LT(2, KC_SPC)  , CMD_GRV_CMD, ISO_COUNTRY_CODE,KC_RGUI, CMD_SFT_L, KC_LEFT,KC_DOWN,KC_RGHT
        ),

  /* Layer 1: iPad mode (Fixed)
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |------------------------------------------------------`    |
   * |CmdSpc|   |   |   |   |   |   |   |   |   |   |   |   |    |
   * |-----------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |   |   |
   * |-----------------------------------------------------------|
   * |   ||  ~|   |CAD|   |         |CmH|   |   |   ||   |   |   |
   * `-----------------------------------------------------------'
   */
  [1] = LAYOUT_JP(
            KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
            KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,
            CMD_SPC,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
            KC_TRNS,    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
            KC_TRNS,  KC_TRNS,KC_TRNS,CMD_ALT_D,KC_TRNS,      KC_TRNS      ,CMD_H,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS
  ),

  /* Layer 2: HHKB mode (Space)
   * ,-----------------------------------------------------------.
   * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
   * |-----------------------------------------------------------|
   * |Caps |DL0|DL1|   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
   * |------------------------------------------------------`    |
   * |      |VoD|VoU|Mut|   |   |   |Bsp|Del|CSL|Lef|Rig|   |    |
   * |-----------------------------------------------------------|
   * |       |   |   |CAC|   |   |   |   |   |   |Dow|   |PgU|   |
   * |-----------------------------------------------------------|
   * |   ||  ~|   |   |   |         |   |   |   |   ||Hom|PgD|End|
   * `-----------------------------------------------------------'
   */
  [2] = LAYOUT_JP(
            KC_PWR,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12, KC_INS,KC_DEL,
            KC_CAPS,  DF(0),  DF(1),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS,  KC_UP,KC_TRNS,
            KC_TRNS,   KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,KC_TRNS,KC_TRNS,KC_BSPC, KC_DEL,CMD_SFT_L,KC_LEFT,KC_RGHT,KC_TRNS,KC_PENT,
            KC_TRNS,    KC_TRNS,KC_TRNS,CMD_ALT_C,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_DOWN,KC_TRNS,KC_PGUP,KC_TRNS,
            KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS      ,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_HOME,KC_PGDN, KC_END
  ),
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CMD_SPC:
            mod_or_mod_with_macro(record, KC_LGUI, " ");
            break;
        case CMD_H:
            mod_or_mod_with_macro(record, KC_RGUI, "H");
            break;
        case CMD_ALT_D:
            mod_or_mod_with_macro(record, KC_LGUI, SS_LALT("D"));
            break;
        default:
            return true;
    }
    return false;
}
