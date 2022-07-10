# Sofle Keyboard with KB2040

This is the [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040) revision, a drop-in Pro Micro replacement controller for Sofle (only RGB tested, should normally also work on V1).

## Keyboard Info

* Keyboard Maintainer (Keyboard): [Josef Adamcik](https://josef-adamcik.cz) [Twitter:@josefadamcik](https://twitter.com/josefadamcik)   [@filterpaper](https://github.com/filterpaper)
* Keyboard Maintainer (KB2040 Port): [marcoster](https://github.com/marcoster)
* Hardware Supported:
  * [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040) controller
  * [Sofle](https://github.com/josefadamcik/SofleKeyboard) keyboard

Make example for this controller (after setting up your build environment):

    make sofle/kb2040:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
* **Physical reset button**: Quick double-tap on the reset button soldered on the PCB.
* **Controller boot button**: Hold the `BOOT` button on the controller and plug in the USB.
* **Bootmagic reset**: Hold down the top left key on the left half and plug in the controller (untested or maybe not available in the keymap).

