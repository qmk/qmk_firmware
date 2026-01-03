# EPOMAKER GALAXY68

A customizable 67-key keyboard.

* Keyboard Maintainer: [EPOMAKER](https://github.com/Epomaker)
* Hardware Supported: EPOMAKER GALAXY68 PCB with es32fs026 microcontroller

Make example for this keyboard (after setting up your build environment):

    make epomaker/galaxy68:default

Flashing example for this keyboard:

1. Hold ESC while plugging it in wired mode to enter flash mode
2. Create the binary with make
3. Copy the binary on the mounted flash drive
4. The flash drive should disappear and the keyboard restarts with the new firmware

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
