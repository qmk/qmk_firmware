# rephlex/2k
![Rephlex/2k](https://media.discordapp.net/attachments/1007286874525667470/1138624777045684345/cV64ZQW.jpeg?width=913&height=685)

*An analog keypad intended for Osu! with dynamic actuation point, VIA, OLED and RGB*

* Keyboard Maintainer: [Jake Stewart](https://github.com/RephlexZero)
* Hardware Supported: *MoonPad, Minipad, Alphatec Helios, anything RP2040 with minor adjustment*
* Hardware Availability: *https://github.com/RephlexZero/MoonPad*

Make example for this keyboard (after setting up your build environment):

    make rephlex/2k:default

Flashing example for this keyboard:

    make rephlex/2k:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and
the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start
with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**: Briefly hold the button on the back of the PCB whilst plugging in the keyboard.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.