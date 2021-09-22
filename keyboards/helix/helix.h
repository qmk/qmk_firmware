#pragma once

#include "quantum.h"

#ifdef KEYBOARD_helix_rev1
    #include "rev1.h"
#endif
#ifdef KEYBOARD_helix_rev2
    #include "rev2.h"
#endif
#ifdef KEYBOARD_helix_rev3_5rows
    #include "rev3_5rows.h"
#endif
#ifdef KEYBOARD_helix_rev3_4rows
    #include "rev3_4rows.h"
#endif
#ifdef KEYBOARD_helix_pico
    #include "pico.h"
#endif
