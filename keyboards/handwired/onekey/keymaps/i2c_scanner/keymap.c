#include QMK_KEYBOARD_H

#include "i2c_master.h"
#include "debug.h"

#define TIMEOUT 50

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(KC_A)  //
};

void do_scan(void) {
    uint8_t nDevices = 0;

    dprintf("Scanning...\n");

    for (uint8_t address = 1; address < 127; address++) {
        // The i2c_scanner uses the return value of
        // i2c_start to see if a device did acknowledge to the address.
#if defined(__AVR__)
        i2c_status_t error = i2c_start(address << 1, TIMEOUT);
#else
#    pragma message("ChibiOS is currently 'best effort' and might not report accurate results")

        i2c_start(address << 1);

        // except on ChibiOS where the only way is do do "something"
        uint8_t      data  = 0;
        i2c_status_t error = i2c_readReg(address << 1, 0, &data, sizeof(data), TIMEOUT);
#endif
        if (error == I2C_STATUS_SUCCESS) {
            i2c_stop();
            dprintf("  I2C device found at address 0x%02X\n", address);
            nDevices++;
        } else {
            // dprintf("  Unknown error (%u) at address 0x%02X\n", error, address);
        }
    }

    if (nDevices == 0)
        dprintf("No I2C devices found\n");
    else
        dprintf("done\n");
}

uint16_t scan_timer = 0;

void matrix_scan_user(void) {
    if (timer_elapsed(scan_timer) > 5000) {
        do_scan();
        scan_timer = timer_read();
    }
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;

    i2c_init();
    scan_timer = timer_read();
}
