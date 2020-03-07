# Arm/ChibiOS Early Initialization

QMK uses ChibiOS as the underlying layer to support a multitude of Arm-based devices. Each ChibiOS-supported board has a low-level board layer, which is responsible for initialising hardware peripherals such as the clocks, and GPIOs.

If your board needs extra initialisation at a very early stage, consider overriding the following APIs.

## `early_hardware_init_pre()`

The function `early_hardware_init_pre` is the earliest possible code that can be executed by a board firmware. This is executed before clocks or GPIOs are configured, so any preparation using GPIOs is not likely to work at this point.

ChibiOS has not yet been initialised either, so functionality such as delays are unlikely to work.

If you wish to override this API, consider limiting use to writing to low-level registers and/or initialising variables.

The default implementation of this function is to jump to bootloader, if the bootloader address has been specified in your board's `rules.mk`.

To implement your own version of this function, in your board's source files:

    void early_hardware_init_pre(void) {
        // do things with registers and variables
    }

## `early_hardware_init_post()`

The function `early_hardware_init_post` is the next earliest possible code that can be executed by a board firmware. This is executed after clocks or GPIOs are configured, so any preparation using GPIOs is not likely to work at this point.

Much like `early_hardware_init_pre`, ChibiOS has not yet been initialised either, so the same restrictions apply.

If you wish to override this API, the same recommendation above applies, with the exception of modifying GPIOs.

The default implementation of this function is to do nothing.

To implement your own version of this function, in your board's source files:

    void early_hardware_init_post(void) {
        // toggle GPIO pins and things
    }

## `board_init()`

The function `board_init` is executed directly after the ChibiOS initialisation routines have completed. At this stage, all normal low-level functionality should be available for use, with the assumption that USB is not yet connected.

The default implementation of this function is to do nothing.

To implement your own version of this function, in your board's source files:

    void board_init(void) {
        // initialise low-level ChibiOS devices
    }
