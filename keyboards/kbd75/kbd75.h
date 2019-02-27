#ifndef KBD75_H
#define KBD75_H

#include "quantum.h"

#ifdef KEYBOARD_kbd75_rev1
    #include "rev1.h"
#endif

#ifdef KEYBOARD_kbd75_rev2
    #include "../rev1/rev1.h"
    #include "rev2.h"
#endif

#endif
