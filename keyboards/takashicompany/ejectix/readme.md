# Ejectix

![takashicompany/ejectix](https://i.imgur.com/gGk5UVdh.jpg)

Ejectix is a 36-key, low-staggered keyboard.  
Its layout is similar to that of a conventional keyboard, making it suitable for an introductory keyboard of 30% size.  
Its relatively simple structure makes it easy to assemble, and it is recommended for those who are just starting to build their own keyboards.  
Since the firmware is VIA-compatible, it is possible to write the firmware and change the keymap from a web browser by using Remap.  
The MX socket is also supported, making it easy to replace the keyswitch for long-lasting use.  
Underglow LEDs can also be used to decorate your desk.

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: Ejectix PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/ejectix

Make example for this keyboard (after setting up your build environment):

    make takashicompany/ejectix:default
    

Flashing example for this keyboard:

    make takashicompany/ejectix:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
