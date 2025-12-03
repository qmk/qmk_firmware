# Evoworks evo80

A customizable 88key keyboard.

![evo80](https://raw.githubusercontent.com/Linyer-qwq/image/main/evo80.jpg)

* Hardware Supported: evo80 PCB with es32fs026 microcontroller

Unfortunately the open-source library still doesn't support setting the Logo LED.

Make example for this keyboard (after setting up your build environment):

    make essemi/evo80:default

Flashing example for this keyboard:

    make essemi/evo80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
