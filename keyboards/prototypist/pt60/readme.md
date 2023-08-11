# prototypist/pt60

![prototypist/pt60](https://i.imgur.com/Iu3QwxRh.png)

*Proto[Typist] Keyboards' first ever in-house universal 60% PCB designed by Josh (Anjheos). 
Features various physical layouts available to fit multiple regional and bottom row layouts.
Default layout is in ISO.*

* Keyboard Maintainer: [Josh @ Prototypist](https://github.com/Anjheos)
* Hardware Supported: **PT-60J PCB and PT-60C PCB**
* Hardware Availability: [Proto[Typist]](https://prototypist.net)

Make example for this keyboard (after setting up your build environment):

    make prototypist/pt60:default
    make prototypist/pt60:via
    make prototypist/pt60:default_ansi
    

Flashing example for this keyboard:

    make prototypist/pt60:default:flash
    make prototypist/pt60:via:flash
    make prototypist/pt60:default_ansi:flash
    

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB marked `RESET0`.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
