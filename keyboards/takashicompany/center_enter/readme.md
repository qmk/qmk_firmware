# Center x Enter

![image](https://raw.githubusercontent.com/takashicompany/center-enter/master/images/qmk.jpg)

A 30% keyboard with the enter key placed in the center.
Option to install a rotary encoder is also available.
VIA (Remap) is also supported.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Center x Enter PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/center-enter

Make example for this keyboard (after setting up your build environment):

    make takashicompany/center_enter:default

Flashing example for this keyboard:

    make takashicompany/center_enter:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
