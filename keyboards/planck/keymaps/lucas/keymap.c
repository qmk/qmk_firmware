/* 
This is the keymap of /u/deepshitgoeshere!
Layer 1 exists so I can have the symbol positions of QWERTY while having my system in german.
The second layer has all the german umlauts I need and with capital and small letters on the 
same layer there is no need to press shift+lower.
This keymap is made to work with software implemented QWERTZ.
The "Gaming" layer is mainly customized for CS:GO.
If you have any question about this keymap feel free to shoot me a message on reddit!
*/

#include QMK_KEYBOARD_H
#include "keymap_german.h"

#define LT_SPC LT(4, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_planck_grid( /* Colemak   
    * ,-----------------------------------------------------------------------.
    * | Esc | q   | w   | f   | p   | g   | j   | l   | u   | y   | ;   |  -  |
    * |-----------------------------------------------------------------------|
    * | BS  | a   | r   | s   | t   | d   | h   | n   | e   | i   | o   |  '  |
    * |-----------------------------------------------------------------------|
    * | SFT | z   | x   | c   | v   | b   | k   | m   |  ,  |  .  |  /  | Ent |
    * |-----------------------------------------------------------------------|
    * | CTL | GUI | Tab | ALT |Lower|   Space   |Raise|Left |Down | Up  |Right|
    * `-----------------------------------------------------------------------'
    */
  KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Z,    DE_SCLN, DE_MINS,
  KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    DE_QUOT,
  M(0),    KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    DE_COMM, DE_DOT,  DE_SLSH, KC_ENT,
  KC_LCTL, KC_LGUI, KC_TAB,  KC_LALT, MO(3),   LT_SPC,  LT_SPC,  MO(2),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
[1] = LAYOUT_planck_grid( /* Symbols
    * ,-----------------------------------------------------------------------.
    * |     |     |     |     |     |     |     |     |     |     |  :  |     |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |  "  |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |  <  |  >  |  ?  |     |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |           |     |     |     |     |     |
    * `-----------------------------------------------------------------------'
    */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_DOT,  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_DQOT,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(1),    DE_MORE, DE_QST,  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
[2] = LAYOUT_planck_grid( /* Raise
    * ,-----------------------------------------------------------------------.
    * |     |  Ä  |     |     |     |     |     |     |  Ü  |  Ö  |     |Game |
    * |-----------------------------------------------------------------------|
    * | Del |  ä  |     |  ß  |     |     |     |     |  ü  |  ö  |     |FVol+|
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |Stop | Prv | Nxt |FVol-|
    * |-----------------------------------------------------------------------|
    * |LCTL |LGUI | Tab |LALT |Lower|   Space   |     |Mute |Vol- |Vol+ | P/P |
    * `-----------------------------------------------------------------------'
    */
  KC_NO,   S(DE_AE), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   S(DE_UE), S(DE_OE), KC_NO,   TG(5),
  KC_DEL,  DE_AE,    KC_NO,   DE_SS,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   DE_UE,    DE_OE,    KC_NO,   RALT(KC_F12),
  KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_MSTP,  KC_MPRV,  KC_MNXT, RALT(KC_F11),
  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_MUTE,  KC_VOLD,  KC_VOLU, KC_MPLY
),
[3] = LAYOUT_planck_grid( /* Lower 
    * ,-----------------------------------------------------------------------.
    * |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  +  |
    * |-----------------------------------------------------------------------| 
    * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  =  |
    * |-----------------------------------------------------------------------|
    * |     |     |     |  |  |  [  |  ]  |  {  |  }  |  €  |     |  \  | Ent |
    * |-----------------------------------------------------------------------|
    * |LCTL |LGUI | Tab |LALT |     |   Space   |Raise|Home |PgDn |PgUp | End |
    * `-----------------------------------------------------------------------'
    */
  DE_TILD, DE_EXLM, DE_AT,   DE_HASH, DE_DLR,  DE_PERC, DE_CIRC,  DE_AMPR, DE_ASTR, DE_LPRN, DE_RPRN, DE_PLUS,
  DE_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    DE_EQL,
  KC_NO,   KC_NO,   KC_NO,   DE_PIPE, DE_LBRC, DE_RBRC, DE_LCBR,  DE_RCBR, DE_EURO, KC_NO,   DE_BSLS, KC_ENT,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),
[4] = LAYOUT_planck_grid( /* Function
    * ,-----------------------------------------------------------------------.
    * | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 | F21 | F22 | F23 | F24 |
    * |-----------------------------------------------------------------------|
    * | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     | KP- | KP+ |     |     |     |     |Reset| 
    * |-----------------------------------------------------------------------|
    * |     |Light|BL DN|BL UP|     |     |     |     |Mute |Vol- |Vol+ | P/P | 
    * `-----------------------------------------------------------------------'
    */
  KC_F13, KC_F14,  KC_F15, KC_F16, KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
  KC_F1,  KC_F2,   KC_F3,  KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_NO,  KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_PMNS, KC_PPLS, KC_NO,   KC_NO,   KC_NO,   RESET,   KC_NO,
  KC_NO,  BL_TOGG, BL_DEC, BL_INC, MO(3),   KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY
),
[5] = LAYOUT_planck_grid( /* Gaming
    * ,-----------------------------------------------------------------------.
    * | Buy | ESC | q   | w   | e   | r   | t   | y   | u   | i   | o   |  p  |
    * |-----------------------------------------------------------------------|
    * | ENT | BS  | a   | s   | d   | f   | g   | h   | j   | k   | l   |  ;  |
    * |-----------------------------------------------------------------------|
    * | CTL | SFT | z   | x   | c   | v   | b   | n   |  m  |  ,  | Up  |  /  |
    * |-----------------------------------------------------------------------|
    * |     |     | Tab | ALT |     |   Space   |CrJmp| GUI |Left |Down |Right|
    * `-----------------------------------------------------------------------'
    */
  MO(6),   KC_ESC,  KC_Q,   KC_W,    KC_E,  KC_R,   KC_T,   KC_Z,         KC_U,    KC_I,    KC_O,    TG(5),
  KC_ENT,  KC_BSPC, KC_A,   KC_S,    KC_D,  KC_F,   KC_G,   KC_H,         KC_J,    KC_K,    KC_L,    DE_SCLN,
  KC_LCTL, KC_LSFT, KC_Y,   KC_X,    KC_C,  KC_V,   KC_B,   KC_N,         KC_M,    DE_DOT,  KC_UP,   DE_SLSH,
  KC_NO,   KC_NO,   KC_TAB, KC_LALT, KC_NO, KC_SPC, KC_SPC, LCTL(KC_SPC), KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT
),
[6] = LAYOUT_planck_grid( /* Gaming 
         * CS:GO buy binds
    * ,-----------------------------------------------------------------------.
    * |     |     |     |     |     |     |     |     |  7  |  8  |  9  |     |
    * |-----------------------------------------------------------------------|
    * | BS  |     |     |     |     |     |     |     |  6  |  5  |  4  | End |
    * |-----------------------------------------------------------------------|
    * | CTL | SFT |     |     |     |     |     |     |  1  |  2  |  3  |Pgdn |
    * |-----------------------------------------------------------------------|
    * |     |     | Tab | ALT |     |   Space   |CrJmp|     |  0  | KP+ |PEnt |
    * `-----------------------------------------------------------------------'
    */
  KC_TRNS, KC_NO,   KC_Q,   KC_W,    KC_F,  KC_P,   KC_G,   KC_J,         KC_P7, KC_P8, KC_P9,   KC_NO,
  KC_BSPC, KC_NO,   KC_A,   KC_R,    KC_S,  KC_T,   KC_D,   KC_H,         KC_P4, KC_P5, KC_P6,   KC_END,
  KC_LCTL, KC_LSFT, KC_Y,   KC_X,    KC_C,  KC_V,   KC_B,   KC_K,         KC_P1, KC_P2, KC_P3,   KC_PGDN,
  KC_NO,   KC_NO,   KC_TAB, KC_LALT, KC_NO, KC_SPC, KC_SPC, LCTL(KC_SPC), KC_NO, KC_P0, KC_PDOT, KC_PENT
),
};

const uint16_t PROGMEM fn_actions[] = {
	[5] = ACTION_MODS_TAP_KEY(KC_LSFT, KC_CAPS),  //Shift on press, Caps on tap
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  switch(id) {
    case 0: // M(0)
        if (record->event.pressed) {
            register_code(KC_LSFT);
            layer_on(1);
        } else {
            layer_off(1);
            unregister_code(KC_LSFT);
        }
        break;       
    case 1: // M(1)
        if (record->event.pressed) {
            unregister_code(KC_LSFT);
            register_code(DE_LESS);
        } else {
            unregister_code(DE_LESS);
        }
        break;    
  }
  return MACRO_NONE;

};          
