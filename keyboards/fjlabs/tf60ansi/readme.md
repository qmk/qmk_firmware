# FJLabs TF60 ANSI 

The following is the QMK Firmware for the FJLabs TF60 ANSI PCB, a universal tray mount 60% hotswap PCB with per key RGB LED's. 

The PCB will feature:
* Kailh Hotswap sockets
* QMK & VIA compatibility
* Per-Key RGB LED's

---

* Keyboard Maintainer: FJLabs
* Hardware Supported: TF60 ANSI

Make example for this keyboard (after setting up your build environment):

    make fjlabs/tf60ansi:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs). 

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available