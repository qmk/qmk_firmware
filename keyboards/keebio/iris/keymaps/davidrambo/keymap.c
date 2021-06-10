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

	[_COLEMAK] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_GRV , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  ,                KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
   KC_NAVMAC, KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,                KC_H  , KC_N  , KC_E  , KC_I  , KC_O  ,KC_QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     KC_SFLK, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_PC ,     KC_ENT , KC_K  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       KC_LCTL,KC_LGUI,KC_CMBS,         KC_SPC, KC_SYM, KC_LALT
  //                  `----+----+----'        `----+----+----'
  ),

    [_PC] = LAYOUT(
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,          KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,          KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
    KC_NAVPC,KC____ , KC____ , KC____ , KC____ , KC____ ,          KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ , KC_GM, KC____, KC____ , KC____ , KC____ , KC____ , KC____ , KC____ , 
        
                      KC_LGUI , KC_LCTL , KC_CTBS ,    KC____ , KC____ , KC____ 
    ),
   
    [_GAME] = LAYOUT(
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,          KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
     KC_B  ,  KC_T  ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,          KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
    KC_TAB , KC_LSFT,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,          KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
    KC_LALT, KC_LCTL,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_M,   KC_P , KC____, KC____ , KC____ , KC____ , KC____ , KC____ , 
        
                          KC_G   ,  KC_I  , KC_SPC,    KC_BSPC, KC_MAC, KC____ 
    ), 
    
    [_SYMBOL] = LAYOUT(
    
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,         KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
    
    KC_LBRC,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,          KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_RBRC,
        
    KC_BSLS, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL ,
        
    KC____ , KC_HOME, KC_END , KC_VOLD, KC_VOLU, KC_MPLY,KC____,  KC____,KC____, KC_MINS, KC____ , KC____ , KC____ , KC____ , 
        
                        KC____ , KC____ , KC____,      KC____, KC____ , KC____ 
    ),
   
    [_NAVMAC] = LAYOUT(
    
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,         KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,         KC_C_TAB, KC_AL ,  KC_UP ,  KC_AR , KC_DEL , KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,         KC_GSL , KC_LEFT, KC_DOWN, KC_RGHT, KC_GSR , KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,KC____,  KC____,KC_G_TAB,KC_ABSPC, KC____ , KC____ , KC____ , KC____ , 
        
                        KC____ , KC____ , KC____ ,       KC____ , KC____ , KC____ 
    ),
    
    [_NAVPC] = LAYOUT(
    
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,         KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,         KC_C_TAB, KC_CL ,  KC_UP ,  KC_CR , KC_DEL , KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,         KC_CPGU, KC_LEFT, KC_DOWN, KC_RGHT, KC_CPGD, KC____ ,
        
    KC____ , KC____ , KC____ , KC____ , KC____ , KC____ ,KC____,  KC____,KC_A_TAB,KC_CBSPC, KC____ , KC____ , KC____ , KC____ , 
        
                        KC____ , KC____ , KC____ ,       KC____ , KC____ , KC____ 
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
