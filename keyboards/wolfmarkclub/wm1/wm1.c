#include "quantum.h"

void bootloader_jump(void) {
    // This board doesn't use the "standard" stm32duino bootloader, and no information is available regarding how to enter bootloader mode. All we can do here is reset.
    NVIC_SystemReset();
}

void matrix_init_kb(void) {
  gpio_set_pin_output(B1); // Top Indicator LED
  gpio_set_pin_output(B0); // Middle Indicator LED
  gpio_set_pin_output(C5); // Bottom Indicator LED
  matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        gpio_write_pin(B1, led_state.caps_lock);
        gpio_write_pin(B0, led_state.num_lock);
        gpio_write_pin(C5, led_state.scroll_lock);
    }
    return true;
}
