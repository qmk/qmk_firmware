#include "ws2812.h"
#include "i2c_master.h"

#ifdef RGBW
#    error "RGBW not supported"
#endif

#ifndef WS2812_I2C_ADDRESS
#    define WS2812_I2C_ADDRESS 0xB0
#endif

#ifndef WS2812_I2C_ADDRESS_RIGHT
#    define WS2812_I2C_ADDRESS_RIGHT 0xB8
#endif

#ifndef WS2812_I2C_TIMEOUT
#    define WS2812_I2C_TIMEOUT 100
#endif

void ws2812_init(void) {
    i2c_init();
}

// Setleds for standard RGB
void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds) {
    static bool s_init = false;
    if (!s_init) {
        ws2812_init();
        s_init = true;
    }

    i2c_transmit(WS2812_I2C_ADDRESS, (uint8_t *)ledarray, sizeof(LED_TYPE) * (leds >> 1), WS2812_I2C_TIMEOUT);
    i2c_transmit(WS2812_I2C_ADDRESS_RIGHT, (uint8_t *)ledarray+(sizeof(LED_TYPE) * (leds >> 1)), sizeof(LED_TYPE) * (leds - (leds >> 1)), WS2812_I2C_TIMEOUT);
}
