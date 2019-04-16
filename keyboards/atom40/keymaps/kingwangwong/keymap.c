#include "atom40.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _ML 0 //Main layer
#define _FL 1 //Function layer
#define _NL 2 //Number layer
#define _SL 3 //Symbol layer
#define _RL 4 //Reset layer


#define SPC_FUN LT(_FL, KC_SPC)
#define BSC_NUM LT(_NL, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

      /* 0: Main Layer

   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ ESC │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │ENTER│  
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴─────┤
   * │ TAB  │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │ ;        │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───────┤
   * │ LSHFT   │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /    │
   * ├─────┬───┴─┬───┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬─────┤
   * │LCTRL│LGUI │LALT │MO(SL│SPACE(_FL)  │BACKSPACE(_NL)  │RSHFT│     │MO(RL│
   * └─────┴─────┴─────┴─────┴────────────┴────────────────┴─────┴─────┴─────┘
   */
    [_ML] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_ENT,  
        KC_TAB,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN,          
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,          
        KC_LCTL, KC_LGUI, KC_LALT, MO(_SL),        SPC_FUN,        BSC_NUM,         KC_RSFT, ______,  MO(_RL)),


      /* 1: Function Layer

   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │HOME │ UP  │END  │     │     │ F1  │ F2  │ F3  │ F4  │     │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴─────┤
   * │      │     │LEFT │DOWN │RIGHT│     │     │ F5  │ F6  │ F7  │ F8       │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───────┤
   * │         │     │     │PGDWN│PGUP │     │     │ F9  │ F10 │ F11 │ F12   │
   * ├─────┬───┴─┬───┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬─────┤
   * │     │     │     │MO(SL│SPACE(_FL)  │BACKSPACE(_NL)  │     │     │     │
   * └─────┴─────┴─────┴─────┴────────────┴────────────────┴─────┴─────┴─────┘
   */
    [_FL] = LAYOUT(
        ______,  XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX, KC_F1, KC_F2,  KC_F3,  KC_F4,  ______,  
        ______,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, KC_F5, KC_F6,  KC_F7,  KC_F8,           
        ______,  XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, KC_F9, KC_F10, KC_F11, KC_F12,          
        ______,  ______,  ______,  XXXXXXX,          ______,           ______,        ______, ______,  ______),



      /* 2: Number Layer

   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │  ~  │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  (  │  )  │     │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴─────┤
   * │   `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  8  │ 0        │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───────┤
   * │         │     │     │     │     │     │     │     │     │     │       │
   * ├─────┬───┴─┬───┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬─────┤
   * │     │     │     │MO(SL│SPACE(_FL)  │BACKSPACE(_NL)  │     │     │     │
   * └─────┴─────┴─────┴─────┴────────────┴────────────────┴─────┴─────┴─────┘
   */
    [_NL] = LAYOUT(
        KC_TILD,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  ______,  
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,              
        ______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           
        ______,  ______,   ______,  XXXXXXX,          ______,           ______,           ______,  ______,  ______),

      /* 3: Symbol Layer

   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │  |  │  _  │  +  │  {  │  }  │     │     │     │     │     │  "  │  "  │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴─────┤
   * │   \  │  -  │  =  │  [  │  ]  │     │     │     │     │     │ '        │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───────┤
   * │         │     │     │     │     │     │     │     │     │     │       │
   * ├─────┬───┴─┬───┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬─────┤
   * │     │     │     │MO(SL│SPACE(_FL)  │BACKSPACE(_NL)  │     │     │     │
   * └─────┴─────┴─────┴─────┴────────────┴────────────────┴─────┴─────┴─────┘
   */
    [_SL] = LAYOUT(
        KC_PIPE,  KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DQUO, KC_DQUO,  
        KC_BSLS,  KC_MINS, KC_EQL,   KC_LBRC, KC_RBRC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT,           
        ______,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           
        ______,   ______,  ______,   XXXXXXX,           ______,           ______,           ______,  ______,  ______),

        /* 4: Reset Layer

   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │RESET│     │     │     │     │     │     │     │     │     │     │     │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴─────┤
   * │      │     │     │     │     │     │     │     │     │     │          │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬───────┤
   * │         │     │     │     │     │     │     │     │     │     │       │
   * ├─────┬───┴─┬───┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬─────┤
   * │     │     │     │     │            │                │     │     │     │
   * └─────┴─────┴─────┴─────┴────────────┴────────────────┴─────┴─────┴─────┘
   */
    [_RL] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,           XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX,  XXXXXXX),
};  

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 6);
    } else {
        DDRB &= ~(1 << 6);
    }
}

