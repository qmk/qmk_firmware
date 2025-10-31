# bobpad

![bobpad](https://i.imgur.com/93zguh1h.jpg)

A bentopad based macropad with incline

* Keyboard Maintainer: [Ananya Kirti](https://github.com/AnanyaKirti)
* Hardware Supported: Custom 3D printed Case
* Hardware Availability: Contact bob at IMKC Discord

Make example for this keyboard (after setting up your build environment):

    make bobpad:default

Flashing example for this keyboard:

    make bobpad:default:flash

## Bootloader

Enter the bootloader in 3 ways:
* **Physical reset button**: Briefly short the pad connected to *RESET* and *GND* on the back
* **Keycode in layout**: Press the key mapped to `QK_BOOT`, this is the recommened method

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
