#include QMK_KEYBOARD_H
#include "keymap_bepo.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BASE 0
#define _SYMBOLS 1
#define _MEDIA 2
#define _TRNS 8

#define PEDAL_DELAY 250
#define KEY_DELAY 130

enum custom_keycodes {
    M_LP = SAFE_RANGE, // left pedal
    M_RP,   // right pedal
    M_SF,   // shift
    M_SFS,  // shift and space
    M_L1E,  // L1 and space
    L2INS,  // L2 and insert
    L2LOC,  // Lock L2
    M_UN,   // undo
    M_CUT,  // cut
    M_CP,   // copy
    M_PS,   // paste
    M_SE,   // search
    M_SFU,  // shift and underscore
};

static uint16_t key_timer_left_pedal;
static uint16_t key_timer_right_pedal;
static uint16_t key_timer_shift;
static uint16_t key_timer_1;
static uint16_t key_timer_2;

static uint16_t shift_count = 0; //this is used to keep track of shift state and avoid inserting non breakable space
static uint16_t l2_locked = 0; //this indicate wether L2 is locked

#define BP_CBSP  CTL_T(KC_BSPC)
#define BP_CDEL  CTL_T(KC_DEL)

//layout : http://www.keyboard-layout-editor.com/#/gists/4480e3ab8026eb7c710a7e22203ef4aa
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* base
 *   left foot clicked is right click
 *   left foot pressed is layer 2
 *   right foot clicked is left click
 *   right foot pressed is layer 1 + scroll lock (used with autohotkey for easier scrolling with trackballs)
 *                      ,------.                                    ..                                    ,------.                      *
 *               ,------|  F3  |-------------.                      ..                      ,-------------|  F10 |------.               *
 *        ,------|  F2  |------|  F4  |  F5  |------.               ..               ,------|  F8  |  F9  |------| F11  |------.        *
 *        |  F1  |------| »/3  |------|------|  F6  |               ..               |  F7  |------|------| -/8  |------|  F12 |        *
 * ,------+------| «/2  |------|  (/4 | )/5  |------|               ..               |------| @/6  | +/7  |------| //9  |------+------. *
 * |  ESC | "/1  |------|  O   |------|------|  ¨   |               ..               |  ^   |------|------|  D   |------| * /0 |BCKSP | *
 * |------+------|  É   |------|  P   |  È   |------|               ..               |------|  K   |  V   |------|  L   |------+------| *
 * | TAB  |  B   |------|  E   |------|------|  _   |               ..               | =/°  |------|------|  S   |------|  J   |ENTER | *
 * |------+------|  U   |------|  I   |  F   |------|               ..               |------|  C   |  T   |------|  R   |------+------| *
 * | `    |  A   |------|  Y   |------|------|  ;   |               ..               |  !   |------|------|  UP  |------|  N   |  '/? | *
 * |------+------|  À   |------|  X   |  W   |------|-------------. .. .-------------|------|  M   |  G   |------|  H   |------+------| *
 * | SHIFT|  Z   |------|  .   |------|------|sp/sh |bsp/ct|L2/ins| .. |L2lock|del/CT|sp/sh |------|------| DOWN |------|  Q   |SHIFT | *
 * |------+------|  /   |------|  ,   | space|------|------|------  ..  ------|------|------| L1/sp| LEFT |------|  UP  |------+------| *
 * | CTRL | win  |------/      \-------------| L1   | alt  |        ..        | CAPS | L1   |-------------/      \------| :    | CTRL | *
 * `-------------/                           \-------------/        ..        \-------------/                           \-------------/ *
 */
[_BASE] = LAYOUT(
           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     \
  KC_ESC,  BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN, BP_DIAE,                                        BP_DCIR, BP_AT,   BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, KC_BSPC, \
  KC_TAB,  BP_B,    BP_EACU, BP_O,    BP_P,    BP_EGRV, BP_UNDS,                                        BP_EQL,  BP_K,    BP_V,    BP_D,    BP_L,    BP_J,    KC_ENT,  \
  BP_GRV,  BP_A,    BP_U,    BP_E,    BP_I,    BP_F,    BP_SCLN,                                        BP_EXLM, BP_C,    BP_T,    BP_S,    BP_R,    BP_N,    BP_QUOT, \
  M_SF,    BP_Z,    BP_AGRV, BP_Y,    BP_X,    KC_RBRC, M_SFS,   BP_CBSP, L2INS,        L2LOC, BP_CDEL, M_SFS,   BP_M,    BP_G,    KC_UP,   BP_H,    BP_Q,    M_SF, \
  KC_LCTL, KC_LGUI, KC_PSLS, BP_DOT,  BP_COMM, KC_SPACE,M_L1E,   KC_LALT,                     KC_CAPS, M_L1E,  KC_SPACE,  KC_LEFT, KC_DOWN, KC_RIGHT,BP_COLN, KC_RCTL,   \
  //left pedals
  M_LP, M_RP, KC_TRNS, \
  //right pedals
  M_LP, M_RP, KC_TRNS \
),

 /* Larer 1 for symbols.
 *   left foot is middle click
  *                      ,------.                                    ..                                    ,------.                      *
  *               ,------|      |-------------.                      ..                      ,-------------|      |------.               *
  *        ,------|      |------|      |      |------.               ..               ,------|      |      |------|      |------.        *
  *        |      |------|  §   |------|------|      |               ..               |      |------|------|  ±   |------|      |        *
  * ,------+------|  ¶   |------|  µ   |      |------|               ..               |------|  ≤   |  ≥   |------|  ÷   |------+------. *
  * |      |  ¤   |------|  {   |------|------|  ~   |               ..               |  ˇ   |------|------|  ]   |------|  ×   |      | *
  * |------+------|  *   |------|  }   |  `   |------|               ..               |------|  #   |  [   |------|  %   |------+------| *
  * |      |  \   |------|  (   |------|------|      |               ..               |  ≠   |------|------|  >   |------|  ‰  |      | *
  * |------+------|  Ù   |------|  )   |  +   |------|               ..               |------|  Ç   |  <   |------|  &   |------+------| *
  * |      |  =   |------| copy |------|------|  :   |               ..               |  ?   |------|------| PGUP |------|  _   |      | *
  * |------+------|  cut |------| paste|search|------|-------------. .. .-------------|------|  $   |  =   |------|  |   |------+------| *
  * |      | undo |------|  \   |------|------|      |      |      | .. |      |      |      |------|------| PGDN |------|  /   |      | *
  * |------+------|      |------|      |      |------|------|------  ..  ------|------|------|      | HOME |------| PGDN |------+------| *
  * |      |      |------/      \-------------|      |      |        ..        |      |      |-------------/      \------|      |      | *
  * `-------------/                           \-------------/        ..        \-------------/                           \-------------/ *
  *
  */
[_SYMBOLS] = LAYOUT(
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          \
  KC_TRNS, BP_CURR, BP_PARA, BP_SECT, BP_DGRK, KC_TRNS, BP_TILD,                                       BP_CARN, BP_LEQL, BP_GEQL, BP_PLMN, BP_DIV,  BP_MUL,  KC_TRNS, \
  KC_TRNS, BP_BSLS, BP_ASTR, BP_LCBR, BP_RCBR, BP_GRV,  KC_TRNS,                                       BP_NEQL, BP_HASH, BP_LBRC, BP_RBRC, BP_PERC, BP_PERM, KC_TRNS, \
  KC_TRNS, BP_EQL,  BP_UGRV, BP_LPRN, BP_RPRN, BP_PLUS, BP_COLN,                                       BP_QUES, BP_CCED, BP_LABK, BP_RABK, BP_AMPR, BP_UNDS, KC_TRNS, \
  KC_TRNS, M_UN,    M_CUT,   M_CP,    M_PS,    M_SE,    KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, BP_DLR,  BP_EQL,  KC_PGUP, BP_PIPE, BP_SLSH, KC_TRNS, \
  KC_TRNS, KC_TRNS, BP_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END,  KC_TRNS, KC_TRNS,  \
  //left pedals
  KC_TRNS, KC_BTN1, KC_TRNS, \
  //right pedals
  KC_TRNS, KC_BTN1, KC_TRNS  \
),

 /* MEDIA, mouse and numpad.
  * right pedal is left clic
  *                      ,------.                                    ..                                    ,------.                      *
  *               ,------|PAUSE |-------------.                      ..                      ,-------------| PRINT|------.               *
  *        ,------|SCROLL|------|MUTE  |VOLUD |------.               ..               ,------| pre  | next |------| calc |------.        *
  *        |RESET |------| stop |------|------|VOLDU |               ..               | play |------|------| stop |------| num  |        *
  * ,------+------|      |------| pre  | next |------|               ..               |------| pre  | next |------|      |------+------. *
  * |      |      |------|scrolu|------|------| play |               ..               | play |------|------|  8   |------|  -   |      | *
  * |------+------|      |------|      | bt4  |------|               ..               |------| next |  7   |------|  9   |------+------| *
  * |      |      |------|scrold|------|------| bt5  |               ..               | pre  |------|------|  5   |------|  +   |      | *
  * |------+------|      |------|mclic | rclic|------|               ..               |------| rclic|  4   |------|  6   |------+------| *
  * |      |      |------|      |------|------| lclic|               ..               | lclic|------|------|  2   |------|  *   |      | *
  * |------+------|      |------|      | mclck|------|-------------. .. .-------------|------| mclic|  1   |------|  3   |------+------| *
  * |      |      |------|      |------|------|      |      |      | .. |      |      |      |------|------| num. |------|  /   |      | *
  * |------+------|      |------|      |      |------|------|------  ..  ------|------|------|      |  0   |------|  .   |------+------| *
  * |      |      |------/      \-------------|      |      |        ..        |      |      |-------------/      \------|  ,   |      | *
  * `-------------/                           \-------------/        ..        \-------------/                           \-------------/ *
  *
  */
[_MEDIA] = LAYOUT(
           RESET,   KC_SLCK, KC_PAUS, KC_MUTE, KC_VOLD, KC_VOLU,                                     KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, KC_CALC, KC_NLCK,          \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_MPRV, KC_MNXT, KC_MPLY,                                     KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, KC_TRNS, KC_PMNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_U, KC_TRNS, KC_BTN4, KC_BTN5,                                     KC_BTN4, KC_BTN5, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D, KC_BTN3, KC_BTN2, KC_BTN1,                                     KC_BTN1, KC_BTN2, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST, KC_TRNS, \
  KC_TRNS, M_UN,    M_CUT,   M_CP,    M_PS,    KC_BTN3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN3, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_PDOT, BP_DOT,  BP_COMM, KC_TRNS,  \
  //left pedals
  KC_BTN3, M_RP,    KC_TRNS, \
  //right pedals
  KC_BTN3, M_RP,    KC_TRNS  \
),

/* TRNS - skeleton for laters
 *                      ,------.                                    ..                                    ,------.                      *
 *               ,------|      |-------------.                      ..                      ,-------------|      |------.               *
 *        ,------|      |------|      |      |------.               ..               ,------|      |      |------|      |------.        *
 *        |      |------|      |------|------|      |               ..               |      |------|------|      |------|      |        *
 * ,------+------|      |------|      |      |------|               ..               |------|      |      |------|      |------+------. *
 * |      |      |------|      |------|------|      |               ..               |      |------|------|      |------|      |      | *
 * |------+------|      |------|      |      |------|               ..               |------|      |      |------|      |------+------| *
 * |      |      |------|      |------|------|      |               ..               |      |------|------|      |------|      |      | *
 * |------+------|      |------|      |      |------|               ..               |------|      |      |------|      |------+------| *
 * |      |      |------|      |------|------|      |               ..               |      |------|------|      |------|      |      | *
 * |------+------|      |------|      |      |------|-------------. .. .-------------|------|      |      |------|      |------+------| *
 * |      |      |------|      |------|------|      |      |      | .. |      |      |      |------|------|      |------|      |      | *
 * |------+------|      |------|      |      |------|------|------  ..  ------|------|------|      |      |------|      |------+------| *
 * |      |      |------/      \-------------|      |      |        ..        |      |      |-------------/      \------|      |      | *
 * `-------------/                           \-------------/        ..        \-------------/                           \-------------/ *
 *
 */

[_TRNS] = LAYOUT(
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  //left pedals
  KC_BTN3, M_RP,    KC_TRNS, \
  //right pedals
  KC_BTN3, M_RP,    KC_TRNS  \
),

};

void hold_shift(void) {
  shift_count = shift_count + 1;
  register_code(KC_LSHIFT);
}

void release_shift(void) {
  shift_count = shift_count - 1;
  if(shift_count <= 0){
    unregister_code(KC_LSHIFT);
    shift_count = 0;
  }
}

void press_space(void) {
  if(shift_count > 0) unregister_code (KC_LSHIFT);
  tap_code(KC_SPACE);
  if(shift_count > 0) register_code (KC_LSHIFT);
}

void press_enter(void) {
  if(shift_count > 0) unregister_code (KC_LSHIFT);
  tap_code (KC_ENT);
  if(shift_count > 0) register_code (KC_LSHIFT);
}

void press_underscore(void) {
  if(shift_count > 0) unregister_code (KC_LSHIFT);
  tap_code ((unsigned char) BP_UNDS);
  if(shift_count > 0) register_code (KC_LSHIFT);
}

// Bleah globals need to be initialized.
uint8_t old_layer=_BASE;

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    frenchdev_led_1_off();
    frenchdev_led_2_off();
    switch (layer) {
        case _BASE:
            frenchdev_led_2_on();
            break;
        case _SYMBOLS:
            frenchdev_led_1_on();
            break;
        case _MEDIA:
           frenchdev_led_1_on();
           frenchdev_led_2_on();
        default:
            // none
            break;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case M_LP: //left pedal
      if (record->event.pressed) {
        layer_on(1);
        register_code (KC_SLCK);
        key_timer_left_pedal = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_left_pedal) < KEY_DELAY) {
           tap_code (KC_BTN2);
        }
        unregister_code (KC_SLCK);
        layer_off(1);
      }
      break;
    case M_RP: //right pedal
      if (record->event.pressed) {
        layer_on(2);
        key_timer_right_pedal = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_right_pedal) < PEDAL_DELAY) {
           tap_code (KC_BTN1);
        }
        layer_off(2);
      }
      break;
    case M_SF: // shift, using macro to keep track of shift state and avoid inserting nbsp by mistake
      if (record->event.pressed) {
        hold_shift();
      } else {
        release_shift();
      }
      break;
    case M_SFS: // shift when held, space when tapped
      if (record->event.pressed) {
        hold_shift();
        key_timer_shift = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_shift) < KEY_DELAY) {
          press_space();
        }
        release_shift();
      }
      break;
    case M_SFU: // shift when held, _ when tapped
      if (record->event.pressed) {
        hold_shift();
        key_timer_shift = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_shift) < KEY_DELAY) {
          press_space();
        }
        release_shift();
      }
      break;
    case M_L1E: // L1 when held, space when tapped
      if (record->event.pressed) {
        layer_on(1);
        key_timer_1 = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_1) < KEY_DELAY) {
          press_enter();
        }
        layer_off(1);
      }
      break;
    case L2INS: //activate layer 2, if released before 100ms trigger INS. basicaly equivalent to LT(2, KC_INS) but without delay for activation of layer 2
      if (record->event.pressed) {
        layer_on(2);
        key_timer_2 = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_2) < KEY_DELAY) {
           tap_code (KC_INS);
        }
        l2_locked = 0;
        layer_off(2);
      }
      break;
    case L2LOC: //lock L2
      if (record->event.pressed) {
        key_timer_2 = timer_read(); // if the key is being pressed, we start the timer.
        layer_on(2);
      } else {
        if (timer_elapsed(key_timer_2) < KEY_DELAY && l2_locked == 0) {
          l2_locked = 1;
          layer_on(2);
        } else {
          l2_locked = 0;
          layer_off(2);
        }
      }
      break;
    case M_UN: // undo
      if (record->event.pressed) {
        tap_code16(C(BP_Z));
      }
      break;
    case M_CUT: // cut
      if (record->event.pressed) {
        tap_code16(C(BP_X));
      }
      break;
    case M_CP: // copy
      if (record->event.pressed) {
        tap_code16(C(BP_C));
      }
      break;
    case M_PS: // paste
      if (record->event.pressed) {
        tap_code16(C(BP_V));
      }
      break;
    case M_SE: // search
      if (record->event.pressed) {
        tap_code16(C(BP_F));
      }
      break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)){
    frenchdev_led_3_on();
  } else {
    frenchdev_led_3_off();
  }
  return ;
}
