# lilith

![lilith](https://i.imgur.com/aHr3Iiah.jpg)

Lilith by nix studio. 65% keyboard with gasket mount

* Keyboard Maintainer: [Martin Arnstad](https://github.com/arnstadm)
* Hardware Supported: Lilith PCB
* Hardware Availability: https://www.antipode.no/products/nix-lilith

Make example for this keyboard (after setting up your build environment):

    qmk compile nix_studio/lilith -km default

Flashing example for this keyboard:

    qmk flash nix_studio/lilith -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Briefly press the button on the back of the PCB, located on the top right
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
