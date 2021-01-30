#include "sl8.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config ={
    {
        {0  ,2  ,4  ,6  },
        {1  ,3  ,5  ,7  }
	},
	{
        {0,0},{32,0},{64,0},{96,0},
        {128,0},{160,0},{192,0},{224,0}
    },
    {
        0x04,0x04,0x04,0x04,
        0x04,0x04,0x04,0x04
    }
};

#endif