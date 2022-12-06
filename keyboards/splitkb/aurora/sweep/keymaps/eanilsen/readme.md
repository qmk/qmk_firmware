# Aurora Sweep

![Sweep](https://raw.githubusercontent.com/splitkb/qmk_firmware/assets/aurora/sweep/sweep.jpg)

*The Aurora Sweep is a redesign by splitkb.com of the popular Sweep
(Sweep Bling MX) by David Barr and contributors.*

* Keyboard Maintainer: [Even A. Nilsen](https://github.com/eanilsen)
* Hardware Supported: Pro Micro 5V/16MHz and compatible.
* Hardware Availability: [splitkb.com](https://splitkb.com)

Make example for this keyboard (after setting up your build environment):

    make splitkb/aurora/sweep/rev1:eanilsen

Flashing example for this keyboard:

    make splitkb/aurora/sweep/rev1:eanilsen:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
