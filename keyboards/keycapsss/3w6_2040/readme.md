# 3w6_2040

![image](https://i.imgur.com/QAL63nyh.jpg)

A split keyboard with 3x5 vertically staggered keys and 3 thumb keys, with support for pimoroni trackball modules on each half.

This version is distinct from keyboards/3w6 and is exclusive to [keycapsss.com](https://keycapsss.com).

* Keyboard Maintainer: [@keyboard-magpie]
* Hardware Supported: On board rp2040 microcontrollers.
* Hardware Availability: [keycapsss.com](https://keycapsss.com)

Make firmware .uf2 for this keyboard (after setting up your build environment):

    qmk compile -kb keycapsss/3w6_2040 -km default

Example of flashing this keyboard:

    qmk flash -kb keycapsss/3w6_2040 -km default (or drag and drop the uf2 from the above command into the mass storage device that appears when in bootloader mode)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press and hold the button on the front of the PCB when plugging in.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
