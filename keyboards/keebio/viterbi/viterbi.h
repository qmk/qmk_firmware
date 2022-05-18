#pragma once

#include "quantum.h"

#ifdef KEYBOARD_keebio_viterbi_rev1
    #include "rev1.h"
#elif KEYBOARD_keebio_viterbi_rev2
    #include "rev2.h"
#endif

#define LAYOUT_ortho_5x14 LAYOUT

