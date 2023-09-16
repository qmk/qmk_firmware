# bahm/aster_ergo

The Aster Ergo PCB for the Aster Ergo keyboard (A TKL ergo keyboarđ)

* Keyboard Maintainer: [mechlovin](https://github.com/mechlovin)
* Hardware Supported: Aster Ergo PCB, APM32F103
* Hardware Availability: [GH](https://geekhack.org/index.php?topic=116962.0)

Make example for this keyboard (after setting up your build environment):

    make bahm/aster_ergo:default

Flashing example for this keyboard:

    make bahm/aster_ergo:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
