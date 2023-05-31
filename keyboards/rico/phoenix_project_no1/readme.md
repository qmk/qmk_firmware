# Phoenix Project No 1

![Type S](https://i.imgur.com/YJaz6P3h.jpeg)
![Type H](https://i.imgur.com/7Lz9oRLh.jpeg)

This is an open source collection of M65-A keyboard replacement PCBs, available both in solderable and hotswap variants.  

* Keyboard Maintainer: [Eric Becourt, aka Rico](https://github.com/mymakercorner)
* Hardware Supported: Phoenix Project No 1 Type S (solder) and Type H (hotswap)
* Hardware Availability: hardware is open source, Github repository contains everything to easily have fully assembled PCBs at JLCPCB

More details in Github repository [here](https://github.com/mymakercorner/Phoenix_Project_No1)

Make example for this keyboard (after setting up your build environment):

    make rico/phoenix_project_no1:default

Flashing example for this keyboard:

    make rico/phoenix_project_no1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

You can enter the bootloader in 5 ways:

* **QMK software ways:**
    * **Bootmagic reset**: hold down the key at (0,0) in the matrix (the top left key or Escape) and plug in the keyboard
    * **Keycode in layout**: press the key mapped to `QK_BOOT` that is the top left key or Escape on layer 2
    * **Physical BOOTSEL button**: double tap the BOOTSEL button
* **Native RP2040 MCU ways:**
    * **Physical BOOTSEL and RESET button**: while keyboard is plugged maintain RESET button pressed, press BOOTSEL button then release the RESET button
    * **Physical RESET button**: maintain RESET button pressed while plugging in the keyboard
