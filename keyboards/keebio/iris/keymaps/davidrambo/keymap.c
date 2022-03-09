#include QMK_KEYBOARD_H

//keycode shorthands
#define MACNAV LT(4, KC_TAB)
#define PCNAV  LT(5, KC_TAB)

//text editor shortcuts for NAV and NAVPC
#define ALEFT   LALT(KC_LEFT)
#define ARGHT   LALT(KC_RGHT)
#define CLEFT   LCTL(KC_LEFT)
#define CRGHT   LCTL(KC_RGHT)
#define ABSPC LALT(KC_BSPC)
#define CBSPC LCTL(KC_BSPC)

//internet browser tab shortcuts and window swapping for Mac and Windows
#define GSL  LGUI(S(KC_LEFT))
#define GSR  LGUI(S(KC_RGHT))
#define CTLPGDN LCTL(KC_PGDN)
#define CTLPGUP LCTL(KC_PGUP)

#define CMBS  GUI_T(KC_BSPC)
#define CTBS  CTL_T(KC_BSPC)
#define C_TAB LCTL(KC_TAB)
#define G_TAB LGUI(KC_TAB)
#define A_TAB LALT(KC_TAB)

#define SFLK TD(SFT_LCK)     // alias for tapdance

//layer shorthands
#define _COLEMAK 0
#define _PC 1
#define _GAME 2
#define _SYMBOL 3
#define _NAVMAC 4
#define _NAVPC 5

enum custom_keycodes {
    SFT_LCK, //tapdance declarations
    COLEMAK = 0,
    PC,
    GAME,
    SYMBOL,
    NAV, //Navigation layer for Mac Colemak
    NAVPC, //Navigation layer for PC Colemak
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_COLEMAK] = LAYOUT(
  //,------+------+------+------+------+------.                    ,------+------+------+------+------+------.
     KC_ESC, KC_1 , KC_2 , KC_3 , KC_4, KC_5,                       KC_6  , KC_7 , KC_8 , KC_9 , KC_0  , KC_MINS,
  //|------+------+------+------+------+------|                    |------+------+------+------+------+------|
     KC_GRV, KC_Q , KC_W , KC_F , KC_P, KC_G,                       KC_J  , KC_L , KC_U , KC_Y , KC_SCLN,KC_BSPC,
  //|------+------+------+------+------+------|                    |------+------+------+------+------+------|
     MACNAV, KC_A , KC_R , KC_S , KC_T, KC_D,                       KC_H  , KC_N , KC_E , KC_I , KC_O, KC_QUOT,
  //|------+------+------+------+------+------+------.      ,------|------+------+------+------+------+------|
     KC_LSFT,KC_Z , KC_X , KC_C , KC_V, KC_B , TO(1),        KC_ENT, KC_K, KC_M , KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,
  //`------+------+------+------+------+----+------/         \-----+------+------+------+------+------+------'
                              KC_LCTL, KC_LALT, CMBS,         KC_SPC, MO(3), KC_RALT
  //                          `------+------+------'           `------+------+------'
  ),

    [_PC] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        
    _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        
    PCNAV  , _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        
    _______, _______, _______, _______, _______, _______, TO(2),    _______, _______, _______, _______, _______, _______, _______, 
        
                                    KC_LALT, KC_LGUI, CTBS,            _______, _______, _______
    ),
   
    [_GAME] = LAYOUT(
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
       
    KC_B   , KC_T   , KC_Q   , KC_W   , KC_E   , KC_R   ,                _______, _______, _______, _______, _______, _______,
        
    KC_TAB , KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   ,                _______, _______, _______, _______, _______, _______,
        
    KC_LALT, KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_M,   KC_P , _______, _______, _______, _______, _______, _______, 
        
                                   KC_G, KC_I, KC_SPC,                KC_BSPC, TO(0), _______
    ), 
    
    [_SYMBOL] = LAYOUT(
    
    KC_F12 , KC_F1  , KC_F2 , KC_F3  , KC_F4  , KC_F5,                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,
    
    KC_LBRC, KC_1   , KC_2  , KC_3   , KC_4   , KC_5,                       KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_RBRC,
        
    KC_BSLS, KC_EXLM, KC_AT , KC_HASH, KC_DLR , KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
        
    _______, KC_HOME, KC_END, KC_VOLD, KC_VOLU, KC_MPLY, _______,   _______, _______, KC_MINS, _______, _______, _______, _______, 
        
                           _______, _______, _______,                    _______, _______, _______
    ),
   
    [_NAVMAC] = LAYOUT(
    
    RESET  , _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        
    _______, _______, _______, _______, _______, _______,                    C_TAB,   ALEFT  ,  KC_UP , ARGHT  , KC_DEL , _______,
        
    _______, _______, _______, _______, _______, _______,                    GSL ,    KC_LEFT, KC_DOWN, KC_RGHT, GSR    , _______,
        
    _______, _______, _______, _______, _______, _______, _______,  _______, G_TAB,   ABSPC  , _______, _______, _______, _______, 
        
                                   _______, _______, _______,         _______, _______, _______
    ),
    
    [_NAVPC] = LAYOUT(
    
    RESET , _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        
    _______, _______, _______, _______, _______, _______,                   C_TAB  , CLEFT  , KC_UP  , CRGHT  , KC_DEL , _______,
        
    _______, _______, _______, _______, _______, _______,                   CTLPGUP, KC_LEFT, KC_DOWN, KC_RGHT, CTLPGDN, _______,
        
    _______, _______, _______, _______, _______, _______,_______,  _______, A_TAB  , CBSPC, _______, _______, _______, _______, 
        
                              _______, _______, _______,                _______, _______, _______
    ),
   
};

// Shift vs. capslock function. From bbaserdem's Planck keymap (since deprecated).
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
