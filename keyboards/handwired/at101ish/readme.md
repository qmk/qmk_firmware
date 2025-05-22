# AT101(-ish)

A replacement PCB for Dell AT101 family. (In theory) supports AT101, AT101W, AT102, AT102W, maybe other Bigfoot platform boards.

Keyboard Maintainer: QMK Community and Henrik O. Sørensen  
Hardware Supported: AT101(ish) PCB  
Hardware Availability: https://github.com/henrikosorensen/keyboard_pcbs/tree/master/at101_pcb

Make example for this keyboard (after setting up your build environment):

    make handwired/at101ish:default

Flashing example for this keyboard:
    
    make handwired/at101ish:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the programming button on the teensy 2.0 PCB.

