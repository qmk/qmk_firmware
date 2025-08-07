# Cans12erV2
![Cans12erV2](https://i.imgur.com/3fkbydJ.png)

New version of my 12-key orthogonal macro keypad with hot swappable keyswitch support and an encoder knob.

* Keyboard Maintainer: [Can Baytok](https://github.com/canbaytok)
* Build Instructions: [Github](https://github.com/canbaytok/Cans12erV2)
* Hardware Supported: RP2040 Zero
* Hardware Availability: amazon, aliexpress (RP2040 Zero clones work too)

Make example for this keyboard (after setting up your build environment):

    make handwired/cans12erv2:default

Flashing example for this keyboard:

    make handwired/cans12erv2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Quickly double press the reset button on the PCB to make the RP2040 boot into its uf2 mode
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available