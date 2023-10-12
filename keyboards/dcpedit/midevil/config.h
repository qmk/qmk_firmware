#pragma once

/* LCD config */
#define LCD_DC_PIN GP16   // data/command
#define LCD_CS_PIN GP17   // chip select
#define LCD_RST_PIN GP14  // reset
#define LCD_LED_PIN GP15  // backlight
#define LCD_SDA_PIN GP19  // SDI,MOSI data input
#define LCD_SCK_PIN GP18  // clock

#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0 // milliseconds
#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE