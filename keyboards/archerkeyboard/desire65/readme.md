# desire65

![desire65](https://i.imgur.com/bTjvGzC.jpg)

A desirable 65% keyboard

* Keyboard Maintainer: [ArcherKeyboard](https://github.com/akyp)
* Hardware Supported: Desire65 PCB
* Hardware Availability: [Open source on GitHub](https://github.com/akyp/desire65-pcb)

Make example for this keyboard (after setting up your build environment):

    make archerkeyboard/desire65:default

Flashing example for this keyboard:

    make archerkeyboard/desire65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold the "USB_BOOT" button on the back of the PCB (the one closest to the MCU) and briefly press the "RESET" button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available