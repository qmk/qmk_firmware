// using as reference
// https://docs.qmk.fm/#/keymap

// thanks to atlacat, hailbreno, itsaferbie and weeheavy...

// and special thanks to  AGausmann and drashna for the layer-activated RGB underglow
// https://www.reddit.com/r/olkb/comments/6t1vdu/update_layeractivated_rgb_underglow/ 
// https://github.com/AGausmann/qmk_firmware/blob/agausmann-v3.x/keyboards/nyquist/keymaps/agausmann/keymap.c

#include QMK_KEYBOARD_H
#include "keymap_uk.h"
/* 
* Each layer gets a name for readability.
* The underscores don't mean anything - you can
* have a layer called STUFF or any other name.
* Layer names don't all need to be of the same
* length, and you can also skip them entirely
* and just use numbers.
*
*/
#define BL 0     // Base Layer
#define FL 1     // Function Layer
#define NL 2     // Numpad Layer
#define RL 3     // RGB Layer

/* 
* Let's give an easier name to the RGB modes 
* and assign the ones we want to the different layer
* these will then be used by the function below
*
*/
#define RGB_STA RGB_M_P   //rgb static
#define RGB_BRE RGB_M_B   //rgb breathe
#define RGB_RAI RGB_M_R   //rgb rainbow
#define RGB_SWI RGB_M_SW  //rgb swirl
#define RGB_SNA RGB_M_SN  //rgb snake
#define RGB_KNI RGB_M_K   //rgb knight
#define RGB_GRA RGB_M_G   //rgb gradient
#define RGB_XMS RGB_M_X   //rgb christmas
//
#define RGB_BL_MODE    rgblight_mode_noeeprom(3)              //rgb mode for BL layer
#define RGB_BL_LIGHT   rgblight_sethsv_noeeprom_turquoise()   //rgb light for BL layer
//
#define RGB_FL_MODE    rgblight_mode_noeeprom(1)             //rgb mode for FL layer
#define RGB_FL_LIGHT   rgblight_sethsv_noeeprom_orange()      //rgb light for FL layer
//
#define RGB_NL_MODE    rgblight_mode_noeeprom(12)             //rgb mode for NL layer
#define RGB_NL_LIGHT   rgblight_sethsv_noeeprom_turquoise()       //rgb light for NL layer
//
#define RGB_RL_MODE    rgblight_mode_noeeprom(22)             //rgb mode for RL layer
#define RGB_RL_LIGHT   rgblight_sethsv_noeeprom_red()         //rgb light for RL layer
      

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
  /* Keymap BL: Base Layer (Default Layer)
   *
   * ,-----------------------------------------------------------.
   * | ' | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |Backsp |
   * |-----------------------------------------------------------|
   * | Tab | q | w | e | r | t | y | u | i | o | p | [ | ] |enter|
   * |------------------------------------------------------     |
   * | Caps  | a | s | d | f | g | h | j | k | l | ; | ' | # |   |
   * |-----------------------------------------------------------|
   * |Shft| < | z | x | c | v | b | n | m | , | . | / |  Shift   |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt | Space  | FN |  Space  |Alt |Gui | NL |Ctrl |
   * `-----------------------------------------------------------'
   */
   [BL] = LAYOUT_60_iso_split(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
	    UK_ESC,    UK_1,      UK_2,      UK_3,      UK_4,      UK_5,      UK_6,      UK_7,      UK_8,      UK_9,      UK_0,      UK_MINS,   UK_EQL,    UK_INS,
        UK_TAB ,   UK_Q,      UK_W,      UK_E,      UK_R,      UK_T,      UK_Y,      UK_U,      UK_I,      UK_O,      UK_P,      UK_LBRC,   UK_RBRC,
        UK_LCTL,   UK_A,      UK_S,      UK_D,      UK_F,      UK_G,      UK_H,      UK_J,      UK_K,      UK_L,      UK_SCLN,   UK_QUOT,   UK_HASH,   UK_ENT,
        KC_LSHIFT,   UK_BSLS,   UK_Z,      UK_X,      UK_C,      UK_V,      UK_B,      UK_N,      UK_M,      UK_COMM,   UK_DOT,    UK_SLSH,   UK_RSFT,
        UK_LCTL,   UK_LGUI,   UK_LALT,   UK_SPC,    MO(FL),    UK_BSPC,    _______,   KC_MENU,   TO(NL),    UK_RCTL),

  /* Keymap FL: Function Layer
   *
   * ,-----------------------------------------------------------.
   * |ESC|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |prt|   |   |     |
   * |------------------------------------------------------     |
   * |       |m l|m d|m u|m r|   |   | l | d | u | r |   |   |   |
   * |-----------------------------------------------------------|
   * |    |   |   |   |   |mb1|mb2|   |hm |pgd|pgu|end|          |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    |    |     |
   * `-----------------------------------------------------------'
   */
   [FL] = LAYOUT_60_iso_split(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
	    UK_GRV,    UK_F1,     UK_F2,     UK_F3,     UK_F4,     UK_F5,     UK_F6,     UK_F7,     UK_F8,     UK_F9,     UK_F10,    UK_F11,    UK_F12,    _______,
        _______ ,  _______,   _______,   _______,   _______,   _______,   UK_HOME,   UK_PGDN,     UK_PGUP,   UK_END,     UK_PSCR,   _______,   _______,
        UK_LCTL,   _______,   _______,   _______,   _______,   _______,  UK_LEFT,   UK_DOWN,       UK_UP,     UK_RGHT,  _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,   UK_HOME,   UK_PGDN, UK_PGUP,   UK_END,    _______,
        _______,   _______,   _______,   _______,   _______,   UK_DEL,    _______,   _______,   _______,   _______),

  /* Keymap NL: Numpad Layer
   *
   * ,-----------------------------------------------------------.
   * |BL | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 |   |   |       |
   * |-----------------------------------------------------------|
   * |     | 4 | 5 | 6 | * | / |   | 4 | 5 | 6 | * | / | ] |     |
   * |------------------------------------------------------     |
   * |       | 7 | 8 | 9 | + | - |   | 1 | 2 | 3 | + | - |   |   |
   * |-----------------------------------------------------------|
   * |    |   | 0 | , | . | = |   |   | 0 | , | . | = |      |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    | RL |     |
   * `-----------------------------------------------------------'
   */
   [NL] = LAYOUT_60_iso_split(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
	    TG(NL),    UK_1,      UK_2,      UK_3,      UK_4,      UK_5,      UK_6,      UK_7,      UK_8,      UK_9,      UK_0,      UK_MINS,   UK_EQL,    _______,
        _______,   UK_4,      UK_5,      UK_6,      UK_PAST,   UK_PSLS,   _______,   UK_4,      UK_5,      UK_6,      UK_PAST,   UK_PSLS,   _______,
        _______,   UK_7,      UK_8,      UK_9,      UK_PPLS,   UK_PMNS,   _______,   UK_1,      UK_2,      UK_3,      UK_PPLS,   UK_PMNS,   _______,   _______,
        _______,   UK_0,      UK_COMM,   UK_DOT,    UK_EQL,    _______,   _______,   _______,   UK_0,      UK_COMM,   UK_DOT,    UK_EQL,    _______,
        _______,   _______,   _______,   _______,   MO(FL),    _______,   _______,   _______,   TG(RL),    _______),

  /* Keymap RL: RGB Layer
   *
   * ,-----------------------------------------------------------.
   * |BL |   |   |   |   |   |   |   |   |   |   |   |   |Reset  |
   * |-----------------------------------------------------------|
   * |     |tog|mod|hui|hud|   |   |sai|sad|vai|vad|   |   |     |
   * |------------------------------------------------------     |
   * |       |sta|bre|rai|swi|   |   |sna|kni|gra|xms|   |   |   |
   * |-----------------------------------------------------------|
   * |    |   |bd |bt |bi |bs |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    | BL |     |
   * `-----------------------------------------------------------'
   */
   [RL] = LAYOUT_60_iso_split(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
	    TG(RL),    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   RESET,
        _______,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_HUD,   _______,   _______,   RGB_SAI,   RGB_SAD,   RGB_VAI,   RGB_VAD,   _______,   _______,
        _______,   RGB_STA,   RGB_BRE,   RGB_RAI,   RGB_SWI,   _______,   _______,   RGB_SNA,   RGB_KNI,   RGB_GRA,   RGB_XMS,   _______,   _______,   _______,
        _______,   BL_DEC,    BL_TOGG,   BL_INC,    BL_STEP,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   MO(FL),    _______,   _______,   _______,   TO(BL),    _______),
        

};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


// layer-activated RGB underglow

void matrix_scan_user(void) {

  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 1;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case BL:
          RGB_BL_MODE;
          RGB_BL_LIGHT;        
        break;
      case FL:
          RGB_FL_MODE;
          RGB_FL_LIGHT;  
        break;
      case NL:
          RGB_NL_MODE; 
         // RGB_NL_LIGHT; 
        break;
      case RL:
          RGB_RL_MODE; 
         // RGB_RL_LIGHT;        
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE

}
