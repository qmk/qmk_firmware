#include "ws2812.h"
#include "i2c_master.h"

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

    i2c_transmit(0xb0, (uint8_t*)ledarray, sizeof(LED_TYPE) * leds, 100);
}

// Setleds for SK6812RGBW
void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t leds) {
// not supported - for now error out if its enabled
#ifdef RGBW
#    error "RGBW not supported"
#endif
}
