# fabiclawz/alpha_fs

My first keyboard with custom PCB, originally designed for the milk-v duo series of RISC-V MCUs with pin compatibility with the Raspberry Pi Pico.

* Keyboard Maintainer: [Fabian Felix Selbach](https://github.com/FFS2309)
* Hardware Supported: Raspberry Pi Pico, Custom PCB
* Hardware Availability: wherever

Make example for this keyboard (after setting up your build environment):

    make fabiclawz/alpha_fs:default

Flashing example for this keyboard:

    make fabiclawz/alpha_fs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
