/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "rev1.h"
#include "touch_encoder.h"
#include "common_oled.h"
#include "transactions.h"

#define NUMBER_OF_TOUCH_ENCODERS 2
#define TOUCH_ENCODER_OPTIONS TOUCH_SEGMENTS + 2

typedef struct PACKED {
    uint8_t r;
    uint8_t c;
} encodermap_t;

const encodermap_t touch_encoder_map[NUMBER_OF_TOUCH_ENCODERS][TOUCH_ENCODER_OPTIONS] =
{
    { {  6, 0 }, {  6, 1 }, {  6, 2 }, {  6, 3 }, {  6, 4 } }, // Touch Encoder 1 matrix entries
    { { 13, 0 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 } }  // Touch Encoder 2 matrix entries
};

static void process_encoder_matrix(encodermap_t pos) {
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, true));
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, false));
}

bool touch_encoder_tapped_kb(uint8_t index, uint8_t section) {
    if (!touch_encoder_tapped_user(index, section))
        return false;

    process_encoder_matrix(touch_encoder_map[index][section + 2]);
    return false;
}

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
