# Tercy/rev004

![Tercy/rev004](https://imgur.com/qRwZ9uX.png)

Tercy_rev004 is a 44-key keyboard. The default key map is follows.

* Layer 0 : ![Layer0](https://imgur.com/Is4nQgY.png)

* Layer 1, 2 (Tri Layer Lower, Upper) ![Layer1,2](https://imgur.com/xV5cnSK.png)

* Layer 3 (Tri Layer Adjust) ![Layer3](https://imgur.com/r9GMytI.png)

* Keyboard Maintainer: [TercyKB](https://github.com/TercyKB)
* Hardware Supported: Tercy_rev004 PCB, Pro Micro.
* Hardware Availability: The PCB is not for sale for now (May 2024). But you can download kicad project of the PCB from https://etlife.info/wp-content/uploads/2024/05/Keyboard_004.kicad_pro.zip. Pro Micro embedded on the PCB is [OSOYOO Type C version Pro Micro board](https://amzn.asia/d/95Ze0f2). The simplest schematic diagram for Tercy_rev004 is follows.

![Tercy/rev004_schematic](https://imgur.com/pDtgFxh.png)

Make example for this keyboard (after setting up your build environment):

    make Tercy/rev004:default

Flashing example for this keyboard:

    make Tercy/rev004:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset**: Short RST and GND on ProMicro board
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available