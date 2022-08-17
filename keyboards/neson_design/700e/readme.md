# Neson Design (formerly iNETT Studio) 700E

A 65% keyboard with function keys from the Neson Design's N series.

* Keyboard Maintainer: [astro](https://github.com/yulei)  
* Hardware Supported: 700E keyboard
* Hardware Availability: Limited gb

Make example for this keyboard (after setting up your build environment):

    make neson_design/700e:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Briefly press the *RST* button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.