#include "../../../MS_sculpt_mobile/babblePaste.h"
#include "../../MS_sculpt_mobile.h"
#include "action_layer.h"
#include "action_util.h"

#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

#define _QWR 0
#define _CDH 2
#define _SYM 3
#define _MOV 4
#define _TRAN 5


enum layer_keycodes {
QWR,
CDH,
SYM,
MOV,
NUM,
TRAN
};


// Shorter spacing
#define XXXX  KC_NO
#define ____  KC_TRNS

// Custom macros

/* Fn Keys */
#define TT_SYM MO(_SYM)
#define TT_MOV KC_FN2
#define TT_NUM MO(_NUM)
#define SSFT ACTION_MODS_ONESHOT(MOD_LSFT)

enum macro_keycodes {
DHPASTE=1,
VIBRK,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*  QWERTY
*
* |ESC | F1 | F2 | F3 | F4 | F5 | F6 | f7 | F8 | F9 | F10| F11| F12|Vol-|Vol+|_CDH|
*  -------------------------------------------------------------------------------'
* | ESC |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Bakspace| Del|
* ---------------------------------------------------------------------------
* | tab  |  q |  w |  e |  r |  t |  y |  u |  i |  o |  p |  [ |  ] |  \    |    |
*  -------------------------------------------------------------------------------'
* |Bak/Mov|  a |  s |  d |  f |  g |  h |  j |  k |  l |  ; |  ' | enter     |PgUp|
* --------------------------------------------------------------------------------
* |Lsft    |  z |  x |  c |  v |  b |  n |  m |  , |  . |  / |      Rsft| Up| PgDn|
* ---------------------------------------------------------------------------------
* |Lctl   |Lgui  |Lalt |       Space/Sym      | GUI |  Sym |  Rctl |Left|Down|Rght|
* ---------------------------------------------------------------------------------
*/

[_QWR] = KEYMAP( \
   KC_ESC,   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9, KC_F10,    KC_F11,   KC_F12, KC_VOLD, KC_VOLU, CDH,\
   KC_ESC,   KC_1, KC_2, KC_3 ,KC_4, KC_5, KC_6, KC_7, KC_8,   KC_9, KC_0,    KC_MINUS, KC_EQL, KC_BSPC, KC_DEL,\
   KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,   KC_O, KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,\
   TT_MOV,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L, KC_SCLN, KC_QUOT,  KC_ENT, KC_PGUP,\
   KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,  KC_UP,  KC_PGDN,\
   KC_LCTL,  KC_LGUI, KC_LALT, KC_FN1, KC_RGUI,TT_SYM,KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
),

[_CDH] = KEYMAP (\
   ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     QWR,  \
   KC_ESC,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,   \
   KC_TAB,  KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, ____,    ____,   ____,\
   TT_MOV,  KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT, KC_ENT, KC_2,\
   KC_LSFT, KC_Z, KC_X, KC_C, M(DHPASTE), KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, ____,   KC_1,\
  ____,     ____, ____ , KC_FN1, ____, ____, ____, ____, ____,   ____

),


/*  SYM
*
* |ESC | F1 | F2 | F3 | F4 | F5 | F6 | f7 | F8 | F9 | F10| F11| F12|Vol-|Vol+|_CDH|
*  -------------------------------------------------------------------------------'
* | ESC |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Bakspace|Del |
*  --------------------------------------------------------------------------
* | ESC: | ^  |  { |  } |  @ |  % |    |   [ | ( | )  | _  |  [ |  ] |  \    |    |
*  -------------------------------------------------------------------------------'
* |Bak/Mov|  ! |  # |  0 | =  |  { |   } | -  | 1 |  + |  ] |  ` | enter     |PgUp|
* --------------------------------------------------------------------------------
* |Lsft    |  ; | ~ |  : | ~  | "|"|  $ | *   |    |  .  |  / |      Rsft| Up| PgDn|
* ---------------------------------------------------------------------------------
* |Lctl   |Lgui  |Lalt |       Space/Sym      | GUI |  Sym |  Rctl |Left|Down|Rght|
* ---------------------------------------------------------------------------------
*/

[_SYM] = KEYMAP (\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,   \
  M(VIBRK),  KC_CIRC, KC_LCBR, KC_RCBR,KC_AT, KC_PERC,         ____,   KC_LBRC,KC_LPRN,KC_RPRN,KC_UNDS,   ____,   ____,   ____,\
  ____,    KC_EXLM, KC_HASH,  KC_0,  KC_EQL, KC_LCBR,            KC_RCBR,KC_MINS,KC_1,  KC_PLUS,KC_RBRC,  KC_GRV,   ____,  ____,\
  ____,    KC_SCLN, KC_TILDE,  KC_COLN,  KC_TILDE,  KC_PIPE,     KC_DLR, KC_ASTR, ____,  KC_DOT ,   KC_SLSH,     ____, ____, ____,\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____
),
/*
* |ESC | MAC| Win|RdLn| VI |    |    |    |    |    |    |    |    |    |    |    |
*  -------------------------------------------------------------------------------'
* |     |    |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Bakspace| Del|
* ---------------------------------------------------------------------------
* | tab  |    |    |Find|    |pTab |DSOL|DelW| Up |DelW|DEOL|  [ |  ] |  \    |    |
*  -------------------------------------------------------------------------------'
* |Bak/Mov|    |    |    |    |nTab |GSOL| <- | Dwn | -> | EOL |  ' | enter   |PgUp|
* --------------------------------------------------------------------------------
* |Lsft    |Undo| Cut|Copy|Pste|    |    |    |    |    |  / |      Rsft| Up| PgDn|
* ---------------------------------------------------------------------------------
* |Lctl   |Lgui  |Lalt |       Space/Sym      | GUI |  Sym |  Rctl |Left|Down|Rght|
* ---------------------------------------------------------------------------------
*/

[_MOV] = KEYMAP (\
  ____,    B_MAC,B_WIN,B_READ, B_VI, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
  ____,      ____, B_PAPP, B_NAPP, ____, ____,      ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,   \
  ____,     B_UNDO, ____, B_BFND, ____, B_PTAB,     B_DSOL, B_DLW, B_UP,   B_DRW, B_DEOL,  ____,  ____,   ____, \
  ____,     B_SELA, B_BRLD, ____, ____, B_NXTB,     B_GSOL, B_L1C, B_DOWN, B_R1C,B_GEOL,   ____, ____, ____,\
  ____,     B_UNDO,B_CUT, B_COPY, B_PAST, B_PAST,    ____, ____, ____, ____, ____,       ____,  ____,   ____, \
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____
),

[_TRAN] = KEYMAP (\
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, ____,   \
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, \
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, \
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, \
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____
)
};

const uint16_t PROGMEM fn_actions[] = {
[1] = ACTION_LAYER_TAP_KEY(_SYM,KC_SPACE),
[2] = ACTION_LAYER_TAP_KEY(_MOV,KC_BSPC)
};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWR:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        layer_off(_CDH);
      }
      return false;
      break;

    case CDH:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        layer_on(_CDH);
      }
      return false;
      break;

    case SYM:
      if (record->event.pressed) {
        layer_on(_SYM);
      } else {
		layer_off(_SYM);
      }
     return false;
     break;

   }
 return true;

}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{

/* If id is in the range of BABL macros, call the babl function */
/* Any clever remapping with modifiers should happen here e.g. shift bablkey does opposite*/
#ifdef USE_BABLPASTE

   if( id >= BABL_START_NUM && id < (BABL_START_NUM + BABL_NUM_MACROS ) ) {
   		if (record->event.pressed)  { // is there a case where this isn't desired?

   			babblePaste ( record,  id );
   			return MACRO_NONE;
   		}
   	}
#endif


  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;

 /* Colemak mod-dh moves the D key to the qwerty V position
   This hack makes apple-V_position do what I mean */
 	case DHPASTE:
		if(keyboard_report->mods & MOD_BIT(KC_LGUI) ) {
			if (record->event.pressed) {
	  	 		clear_keyboard_but_mods();
		 		register_code(KC_V);
	     	} else {
		 		unregister_code(KC_V);
	    	}
		} else {
            if (record->event.pressed) {
          		register_code(KC_D);
            } else {
           		unregister_code(KC_D);
	   		}
		}
	break;

	case VIBRK: // vi esc:
		 if (record->event.pressed) {
			return MACRO( T(ESC),D(LSFT),T(SCLN),U(LSFT), END );
		 }
	break;




	default:
    	return MACRO_NONE;
    }


return MACRO_NONE;
};





void matrix_init_user(void) {
}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {

}






