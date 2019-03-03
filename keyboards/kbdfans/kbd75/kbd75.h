#pragma once

#include "quantum.h"

#ifdef KEYBOARD_kbdfans_kbd75_rev1
    #include "rev1.h"
#endif

#ifdef KEYBOARD_kbdfans_kbd75_rev2
    #include "../rev1/rev1.h"
    #include "rev2.h"
#endif

