/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "sol3.h"
#include "eeconfig.h"
#include "audio.h"
#include <transactions.h>

extern audio_config_t audio_config;

void keyboard_post_init_kb(void) {
    touch_encoder_init();
    transaction_register_rpc(TOUCH_ENCODER_SYNC, touch_encoder_slave_sync);
    transaction_register_rpc(RGB_MENU_SYNC, rgb_menu_slave_sync);
    keyboard_post_init_user();
}

void eeconfig_init_kb(void) {
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);

    audio_config.raw = eeconfig_read_audio();
    audio_config.clicky_enable = false;
    eeconfig_update_audio(audio_config.raw);

    eeconfig_init_user();
}

void housekeeping_task_kb(void) {
    touch_encoder_update(TOUCH_ENCODER_SYNC);
    rgb_menu_update(RGB_MENU_SYNC);
}
