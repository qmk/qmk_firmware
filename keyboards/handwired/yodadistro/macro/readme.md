# Yoda Distro

![YodaDistro](https://i.imgur.com/W2xnKjF.jpeg)

Scratch made direct wire pin 8-Key (4x2) Macro Pad using a Raspberry Pi Pico (2040).

* Keyboard Maintainer: [YodaDistro](https://github.com/YodaDistro)
* Hardware Supported: Raspberry Pi Pico (2040)
* Hardware Availability: 3D Printed Design (https://github.com/YodaDistro/MacroPad)

Make example for this keyboard (after setting up your build environment):

    make handwired/yodadistro/macro:default
    
Flashing example for this keyboard:

    make handwired/yodadistro/macro:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs)

## Bootloader

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available