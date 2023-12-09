/* Copyright 2020 Jordan Egstad
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H






/* ==========================================================================
    LAYERS
   ========================================================================== */

// qwerty
#define _QW 0
// functions
#define _FN 1






/* ==========================================================================
    CUSTOM KEYS
   ========================================================================== */

// Tap dances
#define TD_ESCP TD(TD_GV_ESC)           // Tap for grave, twice for escape
#define TD_MINS TD(TD_MIN)              // Tap for minus, twice for equal
#define TD_BRAC TD(TD_BRC)              // Tap for open brace, twice for close

// Layers
#define FN_SPC LT(_FN, KC_SPC)          // Tap for space, hold for _FN

// Modifiers
#define LG_ZMIN LGUI(KC_EQUAL)          // Command + plus (zoom in)
#define LG_ZMOT LGUI(KC_MINUS)          // Command + minus (zoom out)
#define MT_SHFT MT(MOD_RSFT, KC_ENT)    // Tap for enter, hold for shift

// Tap Dances
enum {
  TD_BRC = 0,
  TD_MIN,
  TD_GV_ESC,
  TD_BS
};

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Left Brace, twice for Right Brace
  [TD_BRC]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  //Tap once for Minus, twice for Equal
  [TD_MIN]  = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_EQUAL),
  // Tap once for Grave, tap twice for Escape
  [TD_GV_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_ESCAPE)
};






/* ==========================================================================
    KEYMAPS
   ========================================================================== */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY (_QW)
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      |   \|   | 6      | 7      | 8      | 9      | 0      |  -  +  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      |  [  ]  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      |        |        |        | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      |        |        |        | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | ZOOM-  | ZOOM+  | LALT   | FN     | CMD    | BSPC   |        |        | FN     | SPACE  | ENTER  | LEFT   | UP     | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    TD_ESCP, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_PIPE, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TD_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD_BRAC,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, _______, _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT_SHFT,
    LG_ZMOT, LG_ZMIN, KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, _______, QK_BOOT, _______, FN_SPC,  KC_ENT,  KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
 ),


/* FUNCTION (_FN)
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     |        | P      |        | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | RGB HD | RGB HI |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | A-SFT  |        |        |        |        |        | RGB SD | RGB SI |        |        | LEFT   | UP     | DOWN   | RIGHT  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RGB    |        |        |        |        |        | RGB VD | RGB VI |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | QK_BOOT  |        |        |        |        |        | RGB RMD| RGB MD |        |        | PLAY   | PREV   | VOL UP | VOL DN | NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______,
    AS_TOGG, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI, _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,
    RGB_TOG, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______,
    QK_BOOT, _______, _______, _______, _______, _______, RGB_RMOD,RGB_MOD, _______, _______, KC_MPLY, KC_MRWD, KC_VOLU, KC_VOLD, KC_MFFD
 ),
};






/* ==========================================================================
    LEDs
   ========================================================================== */

// RGB MODES
// 1 = Static
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient

// Default LED colors
uint8_t h = 170;
uint8_t s = 255;
uint8_t v;

// default animation
uint8_t rgbMode = RGBLIGHT_MODE_STATIC_LIGHT;
// boot animation
uint8_t rgbBootMode = RGBLIGHT_MODE_SNAKE;
// boot timeout vars
uint8_t bootComplete = 0;
int bootTimeoutDuration = 2000;
int bootTimeout;


void init_hsv(void) {
    // fetch what the brightness was last sesion
	v = rgblight_get_val();
    rgblight_sethsv(h,s,v);
}

// fetch current HSV vals
void get_hsv(void) {
	h = rgblight_get_hue();
	s = rgblight_get_sat();
	v = rgblight_get_val();
}

// reset HSV vals
void reset_hsv(void) {
    int currentV = rgblight_get_val();
	rgblight_sethsv(h,s,currentV);
}

// deterimes when to stop bootup animation
void bootupAnimation(void) {
  bootComplete = (timer_elapsed(bootTimeout) > bootTimeoutDuration) ? 1 : 0;

  if (bootComplete) {
    rgblight_mode(rgbMode);
  }
}






/* ==========================================================================
    INITIALIZATION FUNCTION
   ========================================================================== */

void keyboard_post_init_user(void) {
  // start a timeout
  bootTimeout = timer_read();
  // set rgb color
  init_hsv();
  // init rgb
  rgblight_enable();
  // animate in snake ledGreende
  rgblight_mode(rgbBootMode);
};






/* ==========================================================================
    ALWAYS RUNNING
   ========================================================================== */
void matrix_scan_user(void) {
    // keep an eye on these layers
    uint8_t layer = get_highest_layer(layer_state);
    // handle boot-up sequence
    bootupAnimation();
    // watch the brightness for changes
    v = rgblight_get_val();

    switch (layer) {
      case _FN:
        // set leds to white
        rgblight_sethsv_noeeprom(h,0,v);
        break;
      default:
        break;
    }
};






/* ==========================================================================
    KEYPRESS CALLBACKS
   ========================================================================== */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // keep an eye on these layers
  uint8_t layer = get_highest_layer(layer_state);

  switch (keycode) {
    case FN_SPC:
      // stash and pop color on key down and key up
      (record->event.pressed) ? get_hsv() : reset_hsv();
      return true;
    default:
      switch (layer) {
          case _QW:
            // tick the hue up with each keypress
            rgblight_increase_hue();
            break;
          default:
            break;
      }
      return true; // Process all other keycodes normally
  }
}
