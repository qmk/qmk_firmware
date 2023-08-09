# Framework Laptop 16 Keyboard

Keyboard input modules for the Framework Laptop 16.

* Keyboard Maintainer: [Daniel Schaefer](https://github.com/JohnAZoidberg)
* Hardware Supported: Framework Laptop 16 Keyboard, Numpad and Macropad
* Hardware Availability: Soon available at https://frame.work/marketplace

## Variants

There are 5 different hardware variants with different number of keys and
backlight options.

| Name     | Size     | Backlight  | Keys |
| -------- | -------- | ---------- | ---- |
| ansi     | Keyboard | RGB/White  |   78 |
| iso      | Keyboard | White      |   79 |
| jis      | Keyboard | White      |   83 |
| numpad   | Numpad   | White      |   21 |
| macropad | Numpad   | RGB        |   24 |

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb framework/ansi -km default
    qmk compile -kb framework/iso -km default
    qmk compile -kb framework/jis -km default
    qmk compile -kb framework/numpad -km default
    qmk compile -kb framework/macropad -km default

Flashing example for the ANSI keyboard:

    qmk compile -kb framework/ansi -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **On Framework Laptop 16 Keyboard**: Hold down left ALT and right ALT while installing the module
* **On Framework Laptop 16 Numpad**: Hold down keys for 2 and 6 while installing the module
* **On Raspberry Pi Pico**: Hold down bootsel button when plugging in
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available