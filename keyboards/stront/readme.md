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

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Keymaps

-   `default` - sample keymap with home row mods. Not recommended for longer use - create your own.
-   `hid` - default keymap with HID support. Requires additional software running on computer, see https://github.com/zzeneg/qmk-hid-host.
-   `i2c` - default keymap with I2C Cirque instead of default SPI
-   `zzeneg` - my highly customized layout, you can use as a reference

Keymaps have [EE_HANDS](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) enabled, so any side can be master (though using side with touchpad as master is recommended). You have to specify left/right side by flashing with different commands:

`qmk flash -kb stront -km default -bl uf2-split-left`

or

`qmk flash -kb stront -km default -bl uf2-split-right`

If your keyboard is flashed already, you can do it by pressing key combinations - hold inner thumb key, then hold outer thumb key to activate SYSTEM layer. Now press outer bottom pinky key for left side or inner bottom index key for right side. See [keymap](./keymaps/default/keymap.c) for better understanding. Reconnect the keyboard to apply changes.

## Bootloader

Enter the bootloader in 2 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (outer top pinky key) and plug in the keyboard
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` - by default you need to hold inner thumb key, then hold outer thumb key and press middle thumb key (see [keymap.c](./keymaps/default/keymap.c) for details). It's a complicated combination to avoid accidental activations.

RP2040 Zero has physical boot/reset buttons but they are unaccessible after the keyboards is assembled, so always keep a `QK_BOOT` key and/or bootmagic feature in your keymaps.
