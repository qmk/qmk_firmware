/* -*- Mode:C; c-basic-offset:2; tab-width:2; indent-tabs-mode:nil; evil-indent-convert-tabs:t; -*- */

#include QMK_KEYBOARD_H

//#define DYNAMIC_MACRO_SIZE 128

#define LAYER_BASE 0 /* default layer */
#define LAYER_NUM  1 /* numbers and symbols */
#define LAYER_LNUM 2 /* Left side -> LAYER_NUM,              Right side -> Shift + LAYER_BASE */
#define LAYER_RNUM 3 /* Left side -> Shift + LAYER_BASE,     Right side -> LAYER_NUM  */

enum custom_keycodes5 {
  PLACEHOLDER = SAFE_RANGE, /* can always be here */

  M_POINER,  /* -> */
  M_LAMBDA,  /* => */
  M_IN_CBR,  /* {} */
  M_IN_PRN,  /* () */
  M_IN_BRC,  /* [] */
  M_IN_ANG,  /* <> */
  M_NOT_EQL, /* != */
  M_COL_EQL, /* := */
  M_PLUS_EQL,/* += */

  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * .--------------------------------------------------.  .--------------------------------------------------.
 * | Grave  |   !  |   @  |   #  |   $  |   %  |   ^  |  | TG(1)|   &  |   *  |   (  |   )  |   -  |  Bspc  |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |   =  |  |  _   |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   R  |   S  |   T  |   D  |------|  |------|   H  |   N  |   E  |   I  |   O  |  '     |
 * |--------+------+------+------+------+------|   {  |  |  }   |------+------+------+------+------+--------|
 * | LShift |Z/LCtl|X/Supe|   C  |   V  |B/RAlt|      |  |      |K/RAlt|   M  |   ,  |./Supe|/ RCtl| RShift |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   | LCtl |Super | Alt  |   [  |   ]  |                              | Left | Down | Up   |Right | Del  |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      | Home | End  |  | Ins  |ScrLck|
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |PrnScr|  | PgUp |      |      |
 *                               | LNUM | Enter|------|  |------| Space| RNUM |
 *                               |      |      | Super|  | PgDn |      |      |
 *                               '--------------------'  '--------------------'
 */

[LAYER_BASE] = LAYOUT_ergodox(  /* layer 0 : default */
  /* left hand */
  KC_GRV,         KC_EXLM,       KC_AT,         KC_HASH,  KC_DLR,          KC_PERC,         KC_CIRC,
  KC_TAB,         KC_Q,          KC_W,          KC_F,     KC_P,            KC_G,            KC_EQL,
  KC_ESC,         KC_A,          KC_R,          KC_S,     KC_T,            KC_D,
  KC_LSFT,        LCTL_T(KC_Z),  LGUI_T(KC_X),  KC_C,     KC_V,            RALT_T(KC_B),    KC_LCBR,
  KC_LCTL,        KC_LGUI,       KC_LALT,       KC_LBRC,  KC_RBRC,

                                                              KC_HOME, KC_END,
                                                                      KC_PSCR,
                                            MO(LAYER_LNUM), KC_ENT,   KC_LGUI,
  /* right hand */
  TG(1),          KC_AMPR,       KC_ASTR,       KC_LPRN,  KC_RPRN,         KC_MINS,          KC_BSPC,
  KC_UNDS,        KC_J,          KC_L,          KC_U,     KC_Y,            KC_SCLN,          KC_BSLS,
                  KC_H,          KC_N,          KC_E,     KC_I,            KC_O,             KC_QUOT,
  KC_RCBR,        RALT_T(KC_K),  KC_M,          KC_COMM,  LGUI_T(KC_DOT),  RCTL_T(KC_SLSH),  KC_RSFT,
                                 KC_LEFT,       KC_DOWN,  KC_UP,           KC_RGHT,          KC_DEL,
  KC_INS,  KC_SCRL,
  KC_PGUP,
  KC_PGDN, KC_SPC, MO(LAYER_RNUM)
),
/* Keymap 1: Numbers, Macro Record
 *
 * .--------------------------------------------------.  .--------------------------------------------------.
 * |        |      |      |      |      |  <>  |      |  |      |      |   *  |   (  |  )   |  -   |        |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * |        |  F12 |  F11 |  F10 |  F9  |  {}  |      |  |  =   |  =>  |   7  |   8  |   9  |  +   |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |  F8  |  F7  |  F6  |  F5  |  ()  |------|  |------|  ->  |   4  |   5  |   6  |  0   |        |
 * |--------+------+------+------+------+------|      |  | Enter|------+------+------+------+------+--------|
 * |        |  F4  |  F3  |  F2  |  F1  |  []  |      |  |      |  !=  |   1  |   2  |   3  |      |        |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   | MUTE | VOLD | VOLU |      |      |                              |   0  |   ,  |   .  |      |      |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |      |      |  |      | Stop |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |Start1|  |Start2|      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |Play1 |  |Play2 |      |      |
 *                               '--------------------'  '--------------------'
 */
[LAYER_NUM] = LAYOUT_ergodox(
  /* left hand */
  KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  M_IN_ANG,       KC_TRNS,
  KC_TRNS, KC_F12,     KC_F11,  KC_F10,   KC_F9,    M_IN_CBR,       KC_TRNS,
  KC_TRNS, KC_F8,      KC_F7,   KC_F6,    KC_F5,    M_IN_PRN,
  KC_TRNS, KC_F4,      KC_F3,   KC_F2,    KC_F1,    M_IN_BRC,       KC_TRNS,
  KC_MUTE, KC_VOLD,    KC_VOLU, KC_TRNS,  KC_TRNS,

                                                       KC_TRNS,   KC_TRNS,
                                                           DM_REC1,
                                        KC_TRNS, KC_TRNS, DM_PLY1,
  /* right hand */
  KC_TRNS, KC_TRNS,    KC_ASTR, KC_LPRN,  KC_RPRN,  KC_MINS,  KC_TRNS,
  KC_EQL,  M_LAMBDA,   KC_7,    KC_8,     KC_9,     KC_PLUS,  KC_TRNS,
           M_POINER,   KC_4,    KC_5,     KC_6,     KC_0,     KC_TRNS,
  KC_ENT,  M_NOT_EQL,  KC_1,    KC_2,     KC_3,     KC_TRNS,  KC_TRNS,
                       KC_0,    KC_COMM,  KC_DOT,   KC_TRNS,  KC_TRNS,
  KC_TRNS, DM_RSTP,
  DM_REC2,
  DM_PLY2, KC_TRNS, KC_TRNS
),
/* Keymap 2: Left side -> LAYER_NUM,                             Right side -> Shift + LAYER_BASE
 *
 * .--------------------------------------------------.  .--------------------------------------------------.
 * |        |      |      |      |      |  <>  |      |  | TG(1)|   &  |   *  |   (  |   )  |   -  |  Bspc  |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * |        |  F12 |  F11 |  F10 |  F9  |  {}  |      |  |  _   |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |  F8  |  F7  |  F6  |  F5  |  ()  |------|  |------|   H  |   N  |   E  |   I  |   O  |  '     |
 * |--------+------+------+------+------+------|      |  |  }   |------+------+------+------+------+--------|
 * |        |  F4  |  F3  |  F2  |  F1  |  []  |      |  |      |K/RAlt|   M  |   ,  |./Supe|/ RCtl| RShift |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   | MUTE | VOLD | VOLU |      |      |                              | Left | Down | Up   |Right | Del  |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |      |      |  | Ins  |ScrLck|
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |Start1|  | PgUp |      |      |
 *                               |      |      |------|  |------| Space|CapsLk|
 *                               |      |      |Play1 |  | PgDn |      |      |
 *                               '--------------------'  '--------------------'
 */
[LAYER_LNUM] = LAYOUT_ergodox(
  /* left hand */
  KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  M_IN_ANG,       KC_TRNS,
  KC_TRNS, KC_F12,     KC_F11,  KC_F10,   KC_F9,    M_IN_CBR,       KC_TRNS,
  KC_TRNS, KC_F8,      KC_F7,   KC_F6,    KC_F5,    M_IN_PRN,
  KC_TRNS, KC_F4,      KC_F3,   KC_F2,    KC_F1,    M_IN_BRC,       KC_TRNS,
  KC_MUTE, KC_VOLD,    KC_VOLU, KC_TRNS,  KC_TRNS,

                                                       KC_TRNS,   KC_TRNS,
                                                           DM_REC1,
                                        KC_TRNS, KC_TRNS, DM_PLY1,
  /* right hand */
  TG(1),          KC_AMPR,       KC_ASTR,       KC_LPRN,    KC_RPRN,    S(KC_MINS),  S(KC_BSPC),
  KC_UNDS,        S(KC_J),       S(KC_L),       S(KC_U),    S(KC_Y),    S(KC_SCLN),  S(KC_BSLS),
                  S(KC_H),       S(KC_N),       S(KC_E),    S(KC_I),    S(KC_O),     S(KC_QUOT),
  KC_RCBR,        S(KC_K),       S(KC_M),       S(KC_COMM), S(KC_DOT),  S(KC_SLSH),  KC_RSFT,
                                 S(KC_LEFT),    S(KC_DOWN), S(KC_UP),   S(KC_RGHT),  S(KC_DEL),
  S(KC_INS),  S(KC_SCRL),
  S(KC_PGUP),
  S(KC_PGDN), S(KC_SPC), KC_CAPS
),
/* Keymap 3: Left side -> Shift + LAYER_BASE,                    Right side -> LAYER_NUM
 *
 * .--------------------------------------------------.  .--------------------------------------------------.
 * | Grave  |   !  |   @  |   #  |   $  |   %  |   ^  |  |      |      |   *  |   (  |  )   |  -   |        |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |   =  |  |  =   |  =>  |   7  |   8  |   9  |  +   |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   R  |   S  |   T  |   D  |------|  |------|  ->  |   4  |   5  |   6  |  0   |        |
 * |--------+------+------+------+------+------|   {  |  | Enter|------+------+------+------+------+--------|
 * | LShift |Z/LCtl|X/Supe|   C  |   V  |B/RAlt|      |  |      |  !=  |   1  |   2  |   3  |      |        |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   | LCtl |Super | Alt  |   [  |   ]  |                              |   0  |   ,  |   .  |      |      |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      | Home | End  |  |      | Stop |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |PrnScr|  |Start2|      |      |
 *                               |CapsLk| Enter|------|  |------|      |      |
 *                               |      |      | Super|  |Play2 |      |      |
 *                               '--------------------'  '--------------------'
 */
[LAYER_RNUM] = LAYOUT_ergodox(
  /* left hand */
  S(KC_GRV),   KC_EXLM,     KC_AT,       KC_HASH,     KC_DLR,      KC_PERC,    KC_CIRC,
  S(KC_TAB),   S(KC_Q),     S(KC_W),     S(KC_F),     S(KC_P),     S(KC_G),    S(KC_EQL),
  S(KC_ESC),   S(KC_A),     S(KC_R),     S(KC_S),     S(KC_T),     S(KC_D),
  KC_LSFT,     S(KC_Z),     S(KC_X),     S(KC_C),     S(KC_V),     S(KC_B),    KC_LCBR,
  S(KC_LCTL),  S(KC_LGUI),  S(KC_LALT),  S(KC_LBRC),  S(KC_RBRC),

                                                              S(KC_HOME), S(KC_END),
                                                                         S(KC_PSCR),
                                                   KC_CAPS, S(KC_ENT),   S(KC_LGUI),
  /* right hand */
  KC_TRNS, KC_TRNS,     KC_ASTR, KC_LPRN,  KC_RPRN,  KC_MINS,  KC_TRNS,
  KC_EQL,  M_LAMBDA,    KC_7,    KC_8,     KC_9,     KC_PLUS,  KC_TRNS,
           M_POINER,    KC_4,    KC_5,     KC_6,     KC_0,     KC_TRNS,
  KC_ENT,  M_NOT_EQL,   KC_1,    KC_2,     KC_3,     KC_TRNS,  KC_TRNS,
                        KC_0,    KC_COMM,  KC_DOT,   KC_TRNS,  KC_TRNS,
  KC_TRNS, DM_RSTP,
  DM_REC2,
  DM_PLY2, KC_TRNS, KC_TRNS
),
};

static bool recording_dynamic_macro;

static bool process_record_dynamic_macro_wrapper(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* detect dynamic macro recording state */
    case QK_DYNAMIC_MACRO_RECORD_START_1:
    case QK_DYNAMIC_MACRO_RECORD_START_2:
      if (record->event.pressed) {
        recording_dynamic_macro = true;
      }
      break;
    case QK_DYNAMIC_MACRO_RECORD_STOP:
      if (record->event.pressed) {
        recording_dynamic_macro = false;
      }
      break;
  }

  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  /* the purpose of the ..._wrapper is to detect START/ST0P keys to
     light the blue led during recording */
  if (!process_record_dynamic_macro_wrapper(keycode, record)) {
    return false;
  }

  switch (keycode) {
    /* static macro keys */
    case M_IN_CBR:
      if (record->event.pressed) {
        SEND_STRING("{}" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_IN_PRN:
      if (record->event.pressed) {
        SEND_STRING("()" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_IN_BRC:
      if (record->event.pressed) {
        SEND_STRING("[]" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_IN_ANG:
      if (record->event.pressed) {
        SEND_STRING("<>" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_POINER:
      if (record->event.pressed) {
        SEND_STRING("->");
        return false;
      }
      break;
    case M_LAMBDA:
      if (record->event.pressed) {
        SEND_STRING("=>");
        return false;
      }
      break;
    case M_NOT_EQL:
      if (record->event.pressed) {
        SEND_STRING("!=");
        return false;
      }
      break;
    case M_COL_EQL:
      if (record->event.pressed) {
        SEND_STRING(":=");
        return false;
      }
      break;
    case M_PLUS_EQL:
      if (record->event.pressed) {
        SEND_STRING("+=");
        return false;
      }
      break;
  }

  return true;
}

/* Runs just one time when the keyboard initializes. */
void matrix_init_user(void) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  ergodox_right_led_1_set(5);
  ergodox_right_led_2_set(5);
  ergodox_right_led_3_set(5);
};

/* Runs constantly in the background, in a loop. */
void matrix_scan_user(void) {
  uint8_t layer = get_highest_layer(layer_state);

  //led 2, GREEN
  if (layer == LAYER_NUM)
      ergodox_right_led_2_on();
  else
      ergodox_right_led_2_off();

  //led 3, BLUE
  if (recording_dynamic_macro)
      ergodox_right_led_3_on();
  else
      ergodox_right_led_3_off();
};

// Runs constantly in the background, in a loop.
bool led_update_user(led_t led_state) {
    if (led_state.caps_lock)
        ergodox_right_led_1_on();
    else
        ergodox_right_led_1_off();
    return false;
}
