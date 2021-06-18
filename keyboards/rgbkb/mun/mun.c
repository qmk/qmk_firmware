#include "mun.h"
#include "touch_encoder.h"
#include "common_oled.h"
#include <transactions.h>

void keyboard_post_init_kb(void)
{
    touch_encoder_init();
    transaction_register_rpc(TOUCH_ENCODER_SYNC, touch_encoder_slave_sync);
    transaction_register_rpc(RGB_MENU_SYNC, rgb_menu_slave_sync);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void)
{
    touch_encoder_update(TOUCH_ENCODER_SYNC);
    rgb_menu_update(RGB_MENU_SYNC);
}

#if defined(BUSY_WAIT)
void matrix_output_unselect_delay(void) {
    for (int32_t i = 0; i < BUSY_WAIT_INSTRUCTIONS; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}
#endif