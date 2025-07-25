# DE60 Round 2

![DE60 R2](https://i.imgur.com/bXclgwa.png)

A GH60 form factor PCB for 60% keyboards. Uses a Left USB Type C connector or 5 JST SH positions for daughter board.

* Keyboard Maintainer: [Deemen17](https://github.com/Deemen17)
* Hardware Supported: STM32F103, De60fs Oring Edition PCB (White), De60 Tsangan Edition PCB (Red)
* Hardware Availability: Private Group Buy in Vietnam

Make example for this keyboard (after setting up your build environment):

    make deemen17/de60/r2:default

Flashing example for this keyboard:

    make deemen17/de60/r2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly double press the button RESET on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available