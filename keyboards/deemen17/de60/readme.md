# DE60

Deemen17 Works's 60% PCB Platform, which works as the base for our 60%-layout PCB designs.

* Keyboard Maintainer: [Deemen17](https://github.com/Deemen17)
* Hardware Supported: DE60 PCBs
* Hardware Availability: [Deemen17 Facebook Page](https://www.facebook.com/deemen17/), [Deemen17 Works Instagram](https://www.instagram.com/deemen17.works)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (ESC/Escape) and plug in the keyboard
* **Physical reset button**: Double tap the button RESET on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available