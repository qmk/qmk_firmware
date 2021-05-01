/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _COLEMAKDH 1
#define _ROBOT 2
#define _SUPER 3
#define _LOWER 4

//#define QWERTY TG(_QWERTY)
#define COLMKDH TG(_COLEMAKDH)
#define ROBOT MO(_ROBOT)
#define SUPER MO(_SUPER)
#define LOWER MO(_LOWER)

#define CTRLESC MT(MOD_LCTL, KC_ESC)
#define RUNPRMT RGUI(KC_R)
#define UNDO RCTL(KC_Z)
#define REDO RCTL(KC_Y)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
     KC_GESC, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  , UNDO  ,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
     CTRLESC, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,
                     KC_MINS,_______,                                                        KC_EQL , KC_PLUS,
                                       ROBOT,KC_BSPC,                         KC_SPC, SUPER ,
                                      KC_LALT,KC_DEL,                         KC_ENT , LOWER,
                                     KC_LGUI,_______,                        _______,RUNPRMT 
  ),

  [_COLEMAKDH] = LAYOUT_5x6(
     KC_GESC, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  , UNDO  ,
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_BSLS,
     CTRLESC, KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_M  , KC_N  , KC_E  , KC_I  , KC_O  ,KC_QUOT,
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,                         KC_K  , KC_H  ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,
                     KC_MINS,_______,                                                        KC_EQL , KC_PLUS,
                                       ROBOT,KC_BSPC,                         KC_SPC, SUPER ,
                                     KC_LALT ,KC_DEL,                         KC_ENT , LOWER,
                                     KC_LGUI,_______,                        _______,RUNPRMT
  ),
//------------------------------------------------------------------------------------------------------------------------------ 

  [_ROBOT] = LAYOUT_5x6(
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
     _______,KC_TILD,KC_DLR ,KC_AMPR,KC_PIPE,KC_LBRC,                        KC_RBRC,KC_HOME, KC_UP ,KC_END ,KC_PGUP,_______,
     _______,KC_AT  ,KC_HASH,KC_QUES,KC_EXLM,KC_LPRN,                        KC_RPRN,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,_______,
     KC_SLCK,KC_CIRC,KC_PERC,KC_ASTR,KC_UNDS,KC_LCBR,                        KC_RCBR,KC_QUES,_______,_______,_______,_______,
                     _______,_______,                                                        _______,_______,
                                      ROBOT ,_______,                        _______,_______,
                                     _______,_______,                        _______,_______,
                                     _______,RESET  ,                        _______,_______
  ),

  [_SUPER] = LAYOUT_5x6(

     _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______, REDO  ,
     _______,_______,_______,_______,KC_PIPE,KC_LBRC,                        KC_RBRC,KC_AMPR,_______,_______,_______,_______,
     _______,_______,_______,_______,KC_EXLM,KC_LPRN,                        KC_RPRN,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,KC_UNDS,KC_LCBR,                        KC_RCBR,KC_QUES,_______,_______,_______,KC_PAUS,
                     _______,_______,                                                        _______,_______,
                                     _______,_______,                        _______, SUPER ,
                                     _______,_______,                        _______,_______,
                                      KC_INS,COLMKDH,                         RESET ,KC_PSCR

  ),

  [_LOWER] = LAYOUT_5x6(
     _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
     _______,_______, KC_P7 , KC_P8 , KC_P9 ,_______,                        RGB_VAI,RGB_M_SW,RGB_M_SN,RGB_M_K,_______,KC_MUTE,
     _______,_______, KC_P4 , KC_P5 , KC_P6 ,_______,                        RGB_HUI,RGB_M_P,RGB_M_B,RGB_M_R,_______,KC_VOLU,
     _______,_______, KC_P1 , KC_P2 , KC_P3 ,KC_PDOT,                        RGB_SAI,RGB_M_G,RGB_M_T,RGB_M_X,_______,KC_VOLD,
                     _______, KC_P0 ,                                                        RGB_MOD,RGB_TOG,
                                     KC_PMNS,KC_PPLS,                        _______,_______,
                                     KC_PSLS,KC_PAST,                        _______, LOWER ,
                                     KC_PEQL,KC_NLCK,                        _______,_______
  ),
};
