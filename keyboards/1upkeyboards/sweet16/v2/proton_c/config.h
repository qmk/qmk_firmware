#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x0162
#define DEVICE_VER      0x0001

/* key matrix pins */
#define MATRIX_ROW_PINS { B5, B7, B2, B0 }
#define MATRIX_COL_PINS { B8, A0, A10, A9 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Encoder pins */
#define ENCODERS_PAD_A { A2 }
#define ENCODERS_PAD_B { A1 }
#define ENCODER_RESOLUTION 4

#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE
