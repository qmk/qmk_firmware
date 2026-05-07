# handwired/fabiclawz/alpha_fs

![handwired/fabiclawz/alpha_fs](https://i.imgur.com/FOOmKXN.jpeg)

My first keyboard with custom PCB, originally designed for the Milk-V duo series of RISC-V MCUs with pin compatibility with the Raspberry Pi Pico used in this
case for QMK.

* Keyboard Maintainer: [Fabian Felix Selbach](https://github.com/FFS2309)
* Hardware Supported: Raspberry Pi Pico, Custom PCB
* Hardware Availability: [Hardware design files](https://github.com/FFS2309/alpha_fs_keyboard)

Make example for this keyboard (after setting up your build environment):

    make handwired/fabiclawz/alpha_fs:default

Flashing example for this keyboard:

    make handwired/fabiclawz/alpha_fs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the Pi Pico if available
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
