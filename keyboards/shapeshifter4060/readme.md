Shapeshifter 4060
![Shapeshifter 4060](#TODO)

The Shapeshifter 4060 is a 40% keyboard that takes inspiration from the Atreus and makes it accessible by putting it on a standard-sized 60% keyboard pcb. Ergonomics should be accessible by anyone!

Keyboard Maintainer: [Chuck Lauer Vose](https://github.com/vosechu)
Hardware Supported: Kitsune Shapeshifter 4060 (v3.0.3) with a Pro Micro Compatible board / Proton C
Hardware Availability: GB coming soon

Make example for this keyboard (after setting up your build environment):

    make shapeshifter4060:default
    
For use with the Proton C
    
    make shapeshifter4060:default CTPC=yes
    
Flashing example for this keyboard:

    make shapeshifter4060:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Physical reset button**: Briefly press the button on the top of the PCB
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available

## Changelog

v3.0.3: Complete rewrite using a standard pro micro pinout.

## Build log

https://docs.google.com/document/d/1ml2rBdiO6GhrUx2HyLqip0i24bCU8d-fQR8adSEPWzQ/edit
