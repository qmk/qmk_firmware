#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xDA19
#define MANUFACTURER    WorthlessOwl
#define PRODUCT         Owlet60
#define DESCRIPTION     TGR Alice inspired 65 or 60 percent keyboard

#define MATRIX_ROWS 9
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS {B5, F4, F5, F6, F7, B1, B3, B2, B6}
#define MATRIX_COL_SELECT_PINS {D7, B4, E6}
#define MATRIX_COL_DATA_PIN {C6}

#define BACKLIGHT_PIN D3

#define DIODE_DIRECTION ROW2COL

#define BACKLIGHT_LEVELS 5

#define DEBOUNCE 5

#endif
