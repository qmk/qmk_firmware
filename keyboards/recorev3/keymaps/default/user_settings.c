//Layers
#define _QWERTY 0
#define _SYMB 2
#define _NAV 3
#define _ADJUST 4
// //Custom Layers
#define _TEMPRTY 1
#define _THECORE 7
#define _DIABLO 8
#define _PLAYERS 9

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
                            KC_P, \
                            KC_SCLN, \
                            KC_SLSH, \
                            KC_QUOT, \
                            KC_COMM
#define FAST_REPEAT_KEY_COUNT 11

#define FAST_REPEAT_LAYERS _THECORE
#define FAST_REPEAT_LAYER_COUNT 1

enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   SYMB,
   NAV,
   ADJUST,
   SC2,
   THECORE,
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
#define SYM_NAV LT(_NAV, KC_PPLS)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

// Layer Switch Shortcuts
#define SYM_CRE TO(_THECORE)
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