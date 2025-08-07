# itstleo/itstleo40

![itstleo/itstleo40](https://i.imgur.com/snNWZPmh.jpeg)

* ItsTLeo first pcb using planck mit community layout, powered by QMK with VIA supported

* Keyboard Maintainer: [ItsTLeo](https://github.com/ItsTLeo)
* Hardware Supported: Powered with RP2040

Make example for this keyboard (after setting up your build environment):

    make itstleo/itstleo40:default

Flashing example for this keyboard:

    make itstleo/itstleo40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available