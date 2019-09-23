//#pragma once
#ifndef TONE_BLE_H_
#define TONE_BLE_H_


#include "custom_board.h"

#define THIS_DEVICE_ROWS 1
#define THIS_DEVICE_COLS 10

#define MATRIX_ROW_PINS { NO_PIN }
#define MATRIX_COL_PINS { F6,F7,B1,B3,D4,C6,D7,E6 }

#define LAYOUT( \
    k00, k01, k02, k03, \
    k04, k05, k06, k07 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
}

#define IS_LEFT_HAND  true
#define ENABLE_STARTUP_ADV_NOLIST

#endif /* TONE_BLE_H_ */
