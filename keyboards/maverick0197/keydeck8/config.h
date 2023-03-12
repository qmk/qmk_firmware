#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* Encoder Configuration */
#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D3 }
#define ENCODER_RESOLUTION 4
#define ENCODER_DIRECTION_FLIP
//#define ENCODER_DEFAULT_POS 0x3

