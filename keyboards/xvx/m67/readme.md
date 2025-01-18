# XVX M67
[![XVX M67](https://s21.ax1x.com/2025/01/17/pEFLLGt.png)](https://imgse.com/i/pEFLLGt)
* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: [XVX M67](https://www.xvxchannel.com/products/xvx-m67-jadestone-mechanical-keyboard-with-imd-tech-keycaps-interstellar-black-wired)
* Hardware Availability: [XVX](https://www.xvxchannel.com)

Make example for this keyboard (after setting up your build environment):

    make xvx/m67:default

Flashing example for this keyboard:

    make xvx/m67:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
