# alcor_dactyl

![alcor_dactyl](https://i.imgur.com/F0E1JCQh.jpg)

This is a handwired dactyl manufor utalising an RP2040-zero

* Keyboard Maintainer: [Ethan](https://github.com/rocketstrong)
* Hardware Supported: Waveshare RP2040-Zero
* Hardware Availability: https://www.waveshare.com/wiki/RP2040-Zero
* 3D Print File Source: https://dactyl.mbugert.de/manuform

Make example for this keyboard (after setting up your build environment):

    make handwired/alcor_dactyl:default

Flashing example for this keyboard:

    make handwired/alcor_dactyl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
