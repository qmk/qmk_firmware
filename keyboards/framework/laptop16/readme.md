# Framework Laptop 16 Keyboard

Keyboard input modules for the Framework Laptop 16.

* Keyboard Maintainer: [Daniel Schaefer](https://github.com/JohnAZoidberg)
* Hardware Supported: Framework Laptop 16 Keyboard, Numpad and Macropad
* Hardware Availability: Soon available at https://frame.work/marketplace

## Variants

| Name     | Size     | Backlight  | Keys |
| -------- | -------- | ---------- | ---- |
| ansi     | Keyboard | White      |   78 |

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb framework/laptop16/ansi -km default

Flashing example for the ANSI keyboard:

    qmk compile -kb framework/laptop16/ansi -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **On Framework Laptop 16 Keyboard**: Hold down left ALT and right ALT while installing the module
* **On Framework Laptop 16 Numpad**: Hold down keys for 2 and 6 while installing the module
* **On Raspberry Pi Pico**: Hold down bootsel button when plugging in

//TODO: BOOTMAGIC DOESN'T WORK!!
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
