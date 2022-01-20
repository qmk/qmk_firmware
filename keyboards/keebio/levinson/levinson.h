#pragma once

#include "quantum.h"

#ifdef KEYBOARD_keebio_levinson_rev1
    #include "rev1.h"
#elif KEYBOARD_keebio_levinson_rev2
    #include "rev2.h"
#elif KEYBOARD_keebio_levinson_rev3
    #include "rev3.h"
#endif
