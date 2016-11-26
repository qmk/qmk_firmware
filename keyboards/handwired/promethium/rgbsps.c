#include "light_ws2812.h"
#include "rgbsps.h"

struct cRGB led[RGBSPS_NUM];

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