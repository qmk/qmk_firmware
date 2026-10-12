# hnk65

Our Hide Nothing Keyboard version of the traditional 65%, with or without RGB support. For more information visit https://hnkbd.ca

* Keyboard Maintainer: [hnkbd](https://github.com/ascYAOBT)
* Hardware Supported: hnk65, either with or without per key RGB LED
* Hardware Availability: https://hnkbd.ca

Make example for this keyboard (after setting up your build environment):

    make hnk/hnk65:default

Flashing example for this keyboard:

    make hnk/hnk65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB while plugged in and with QMK Toolbox opened. 
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
