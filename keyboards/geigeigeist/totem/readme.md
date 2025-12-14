# ToTeM

![geigeigeist/totem](https://imgur.com/a/Hb10koy)

*TOTEM is 38 keys column-staggered split keyboard made by @geigeigeist. It uses the Seeed XIAO RP2040.*

* Keyboard Maintainer: [zelezarof](https://github.com/zelezarof)
* Hardware Supported: [Seeed Studio XIAO nRF52840 BLE](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html) or [XIAO RP2040](https://www.seeedstudio.com/XIAO-RP2040-v1-0-p-5026.html).
* Hardware Availability: [GEIGEIGEIST](https://github.com/GEIGEIGEIST/TOTEM/tree/main/PCB) / [keeb.supply](https://keeb.supply/products/geist-totem)

Flashing example for this keyboard:

    # Flash left side of the keyboard
    qmk flash -kb geigeigeist/totem -km default -bl uf2-split-left

    # Flash right side of the keyboard
    qmk flash -kb geigeigeist/totem -km default -bl uf2-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Double press in quick succession the button on the back of the PCB
