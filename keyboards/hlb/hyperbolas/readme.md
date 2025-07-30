# hyperbolas

![hyperbolas](imgur.com image replace me!)

TKL project from HLB with 8K pcb layout compatibility.

* Keyboard Maintainer: [H3lli0n](https://github.com/H3lli0n)
* Hardware Supported: HLB Hyperbolas

Make example for this keyboard (after setting up your build environment):

    make hlb/hyperbolas:default

Flashing example for this keyboard:

    make hlb/hyperbolas:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
