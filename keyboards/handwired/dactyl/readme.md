# Dactyl

![Dactyl](https://i.imgur.com/3s2sqdGh.png)

The *Dactyl* is a parameterized, split-bodied, concave key-well, columnar arranged, ergonomic keyboard. The 'legacy' configuration of this board required a microcontroller and I/O expander, though modern renditions require 2 micro controllers.

- Default is the modernized 2 micro controller configuration in the `promicro` sub-directory.
- The legacy configuration has been retained and is available in the `legacy` sub-directory.

* Keyboard Maintainer: [Matthew Adereth](https://github.com/adereth)
* Hardware Supported: 
    * **Default** (Promicro): Arduino Pro Micro controllers, of clones of
    * Legacy: Teensy2 controller and MCP23018 I/O expander
* Hardware Availability: [Case Files](https://github.com/adereth/dactyl-keyboard)

Make examples for this keyboard (after setting up your build environment):

    make handwired/dactyl:default

Flashing examples for this keyboard:

    make handwired/dactyl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
