# Mini Ashen 40

![Mini Ashen 40](https://i.imgur.com/0k3gFZCh.jpeg)

![Mini Ashen 40](https://i.imgur.com/B1w8qwPh.jpeg)

![Mini Ashen 40](https://i.imgur.com/LqxXW0Rh.jpeg)

A 40% keyboard with some extras
  - Arrows
  - Mini macro cluster
  - Full assembly with only through hole components

* Keyboard Maintainer: [jfescobar18](https://github.com/jfescobar18)
* Hardware Supported: Mini Ashen 40 PCB and Case
* Hardware Availability: [MechanicKeys](https://www.facebook.com/MechanicKeys-104963764775280)

Make example for this keyboard (after setting up your build environment):

    make mechanickeys/miniashen40:default

Flashing example for this keyboard:

    make mechanickeys/miniashen40:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical**: 
  1. Press and hold `BOOT` switch
  2. Tap `QK_BOOT` switch
  3. Release `BOOT` switch
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Flash bootloader
* [Follow this instructions](https://github.com/jfescobar18/USBaspLoader)
