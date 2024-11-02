# KLEC-02

![takashicompany/klec_02](https://i.imgur.com/1w6agBI.jpeg)

The KLEC-02 is a 36-key segmented keyboard.
The PCB can be fitted with key switch sockets, allowing easy replacement of key switches.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/klec_02

Make example for this keyboard (after setting up your build environment):

    make takashicompany/klec_02:default

Flashing example for this keyboard:

    make takashicompany/klec_02:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
