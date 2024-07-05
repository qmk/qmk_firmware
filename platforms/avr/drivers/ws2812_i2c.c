#include "ws2812.h"
#include "i2c_master.h"

#ifdef WS2812_RGBW
#    error "RGBW not supported"
#endif

#ifndef WS2812_I2C_ADDRESS
#    define WS2812_I2C_ADDRESS 0xB0
#endif

#ifndef WS2812_I2C_TIMEOUT
#    define WS2812_I2C_TIMEOUT 100
#endif

void ws2812_init(void) {
    i2c_init();
}

// Setleds for standard RGB
void ws2812_setleds(rgb_led_t *ledarray, uint16_t leds) {
    i2c_transmit(WS2812_I2C_ADDRESS, (uint8_t *)ledarray, sizeof(rgb_led_t) * leds, WS2812_I2C_TIMEOUT);
}
