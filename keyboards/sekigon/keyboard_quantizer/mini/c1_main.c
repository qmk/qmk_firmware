
#include "tusb.h"
#include "pio_usb.h"
#include "pico/multicore.h"

static volatile bool core1_active;
static volatile bool core1_stop_trigger;
static volatile bool core1_start_trigger;

void __not_in_flash_func(c1_main)(void) {
    core1_active = true;

    // Use tuh_configure() to pass pio configuration to the host stack
    // Note: tuh_configure() must be called before
    pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
    pio_cfg.pin_dp = 4;
    pio_cfg.extra_error_retry_count = 10;
    tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &pio_cfg);

    // To run USB SOF interrupt in core1, init host stack for pio_usb (roothub
    // port1) on core1
    tuh_init(1);

    bool     core1_task_active = true;
    uint32_t interrupt         = 0;

    while (1) {
        if (core1_task_active) tuh_task();  // tinyusb host task

        if (core1_stop_trigger) {
            interrupt         = save_and_disable_interrupts();
            core1_task_active = false;
            core1_stop_trigger = false;
        } else if (core1_start_trigger) {
            restore_interrupts(interrupt);
            core1_task_active = true;
            core1_start_trigger = false;
        }
    }
}