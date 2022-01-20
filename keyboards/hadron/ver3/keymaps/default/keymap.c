#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _MOUSECURSOR 5
#define _ADJUST 6

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT,
  RGBLED_TOGGLE,
  RGBLED_STEP_MODE,
  RGBLED_INCREASE_HUE,
  RGBLED_DECREASE_HUE,
  RGBLED_INCREASE_SAT,
  RGBLED_DECREASE_SAT,
  RGBLED_INCREASE_VAL,
  RGBLED_DECREASE_VAL,
  DEMOMACRO
};

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define CTL_TTAB    CTL_T(KC_TAB)               // Tap for Esc, hold for Ctrl
#define CTL_ENT     CTL_T(KC_ENT)               // Tap for Enter, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define LT_MC(kc)   LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor
#define LT_RAI(kc)  LT(_RAISE, kc)              // L-ayer T-ap to Raise

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------+------+------+------+------+------------------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  DEL |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   7  |   8  |   9  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |   A  |   S  |   D  |   F  |   G  |   4  |   5  |   6  |   H  |   J  |   K  |   L  | ;/Nav|  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   1  |   2  |   3  |   N  |   M  |   ,  |   .  |   /  |Ctl/Et|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |  `   | Ctrl | Alt  | GUI  |Lower |Space |   0  |   .  |   =  |Space |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_P7,   KC_P8,   KC_P9,    KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,     KC_BSPC,
  KC_CAPS,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_P4,   KC_P5,   KC_P6,    KC_H,    KC_J,    KC_K,   KC_L,LT_MC(KC_SCLN), KC_QUOT,
  KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_P1,   KC_P2,   KC_P3,    KC_N,    KC_M,    KC_COMM,KC_DOT,  KC_SLSH,  CTL_ENT,
  KC_GRV,   KC_LCTRL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_P0,   KC_DOT,  KC_EQL,  KC_SPC,   RAISE,   KC_LEFT,KC_DOWN, KC_UP,    KC_RGHT
),

/* Colemak
 * ,------+------+------+------+------+------------------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   7  |   8  |   9  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | CAPS |   A  |   R  |   S  |   T  |   D  |   4  |   5  |   6  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   1  |   2  |   3  |   K  |   M  |   ,  |   .  |   /  |Ctl/Et|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  | Ctrl | Alt  | GUI  |Lower |Space |   0  |   .  |   =  |Space |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT(
  KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_DEL,
  KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_P7,   KC_P8,   KC_P9,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSPC,
  KC_LCTRL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_P4,   KC_P5,   KC_P6,    KC_H,    KC_N,    KC_E,    KC_I, LT_MC(KC_O), KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_P1,   KC_P2,   KC_P3,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  CTL_ENT,
  KC_GRV,   KC_CAPS, KC_LGUI, KC_LALT, LOWER,  KC_SPC,  KC_P0,   KC_DOT,  KC_EQL,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT
  ),

/* Dvorak
 * ,------+------+------+------+------+------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   7  |   8  |   9  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   4  |   5  |   6  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   1  |   2  |   3  |   B  |   M  |   W  |   V  |   Z  |Ctl/Et|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  | Ctrl | Alt  | GUI  |Lower |Space |   0  |   .  |   =  |Space |Raise | Left | Down |  Up  |Right |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT(
  KC_ESC,   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_DEL,
  KC_TAB,   KC_QUOT,  KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_P7,   KC_P8,   KC_P9,    KC_F,    KC_G,   KC_C,    KC_R,    KC_L,     KC_BSPC,
  KC_LCTL,  KC_A,     KC_O,    KC_E,    KC_U,    KC_I,    KC_P4,   KC_P5,   KC_P6,    KC_D,    KC_H,   KC_T,    KC_N, LT_MC(KC_S), KC_SLSH,
  KC_LSFT,  KC_SCLN,  KC_Q,    KC_J,    KC_K,    KC_X,    KC_P1,   KC_P2,   KC_P3,    KC_B,    KC_M,   KC_W,    KC_V,    KC_Z,     CTL_ENT,
  KC_GRV,   KC_LCTRL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_P0,   KC_DOT,  KC_EQL,   KC_SPC,  RAISE,  KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT
),

/* Lower
 * ,------+------+------+------+------+------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |      |      |      |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |      |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN, KC_DEL,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_UNDS, KC_PLUS,  KC_LBRC, KC_RBRC, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, _______, KC_F12,S(KC_NUHS),S(KC_NUBS),_______,_______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,------+------+------+------+------+------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |      |      |      |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |      |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, _______, KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______,
  _______, _______, _______, _______,  _______, KC_SPC, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Mouse Layer (semi-col)
 * ,------+------+------+------+------+------------------------------------------------.
 * | ACCL0| ACCL1| ACCL2|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |      |      |      |      |      |      |      |      | Home | Wh_Up| WHL_L| M_Up | WHL_R| Macro|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | End  | Wh_Dn| M_Lft| M_Dn | M_Rt |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | BTN2 | BTN3 | BTN4 | BTN5 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | BTN1 |      |      |      | BTN1 |      |      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */

[_MOUSECURSOR] = LAYOUT(
  KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_WH_L, KC_MS_U, KC_WH_R,DEMOMACRO,_______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_END , KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, _______, _______,
  _______, _______, _______, _______, _______, KC_BTN1, _______, _______, _______, KC_BTN1, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,------+------+------+------+------+------------------------------------------------.
 * | Reset|HPT TG|HPT FB|HPT M+|HPT M-|HPT RS|      |      |      |      |      |EEP RS|
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |      |RGB TG|RGB ST|RGBH -|RGBH +|RGBS -|RGBS +|RGBV -|RGBV +|      |      |      |      |      |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|      |      |      |AGswap|Qwerty|Colemk|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|      |      |      |      |      |      |BL -  | BL + |BL ST |BL TG |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |CK RS |CK -  |CK +  |CK TG |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT(
  RESET,   HPT_TOG, HPT_FBK, HPT_MODI, HPT_MODD, HPT_RST , _______, _______, _______, _______, _______, EEP_RST,
  _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, _______, _______, _______, AG_SWAP, QWERTY,  COLEMAK, _______,  _______,  _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF, _______, _______, _______,  _______, BL_DEC,  BL_INC,  BL_STEP, BL_TOGG,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, CK_RST,  CK_DOWN, CK_UP,   CK_TOGG
)



};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case DEMOMACRO:
      if (record->event.pressed) {
        SEND_STRING("hello world");
      }
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
