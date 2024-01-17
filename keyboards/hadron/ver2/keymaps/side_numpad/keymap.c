#include QMK_KEYBOARD_H

//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _FNLAYER 3
#define _NUMLAY 4
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
  DEMOMACRO,
};

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define CTL_TTAB    CTL_T(KC_TAB)               // Tap for Esc, hold for Ctrl
#define CTL_ENT     CTL_T(KC_ENT)               // Tap for Enter, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define LT_FN(kc)   LT(_FNLAYER, kc)            // L-ayer T-ap Function Layer
#define LT_MC(kc)   LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor
#define LT_RAI(kc)  LT(_RAISE, kc)              // L-ayer T-ap to Raise
#define TG_NUMLAY   TG(_NUMLAY)                 //Toggle for layer _NUMLAY


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------+------+------+------+------+------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |   7  |   8  |   9  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |   4  |   5  |   6  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   =  |   1  |   2  |   3  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  | Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | RAlt | Ins  |  Del |NumLay|   0  |   .  |  ENT |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          KC_MINS,
  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,           KC_BSPC,    KC_P7,   KC_P8,   KC_P9,
  KC_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT_MC(KC_SCLN), CTL_ENT,    KC_P4,   KC_P5,   KC_P6,
  KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,         KC_EQL,    KC_P1,   KC_P2,   KC_P3,
  KC_GRV,    KC_RCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RALT, KC_INS,  KC_DEL,       TG_NUMLAY,    KC_P0,   KC_PDOT, KC_PENT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   ~  |  \   |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * | CAPS |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |   [  |   ]  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT(
  KC_ESC,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_1,       KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,       KC_8,       KC_9,    KC_0,  KC_GRV, KC_BSLS, _______, _______, _______,
  KC_CAPS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_UNDS,     KC_EQL, KC_LBRC, KC_RBRC, KC_PIPE, _______, _______, _______,
  _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, S(KC_NUHS), S(KC_NUBS), KC_LCBR, KC_RCBR, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   ~  |  \   |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
 * |      |   A  |  Up  |   D  | PrSc |      |   4  |   5  |   6  |   *  |   :  |  '   |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  Lt  |  Dn  |  Rt  | Mute |      |   1  |   2  |   3  |  Up  |   /  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |Space |   0  |      | Left | Down | Right|      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT(
  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,   KC_F6, KC_F7,   KC_F8,      KC_F9,  KC_F10,   KC_F11,  KC_F12,
  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,        KC_6,  KC_7,    KC_8,       KC_9,    KC_0,  KC_PLUS, KC_BSLS, _______, _______, _______,
  _______, KC_A,    KC_UP,   KC_D,     KC_PSCR,  _______,  KC_4,    KC_5,       KC_6, KC_PAST,  KC_COLN, KC_QUOT, _______, _______, _______,
  _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MUTE,  _______,  KC_1,    KC_2,       KC_3,   KC_UP,  KC_SLSH, _______, _______, _______, _______,
  _______, _______, _______, _______,   _______,  KC_SPC,  KC_0,   _______,  KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______
),

/* FN layer on Esc key
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   +  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   =  |   [  |   ]  |  '   |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |   {  |   }  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_FNLAYER] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC,   KC_AMPR,    KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS, _______, _______, _______,
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,     KC_EQL, KC_LBRC, KC_RBRC, KC_QUOT, _______, _______, _______,
  _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,S(KC_NUHS), S(KC_NUBS), KC_LCBR, KC_RCBR, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,   _______,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, _______
),

/* Num Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |  F7  |  F8  |  F9  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |  F4  |  F5  |  F6  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |  Up  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Exit | Left | Down | Rght |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_NUMLAY] = LAYOUT(
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME,  KC_PGUP,
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, KC_DEL,   KC_END,  KC_PGDN,
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, KC_PMNS,    KC_UP,   KC_PPLS,
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT
),

/* Mouse Layer (semi-col)
 * ,-----------------------------------------------------------------------------------.
 * |      |ACCL0| ACCL1| ACCL2 |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |      |      |      |      |      | Home | Wh_Up| WHL_L| M_Up | WHL_R|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | End  | Wh_Dn| M_Lft| M_Dn | M_Rt |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | BTN2 | BTN3 | BTN4 | BTN5 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | BTN1 |      |      |      | BTN1 |      |      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */

[_MOUSECURSOR] = LAYOUT(
  _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______,   _______, _______,
  _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_WH_L, KC_MS_U, KC_WH_R, DEMOMACRO, _______, _______, _______, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_END , KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R,   _______, _______, _______, _______, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5,   _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______,   _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)

 * ,-----------------------------------------------------------------------------------.
 * | Reset|      |      |      |      |      |      |      |      | VolD | VolU | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------+--------------------.
 * |      |RGB TG|RGB ST|RGBH -|RGBH +|RGBS -|RGBS +|RGBV -|RGBV +|      |      |  Del |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      | BL + |BL ST |BLSTEP| BL TG|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT(
  QK_BOOT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_VOLD, KC_VOLU, KC_MUTE,
  _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______,  KC_DEL, _______, _______, _______,
  _______, _______, _______,   AU_ON,  AU_OFF, AG_NORM, AG_SWAP,  QWERTY, _______, _______, _______, _______, _______, _______, _______,
  _______, AU_PREV, AU_NEXT,   MU_ON,  MU_OFF,   MI_ON,  MI_OFF, _______, BL_DOWN, BL_UP,   BL_STEP, BL_TOGG, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)



};

// define variables for reactive RGB
bool RGB_INIT = false;
bool TOG_STATUS = false;
bool NUMLAY_STATUS = false;
int RGB_current_mode;


void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    rgblight_mode(RGB_current_mode);
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (RGB_INIT) {} else {
          RGB_current_mode = rgblight_config.mode;
          RGB_INIT = true;
        }
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(16);
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (RGB_INIT) {} else {
          RGB_current_mode = rgblight_config.mode;
          RGB_INIT = true;
        }
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(15);
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
      //my attempt for RGB layer lock indication via changing the mode, still have to figure out how to not have other keypress not override this mode
    case TG_NUMLAY:
      if (record->event.pressed) {
        if (RGB_INIT) {} else {
          RGB_current_mode = rgblight_config.mode;
          RGB_INIT = true;
        }
        NUMLAY_STATUS = !NUMLAY_STATUS;
        if (NUMLAY_STATUS) {
        rgblight_mode(4);
        layer_on(_NUMLAY);
        } else {
        rgblight_mode(RGB_current_mode);
        layer_off(_NUMLAY); }
      }
      return false;
      break;
    case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
        rgblight_step();
        RGB_current_mode = rgblight_config.mode;
      }
      return false;
      break;
    case DEMOMACRO:
      if (record->event.pressed) {
        SEND_STRING("hello world");
      }
      return false;
      break;
  }
  return true;
}
