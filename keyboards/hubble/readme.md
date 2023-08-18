# hubble

![hubble](https://i.imgur.com/buTSdUqh.jpg)

*ProMicro based 40% keyboard for with nav cluster, underglow and cyrillic layout support*

* Keyboard Maintainer: [Anton Chernenko](https://github.com/ch3rny)
* Hardware Supported: [Hubble PCB](https://github.com/ch3rny/hubble-keyboard)
* Hardware Availability: Opensource

Make example for this keyboard (after setting up your build environment):

    make hubble:default

Flashing example for this keyboard:

    make hubble:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
