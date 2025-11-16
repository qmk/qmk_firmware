# Framework Laptop 16 Keyboard

Keyboard input modules for the Framework Laptop 16.

* Keyboard Maintainer: [Daniel Schaefer](https://github.com/JohnAZoidberg)
* Hardware Supported: Framework Laptop 16 Keyboard. Soon: Numpad and Macropad
* Hardware Availability: Available at https://frame.work/marketplace


## Vendor specific
On the Framework 16, KC_MSEL launches the Framework website

## Variants

| Name           | Size     | Backlight  | Keys |
| -------------- | -------- | ---------- | ---- |
| ansi/white     | Keyboard | White      |   78 |

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb framework/laptop_16/ansi/white -km default

Flashing example for the ANSI keyboard:

    qmk compile -kb framework/laptop_16/ansi/white -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **On Framework Laptop 16 Keyboard**: Hold down left ALT and right ALT while installing the module
* **On Raspberry Pi Pico**: Hold down bootsel button when plugging in
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard. On the ANSI board, this is the C key.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
