/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum {
    _ALPHA,     // default (Colemak DHm)
    _SPECIAL,   // special characters
    _NUMBERS    // numbers/function/motion
};

// alpha hold modifiers
#define KC_CTL_A  MT(MOD_LCTL, KC_A)     // Tap for A, hold for Control
#define KC_CTL_O  MT(MOD_RCTL, KC_O)     // Tap for colon, hold for Control
#define KC_SFT_Z  MT(MOD_LSFT, KC_Z)     // Tap for Z, hold for Shift
#define KC_SFT_SL MT(MOD_RSFT, KC_SLSH)  // Tap for slash, hold for Shift

// thumb modifiers/toggles
#define KC_GUI_ESC MT(MOD_LGUI, KC_ESC)  // Tap for Esc, hold for GUI (Meta, Command, Win)
#define KC_ALT_ENT MT(MOD_LALT, KC_ENT)  // Tap for Enter, hold for Alt (Option)
#define KC_SPE_SPC LT(_SPECIAL, KC_SPC)  // Tap for Space, hold for Special layer
#define KC_NUM_SPC LT(_NUMBERS, KC_SPC)  // Tap for Space, hold for Numbers layer
#define KC_SFT_TAB MT(MOD_RSFT, KC_TAB)  // Tap for Tab, hold for Right Shift

    /* Combomap
     *
     * ,-------------------------------.      ,-------------------------------.
     * |       |    ESC    |     |     |      |     |    ESC    |     \       |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |       |   BSPC   TAB    |     |      |     <     :     >     |       |
     * |-------+-----+-----+-RMB-+-LMB-|      |ENTER+-----+-----+-----+-------|
     * |       |     -   ENTER   |     |      |     '     _     |     |       |
     * `-------------------------------'      `-------------------------------'
     *            .-----------------.            .-----------------.
     *            |     |     |     |            |     |     |     |
     *            '-----------------'            '-----------------'
     */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Alpha layer / Colemak DHm
     *
     * ,-------------------------------.      ,-------------------------------.
     * |     Q |  W  |  F  |  P  |  B  |      |  J  |  L  |  U  |  Y  |   ;   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * | CTRL A|  R  |  S  |  T  |  G  |      |  M  |  N  |  E  |  I  |   O   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * | SHFT Z|  X  |  C  |  D  |  V  |      |  K  |  H  |  <  |  >  |SHFT / |
     * `-------------------------------'      `-------------------------------'
     *   .------------------------------.    .----------------------.
     *   | ESC META | ENT ALT | SPC SPE |    | SPC NUM | SHFT | TAB |
     *   '------------------------------'    '----------------------'
     */
    [_ALPHA] = LAYOUT_split_3x5_3(
         KC_Q,     KC_W,   KC_F,   KC_P,   KC_B,          KC_J,   KC_L,   KC_U,     KC_Y,   KC_SCLN,
         KC_CTL_A, KC_R,   KC_S,   KC_T,   KC_G,          KC_M,   KC_N,   KC_E,     KC_I,   KC_CTL_O,
         KC_SFT_Z, KC_X,   KC_C,   KC_D,   KC_V,          KC_K,   KC_H,   KC_COMMA, KC_DOT, KC_SFT_SL,
             KC_GUI_ESC, KC_ALT_ENT, KC_SPE_SPC,          KC_NUM_SPC, KC_LSFT, KC_SFT_TAB),

    /* Keymap 1: Special characters layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |    !  |  @  |  {  |  }  |  |  |      |  `  |  ~  |     |     |   \   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    #  |  $  |  (  |  )  | RMB |      |  +  |  -  |  /  |  *  |   '   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    %  |  ^  |  [  |  ]  | LMB |      |  &  |  =  |  ,  |  .  |   -   |
     * `-------------------------------'      `-------------------------------'
     *     .-------------------------.          .-----------------.
     *     | ComboToggle |  ;  |  =  |          |  =  |  ;  | DEL |
     *     '-------------------------'          '-----------------'
     */
    [_SPECIAL] = LAYOUT_split_3x5_3(
         KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,          KC_GRV,  KC_TILD, KC_TRNS, KC_TRNS, KC_BSLS,
         KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_BTN2,          KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_QUOT,
         KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BTN1,          KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_MINS,
                            CM_TOGG, KC_SCLN, KC_EQL,          KC_EQL, KC_SCLN, KC_DEL),

    /* Keymap 2: Numbers/Function/Motion layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |   1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F1   | F2  | F3  | F4  | F5  |      | LFT | DWN | UP  | RGT | VOLUP |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F6   | F7  | F8  | F9  | F10 |      | MLFT| MDWN| MUP | MRGT| VOLDN |
     * `-------------------------------'      `-------------------------------'
     *             .-----------------.          .-----------------.
     *             | F11 | F12 |     |          |     | PLY | SKP |
     *             '-----------------'          '-----------------'
     */
    [_NUMBERS] = LAYOUT_split_3x5_3(
         KC_1,  KC_2,  KC_3,  KC_4,  KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
         KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU,
         KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD,
                    KC_F11, KC_F12, KC_TRNS,         KC_TRNS,  KC_MPLY,  KC_MNXT)
};
