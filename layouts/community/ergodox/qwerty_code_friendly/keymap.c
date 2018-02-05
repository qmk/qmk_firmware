#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/**
 * See `readme.md` for notes on each define.
 */

// Personal preference (enable by passing EXTRAFLAGS=... to make).
// #define CFQ_USE_MOMENTARY_LAYER_KEYS
// #define CFQ_USE_EXPEREMENTAL_LAYER

// keep enabled for now
#define CFQ_USE_DYNAMIC_MACRO

#if !defined(CFQ_USER_KEY1)
#  define CFQ_USER_KEY1 CFQ_KC_FN1
#endif
#if !defined(CFQ_USER_KEY2)
#  define CFQ_USER_KEY2 KC_INS
#endif
#if !defined(CFQ_USER_KEY3)
#  ifdef CFQ_USE_EXPEREMENTAL_LAYER
#    define CFQ_USER_KEY3 CFQ_KC_FN3
#  else
#    define CFQ_USER_KEY3 KC_CAPS
#  endif
#endif
#if !defined(CFQ_USER_KEY4)
#  define CFQ_USER_KEY4 KC_SPC
#endif
#if !defined(CFQ_USER_KEY5)
#  define CFQ_USER_KEY5 KC_ENT
#endif
#if !defined(CFQ_USER_KEY6)
#  define CFQ_USER_KEY6 CFQ_KC_FN2
#endif
#if !defined(CFQ_USER_KEY7)
#  define CFQ_USER_KEY7 CFQ_KC_FN1
#endif

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#ifdef CFQ_USE_EXPEREMENTAL_LAYER
#  define EXPR 3 // experimental keys
#endif

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
#ifdef CFQ_USE_DYNAMIC_MACRO
  DYNAMIC_MACRO_RANGE,
#endif
};

#ifdef CFQ_USE_DYNAMIC_MACRO
#include "dynamic_macro.h"
#endif

// macros
#ifdef CFQ_USE_EXPEREMENTAL_LAYER
#define M_SPACES_1 2
#define M_SPACES_2 3
#define M_SPACES_3 4
#define M_SPACES_4 5
#define M_SPACES_5 6
#define M_SPACES_6 7
#define M_SPACES_7 8
#define M_SPACES_8 9
#endif
#define M_BRACKET_IN_CBR 10
#define M_BRACKET_IN_PRN 11
#define M_BRACKET_IN_BRC 12
#define M_BRACKET_IN_ANG 13
#define M_BRACKET_OUT_CBR 14
#define M_BRACKET_OUT_PRN 15
#define M_BRACKET_OUT_BRC 16
#define M_BRACKET_OUT_ANG 17
#define M_ARROW_RMINUS 18
#define M_ARROW_LMINUS 19
#define M_ARROW_REQL 20
#define M_ARROW_LEQL 21

#ifdef CFQ_USE_MOMENTARY_LAYER_KEYS
#define CFQ_KC_FN1 MO(1)
#define CFQ_KC_FN2 MO(2)
#define CFQ_KC_FN3 MO(3)
#else
#define CFQ_KC_FN1 KC_FN1
#define CFQ_KC_FN2 KC_FN2
#define CFQ_KC_FN3 KC_FN3
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Grave  |   !  |   @  |   #  |   $  |   %  |   {  |           |  }   |   ^  |   &  |   *  |   -  |   =  | BSpace |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   (  |           |  )   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtl |Super | Alt  | ~L1  |Space |                                       | Left | Down | Up   |Right | Del  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Ins  |CapsLk|       | Home | End  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | ~L2  |       | PgUp |      |      |
 *                                 |Space |Enter |------|       |------|Enter |Space |
 *                                 |      |      | ~L1  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 *
 * Optional overrides: see CFQ_USER_KEY# defines.
 *
 *   -------+------+------+------+------+
 *   |      |      |      | USR1 |      |
 *   `----------------------------------'
 *
 *                                        ,-------------.
 *                                        | USR2 | USR3 |
 *                                 ,------|------|------|
 *                                 |      |      | USR6 |
 *                                 | USR4 | USR5 |------|
 *                                 |      |      | USR7 |
 *                                 `--------------------'
 */

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
  // left hand
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH,       KC_DLR, KC_PERC, KC_LCBR,
  KC_TAB,  KC_Q,    KC_W,    KC_E,          KC_R,   KC_T,    KC_LPRN,
  KC_ESC,  KC_A,    KC_S,    KC_D,          KC_F,   KC_G,
  KC_LSFT, KC_Z,    KC_X,    KC_C,          KC_V,   KC_B,    KC_LBRC,
  KC_LCTL, KC_LGUI, KC_LALT, CFQ_USER_KEY1, KC_SPC,
                                                    CFQ_USER_KEY2, CFQ_USER_KEY3,
                                                                   CFQ_USER_KEY6,
                                     CFQ_USER_KEY4, CFQ_USER_KEY5, CFQ_USER_KEY7,
  // right hand
  KC_RCBR,     KC_CIRC, KC_AMPR, KC_ASTR,KC_MINS, KC_EQL,    KC_BSPC,
  KC_RPRN,     KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,      KC_BSLS,
               KC_H,    KC_J,    KC_K,   KC_L,    KC_SCLN,   KC_QUOT,
  KC_RBRC,     KC_N,    KC_M,    KC_COMM,KC_DOT,  KC_SLSH,   KC_RSFT,
                        KC_LEFT, KC_DOWN,KC_UP,   KC_RGHT,   KC_DELT,
  KC_HOME, KC_END,
  KC_PGUP,
#ifdef CFQ_USE_SWAP_RIGHT_SPACE_ENTER
  KC_PGDN, KC_SPC, KC_ENT
#else
  KC_PGDN, KC_ENT, KC_SPC
#endif
),
/* Keymap 1: Symbol layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  {}  |           |  }{  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |  =>  |  ()  |           |  )(  |  <=  |   7  |   8  |   9  |   \  |   F11  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |  ->  |------|           |------|  <-  |   4  |   5  |   6  |   *  |   F12  |
 * |--------+------+------+------+------+------|  []  |           |  ][  |------+------+------+------+------+--------|
 * |        |      |      |      |      |  <>  |      |           |      |  ><  |   1  |   2  |   3  |   -  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |      |   .  |   +  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |Start1|Start2|       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Stop |       |      |        |      |
 *                                 |Play1 |Play2 |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,               M(M_BRACKET_IN_CBR),
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(M_ARROW_REQL),     M(M_BRACKET_IN_PRN),
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(M_ARROW_RMINUS),
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(M_BRACKET_IN_ANG), M(M_BRACKET_IN_BRC),
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#ifdef CFQ_USE_DYNAMIC_MACRO
                               DYN_REC_START1, DYN_REC_START2,
                                               DYN_REC_STOP,
                              DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, KC_TRNS,
#else
                                      KC_TRNS, KC_TRNS,
                                               KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,
#endif
  // right hand
  M(M_BRACKET_OUT_CBR), KC_F6,                KC_F7,   KC_F8,   KC_F9,     KC_F10,         KC_TRNS,
  M(M_BRACKET_OUT_PRN), M(M_ARROW_LEQL),      KC_KP_7, KC_KP_8, KC_KP_9,   KC_KP_SLASH,    KC_F11,
                        M(M_ARROW_LMINUS),    KC_KP_4, KC_KP_5, KC_KP_6,   KC_KP_ASTERISK, KC_F12,
  M(M_BRACKET_OUT_BRC), M(M_BRACKET_OUT_ANG), KC_KP_1, KC_KP_2, KC_KP_3,   KC_KP_MINUS,    KC_TRNS,
                                              KC_KP_0, KC_TRNS, KC_KP_DOT, KC_KP_PLUS,     KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |MWhlUp|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------| Left | Down | Up   |Right |      |        |
 * |--------+------+------+------+------+------|MWhlDn|           |      |------+------+------+------+------+--------|
 * |        |      | Rclk | Mclk | Lclk |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | MRwd | MFwd |       | MPrv | MNxt |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |VolUp |      |      |
 *                                 |      |      |------|       |------| Mute | Play |
 *                                 |      |      |      |       |VolDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_WH_U,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_BTN2, KC_BTN3, KC_BTN1, KC_TRNS, KC_WH_D,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                      KC_MRWD, KC_MFFD,
                                               KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_MPRV, KC_MNXT,
  KC_VOLU,
  KC_VOLD, KC_MUTE, KC_MPLY
),
#ifdef CFQ_USE_EXPEREMENTAL_LAYER
/* Keymap 3: My own testing keys!
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |  {   |   }  |      |   }  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |  (   |   )  |      |   )  |           |      | Spc7 | Spc8 |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  [   |   ]  |      |------|           |------| Spc4 | Spc5 | Spc6 |      |      |        |
 * |--------+------+------+------+------+------|   ]  |           |      |------+------+------+------+------+--------|
 * |        |      |      |  <   |   >  |      |      |           |      | Spc1 | Spc2 | Spc3 |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

// EXPERIMENT
[EXPR] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR,    KC_RCBR,    KC_TRNS, KC_RCBR,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_LPRN,    KC_RPRN,    KC_TRNS, KC_RPRN,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC,    KC_RBRC,	 KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, S(KC_COMM), S(KC_DOT),  KC_TRNS, KC_RBRC,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                                         KC_TRNS, KC_TRNS,
                                                  KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, M(M_SPACES_7), M(M_SPACES_8), KC_TRNS,       KC_TRNS, KC_TRNS,
           KC_TRNS, M(M_SPACES_4), M(M_SPACES_5), M(M_SPACES_6), KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, M(M_SPACES_1), M(M_SPACES_2), M(M_SPACES_3), KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
#endif // CFQ_USE_EXPEREMENTAL_LAYER
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),               // FN1 - Momentary Layer 1 (Symbols)
  [2] = ACTION_LAYER_TAP_TOGGLE(MDIA),               // FN2 - Momentary Layer 2 (Media)
#ifdef CFQ_USE_EXPEREMENTAL_LAYER
  [3] = ACTION_LAYER_TAP_TOGGLE(EXPR),               // FN3 - Momentary Layer 3 (Expremental)
#endif
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
    if (record->event.pressed) {
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    break;
    case 1:
    if (record->event.pressed) { // For resetting EEPROM
      eeconfig_init();
    }
    break;
#ifdef CFQ_USE_EXPEREMENTAL_LAYER
    case M_SPACES_1:
      if (record->event.pressed) { return MACRO(T(SPC), END); }
    case M_SPACES_2:
      if (record->event.pressed) { return MACRO(T(SPC), T(SPC), END); }
    case M_SPACES_3:
      if (record->event.pressed) { return MACRO(T(SPC), T(SPC), T(SPC), END); }
    case M_SPACES_4:
      if (record->event.pressed) { return MACRO(T(SPC), T(SPC), T(SPC), T(SPC), END); }
    case M_SPACES_5:
      if (record->event.pressed) { return MACRO(T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), END); }
    case M_SPACES_6:
      if (record->event.pressed) { return MACRO(T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), END); }
    case M_SPACES_7:
      if (record->event.pressed) { return MACRO(T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), END); }
    case M_SPACES_8:
      if (record->event.pressed) { return MACRO(T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), T(SPC), END); }
#endif // CFQ_USE_EXPEREMENTAL_LAYER
    case M_BRACKET_IN_CBR: // {}
      if (record->event.pressed) { return MACRO(D(LSFT), T(LBRC), T(RBRC), U(LSFT), T(LEFT), END); }
    case M_BRACKET_IN_PRN: // ()
      if (record->event.pressed) { return MACRO(D(LSFT), T(9), T(0), U(LSFT), T(LEFT), END); }
    case M_BRACKET_IN_BRC: // []
      if (record->event.pressed) { return MACRO(T(LBRC), T(RBRC), T(LEFT), END); }
    case M_BRACKET_IN_ANG: // <>
      if (record->event.pressed) { return MACRO(D(LSFT), T(COMM), T(DOT), U(LSFT), T(LEFT), END); }
    case M_BRACKET_OUT_CBR: // }{
      if (record->event.pressed) { return MACRO(D(LSFT), T(RBRC), T(LBRC), U(LSFT), T(LEFT), END); }
    case M_BRACKET_OUT_PRN: // )(
      if (record->event.pressed) { return MACRO(D(LSFT), T(0), T(9), U(LSFT), T(LEFT), END); }
    case M_BRACKET_OUT_BRC: // ][
      if (record->event.pressed) { return MACRO(T(RBRC), T(LBRC), T(LEFT), END); }
    case M_BRACKET_OUT_ANG: // ><
      if (record->event.pressed) { return MACRO(D(LSFT), T(DOT), T(COMM), U(LSFT), T(LEFT), END); }

    case M_ARROW_RMINUS:
      if (record->event.pressed) { return MACRO(T(MINUS), D(LSFT), T(DOT), U(LSFT), END); }
    case M_ARROW_LMINUS:
      if (record->event.pressed) { return MACRO(D(LSFT), T(COMM), U(LSFT), T(MINUS), END); }
    case M_ARROW_REQL:
      if (record->event.pressed) { return MACRO(T(EQL), D(LSFT), T(DOT), U(LSFT), END); }
    case M_ARROW_LEQL:
      if (record->event.pressed) { return MACRO(D(LSFT), T(COMM), U(LSFT), T(EQL), END); }
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CFQ_USE_DYNAMIC_MACRO
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
#endif
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
#endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
#ifdef CFQ_USE_EXPEREMENTAL_LAYER
    case 3:
      ergodox_right_led_3_on();
      break;
#endif
    default:
      // none
      break;
  }

};
