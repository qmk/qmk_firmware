#pragma once

#include "quantum.h"

#define TD_ESC TD(TD_SWP_BASE)
#define TD_TEST TD(X_CTL)
#define TD_SEMI TD(TD_SEM_COLN)
#define TD_LBRC TD(TD_LBRACE)
#define TD_RBRC TD(TD_RBRACE)

#if TAP_DANCE_ENABLE
enum tapdance_id {
    TD_ESC_CAPS = 0,	// not used presently
    TD_SWP_BASE,	// used to swap between english and runes
    TD_SEM_COLN,
    X_CTL,		// demo multi-tap / hold -- useful to expand upon
    TD_LBRACE,
    TD_RBRACE,
};
#endif
