# stront

![stront](https://i.imgur.com/FOPnWhch.jpg)

Split keyboard with 38 keys, LCD display and Cirque trackpad.

-   Keyboard Maintainer: [zzeneg](https://github.com/zzeneg)
-   Hardware Supported: Stront PCBs, Waveshare RP2040 Zero
-   Hardware Availability: [GitHub](https://github.com/zzeneg/stront)

Make example for this keyboard (after setting up your build environment):

    make stront:default

Flashing example for this keyboard:

    make stront:default:flash

Existing keymaps:

-   `default` - sample keymap with home row mods. Not recommended for longer use - create your own.
-   `hid` - default keymap with HID support. Requires additional software running on computer, see https://github.com/zzeneg/qmk-hid-host.
-   `i2c` - default keymap with I2C Cirque instead of default SPI
-   `zzeneg` - my highly customized layout, you can use as a reference

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available
