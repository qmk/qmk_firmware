# pad9

![pad9](https://github.com/prkrln/pad9/blob/main/pad9.jpg)
A cheap small macropad with the mcu underneath the switches.

* Keyboard Maintainer: [prkrln](https://github.com/prkrln)
* Hardware Supported: [XAIO RP2040](https://wiki.seeedstudio.com/XIAO-RP2040)
* Hardware Availability: [Seeed](https://www.seeedstudio.com/XIAO-RP2040-v1-0-p-5026.html), [Digikey](https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/102010428/14672129)

Make example for this keyboard (after setting up your build environment):

    make pad9:default

Flashing example for this keyboard:

    make pad9:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the encoder or top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the MCU
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
