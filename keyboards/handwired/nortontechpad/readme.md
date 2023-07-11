# NortonTechPad



The NortonTechPad is a numpad inspired by the SiCK-Pad,it is also 3D printed and designed to be inexpensive.

-   Keyboard Maintainer: [NortonTech](https://github.com/NortonTech-Official)
-   Hardware Supported: Pro Micro


Make example for this keyboard (after setting up your build environment):

    make handwired/nortontechpad:default

Flashing example for this keyboard:

    make handwired/nortontechpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Short the GND and RST pins on the Pro Micro with something conductive.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
