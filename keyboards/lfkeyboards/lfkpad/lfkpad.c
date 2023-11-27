#include "quantum.h"

#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"

void matrix_init_kb(void) {
    matrix_init_user();

#ifdef ISSI_ENABLE
    issi_init();
#endif

#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif
}

void matrix_scan_kb(void) {
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif

#ifdef ISSI_ENABLE
    // switch/underglow lighting update
    static uint32_t issi_device = 0;
    static uint32_t twi_last_ready = 0;

    if (twi_last_ready > 1000) {
        // It's been way too long since the last ISSI update, reset the I2C bus and start again
        dprintf("TWI failed to recover, TWI re-init\n");
        twi_last_ready = 0;
        TWIInit();
        force_issi_refresh();
    }

    if (isTWIReady()) {
        twi_last_ready = 0;
        // If the i2c bus is available, kick off the issi update, alternate between devices
        update_issi(issi_device, issi_device);

        if (issi_device) {
            issi_device = 0;
        } else {
            issi_device = 3;
        }
    } else {
        twi_last_ready++;
    }
#endif

    matrix_scan_user();
}

// LFK lighting info
const uint8_t rgb_matrices[] = { 0, 1 };
const uint8_t rgb_sequence[] = {
    32,  1,  2,  3,
    31, 30,  5,  6,
    28, 27,  7,
    17, 18,  9,  8,
    19, 21, 11,
      22,   14, 12,
    16,         26,
     4,         25,
    13,         24,
          20
};
