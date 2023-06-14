/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "mun.h"
#include "touch_encoder.h"
#include "common_oled.h"
#include <transactions.h>

void keyboard_post_init_kb(void) {
    touch_encoder_init();
    transaction_register_rpc(TOUCH_ENCODER_SYNC, touch_encoder_slave_sync);
    transaction_register_rpc(RGB_MENU_SYNC, rgb_menu_slave_sync);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    touch_encoder_update(TOUCH_ENCODER_SYNC);
    rgb_menu_update(RGB_MENU_SYNC);
}
