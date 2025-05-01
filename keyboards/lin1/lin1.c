#include "quantum.h"
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {NO_LED},
    //{0,1,2,3,4,5,6,7,8,9,10,11} //underglow only



  }, {
    // LED Index to Physical Position
    {221,15},{217,64}, {218, 64}, {219,64}, {220, 64}, {221, 64}, {222, 64},{223,64},{224,64}

  }, {
    // LED Index to Flag
    2,2,2,2,2,2,2,2,2

  } };


