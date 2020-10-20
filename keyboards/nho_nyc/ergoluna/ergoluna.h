#pragma once

#if defined(KEYBOARD_nho_nyc_ergoluna_rev1)
    #include "rev1.h"
#elif defined(KEYBOARD_nho_nyc_ergoluna_rev2)
    #include "rev2.h"
#elif defined(KEYBOARD_nho_nyc_ergoluna_STM32)
   #include "STM32.h"
#endif
