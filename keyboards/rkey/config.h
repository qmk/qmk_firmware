#pragma once

// Timing for SK6812
 // #define WS2812_T1H 650
#define WS2812_T1H 600
//// #define WS2812_T1L 600
#define WS2812_T0H 300
//// #define WS2812_T0L 900
//// #define WS2812_TIMING 1250
#define WS2812_TRST_US 80
#define WS2812_EXTERNAL_PULLUP

//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB

/* Underglow */
#define WS2812_SPI_DRIVER           SPID1
#define WS2812_SPI_MOSI_PAL_MODE    5
// #define WS2812_SPI_SCK_PIN          A5
// #define WS2812_SPI_SCK_PAL_MODE     5
// #define WS2812_SPI_DIVISOR          16
#define TRANSIENT_EEPROM_SIZE 		1024

#define AUDIO_PIN A4

#ifdef AUDIO_ENABLE
# define STARTUP_SONG SONG(STARTUP_SOUND)

/* Включаем поддержку хранения настроек */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
/* Если памяти мало, можно ограничить количество слоев для VIA (по умолчанию 4) */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

#endif
