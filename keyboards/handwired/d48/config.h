#pragma once

/* Audio */
#ifdef AUDIO_ENABLE
#define STARTUP_SONG_DOOM SONG(E1M1_DOOM)
#define STARTUP_SONG SONG( \
    Q__NOTE(_E6), \
    Q__NOTE(_A6), \
    H__NOTE(_E7), \
    Q__NOTE(_E6), \
    Q__NOTE(_E7) \
)
#endif

/* OLED */
#define OLED_FONT_H "glcdfont_d48.c"
#define OLED_TIMEOUT 0
// #define OLED_SCROLL_TIMEOUT 1000

/* I2C */
//#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
//#define PAL_MODE_STM32_ALTERNATE_OPENDRAIN (PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN)

/* DS1307 */
#define DS1307_ADDR (0x68 << 1)
