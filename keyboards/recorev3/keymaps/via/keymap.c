#include QMK_KEYBOARD_H


//Layers
#define _QWERTY 0
#define _SYMB 2
#define _NAV 3
#define _ADJUST 4
// //Custom Layers
#define _TEMPRTY 1
#define _RECORE 5
#define _DIABLO 7
#define _PLAYERS 8

// Custom Macros
#define QUICK_GAME_TYPE_ENABLED
#define TEMP_TYPE_LAYER _TEMPRTY
#define DIABLO_PLAYERS_CHANGE_ENABLED
#define REPEAT_ENABLED
#define REPEAT_DELAY 150
#define REPEAT_TERM 5
#define FAST_REPEAT_KEYS    KC_P, \
                            KC_EQL, \
                            KC_RBRC, \
                            KC_BSLS, \
                            KC_BSPC, \
                            KC_LBRC, \
                            KC_SCLN, \
                            KC_SLSH, \
                            KC_QUOT, \
                            KC_COMM, \
                            KC_F, \
                            KC_EQL, \
                            KC_LBRC, \
                            KC_BSLS, \
                            KC_BSPC, \
                            KC_G, \
                            KC_V, \
                            KC_SLSH, \
                            KC_B, \
                            KC_PGUP, \
                            KC_C, \
                            KC_PAST, \
                            KC_X
#define FAST_REPEAT_KEY_COUNT 23

#define FAST_REPEAT_LAYERS _RECORE
#define FAST_REPEAT_LAYER_COUNT 1

enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   SYMB,
   NAV,
   ADJUST,
   RECORE,
   DIABLO,
   //quick type
   CTT,
   TTC,
   //players
   PL_C,
   PL_1,
   PL_2,
   PL_3,
   PL_4,
   PL_5,
   PL_6,
   PL_7,
   PL_8
};

#ifdef REPEAT_ENABLED
   #ifndef REPEAT_DELAY
      #define REPEAT_DELAY 100
   #endif
   #ifndef REPEAT_TERM
      #define REPEAT_TERM 5
   #endif
   #include "repeat.c"
#endif

#ifdef QUICK_GAME_TYPE_ENABLED
   #include "quick_game_type.c"
#endif

#ifdef DIABLO_PLAYERS_CHANGE_ENABLED
   #include "diablo_player_change.c"
#endif

// Shortcut to make keymap more readable
#define SYM_L   MO(_SYMB)

#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_BSLS)

#define KC_NAGR LT(_NAV, KC_GRV)
#define KC_NAMI LT(_NAV, KC_MINS)
#define SYM_NAV LT(_NAV, KC_MINS)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

// Layer Switch Shortcuts
#define SYM_REC TO(_RECORE)
#define SYM_Q TO(_QWERTY)
#define SYM_DIA TO(_DIABLO)
#define PL_C OSL(_PLAYERS)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   #ifdef QUICK_GAME_TYPE_ENABLED
   if (!process_diablo_player_change(keycode, record)) {
      return false;
   }
   #endif

   #ifdef DIABLO_PLAYERS_CHANGE_ENABLED
   if (!process_quick_game_type(keycode, record)) {
      return false;
   }
   #endif

   #ifdef REPEAT_ENABLED
   if (!process_repeat_key(keycode, record)) {
      return false;
   }
   #endif

   return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_NAGR ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,SYM_L   ,SYM_REC , SYM_Q   ,SYM_L   ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_NAMI ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_LBRC ,SYM_REC , KC_PAUS ,KC_RBRC ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ADPU ,KC_PGDN , KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_LGUI ,KC_PMNS ,SYM_NAV ,KC_ALAS ,KC_CTPL ,KC_BSPC ,KC_DEL  ,                   KC_ENT  ,KC_SPC  ,SYM_NAV ,KC_RALT ,KC_RCTL ,KC_MPLY ,KC_RGHT 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_TEMPRTY] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                      KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                   TTC     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_SYMB] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_TRNS ,SYM_DIA , KC_TRNS ,KC_TRNS ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,KC_TRNS ,KC_LCBR , KC_TRNS ,KC_RCBR ,KC_PSLS ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PMNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_TRNS ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_GRV  ,                                      KC_PAST ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_P0   ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                   KC_ENT  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_PDOT ,KC_PENT ,KC_TRNS 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_NAV] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_NO   ,KC_NO   ,KC_NO   ,KC_UP   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   , KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_UP   ,KC_NO   ,KC_NO   ,QK_BOOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_NO   ,KC_NO   ,KC_NO   ,KC_UP   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   , KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_UP   ,KC_NO   ,KC_NO   ,KC_NO   ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_NO   ,KC_LEFT ,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_RIGHT,                                     KC_LEFT ,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_RIGHT,KC_NO   ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_NO   ,KC_NO   ,KC_NO   ,KC_DOWN ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   , KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_DOWN ,KC_NO   ,KC_NO   ,KC_NO   ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                   KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_ADJUST] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                      KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_RECORE] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_EQL  ,KC_BSPC , SYM_Q   ,SYM_L   ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_NAMI ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_9    ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_LBRC ,KC_BSLS , KC_PAUS ,KC_RBRC ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_6    ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_PGUP ,KC_LALT , KC_F10  ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_7    ,KC_BSLS ,KC_PMNS ,KC_PAST ,KC_SLSH ,KC_LSFT ,KC_LCTL ,                   CTT     ,KC_SPC  ,SYM_NAV ,KC_RALT ,KC_RCTL ,KC_MPLY ,KC_RGHT 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_DIABLO] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_NAGR ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_EQL  ,KC_BSPC , SYM_Q   ,SYM_L   ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_NAMI ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_RBRC ,KC_BSLS , KC_PAUS ,KC_RBRC ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                      KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_COMM ,KC_LALT , KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   PL_C    ,KC_PMNS ,KC_PLUS ,KC_DOT  ,KC_ALAS ,KC_LSFT ,KC_LCTL ,                   CTT     ,KC_SPC  ,KC_RALT ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_PLAYERS] = LAYOUT_recore(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   PL_8    ,PL_1    ,PL_2    ,PL_3    ,PL_4    ,PL_5    ,PL_6    ,PL_7    , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                      KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┬────────┬────────┤├────────┬────────┬────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS , KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    )
};

// Light adjustments
#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_user(void) {
  rgblight_enable(); // Enables RGB
  rgblight_sethsv(HSV_ORANGE);
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
}

layer_state_t layer_state_set_user(layer_state_t state) {
   uint8_t layer = biton32(state);
   switch (layer) {
      case _QWERTY:
         rgblight_sethsv(HSV_YELLOW);
         break;
      case _RECORE:
         rgblight_sethsv(HSV_CYAN);
         break;
      case _DIABLO:
         rgblight_sethsv(HSV_RED);
         break;
      case _TEMPRTY:         
         rgblight_sethsv(HSV_GREEN);
         break;
   }
   return state;
}
#endif