# prototypist/pt80

![prototypist/pt80](https://i.imgur.com/voa3ivJh.png)

*Proto[Typist] Keyboards' first ever in-house universal TKL PCB designed by Josh (Anjheos). 
Features various physical layouts available to fit multiple regional, F-row and bottom row layouts.
Default layout is in ISO.*

* Keyboard Maintainer: [Josh @ Prototypist](https://github.com/Anjheos)
* Hardware Supported: **PT-80J PCB and PT-80C PCB**
* Hardware Availability: [Proto[Typist]](https://prototypist.net)

Make example for this keyboard (after setting up your build environment):

    make prototypist/pt80:default
    make prototypist/pt80:via
    make prototypist/pt80:default_ansi
    

Flashing example for this keyboard:

    make prototypist/pt80:default:flash
    make prototypist/pt80:via:flash
    make prototypist/pt80:default_ansi:flash
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB marked `RESET0`.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.