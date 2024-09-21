# BAHRNOB65

![BAHRNOB65](https://i.imgur.com/AK1ksQEh.jpeg)

Bahrnob 65: Gasket Mount 65%

* Keyboard Maintainer: [Zykrah](https://github.com/zykrah)
* Hardware Supported: Bahrnob65 Solder PCB
* Hardware Availability: N/A

Make example for this keyboard (after setting up your build environment):

    make kalakos/bahrnob65:default

Flashing example for this keyboard:

    make kalakos/bahrnob65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the reset button on the back of the pcb
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
