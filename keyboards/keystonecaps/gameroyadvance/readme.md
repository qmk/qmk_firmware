# Game Roy ADVANCE

![Game Roy ADVANCE](https://i.imgur.com/N6RI4fUh.jpg)
![GRALAYOUTS](https://i.imgur.com/lHjTRQK.png)

A one-handed, expandable game pad designed to take your pc gaming to the next level. Designed by [Keystone Caps](https://keystonecaps.store).

* Keyboard Maintainer: [RoyMeetsWorld](https://github.com/ROYMEETSWORLD)
* Hardware Supported: Game Roy ADVANCE
* Hardware Availability: [keystonecaps.store](https://keystonecaps.store)

Make example for this keyboard (after setting up your build environment):

    make keystonecaps/gameroyadvance:default

Flashing example for this keyboard:

    make keystonecaps/gameroyadvance:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` (FN + Escape by default)

Special thanks to @tpstevens for all of his hard work in creating these firmware files from the mess that I had made.
