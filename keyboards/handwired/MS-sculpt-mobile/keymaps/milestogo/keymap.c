#include "MS-sculpt-mobile.h"

#define _QWR 0
#define _CDH 1
#define _SYM 2
#define _MOV 3
#define _NUM 4 
#define _TRAN 9 

// Shorter spacing
#define XXXX  KC_NO
#define ____  KC_TRNS

// Custom macros

/* Fn Keys */
#define TT_SYM MO(_SYM)
#define TO_CDH TG(_CDH)
#define TO_MOV MO(_MOV)
#define TT_NUM MO(_NUM)
#define SSFT ACTION_MODS_ONESHOT(MOD_LSFT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*  QWERTY
*
* |ESC | F1 | F2 | F3 | F4 | F5 | F6 | f7 | F8 | F9 | F10| F11| F12|Vol-|Vol+|Mute|
*  -------------------------------------------------------------------------------'
* |  ~ |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Bakspace| Del |
* --------------------------------------------------------------------------
* | tab  |  q |  w |  e |  r |  t |  y |  u |  i |  o |  p |  [ |  ] |  \   |     |
*  -------------------------------------------------------------------------------'
* | caps  |  a |  s |  d |  f |  g |  h |  j |  k |  l |  ; |  ' | enter     |PgUp|
* --------------------------------------------------------------------------------	
* |Lsft    |  z |  x |  c |  v |  b |  n |  m |  , |  . |  / |      Rsft| Up| PgDn|
* ---------------------------------------------------------------------------------	
* |Lctl   |Lgui  |Lalt |       Space          |Ralt  |  FN |  Rctl |Left|Down|Rght|
* ---------------------------------------------------------------------------------	
*/

[_QWR] = KEYMAP( \
   KC_ESC,   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9, KC_F10,    KC_F11,   KC_F12, KC_VOLD, KC_VOLU, TO_CDH,\
   KC_ESC,   KC_1, KC_2, KC_3 ,KC_4, KC_5, KC_6, KC_7, KC_8,   KC_9, KC_0,    KC_MINUS, KC_EQL, KC_BSPC, KC_DEL,\
   KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,   KC_O, KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,\
   TT_SYM,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L, KC_SCLN, KC_QUOT,  KC_ENT, KC_PGUP,\
   KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,  KC_UP,  KC_PGDN,\
   KC_LCTL,  KC_LGUI, KC_LALT, KC_SPACE, KC_RGUI,TT_SYM,KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
),

[_CDH] = KEYMAP (\
   ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
   KC_ESC,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,   \
   KC_TAB,  KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, ____,    ____,   ____,\
   TO_MOV,  KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT, KC_ENT, ____,\
   KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, ____,   ____,\
  ____,     ____, ____ , TT_SYM, ____, ____, ____, ____, ____,   ____

),

[_SYM] = KEYMAP (\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,   \
  ____,  KC_CIRC, KC_LCBR, KC_RCBR,KC_AT, KC_PERC,         ____,   KC_LBRC,KC_LPRN,KC_RPRN,KC_UNDS,   ____,   ____,   ____,\
  ____,  KC_EXLM, KC_HASH,  KC_0,  KC_EQL, ____,           KC_ASTR,KC_MINS,KC_1,  KC_PLUS,KC_RBRC,  KC_GRV,   ____,  ____,\
  ____,     ____, ____, ____, KC_TILDE,  KC_PIPE,          KC_DLR,   ____, ____,   ____,   ____,     ____, ____, ____,\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____
),

[_MOV] = KEYMAP (\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,   \
  ____,     ____, RGUI(KC_TAB), ____, ____, RCTL(KC_B), ____, ____, ____,   ____, ____,    ____,     ____,   ____, \
  ____,     RCTL(KC_A), KC_S, RCTL(KC_K), RCTL(KC_E), ____,   ____,   KC_LEFT,KC_DOWN, KC_UP,  KC_RIGHT, ____,____,____,\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____, \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____
),

[_TRAN] = KEYMAP (\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,   \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____, \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____, \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____, \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____
)
};


const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;


 	case KC_N:
	  if(keyboard_report->mods & MOD_BIT(KC_LGUI) ) {
		clear_keyboard_but_mods();
		register_code(KC_V);
	  }
	break;
			
		
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
