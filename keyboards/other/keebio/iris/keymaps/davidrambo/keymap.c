#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

//keycode shorthands
#define KC____  KC_TRNS // three underscores "___" for transparent
#define KC_SYM  MO(3)
#define KC_MAC  TO(0)
#define KC_PC   TO(1)
#define KC_GM   TO(2)
#define KC_NAVMAC LT(4, KC_TAB)
#define KC_NAVPC  LT(5, KC_TAB)

//text editor shortcuts for NAV and NAVPC
#define KC_AL   LALT(KC_LEFT)
#define KC_AR   LALT(KC_RGHT)
#define KC_CL   LCTL(KC_LEFT)
#define KC_CR   LCTL(KC_RGHT)
#define KC_ABSPC LALT(KC_BSPC)
#define KC_CBSPC LCTL(KC_BSPC)

//internet browser tab shortcuts and window swapping for Mac and Windows
#define KC_GSL  LGUI(S(KC_LEFT))
#define KC_GSR  LGUI(S(KC_RGHT))
#define KC_CPGD LCTL(KC_PGDN)
#define KC_CPGU LCTL(KC_PGUP)

#define KC_CMBS  GUI_T(KC_BSPC)
#define KC_CTBS  CTL_T(KC_BSPC)
#define KC_C_TAB LCTL(KC_TAB)
#define KC_G_TAB LGUI(KC_TAB)
#define KC_A_TAB LALT(KC_TAB)

//layer shorthands
#define _COLEMAK 0
#define _PC 1
#define _GAME 2
#define _SYMBOL 3
#define _NAVMAC 4
#define _NAVPC 5

enum {
//	SFT_LCK //tapdance declarations
    COLEMAK = 0,
    PC,
    GAME,
    SYMBOL,
    NAV, //Navigation layer for Mac Colemak
    NAVPC, //Navigation layer for PC Colemak
    SFT_LCK //tapdance declaration
};

#define KC_SFLK TD(SFT_LCK)     // alias for tapdance

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
   NAVMAC, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SFLK, Z  , X  , C  , V  , B  , PC ,     ENT , K  , M  ,COMM, DOT,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LCTL,LGUI,CMBS,         SPC, SYM, LALT
  //                  `----+----+----'        `----+----+----'
  ),

    [_PC] = LAYOUT_kc(
    ___ , ___ , ___ , ___ , ___ , ___ ,          ___ , ___ , ___ , ___ , ___ , ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ ,          ___ , ___ , ___ , ___ , ___ , ___ ,
        
    NAVPC,___ , ___ , ___ , ___ , ___ ,          ___ , ___ , ___ , ___ , ___ , ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ , GM, ___, ___ , ___ , ___ , ___ , ___ , ___ , 
        
                      LGUI , LCTL , CTBS ,    ___ , ___ , ___ 
    ),
   
    [_GAME] = LAYOUT_kc(
    ___ , ___ , ___ , ___ , ___ , ___ ,          ___ , ___ , ___ , ___ , ___ , ___ ,
        
     B  ,  T  ,  Q  ,  W  ,  E  ,  R  ,          ___ , ___ , ___ , ___ , ___ , ___ ,
        
    TAB , LSFT,  A  ,  S  ,  D  ,  F  ,          ___ , ___ , ___ , ___ , ___ , ___ ,
        
    LALT, LCTL,  Z  ,  X  ,  C  ,  V  ,  M,   P , ___, ___ , ___ , ___ , ___ , ___ , 
        
                          G   ,  I  , SPC,    BSPC, MAC, ___ 
    ), 
    
    [_SYMBOL] = LAYOUT_kc(
    
    ___ , ___ , ___ , ___ , ___ , ___ ,         ___ , ___ , ___ , ___ , ___ , ___ ,
    
    LBRC,  1  ,  2  ,  3  ,  4  ,  5  ,          6  ,  7  ,  8  ,  9  ,  0  , RBRC,
        
    BSLS, EXLM, AT  , HASH, DLR , PERC,         CIRC, AMPR, ASTR, LPRN, RPRN, EQL ,
        
    ___ , HOME, END , VOLD, VOLU, MPLY,___,  ___,___, MINS, ___ , ___ , ___ , ___ , 
        
                        ___ , ___ , ___,      ___, ___ , ___ 
    ),
   
    [_NAVMAC] = LAYOUT_kc(
    
    ___ , ___ , ___ , ___ , ___ , ___ ,         ___ , ___ , ___ , ___ , ___ , ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ ,         C_TAB, AL ,  UP ,  AR , DEL , ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ ,         GSL , LEFT, DOWN, RGHT, GSR , ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ ,___,  ___,G_TAB,ABSPC, ___ , ___ , ___ , ___ , 
        
                        ___ , ___ , ___ ,       ___ , ___ , ___ 
    ),
    
    [_NAVPC] = LAYOUT_kc(
    
    ___ , ___ , ___ , ___ , ___ , ___ ,         ___ , ___ , ___ , ___ , ___ , ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ ,         C_TAB, CL ,  UP ,  CR , DEL , ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ ,         CPGU, LEFT, DOWN, RGHT, CPGD, ___ ,
        
    ___ , ___ , ___ , ___ , ___ , ___ ,___,  ___,A_TAB,CBSPC, ___ , ___ , ___ , ___ , 
        
                        ___ , ___ , ___ ,       ___ , ___ , ___ 
    ),
   
};

// Shift vs. capslock function. From bbaserdem's Planck keymap.
void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LSFT);
    } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        register_code (KC_CAPS);
    }
}
void caps_tap_end (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_LSFT);
    } else {
        unregister_code (KC_CAPS);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Shift, twice for Caps Lock
    [SFT_LCK] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end)
};