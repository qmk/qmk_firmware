# Lily58 Pro v2

![lily58_pro_v2_pcb_front](https://github.com/user-attachments/assets/a3550114-561d-4928-a12a-50b27f4db750)

![lily58_pro_v2_pcb_back](https://github.com/user-attachments/assets/f2789292-1a69-4769-8b3a-0ea8b8a6f024)

Lily58 Pro v2 is a 58-key split column-staggered keyboard.

* Keyboard Maintainer: [yuchi](https://yuchi.io/)
* Hardware Supported: Lily58 Pro V2 PCB(RP2040)
* Hardware Availability: [Lily58 Repository](https://github.com/kata0510/Lily58)

Make example for this keyboard (after setting up your build environment):

    make lily58/pro_v2:default

Flashing example for this keyboard:

    make lily58/pro_v2:default:flash

See the [build environment setup](https://docs.qmk.fm/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
