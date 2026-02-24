# Chosfox Vero75

A customizable 85key keyboard.

[Vero75](https://chosfox.com/products/vero75)

* Hardware Supported: Vero75 PCB with es32fs026 microcontroller

Make example for this keyboard (after setting up your build environment):

    make chosfox/vero75:default

Flashing example for this keyboard:

    make chosfox/vero75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
