# Arm/ChibiOS Early Initialization

This page describes a part of QMK that is a somewhat advanced concept, and is only relevant to keyboard designers.

QMK uses ChibiOS as the underlying layer to support a multitude of Arm-based devices. Each ChibiOS-supported keyboard has a low-level board definition which is responsible for initializing hardware peripherals such as the clocks, and GPIOs.

Older QMK revisions required duplication of these board definitions inside your keyboard's directory in order to override such early initialization points; this is now abstracted into the following APIs, and allows usage of the board definitions supplied with ChibiOS itself. Check `<qmk_firmware>/lib/chibios/os/hal/boards` for the list of official definitions. If your keyboard needs extra initialization at a very early stage, consider providing keyboard-level overrides of the following APIs:

## `early_hardware_init_pre()`

The function `early_hardware_init_pre` is the earliest possible code that can be executed by a keyboard firmware. This is intended as a replacement for the ChibiOS board definition's `__early_init` function, and is the equivalent of executing at the start of the function.

This is executed before RAM gets cleared, and before clocks or GPIOs are configured; any delays or preparation using GPIOs is not likely to work at this point. After executing this function, RAM on the MCU may be zero'ed. Assigning values to variables during execution of this function may be overwritten.

As such, if you wish to override this API consider limiting use to writing to low-level registers. The default implementation of this function is to do nothing.

To implement your own version of this function, in your keyboard's source files:

    void early_hardware_init_pre(void) {
        // do things with registers
    }

## `early_hardware_init_post()`

The function `early_hardware_init_post` is the next earliest possible code that can be executed by a keyboard firmware. This is executed after RAM has been cleared, and clocks and GPIOs are configured. This is intended as a replacement for the ChibiOS board definition's `__early_init` function, and is the equivalent of executing at the end of the function.

Much like `early_hardware_init_pre`, ChibiOS has not yet been initialized either, so the same restrictions on delays and timing apply.

If you wish to override this API, consider limiting functionality to register writes, variable initialization, and GPIO toggling. The default implementation of this function is to do nothing.

To implement your own version of this function, in your keyboard's source files:

    void early_hardware_init_post(void) {
        // toggle GPIO pins and write to variables
    }

## `board_init()`

The function `board_init` is executed directly after the ChibiOS initialization routines have completed. At this stage, all normal low-level functionality should be available for use (including timers and delays), with the restriction that USB is not yet connected. This is intended as a replacement for the ChibiOS board definition's `boardInit` function.

The default implementation of this function is to do nothing.

To implement your own version of this function, in your keyboard's source files:

    void board_init(void) {
        // initialize anything that requires ChibiOS
    }
