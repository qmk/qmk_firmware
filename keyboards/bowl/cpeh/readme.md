# CPE-H

![CPE-H](https://i.imgur.com/mko3X7A.jpg)

The CPE-H is a Compact Ergo PCB with a left-side numpad, a rotary encoder and three RGB lock indicators (caps, num and scroll lock). It supports split backspace.

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: CPE-H PCB, STM32F401 microcontroller
* Hardware Availability: Group buy ended in 2024

Make example for this keyboard (after setting up your build environment):

    make bowl/cpeh:default

Flashing example for this keyboard:

    make bowl/cpeh:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: With the keyboard plugged in, hold the button on the back of the PCB for 5 seconds or more
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
