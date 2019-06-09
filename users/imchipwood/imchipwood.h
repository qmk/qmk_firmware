#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// change the tapping term to a little bit quicker
#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM    175

#ifndef TAPPING_TERM_PER_KEY
#define TAPPING_TERM_PER_KEY
#endif

#endif