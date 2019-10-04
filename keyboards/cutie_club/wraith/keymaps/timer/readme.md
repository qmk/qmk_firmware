# Timed function layer keymap

Amber's personal keymap for the Wraith, but with a custom timed function layer keycode.  `config.h` contains defines that you can edit to control various aspects of this function.

## How does it work?
We are reading QMK's software timer in `matrix_scan_user()`.

Once the `TIME_TOGGLE` key is pressed, `layer_time_remaining` is set equal to `LAYER_TIMEOUT`, the layer defined in `LAYER_SWITCH` becomes active, and the LED on the Escape key (pin B0) will light up.

Each time the matrix is scanned, the software timer is read, and the value of `layer_time_remaining` is decreased by `prev_loop_time` - the amount of time elapsed since the last matrix scan.

When there are `TIMEOUT_WARNING`ms left in `LAYER_TIMEOUT`, the LED will begin to flash at intervals of `FLASH_PERIOD`ms.

When there are `TIMEOUT_WARNING/TIMEOUT_SCALE`ms left, the LED will begin to flash at intervals of `FLASH_PERIOD/SPEED_SCALE`ms.

When `layer_time_remaining` is equal to or less than 0, the layer defined in `LAYER_SWITCH` is removed from the layer stack.


## What are the defaults?
`LAYER_TIMEOUT` controls how long the layer will stay active for. The default is 10 seconds.

`TIMEOUT_WARNING` controls how long the warning (LED flash) will occur before the layer becomes inactive. The default is 3 seconds.

`FLASH_PERIOD` controls how long each LED flash interval is in the warning time. The default flash period is 250ms.

`SPEED_SCALE` controls how many times faster the LED will flash in the second flash period. The default scale is 2, twice as fast.

`TIMEOUT_SCALE` controls the length of the second flash period, relative to `TIMEOUT_WARNING`. The default scale is 4; for 750ms of the secondary flash period.

`LAYER_SWITCH` is the layer that will be activated by the key. The default is layer 1.
