#include "brandonschlack.h"
#include "rgb_bs.h"

#ifdef RGB_MATRIX_ENABLE

extern led_config_t g_led_config;
void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color( i, red, green, blue );
        }
    }
}
#endif
