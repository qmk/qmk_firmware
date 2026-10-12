# mithril

![mithril](https://i.imgur.com/F0h5OY6.jpg)

*A custom split ortholinear keyboard (4x6 + 3 thumb keys per half) with per-key RGB.*

* Keyboard Maintainer: [Javier San Félix Guajardo](https://github.com/sanfeps)
* Hardware Supported: Mithril rev1 PCB, ATmega32U4 (Caterina bootloader), split halves with serial sync
* Hardware Availability: PCB design, plate files and case at [github.com/sanfeps/mithril_kb](https://github.com/sanfeps/mithril_kb)

Make example for this keyboard (after setting up your build environment):

    make mithril/rev1:default

Flashing example for this keyboard:

    make mithril/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**:
    * **Left half**: hold down `Esc` (matrix position `0,0` — top-outer key) and plug in the keyboard.
    * **Right half**: hold down the top-outer key (`?` on the base layer, matrix position `5,0`) and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (mapped to the bottom-right key on layer 2 of the default keymap)
