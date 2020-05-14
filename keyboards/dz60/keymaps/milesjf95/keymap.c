// milesjf95
// https://www.milesjf95.github.io/
// https://www.reddit.com/u/milesjf95/

// Using as reference
// https://docs.qmk.fm/#/keymap

// original thanks to atlacat, hailbreno, itsaferbie and weeheavy...
// and special thanks to  AGausmann and drashna for the layer-activated RGB underglow
// https://www.reddit.com/r/olkb/comments/6t1vdu/update_layeractivated_rgb_underglow/
// https://github.com/AGausmann/qmk_firmware/blob/agausmann-v3.x/keyboards/nyquist/keymaps/agausmann/keymap.c

// and huge thanks to burukuru for his help working out how to get UK_PND onto my DZ60 keyboard
// https://www.reddit.com/u/burukuru/

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
#define PL 2     // Pound Layer

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
#define RGB_BL_MODE    rgblight_mode_noeeprom(0)              //rgb mode for BL layer
#define RGB_BL_LIGHT   rgblight_sethsv_noeeprom_turquoise()   //rgb light for BL layer
//
#define RGB_FL_MODE    rgblight_mode_noeeprom(1)             //rgb mode for FL layer
#define RGB_FL_LIGHT   rgblight_sethsv_noeeprom_orange()      //rgb light for FL layer
//
#define RGB_PL_MODE    rgblight_mode_noeeprom(2)             //rgb mode for PL layer
#define RGB_PL_LIGHT   rgblight_sethsv_noeeprom_orange()      //rgb light for PL layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap BL: Base Layer (Default Layer)
   *
   * ,-----------------------------------------------------------.
   * | ' | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |Backsp |
   * |-----------------------------------------------------------|
   * | Tab | q | w | e | r | t | y | u | i | o | p | [ | ] |BCSL |
   * |-----------------------------------------------------------|
   * | Caps  | a | s | d | f | g | h | j | k | l | ; | ' | enter |
   * |-----------------------------------------------------------|
   * |  Shift | z | x | c | v | b | n | m | , | . | / |  Shift   |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |          Space        |Alt |MO 2|MO 1|Ctrl |
   * `-----------------------------------------------------------'
   */
   [BL] = LAYOUT_60_ansi(
   	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
		KC_GESC,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_BSPC,
		KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,   KC_BSLS,
		KC_CAPS,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_ENT,
		KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
		KC_LCTL,   KC_LGUI,   KC_LALT,   KC_SPC,    KC_RALT,   MO(2),     MO(1),     KC_RCTL),

  /* Keymap FL: Function and RGB Layer
   *
   * ,-----------------------------------------------------------.
   * |ESC|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
   * |-----------------------------------------------------------|
   * |     |tog|mod|hui|hud|sai|sad|vai|vad|   |   |   |   |reset|
   * |-----------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |dec|tgg|inc|stp|   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    |    |     |
   * `-----------------------------------------------------------'
   */
   [FL] = LAYOUT_60_ansi(
   	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
		KC_GRV,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    KC_DEL,
		_______,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_SAI,   RGB_SAD,   RGB_VAI,   RGB_VAD,   _______,   KC_PSCR,   KC_SLCK,   KC_PAUS,   RESET,
		_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_INS,    KC_HOME,   KC_PGUP,   _______,
		_______,   _______,   _______,   BL_DEC,    BL_TOGG,   BL_INC,    BL_STEP,   _______,   KC_DEL,    KC_END,    KC_PGDN,   _______,
		_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______),

 /* Keymap PL: Pound Layer
   *
   * ,-----------------------------------------------------------.
   * |   |   |   |£  |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |        |    |         |    |    |    |     |
   * `-----------------------------------------------------------'
   */
   [PL] = LAYOUT_60_ansi(
   	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
		_______,   _______,   _______,   UC(0x00A3),_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
		_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
		_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
		_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
		_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______)
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
      case PL:
          RGB_PL_MODE;
          RGB_PL_LIGHT;
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE

}
