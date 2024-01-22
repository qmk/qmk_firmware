# STEED SMK82 PRO
![STEED SMK82 PRO](https://github.com/jonylee1986/qmk_firmware_master/assets/108282809/42973b4e-8ed5-43d7-8379-70851c67df0f)
A customizable 75% encoder keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: STEED SMK82 PRO
* Hardware Availability: [STEED](https://steed.sg/products/smk82)

Make example for this keyboard (after setting up your build environment):

    make steed/smk82_pro:default

Flashing example for this keyboard:

    make steed/smk82_pro:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the Hold down the top left key (commonly programmed as *Esc*) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
