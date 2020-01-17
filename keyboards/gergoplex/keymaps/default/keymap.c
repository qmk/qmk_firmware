/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion

// Combos
enum combos {
	WE,AS,SD,DF,XC,OP,CV,
	UI,HJ,JK,KL,MC,NM,
	FV,GB,HN,
	SDJK
};

// NOTE: If you're using MT,LT or anything you must 
// define it here. Note this if you change your layout!
/* Keymap 0: Basic layer
 *
 * ,-----------------------------.       ,--------------------------------.
 * |      |    ESC    |     |     |      |     |    ESC    |    BSLH      |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |      |   BSPC   ENT    |     |      |    LES   COLN  GRT    |        | 
 * |-----+-----+-----+--RMB+-LMB--+		   |--------------------------------|
 * |      |   MINS    |     |     |      |    QUO   UNDR   |     |        |
 * `------+-----+-----+------+----'		   `--------------------------------'
 *  .-------------------------.           .-----------------.   
 *  |        |       |        |           |        |    |   |
 *  '-------------------------'           '-----------------' 
 */
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
//const uint16_t PROGMEM as_combo[] = {MT(MOD_LCTL, KC_A), KC_S, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};

const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END}; 
const uint16_t PROGMEM mc_combo[] = {KC_M, KC_COMM, COMBO_END};

const uint16_t PROGMEM gb_combo[] = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {KC_F, KC_V, COMBO_END};
const uint16_t PROGMEM hn_combo[] = {KC_H, KC_N, COMBO_END};

const uint16_t PROGMEM sdjk_combo[] = {KC_J, KC_K, KC_S, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
	// Horizontal Chords
  [WE] = COMBO(we_combo, KC_ESC),
  //[AS] = COMBO(as_combo, KC_ENT),
  [SD] = COMBO(sd_combo, KC_BSPC),
  [DF] = COMBO(df_combo, KC_TAB),
  [XC] = COMBO(xc_combo, KC_MINS),
  [CV] = COMBO(cv_combo, KC_ENT),

  [OP] = COMBO(op_combo, KC_BSLS),
  [UI] = COMBO(ui_combo, KC_ESC),
  [HJ] = COMBO(hj_combo, KC_LT),
  [JK] = COMBO(jk_combo, KC_COLN),
  [KL] = COMBO(kl_combo, KC_GT),
  [MC] = COMBO(mc_combo, KC_UNDS), // m,
  [NM] = COMBO(nm_combo, KC_QUOT),
	
	// Vertical
  [GB] = COMBO(gb_combo, KC_BTN1),
  [FV] = COMBO(fv_combo, KC_BTN2),
  [HN] = COMBO(hn_combo, KC_ENT)
};

// Blank template at the bottom
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------.       ,--------------------------------.
 * |    Q |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |    P   |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |CTRL/A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  | CTRL/; | 
 * |-----+-----+-----+-----+------+		   |--------------------------------|
 * |SHFT/Z|  X  |  C  |  V  |  B  |      |  N  |  M  |  <  |  >  | SHFT/? |
 * `------+-----+-----+------+----'		   `--------------------------------'
 *  .-------------------------.           .-----------------.   
 *  |ESC/META|ENT/ALT|SPC(SYM)|           |SPC(NUM)|BSPC|TAB|
 *  '-------------------------'           '-----------------' 
 */
[BASE] = LAYOUT_gergoplex(
    KC_Q,  			 			 KC_W, KC_E, KC_R, KC_T,  	KC_Y, KC_U, KC_I,    KC_O, 	 KC_P, 
    MT(MOD_LCTL, KC_A),KC_S, KC_D, KC_F, KC_G,  	KC_H, KC_J, KC_K,    KC_L, 	 MT(MOD_LCTL, KC_SCLN),
    MT(MOD_RSFT, KC_Z),KC_X, KC_C, KC_V, KC_B,  	KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLSH),

 		MT(MOD_LGUI, KC_ESC), MT(MOD_LALT, KC_ENT), LT(SYMB, KC_SPC),									// Left
		LT(NUMB, KC_SPC), KC_LSFT, MT(MOD_RSFT, KC_TAB)																// Right
    ),
/* Keymap 1: Symbols layer
 * ,-----------------------------.       ,--------------------------------.
 * |  !   |  @  |  {  |  }  |       |  `  |  ~  |     |     |    \   |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |  #   |  $  |  (  |  )  | LMB |      |  +  |  -  |  /  |  *  |    '   | 
 * |-----+-----+-----+-----+------+		   |--------------------------------|
 * |  %   |  ^  |  [  |  ]  | RMB |      |  &  |  =  |  ,  |  .  |   -    |
 * `------+-----+-----+------+----'		   `--------------------------------'
 *  				.-----------------.           .------------------.   
 *  				|MMB |  ;  	|	 = 	|						|  =  |  ;  |  DEL |
 *  				'-----------------'           '------------------' 
 */
[SYMB] = LAYOUT_gergoplex(
    KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,   KC_GRV,  KC_TILD, KC_TRNS, KC_TRNS, KC_BSLS,
    KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_BTN2,   KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_QUOT,
    KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BTN1,   KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_MINS,
                      KC_BTN3, KC_SCLN, KC_EQL,   KC_EQL,  KC_SCLN, KC_DEL
    ),
/* Keymap 2: Pad/Function layer
 * ,-----------------------------.       ,-------------------------------.
 * |  1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
 * |-----+-----+-----+-----+------|      |-------------------------------|
 * |  F1  | F2  | F3  | F4  |  F5 |      | LFT | DWN | UP  | RGT | VOLUP | 
 * |-----+-----+-----+-----+------+		   |-------------------------------|
 * |  F6  | F7  | F8  | F9  | F10 |      |MLFT | MDWN| MUP | MRGT| VOLDN |
 * `------+-----+-----+------+----'		   `-------------------------------'
 *  				.-----------------.           .-----------------.   
 *  				| F11 | F12|	  	|						|     | PLY | SKP |
 *  				'-----------------'           '-----------------' 
 */
[NUMB] = LAYOUT_gergoplex(
    KC_1,  KC_2,  KC_3,  KC_4,  KC_5,		 		KC_6,  	KC_7, 	 KC_8, 		KC_9, 	 KC_0,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,   		KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU,
    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,  		KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD,
     						  KC_F11,KC_F12,KC_TRNS,  	KC_TRNS,KC_MPLY,KC_MNXT
    )
};
