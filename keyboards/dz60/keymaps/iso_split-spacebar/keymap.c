// using as reference
// https://docs.qmk.fm/#/keymap

// thanks to atlacat, hailbreno, itsaferbie and weeheavy...

// and special thanks to  AGausmann and drashna for the layer-activated RGB underglow
// https://www.reddit.com/r/olkb/comments/6t1vdu/update_layeractivated_rgb_underglow/
// https://github.com/AGausmann/qmk_firmware/blob/agausmann-v3.x/keyboards/nyquist/keymaps/agausmann/keymap.c

#include QMK_KEYBOARD_H

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
	    KC_GRV,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_BSPC,
        KC_TAB ,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,
        KC_CAPS,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_NUHS,   KC_ENT,
        KC_LSFT,   KC_NUBS,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,
        KC_LCTL,   KC_LGUI,   KC_LALT,   KC_SPC,    MO(FL),    KC_SPC,    KC_RALT,   KC_RGUI,   TO(NL),    KC_RCTL),

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
	    KC_ESC,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    KC_DEL,
        _______ ,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_PSCR,   _______,   _______,
        _______,   KC_MS_LEFT,KC_MS_DOWN,KC_MS_UP,  KC_MS_RIGHT,_______,  _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   KC_MS_BTN1,KC_MS_BTN2,_______,   KC_HOME,   KC_PGDOWN, KC_PGUP,   KC_END,    _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______),

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
	//  1          2         3          4          5          6          7          8          9        10        11        12         13         14
	    TG(NL),    KC_P1,    KC_P2,     KC_P3,     KC_P4,     KC_P5,     KC_P6,     KC_P7,     KC_P8,   KC_P9,    KC_P0,     KC_PPLS,   KC_PMNS,   _______,
        _______,   KC_P4,    KC_P5,     KC_P6,     KC_PAST,   KC_PSLS,   _______,   KC_P4,     KC_P5,   KC_P6,    KC_PAST,   KC_PSLS,   _______,
        _______,   KC_P7,    KC_P8,     KC_P9,     KC_PPLS,   KC_PMNS,   _______,   KC_P1,     KC_P2,   KC_P3,    KC_PPLS,   KC_PMNS,   _______,   _______,
        _______,   KC_P0,    KC_COMM,   KC_DOT,    KC_PEQL,   KC_PSLS,   KC_PMNS,   _______,   KC_P0,   KC_COMM,  KC_DOT,    KC_PEQL,   _______,
        _______,   _______,  _______,   _______,   MO(FL),    _______,   _______,   _______,   TG(RL),  _______),

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
	    TG(RL),    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   QK_BOOT,
        _______,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_HUD,   _______,   _______,   RGB_SAI,   RGB_SAD,   RGB_VAI,   RGB_VAD,   _______,   _______,
        _______,   RGB_STA,   RGB_BRE,   RGB_RAI,   RGB_SWI,   _______,   _______,   RGB_SNA,   RGB_KNI,   RGB_GRA,   RGB_XMS,   _______,   _______,   _______,
        _______,   BL_DEC,    BL_TOGG,   BL_INC,    BL_STEP,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   MO(FL),    _______,   _______,   _______,   TO(BL),    _______),


};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// always enable num lock on layer NL and disable on other layers
// thanks to spidey3 & Erovia on discord
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case NL:
        if (!host_keyboard_led_state().num_lock) {
             tap_code16(KC_NLCK);
        }
        break;
    default: //  for any other layers, or the default layer
        if (host_keyboard_led_state().num_lock) {
             tap_code16(KC_NLCK);
        }
        break;
    }
  return state;
}

// layer-activated RGB underglow

void matrix_scan_user(void) {

  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 1;
  uint8_t new_layer = get_highest_layer(layer_state);

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
          RGB_NL_LIGHT;
        break;
      case RL:
          RGB_RL_MODE;
          RGB_RL_LIGHT;
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE

}
