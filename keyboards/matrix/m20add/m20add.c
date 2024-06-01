/**
 * m20add.c
 */

#include "m20add.h"
#include "tca6424.h"
#include "rgb_ring.h"
#include "i2c_master.h"

void set_pin(uint16_t pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    data |= ( 1 << GET_PIN(pin));
    tca6424_write_port(GET_PORT(pin), data);
}

void clear_pin(uint16_t pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    data &= ~( 1 << GET_PIN(pin));
    tca6424_write_port(GET_PORT(pin), data);
}

uint8_t read_pin(uint16_t pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    return (data & (1<<GET_PIN(pin))) ? 1 : 0;
}

void matrix_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgb_ring_init();
#endif
    matrix_init_user();
}

void matrix_scan_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgb_ring_task();
#endif
    matrix_scan_user();
}

static uint16_t caps_lock_pin = DEF_PIN(TCA6424_PORT2, 3);
static uint16_t scroll_lock_pin = DEF_PIN(TCA6424_PORT0, 1);

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_state.caps_lock ? set_pin(caps_lock_pin) : clear_pin(caps_lock_pin);
        led_state.scroll_lock ? set_pin(scroll_lock_pin) : clear_pin(scroll_lock_pin);
    }
    return res;
}

#define REBOOT_MAGIC 0x41544B42

void bootloader_jump(void) {
    // set the magic number for resetting to the bootloader
    *(uint32_t *)(&(RTCD1.rtc->BKP0R)) = REBOOT_MAGIC;
    NVIC_SystemReset();
}
