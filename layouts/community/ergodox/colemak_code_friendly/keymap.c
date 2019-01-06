/* -*- Mode:C; c-basic-offset:2; tab-width:2; indent-tabs-mode:nil; evil-indent-convert-tabs:t; -*- */

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

//#define DYNAMIC_MACRO_SIZE 128

#define LAYER_BASE 0 /* default layer */
#define LAYER_NUM  1 /* numbers and symbols */


enum custom_keycodes5 {
  PLACEHOLDER = SAFE_RANGE, /* can always be here */

  M_ARROW_RMINUS,
  M_ARROW_REQL,
  M_DIV_EQL,
  M_LT_EQL,
  M_GT_EQL,
  M_NOT_EQL,
  M_COL_EQL,
  M_PLUS_EQL,

  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * .--------------------------------------------------.  .--------------------------------------------------.
 * | Grave  |   !  |   @  |   #  |   $  |   %  | Bspc |  | Enter|   ^  |   &  |   *  |   -  |   =  |   +    |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |   (  |  |  )   |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * | Esc/L1 |   A  |   R  |   S  |   T  |   D  |------|  |------|   H  |   N  |   E  |   I  |   O  |  ' /L1 |
 * |--------+------+------+------+------+------|   [  |  |  ]   |------+------+------+------+------+--------|
 * | OSL(1) |Z/LCTL|   X  |   C  |   V  |B/RALT|      |  |      |K/RALT|   M  |   ,  |   .  |/ RCTL| TG(1)  |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   | LCtl |Super | Alt  |   {  |   }  |                              | Left | Down | Up   |Right | Del  |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |CapsLk| Ins  |  | Home | End  |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |   ?  |  | PgUp |      |      |
 *                               | Tab  | Enter|------|  |------| Space| Bspc |
 *                               |LShift|      |   _  |  | PgDn |      |RShift|
 *                               '--------------------'  '--------------------'
 */

[LAYER_BASE] = LAYOUT_ergodox(  /* layer 0 : default */
  /* left hand */
  KC_GRV,         KC_EXLM,       KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,         KC_BSPC,
  KC_TAB,         KC_Q,          KC_W,     KC_F,     KC_P,     KC_G,            KC_LPRN,
  LT(1, KC_ESC),  KC_A,          KC_R,     KC_S,     KC_T,     KC_D,
  OSL(1),         LCTL_T(KC_Z),  KC_X,     KC_C,     KC_V,     RALT_T(KC_B),    KC_LBRC,
  KC_LCTL,        KC_LGUI,       KC_LALT,  KC_LCBR,  KC_RCBR,
  
                                                     KC_CAPS,  KC_INS,
                                                               KC_QUES,
                                     LSFT_T(KC_TAB), KC_ENT,   KC_UNDS,
  /* right hand */
  KC_ENT,         KC_CIRC,       KC_AMPR,  KC_ASTR,  KC_MINS,  KC_EQL,           KC_PLUS,
  KC_RPRN,        KC_J,          KC_L,     KC_U,     KC_Y,     KC_SCLN,          KC_BSLS,
                  KC_H,          KC_N,     KC_E,     KC_I,     KC_O,             LT(1, KC_QUOT),
  KC_RBRC,        RALT_T(KC_K),  KC_M,     KC_COMM,  KC_DOT,   RCTL_T(KC_SLSH),  TG(1),
                                 KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,          KC_DEL,
  KC_HOME, KC_END,
  KC_PGUP,
  KC_PGDN, KC_SPC, LSFT_T(KC_BSPC)
),
/* Keymap 1: Numbers, Macro Record
 *
 * .--------------------------------------------------.  .--------------------------------------------------.
 * |        |      |  F12 |  F11 |  F10 |      | Pause|  |PrnScr|      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|  |------+------+------+------+------+------+--------|
 * |        |      |  F9  |  F8  |  F7  |  =>  |      |  |      |  <=  |   7  |   8  |   9  |      |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |  :=  |  F6  |  F5  |  F4  |  ->  |------|  |------|  >=  |   4  |   5  |   6  |      |        |
 * |--------+------+------+------+------+------|      |  |      |------+------+------+------+------+--------|
 * |        |  +=  |  F3  |  F2  |  F1  |  /=  |      |  |      |  !=  |   1  |   2  |   3  |      |        |
 * '--------+------+------+------+------+-------------'  '-------------+------+------+------+------+--------'
 *   | MUTE | VOLD | VOLU |      |      |                              |   0  |   ,  |   .  |      |      |
 *   '----------------------------------'                              '----------------------------------'
 *                                      .-------------.  .-------------.
 *                                      |Stop  |      |  |      |      |
 *                               .------+------+------|  |------+------+------.
 *                               |      |      |Start1|  |Start2|      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |Play1 |  |Play2 |      |      |
 *                               '--------------------'  '--------------------'
 */
[LAYER_NUM] = LAYOUT_ergodox(
  /* left hand */
  KC_TRNS, KC_TRNS,    KC_F12,  KC_F11,   KC_F10,   KC_TRNS,         KC_PAUSE,
  KC_TRNS, KC_TRNS,    KC_F9,   KC_F8,    KC_F7,    M_ARROW_REQL,    KC_TRNS,
  KC_TRNS, M_COL_EQL,  KC_F6,   KC_F5,    KC_F4,    M_ARROW_RMINUS,
  KC_TRNS, M_PLUS_EQL, KC_F3,   KC_F2,    KC_F1,    M_DIV_EQL,       KC_TRNS,
  KC_MUTE, KC_VOLD,    KC_VOLU, KC_TRNS,  KC_TRNS,
  
                                                  DYN_REC_STOP,   KC_TRNS,
                                                           DYN_REC_START1,
                                        KC_TRNS, KC_TRNS, DYN_MACRO_PLAY1,
  /* right hand */
  KC_PSCR, KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS, M_LT_EQL,   KC_7,    KC_8,     KC_9,     KC_TRNS,  KC_TRNS,
           M_GT_EQL,   KC_4,    KC_5,     KC_6,     KC_TRNS,  KC_TRNS,
  KC_TRNS, M_NOT_EQL,  KC_1,    KC_2,     KC_3,     KC_TRNS,  KC_TRNS,
                       KC_0,    KC_COMM,  KC_DOT,   KC_TRNS,  KC_TRNS,
  KC_TRNS, KC_TRNS,
  DYN_REC_START2,
  DYN_MACRO_PLAY2, KC_TRNS, KC_TRNS
),

};

const uint16_t PROGMEM fn_actions[] = {
};

static int recording_dynamic_macro;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
    /* detect dynamic macro recording state */
    case DYN_REC_START1:
    case DYN_REC_START2:
      if (record->event.pressed) {
        recording_dynamic_macro = 1;
      }
      break;
    case DYN_REC_STOP:
      if (record->event.pressed) {
        recording_dynamic_macro = 0;
      }
      break;
    /* static macro keys */
    case M_ARROW_RMINUS:
      if (record->event.pressed) {
        SEND_STRING("->");
        return false;
      }
      break;
    case M_ARROW_REQL:
      if (record->event.pressed) {
        SEND_STRING("=>");
        return false;
      }
      break;
    case M_DIV_EQL:
      if (record->event.pressed) {
        SEND_STRING("/=");
        return false;
      }
      break;
    case M_LT_EQL:
      if (record->event.pressed) {
        SEND_STRING("<=");
        return false;
      }
      break;
    case M_GT_EQL:
      if (record->event.pressed) {
        SEND_STRING(">=");
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
};

/* Runs constantly in the background, in a loop. */
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  //reduce LED on time to 1/6th because LEDs are too strong
  static uint8_t state;
  if (++state < 6) return;
  state = 0;


  //led 1, RED, Caps-Lock ON
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ergodox_right_led_1_on();

  //led 2, GREEN
  if (layer == LAYER_NUM) ergodox_right_led_2_on();    

  //led 3, BLUE
  if (recording_dynamic_macro) ergodox_right_led_3_on();
};
