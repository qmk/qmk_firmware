// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

// Custom Macros
#define QUICK_GAME_TYPE_ENABLED
#define TEMP_TYPE_LAYER _TEMPRTY
#define DIABLO_PLAYERS_CHANGE_ENABLED
#define REPEAT_ENABLED
#define REPEAT_ALPHAS_ENABLED
#define REPEAT_MODS_ENABLED
#define REPEAT_FROW_ENABLED
#define REPEAT_DELAY 130
#define REPEAT_TERM 3
// #define BOOSTED_REPEAT_ENABLED
// #define BOOSTED_REPEAT_DELAY 130
// #define BOOSTED_REPEAT_TERM 0
// #define BOOSTED_REPEAT_KEYS KC_BSPC, KC_EQL, KC_F
// #define BOOSTED_REPEAT_KEY_COUNT 3
// #define BOOSTED2_REPEAT_ENABLED
// #define BOOSTED2_REPEAT_DELAY 130
// #define BOOSTED2_REPEAT_TERM 0
// #define BOOSTED2_REPEAT_KEYS KC_A, KC_S, KC_D, KC_Z, KC_C, KC_6, KC_7, KC_8, KC_9, KC_BSLS
// #define BOOSTED2_REPEAT_KEY_COUNT 8
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