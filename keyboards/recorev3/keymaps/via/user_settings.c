// Custom Macros
#define QUICK_GAME_TYPE_ENABLED
#define TEMP_TYPE_LAYER _TEMPRTY
#define DIABLO_PLAYERS_CHANGE_ENABLED
#define REPEAT_ENABLED
#define REPEAT_ALL_KEYS_ENABLED
#define BOOSTED_REPEAT_ENABLED
#define REPEAT_DELAY 130
#define REPEAT_TERM 6
#define BOOSTED_REPEAT_DELAY 150
#define BOOSTED_REPEAT_TERM 20
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
                            KC_X, \
                            KC_T
#define FAST_REPEAT_KEY_COUNT 24
#define BOOSTED_REPEAT_KEYS KC_Z, \
                            KC_G
#define BOOSTED_REPEAT_KEY_COUNT 2

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
   #ifdef DIABLO_PLAYERS_CHANGE_ENABLED
   PL_C,
   PL_1,
   PL_2,
   PL_3,
   PL_4,
   PL_5,
   PL_6,
   PL_7,
   PL_8
   #endif
};

#ifdef REPEAT_ENABLED
   #ifndef REPEAT_DELAY
      #define REPEAT_DELAY 100
   #endif
   #ifndef REPEAT_TERM
      #define REPEAT_TERM 5
   #endif
   #include "hardware_repeat.c"
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
#define SYM_NAV LT(_NAV, KC_MINS)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

// Layer Switch Shortcuts
#define SYM_REC TO(_RECORE)
#define SYM_Q TO(_QWERTY)
#define SYM_DIA TO(_DIABLO)
#define PL_C OSL(_PLAYERS)

#include "custom_user_scripting.c"