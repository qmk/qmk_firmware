#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include <string.h>

/* Support for HT16K33 backpacks with 16x8 LED drivers.
 */
#define LED_ADDR(x) (0x70 | (x))
#define LED_ADDR_WRITE(x) ((LED_ADDR(x) << 1) | I2C_WRITE)

static uint8_t ht16k33_status_l = 0x0;
static uint8_t ht16k33_status_r = 0x0;

uint8_t
ht16k33_cmd(uint8_t cmd, uint8_t addr) {
    uint8_t status;
    status = i2c_start(LED_ADDR_WRITE(addr));             if (status) goto out;
    status = i2c_write(cmd);
out:
    i2c_stop();
    return status;
}

void init_lcd(void) {
    int stopped = true;
    ht16k33_status_r = ht16k33_cmd(0x21, 1);
    ht16k33_status_l = ht16k33_cmd(0x21, 2);
    ht16k33_status_r = ht16k33_cmd(0x81, 1);
    ht16k33_status_l = ht16k33_cmd(0x81, 2);
    ht16k33_status_r = ht16k33_cmd(0xE8, 1);
    ht16k33_status_l = ht16k33_cmd(0xE8, 2);
    ht16k33_status_r = i2c_start(LED_ADDR_WRITE(1));    if (ht16k33_status_r) goto out;
    stopped = false;
    ht16k33_status_r = i2c_write(0x00);          if (ht16k33_status_r) goto out;
    for (int i = 0; i < 16; ++i) {
	    ht16k33_status_r = i2c_write(0x00);          if (ht16k33_status_r) goto out;
    }
    i2c_stop();
    ht16k33_status_l = i2c_start(LED_ADDR_WRITE(2));    if (ht16k33_status_l) goto out;
    stopped = false;
    ht16k33_status_l = i2c_write(0x00);          if (ht16k33_status_l) goto out;
    for (int i = 0; i < 16; ++i) {
	    ht16k33_status_r = i2c_write(0x00);          if (ht16k33_status_l) goto out;
    }
out:
    if (!stopped)
	    i2c_stop();
}

