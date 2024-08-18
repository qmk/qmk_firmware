# Le Chiffre Pi

![](https://github.com/user-attachments/assets/731698ac-7ee9-4b36-b083-c3377b2a5480)

*A short description of the keyboard/project*

* Keyboard Maintainer: [jkaunert](https://github.com/jkaunert)
* Hardware Supported: RP2040
* Hardware Availability: <https://areyoujoshing.me/keyboards>

Make example for this keyboard (after setting up your build environment):

    make handwired/are_you_joshing_me/le_chiffre_pi:default

Flashing example for this keyboard:

    make handwired/are_you_joshing_me/le_chiffre_pi:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
