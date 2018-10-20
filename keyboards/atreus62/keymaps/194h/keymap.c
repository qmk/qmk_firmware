#include QMK_KEYBOARD_H

//The current Nordic and Norwegian layout files are a mess. I'll do it myself:
//Norwegian
#define  NO_AE    KC_QUOT     //  Æ
#define  NO_AO    KC_LBRC     //  Å
#define  NO_BSLS  KC_EQL      //  Backslash
#define  NO_LT    KC_NUBS     //  <
#define  NO_MINS  KC_SLSH     //  -
#define  NO_OE    KC_SCLN     //  Ø
#define  NO_PIPE  KC_GRV      //  |
#define  NO_PLUS  KC_MINS     //  +
#define  NO_QUOT  KC_NUHS     //  '
#define  NO_UMLA  KC_RBRC     //  ¨
//Norwegian - Modifier dependant definitions
#define  NO_EXLM  LSFT(KC_1)        //  !
#define  NO_DQT   LSFT(KC_2)        //  "
#define  NO_AT    RALT(KC_2)        //  @
#define  NO_HASH  LSFT(KC_3)        //  #
#define  NO_EUR   LSFT(KC_4)        //  €
#define  NO_DLR   RALT(KC_4)        //  $
#define  NO_PERC  LSFT(KC_5)        //  %
#define  NO_AND   LSFT(KC_6)        //  &
#define  NO_SLSH  LSFT(KC_7)        //  /
#define  NO_PO    LSFT(KC_8)        //  (
#define  NO_PC    LSFT(KC_9)        //  )
#define  NO_EQL   LSFT(KC_0)        //  =
#define  NO_LCBR  RALT(KC_7)        //  {
#define  NO_LBRC  RALT(KC_8)        //  [
#define  NO_RBRC  RALT(KC_9)        //  ]
#define  NO_RCBR  RALT(KC_0)        //  }
#define  NO_COLN  LSFT(KC_DOT)      //  :
#define  NO_SCLN  LSFT(KC_COMM)     //  ;
#define  NO_MU    RALT(KC_M)        //  µ
#define  NO_EURO  RALT(KC_E)        //  €
#define  NO_SECT  LSFT(KC_GRV)      //  §
#define  NO_GERC  RALT(KC_COMM)     //  ¸
#define  NO_QUAR  LSFT(RALT(KC_4))  //  ¼
//Norwegian layout - dependant on previous definitions
#define  NO_UNDS  LSFT(NO_MINS)  //  _
#define  NO_QUES  LSFT(NO_PLUS)  //  ?
#define  NO_GRAV  LSFT(NO_BSLS)  //  `
#define  NO_GT    LSFT(NO_LT)    //  >
#define  NO_HALF  RALT(NO_LT)    //  ½
#define  NO_HAT   LSFT(NO_UMLA)  //  ^
#define  NO_ASTR  LSFT(NO_QUOT)  //  *
#define  NO_TILD  RALT(NO_UMLA)  //  ~

//One Shot Modifier
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_LGUI OSM(MOD_LGUI)
#define OSM_RCTL OSM(MOD_RCTL)
#define OSM_RALT OSM(MOD_RALT)
#define OSM_RSFT OSM(MOD_RSFT)
#define OSM_RGUI OSM(MOD_RGUI)

//Layers
#define L1 0
#define L2 1
#define L3 2
#define L4 3
#define L5 4

// Momentary switch to layer - One Shot Layer
#define OSL_L3 OSL(L3)
#define OSL_L4 OSL(L4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L1] = LAYOUT(
	KC_LGUI,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                     KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_RGUI,
	KC_TAB,        KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                     KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         NO_DQT,
	KC_BSPC,       KC_A,         KC_S,         KC_D,         KC_F,         KC_G,                                     KC_H,         KC_J,         KC_K,         KC_L,         NO_SCLN,      NO_QUOT,
	OSM_LSFT,      KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,                                     KC_N,         KC_M,         KC_COMM,      KC_DOT,       NO_MINS,      OSM_RSFT,
	CTL_T(KC_ESC), MO(L5),       KC_LEAD,      OSM_LALT,     MO(L4),       OSL_L3,       KC_SPC,       KC_ENT,       OSL_L3,       MO(L4),       OSM_RALT,     NO_EQL,       NO_PLUS,      KC_RCTL
  ),
  [L2] = LAYOUT(
	_______,       _______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,      _______,
	_______,       _______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,      NO_AO,
	_______,       _______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      NO_OE,        NO_AE,
	_______,       _______,      _______,      _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,      _______,
	_______,       _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______       
  ),
  [L3] = LAYOUT(
	NO_LBRC,       XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,                                  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      NO_RBRC,
	NO_LCBR,       XXXXXXX,      XXXXXXX,      NO_AT,        XXXXXXX,      NO_TILD,                                  NO_QUES,      NO_EXLM,      NO_PIPE,      XXXXXXX,      XXXXXXX,      NO_RCBR,
	_______,       NO_ASTR,      NO_BSLS,      NO_DLR,       NO_HASH,      XXXXXXX,                                  NO_HAT,       XXXXXXX,      NO_COLN,      NO_SLSH,      NO_SCLN,      NO_QUOT,
	NO_PO,         KC_0,         NO_SECT,      NO_PERC,      XXXXXXX,      NO_GRAV,                                  NO_AND,       NO_UMLA,      NO_LT,        NO_GT,        NO_UNDS,      NO_PC,
	XXXXXXX,       _______,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      _______,      _______,      XXXXXXX
  ),
  [L4] = LAYOUT(
	KC_ESC,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,                                    XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,
	XXXXXXX,       KC_F6,        KC_F7,        KC_F8,        KC_F9,        KC_F10,                                   KC_HOME,      KC_PGDN,      KC_PGUP,      KC_END,       XXXXXXX,      XXXXXXX,
	_______,       KC_F11,       KC_F12,       KC_F13,       KC_F14,       KC_F15,                                   KC_LEFT,      KC_DOWN,      KC_UP,        KC_RIGHT,     XXXXXXX,      KC_DEL,
	XXXXXXX,       KC_F16,       KC_F17,       KC_F18,       KC_F19,       KC_F20,                                   XXXXXXX,      KC_APP,       XXXXXXX,      XXXXXXX,      KC_VOLD,      XXXXXXX,
	OSM_LCTL,      _______,      XXXXXXX,      _______,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_MUTE,      KC_VOLU,      OSM_RCTL
  ),
  [L5] = LAYOUT(
	XXXXXXX,       TO(L1),       TO(L2),       TO(L3),       TO(L4),       XXXXXXX,                                  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,
	XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX,      RESET,        XXXXXXX,                                  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      NO_AO,  
	XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,                                  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      NO_OE,        NO_AE,  
	XXXXXXX,       XXXXXXX,      XXXXXXX,      KC_CAPS,      XXXXXXX,      XXXXXXX,                                  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,
	XXXXXXX,       _______,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX
  )
};


// Unicode Linux
void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
};


#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)


LEADER_EXTERNS();

// Runs constantly in the background, in a loop. Only supports basic keycodes.
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    //probably useless in practice, but cool
    SEQ_ONE_KEY (KC_P) {
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
    }

    SEQ_ONE_KEY (KC_G) {
      SEND_STRING("grep something !");
      register_code(KC_RALT);
      TAP_ONCE(KC_4);
      unregister_code(KC_RALT);
    }
    SEQ_ONE_KEY (KC_T) {
      SEND_STRING("tail "); 
      TAP_ONCE(KC_SLSH);
      SEND_STRING("f !");
      register_code(KC_RALT);
      TAP_ONCE(KC_4);
      unregister_code(KC_RALT);
    }
    SEQ_ONE_KEY (KC_S) {
      SEND_STRING("sudo !!");
      TAP_ONCE(KC_ENT);
    }
  }
}
