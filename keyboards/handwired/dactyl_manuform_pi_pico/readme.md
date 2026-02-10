# dactyl_manuform_pi_pico

![dactyl_manuform_pi_pico](https://i.imgur.com/T9b74bI.jpg)

This is a dactyl_manuform 5x6 running Rasrberry Pi Pico.
It's based on alcor_dactyl but with more reasonable GPIO layout for Pi Pico
and clasic dactyl_manuform layout (pinkies have only 4 rows).

Build instructions: https://github.com/GustawXYZ/dactyl_manuform_pi_pico/ 

* Keyboard Maintainer: [Gustaw.xyz](https://github.com/Gustaw.xyz)
* Hardware Supported: Raspberry Pi Pico and other RP2040
* Hardware Availability: https://www.raspberrypi.com/products/raspberry-pi-pico/
* 3D Print model: https://github.com/abstracthat/dactyl-manuform

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_manuform_pi_pico:default

Flashing example for this keyboard:

    make handwired/dactyl_manuform_pi_pico:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
