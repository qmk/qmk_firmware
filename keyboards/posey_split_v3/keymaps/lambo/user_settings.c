#include "keymap_german.h"

//Layers
#define _QWERTY 0
#define _SYMB 4
#define _NAV 3
// //Custom Layers
#define _TEMPRTY 1
#define _SC2 6

// Custom Macros
#define TEMP_TYPE_LAYER _TEMPRTY
#define REPEAT_ENABLED
#define REPEAT_ALL_KEYS_ENABLED
#define BOOSTED_REPEAT_ENABLED
#define REPEAT_DELAY 108
#define REPEAT_TERM 5
#define BOOSTED_REPEAT_TERM 8
#define BOOSTED_REPEAT_KEYS KC_Z
#define BOOSTED_REPEAT_KEY_COUNT 1
#define FAST_REPEAT_LAYERS _SC2
#define FAST_REPEAT_LAYER_COUNT 1

enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   SYMB,
   NAV,
   ADJUST,
   SC2,
   //quick type
   CTT,
   TTC
};

#ifdef REPEAT_ENABLED
   #include "hardware_repeat.c"
#endif

#ifdef QUICK_GAME_TYPE_ENABLED
   #include "quick_game_type.c"
#endif
#ifndef QUICK_GAME_TYPE_ENABLED
   #define TTC KC_ENTER
   #define CTT KC_ENTER
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
#define SYM_NAV LT(_NAV, KC_CAPS)
#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

// Layer Switch Shortcuts
#define SYM_SC2 TO(_SC2)
#define SYM_Q TO(_QWERTY)
#define SYM_DIA TO(_DIABLO)
#define PL_C OSL(_PLAYERS)

#include custom_user_scripting