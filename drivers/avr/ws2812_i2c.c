#include "ws2812.h"
#include "i2c_master.h"

#ifdef RGBW
#    error "RGBW not supported"
#endif

#ifndef WS2812_ADDRESS
#    define WS2812_ADDRESS 0xb0
#endif

#ifndef WS2812_TIMEOUT
#    define WS2812_TIMEOUT 100
#endif

void ws2812_init(void) { i2c_init(); }

// Setleds for standard RGB
void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds) {
    static bool s_init = false;
    if (!s_init) {
        ws2812_init();
        s_init = true;
    }

    i2c_transmit(WS2812_ADDRESS, (uint8_t *)ledarray, sizeof(LED_TYPE) * leds, WS2812_TIMEOUT);
}
