# TOKKI

![TOKKI]( https://i.imgur.com/nW9b5xWh.png )

65% soldered PCB with multiple layout configurations and top right blocker

* Keyboard Maintainer: [Alabahuy](https://github.com/Alabahuy)
* Hardware Supported: Tokki PCB, RP2040, RGB
* Hardware Availability: Private GB

Make example for this keyboard (after setting up your build environment):

    make jaykeeb/tokki:default

Flashing example for this keyboard:

    make jaykeeb/tokki:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
