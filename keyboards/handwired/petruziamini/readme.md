# PetruziaMini

![PetruziaMini](https://i.imgur.com/uk2BSazh.jpeg)

36 key ortholinear keyboard intended to be mapped as a split keyboard.

* Keyboard Maintainer: [LLLKST](https://github.com/LLLKST)
* Hardware Supported: *promicro compatible controller*
* Hardware Availability: [Aliexpress Pro Micro](https://www.aliexpress.us/item/3256805781371913.html)


Make example for this keyboard (after setting up your build environment):

    make handwired/petruziamini:default

Flashing example for this keyboard:

    make handwired/petruziamini:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader with:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` (3,5) + (0,1) in the matrix