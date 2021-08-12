#pragma once

#ifdef KEYBOARD_keebio_iris_rev1
    #include "rev1.h"
#elif KEYBOARD_keebio_iris_rev1_led
    #include "rev1_led.h"
#elif KEYBOARD_keebio_iris_rev2
    #include "rev2.h"
#elif KEYBOARD_keebio_iris_rev3
    #include "rev3.h"
#elif KEYBOARD_keebio_iris_rev4
    #include "rev4.h"
#endif

#include "quantum.h"
#include "via.h"
