#pragma once

#include "quantum.h"

enum {
    X_AT,
    X_ET,
    X_IT,
    X_OT,
    X_UT,
    X_NT,
    X_1N,
    X_2N,
    X_3N,
    X_4N,
    X_5N,
    X_6N,
    X_7N,
    X_8N,
    X_9N,
    X_0N,
    X_N1,
    X_N2,
    X_N3,
    X_N4,
    X_N5,
    X_N6,
    X_N7,
    X_N8,
    X_N9,
    X_N0,
    X_QUOTES,
    X_SLASHES,
    X_LOGIC,
    X_EQ_PL,
    X_LINES,
    X_COLONS,
    X_DOT_GE,
    X_COM_LE,
    X_PGUP_HOME,
    X_PGDN_END,
    X_ROUND_BR,
    X_CURLY_BR,
    X_SQUARE_BR,
    X_ESC_CAPSL,
    X_COPY_CUT,
    X_PST_SV,
    X_FIND_REPL,
    TAP_DANCE_LENGHT,
};

#define KC_TDEC TD(X_ESC_CAPSL)
#define KC_TDLG TD(X_LOGIC)
#define KC_TDSL TD(X_SLASHES)
#define KC_TDUH TD(X_PGUP_HOME)
#define KC_TDDE TD(X_PGDN_END)
#define KC_TDEP TD(X_EQ_PL)
#define KC_TDQT TD(X_QUOTES)
#define KC_TDCB TD(X_CURLY_BR)
#define KC_TDRB TD(X_ROUND_BR)
#define KC_TDSB TD(X_SQUARE_BR)
#define KC_TDMU TD(X_SQUARE_BR)
#define KC_TDLN TD(X_LINES)
#define KC_TDCN TD(X_COLONS)
#define KC_TDDG TD(X_DOT_GE)
#define KC_TDCL TD(X_COM_LE)

#define KC_TDA TD(X_AT)
#define KC_TDE TD(X_ET)
#define KC_TDI TD(X_IT)
#define KC_TDO TD(X_OT)
#define KC_TDU TD(X_UT)
#define KC_TDN TD(X_NT)

#define KC_TDN1 TD(X_N1)
#define KC_TDN2 TD(X_N2)
#define KC_TDN3 TD(X_N3)
#define KC_TDN4 TD(X_N4)
#define KC_TDN5 TD(X_N5)
#define KC_TDN6 TD(X_N6)
#define KC_TDN7 TD(X_N7)
#define KC_TDN8 TD(X_N8)
#define KC_TDN9 TD(X_N9)
#define KC_TDN0 TD(X_N0)
#define KC_TD1N TD(X_1N)
#define KC_TD2N TD(X_2N)
#define KC_TD3N TD(X_3N)
#define KC_TD4N TD(X_4N)
#define KC_TD5N TD(X_5N)
#define KC_TD6N TD(X_6N)
#define KC_TD7N TD(X_7N)
#define KC_TD8N TD(X_8N)
#define KC_TD9N TD(X_9N)
#define KC_TD0N TD(X_0N)

#define KC_TDCC TD(X_COPY_CUT)
#define KC_TDPS TD(X_PST_SV)
#define KC_TDFR TD(X_FIND_REPL)

tap_dance_action_t tap_dance_actions[TAP_DANCE_LENGHT];

void tilde_dance_end(tap_dance_state_t *state, void *user_data);

void tap_and_hold_dance_end(tap_dance_state_t *state, void *user_data);
