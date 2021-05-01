#include "ws2812.h"
#include "rgbsps.h"

cRGB led[RGBSPS_NUM];

void rgbsps_set(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  led[index].r = r;
  led[index].g = g;
  led[index].b = b;
}

void rgbsps_setall(uint8_t r, uint8_t g, uint8_t b) {
  for (uint16_t i = 0; i < RGBSPS_NUM; i++) {
    rgbsps_set(i, r, g, b);
  }
}

void rgbsps_turnoff(void) {
  rgbsps_setall(0, 0, 0);
}

void rgbsps_send(void) {
  ws2812_setleds(led, RGBSPS_NUM);
}

void rgbsps_sethsv(uint8_t index, uint16_t hue, uint8_t sat, uint8_t val) {
  uint8_t r = 0, g = 0, b = 0, base, color;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    r = val;
    g = val;
    b = val;
  } else {
    base = ((255 - sat) * val) >> 8;
    color = (val - base) * (hue % 60) / 60;

    switch (hue / 60) {
      case 0:
        r = val;
        g = base + color;
        b = base;
        break;
      case 1:
        r = val - color;
        g = val;
        b = base;
        break;
      case 2:
        r = base;
        g = val;
        b = base + color;
        break;
      case 3:
        r = base;
        g = val - color;
        b = val;
        break;
      case 4:
        r = base + color;
        g = base;
        b = val;
        break;
      case 5:
        r = val;
        g = base;
        b = val - color;
        break;
    }
  }

  rgbsps_set(index, r, g, b);
}

