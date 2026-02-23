# handwired/dactyl_manuform/5x7_2_6

![keyboad_image](https://i.ibb.co/09tfjY0/kbpic-small-21.jpg)

A standard Dactyl Manuform keyboard with 5x7 matrix, 6 thumb cluster keys. Last row has 2 keys only. Index column has 3 rows. The outer keys are 1,5u wide. [More info on https://github.com/ngrigoriev/dactyl-manuform-5x7_2_6](https://github.com/ngrigoriev/dactyl-manuform-5x7_2_6). Based on the original set of Dactyl Manuform keyboards created and maintaied by [Jack Humbert](https://github.com/jackhumbert).

This keyboard can be generated using one of Dactyl Manuform generators, such as (https://dactyl.mbugert.de/manuform).

* Keyboard Maintainer: [Nikolai Grigoriev](https://github.com/ngrigoriev)
* Hardware Supported: Promicro
* Hardware Availability: general DIY

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_manuform/5x7_2_6:default

Flashing example for this keyboard:

    make handwired/dactyl_manuform/5x7_2_6:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
