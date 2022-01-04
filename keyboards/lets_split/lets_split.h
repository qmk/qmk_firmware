#pragma once

#include "quantum.h"

#ifdef KEYBOARD_lets_split_rev1
    #include "rev1.h"
#elif KEYBOARD_lets_split_rev2
    #include "rev2.h"
#elif KEYBOARD_lets_split_sockets
    #include "sockets.h"
#endif
