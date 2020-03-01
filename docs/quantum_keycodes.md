# Quantum Keycodes

Quantum keycodes allow for easier customization of your keymap than the basic ones provide, without having to define custom actions.

All keycodes within quantum are numbers between `0x0000` and `0xFFFF`. Within your `keymap.c` it may look like you have functions and other special cases, but ultimately the C preprocessor will translate those into a single 4 byte integer. QMK has reserved `0x0000` through `0x00FF` for standard keycodes. These are keycodes such as `KC_A`, `KC_1`, and `KC_LCTL`, which are basic keys defined in the USB HID specification.

On this page we have documented keycodes between `0x00FF` and `0xFFFF` which are used to implement advanced quantum features. If you define your own custom keycodes they will be put into this range as well.

## QMK Keycodes

|Key           |Aliases  |Description                                            |
|--------------|---------|-------------------------------------------------------|
|`RESET`       |         |Put the keyboard into bootloader mode for flashing     |
|`DEBUG`       |         |Toggle debug mode                                      |
|`EEPROM_RESET`|`EEP_RST`|Reinitializes the keyboard's EEPROM (persistent memory)|
