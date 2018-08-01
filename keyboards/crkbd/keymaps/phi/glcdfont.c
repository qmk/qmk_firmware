// This is the 'classic' fixed-space bitmap font for Adafruit_GFX since 1.0.
// See gfxfont.h for newer custom bitmap font info.

#ifndef FONT5X7_H
#define FONT5X7_H

#ifdef __AVR__
 #include <avr/io.h>
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#else
 #define PROGMEM
#endif

#define O 1
#define _ 0
#define BIN(B8, B7, B6, B5, B4, B3, B2, B1) ((((((((B8 << 1) | B7) << 1 | B6) << 1 | B5) << 1 | B4) << 1 | B3) << 1 | B2) << 1 | B1)

// Standard ASCII 5x7 font

static const unsigned char font[] PROGMEM = {
  #include "./glcdfont.txt"
};
#endif // FONT5X7_H
