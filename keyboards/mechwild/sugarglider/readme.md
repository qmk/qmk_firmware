# mechwild/sugarglider

![mechwild/sugarglider](https://i.imgur.com/IYhOU3xh.jpg)

The Sugar Glider is an ergonomic keyboard with columnar stagger and a central touchpad, OLED, and status LEDs.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: Sugar Glider v0.2
* Hardware Availability: [Sugar Glider on MechWild](https://mechwild.com/product/sugar-glider/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/sugarglider:default

Flashing example for this keyboard:

    make mechwild/sugarglider:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (assigned to the top left key) and plug in the keyboard while holding it.
* **Physical reset button**: Press and hold the boot0 button on the blackpill, tap  and release the nrst button on the blackpill, then release the boot0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available. By default this is the top right key on layer 1.
