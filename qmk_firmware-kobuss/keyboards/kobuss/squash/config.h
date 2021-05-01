#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0x1209
#define PRODUCT_ID 0xBA00
#define DEVICE_VER 0x0001
#define MANUFACTURER KoBuss
#define PRODUCT Squash
#define DESCRIPTION Squash Forty

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* TAB	Q	W	E	R	T	Y	U	I	O	P	BACK */
/* CAPS	A	S	D	F	G	H	J	K	L	RET	NO_PIN */
/* LSHFT	LMOD	Z	X	C	V	B	N	M	LT	GT	RSHFT */
/* LCTRL	LSUP	LALT	LSPC	SPC	RSPC	RALT	RFN	RCTRL	NO_PIN	NO_PIN	NO_PIN */
// clang-format off
#define DIRECT_PINS { \
    { B9, E2, E6, F10, C1, A0, A4, C4, B1, E9, E13, B10 }, \
    { B8, E3, C13, C0, F2, A1, A5, C5, B2, E10, E14, NO_PIN }, \
    { B5, E0, E4, F9, C3, F3, A3, A6, B0, E7, E11, E15 }, \
    { B4, E1, E5, C2, A2, A7, E8, E12, B11, NO_PIN, NO_PIN, B12 } \
}
// clang-format on

#define DEBOUNCE 5

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A \
        { B13 }
#    define ENCODERS_PAD_B \
        { B14 }
#    define ENCODER_RESOLUTION 4
#endif
#define TAP_CODE_DELAY 10

#define INDICATOR_TOP_LED_PIN C8
#define INDICATOR_MID_LED_PIN C7
#define INDICATOR_BOT_LED_PIN C6

#ifdef OLED_DRIVER_ENABLE
#    define I2C1_SCL_BANK GPIOB
#    define I2C1_SDA_BANK GPIOB
#    define I2C1_SDA 7
#    define I2C1_SCL 6
#    define I2C1_SCL_PAL_MODE 1
#    define I2C1_SDA_PAL_MODE 1
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 3U
#    define I2C1_TIMINGR_SDADEL 1U
#    define I2C1_TIMINGR_SCLH 3U
#    define I2C1_TIMINGR_SCLL 9U

#    define OLED_DISPLAY_WIDTH 128
#    define OLED_DISPLAY_HEIGHT 32
#    define OLED_UPDATE_INTERVAL 20
#    define OLED_TIMEOUT 30000
#endif