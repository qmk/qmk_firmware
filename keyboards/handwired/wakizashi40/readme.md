# Wakizashi 40

![Wakizashi40](https://i.imgur.com/TVTfa0X.jpg)

Reverse stagger 40% keyboard based on the Katana 60.

* Keyboard Maintainer: [xia0](https://github.com/xia0)
* Hardware Supported: ATmega32u4
* Hardware Availability: [prusaprinters.org](https://www.prusaprinters.org/prints/128575-wakizashi-40-keyboard)

Make example for this keyboard (after setting up your build environment):

    make handwired/wakizashi40:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
