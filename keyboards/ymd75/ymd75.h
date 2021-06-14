#pragma once

#include "quantum.h"

#if defined(KEYBOARD_ymd75_rev1)
    #include "rev1.h"
#elif defined(KEYBOARD_ymd75_rev2)
    #include "rev2.h"
#elif defined(KEYBOARD_ymd75_rev3)
    #include "rev3.h"
#endif
