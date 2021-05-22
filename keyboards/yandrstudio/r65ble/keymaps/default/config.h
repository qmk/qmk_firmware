/* OLED */
#ifdef OLED_DRIVER_ENABLE
// #    define OLED_DISPLAY_128X64
#    define I2C_DRIVER I2CD1
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 7U
#    define I2C1_TIMINGR_SDADEL 0U
#    define I2C1_TIMINGR_SCLH 38U
#    define I2C1_TIMINGR_SCLL 129U
#    define OLED_BRIGHTNESS 50
#    define OLED_TIMEOUT 300000
// #    define OLED_TIMEOUT 0
#    define OLED_FONT_HEIGHT 8
#    define OLED_FONT_WIDTH 6
#    define OLED_FONT_H "../../jason_fount.c"
#    define OLED_FONT_END 127
#    define OLED_FONT_START 0
#endif


#ifdef TAP_DANCE_ENABLE
#define TAPPING_TERM 200

#endif
