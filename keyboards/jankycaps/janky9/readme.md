# Janky No.9

![Janky No.9](https://i.imgur.com/hkEorpO.jpeg)

*A Handmade 3x3 Macropad*

* Keyboard Maintainer: [telybelly](https://github.com/telybelly)
* Hardware Supported: Janky No.9
* Hardware Availability: <https://anky.studio/>

Make example for this keyboard (after setting up your build environment):

    make jankycaps/janky9:default

Flashing example for this keyboard:

    make jankycaps/janky9:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Quickly short the RST and GND pads on the PCB twice
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
