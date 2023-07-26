#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID    0x1B1C
#define PRODUCT_ID   0x1B13
#define DEVICE_VER   0x0001
#define MANUFACTURER "Corsair"
#define PRODUCT      "K70 Vengeance RGB"

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 12

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS {P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9}
#define MATRIX_COL_PINS {P1_12, P1_13, P1_14, P1_15, P1_16, P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23}

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 1
#define USB_POLLING_INTERVAL_MS 1           /* 1000 Hz */
#define FORCE_NKRO

/* Volume Knob */
#define ENCODERS_PAD_A {P0_22}
#define ENCODERS_PAD_B {P0_23}
#define ENCODER_RESOLUTION 4
#define ENCODER_DIRECTION_FLIP
