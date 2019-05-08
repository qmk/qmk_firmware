#ifndef HELIX_H
#define HELIX_H

#ifdef KEYBOARD_helix_rev1
    #include "rev1.h"
#endif
#ifdef KEYBOARD_helix_rev2
    #include "rev2.h"
#endif
#ifdef KEYBOARD_helix_pico
    #include "pico.h"
#endif

#include "quantum.h"

#endif
