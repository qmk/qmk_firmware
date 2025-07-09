# Vault 35 WKL Universal

![Vault 35 WKL Universal](https://i.imgur.com/gtJwgiv.png)

A drop in replacement PCB for the Vault 35 WKL case, originally designed by ProjectCain Mechvault.

* Keyboard Maintainer: [jlw](https://github.com/josh-l-wang)
* Hardware Supported: Vault 35 WKL Universal PCB
* Hardware Availability: [jlw-kb.com](https://jlw-kb.com)

Make example for this keyboard (after setting up your build environment):

    make jlw/vault35_wkl_universal:default

Flashing example for this keyboard:

    make jlw/vault35_wkl_universal:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Hold button on the back of the PCB while plugging in the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
