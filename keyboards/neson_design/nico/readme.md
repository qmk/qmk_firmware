# Neson Design (formerly iNETT Studio) Nico

A 65% keyboard with F area from the Neson Design's N series.

* Keyboard Maintainer: [astro](https://github.com/yulei)  
* Hardware Supported: Nico keyboard
* Hardware Availability: Limited gb

Make example for this keyboard (after setting up your build environment):

    make neson_design/nico:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Briefly press the *RST* button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.