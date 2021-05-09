#pragma once

#include "config_common.h"

/*usb descriptor setup*/

#define VENDOR_ID 0x7474 //tt for tempo turtle
#define PRODUCT_ID 0x6270 //bp for bradpad
#define DEVICE_VER 0x0001 //this is for rev1.x.x pinouts
#define MANUFACTURER Tempo Turtle
#define PRODUCT Tempo Turtle bradpad
#define DESCRIPTION Tempo Turtle bradpad

/* keeb stuff */

#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS {B7, D5, C7, D2, D3}
#define MATRIX_COL_PINS {D7, E6, B4, F1}
#define UNUSED_PINS

#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5