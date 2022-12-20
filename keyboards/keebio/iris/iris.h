#pragma once

#if defined(KEYBOARD_keebio_iris_rev1)
    #include "rev1.h"
#elif defined(KEYBOARD_keebio_iris_rev1_led)
    #include "rev1_led.h"
#elif defined(KEYBOARD_keebio_iris_rev2)
    #include "rev2.h"
#elif defined(KEYBOARD_keebio_iris_rev3)
    #include "rev3.h"
#elif defined(KEYBOARD_keebio_iris_rev4)
    #include "rev4.h"
#elif defined(KEYBOARD_keebio_iris_rev5)
    #include "rev5.h"
#elif defined(KEYBOARD_keebio_iris_rev6)
    #include "rev6.h"
#elif defined(KEYBOARD_keebio_iris_rev6a)
    #include "rev6a.h"
#elif defined(KEYBOARD_keebio_iris_rev6b)
    #include "rev6b.h"
#elif defined(KEYBOARD_keebio_iris_rev7)
    #include "rev7.h"
#endif

#include "quantum.h"
#include "via.h"
