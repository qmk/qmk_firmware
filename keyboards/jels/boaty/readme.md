# Boaty

![Boaty](https://i.imgur.com/6LEaYxSh.jpg)

* Keyboard Maintainer: [jels](https://github.com/JoahNelson)
* Hardware Supported: Boaty
* Hardware Availabililty: Limited Group buy from: [jels](https://jels.au)

Make example for this keyboard (after setting up your build environment):
    
    make jels/boaty:default
    
Flashing example for this keyboard:

    make jels/boaty:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the leftmost key (ESC) and plug in the keyboard
* **USBASPLoader**: Press down the BOOT switch and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

* **Exit Bootloader**: To exit the bootloader, press the RESET switch (Left of BOOT).
