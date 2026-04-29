#pragma once

// Timing for SK6812

#undef WS2812_TRST_US
#define WS2812_TRST_US 300 

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB

/* Underglow */
#define WS2812_SPI_DRIVER           SPID1
#define WS2812_SPI_MOSI_PAL_MODE    5
// #define WS2812_SPI_SCK_PIN          A5
// #define WS2812_SPI_SCK_PAL_MODE     5
#undef WS2812_SPI_DIVISOR
#define WS2812_SPI_DIVISOR          32
#define TRANSIENT_EEPROM_SIZE       1024

/* Включаем поддержку хранения настроек */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
/* Если памяти мало, можно ограничить количество слоев для VIA (по умолчанию 4) */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
#define VIA_RGB_MATRIX_ENABLE
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // Нужно для красивых эффектов
#define RGB_MATRIX_KEYPRESSES        // Нужно для реактивных эффектов

#define RGBLED_NUM 14 // Укажите общее число диодов на плате
#define DRIVER_LED_TOTAL RGBLED_NUM

#define AUDIO_PIN A4

#ifdef AUDIO_ENABLE
# define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

#define AUDIO_VOICES
#define AUDIO_VOICE_DEFAULT something
