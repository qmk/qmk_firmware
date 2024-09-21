# PuckBuddy

![PuckBuddy](https://i.imgur.com/iSVAHJzh.png)

A macropad with a Cirque Glidepoint Trackpad in the middle, powered by the STM32 Blackpill.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: PuckBuddy v1.0
* Hardware Availability: [PuckBuddy on MechWild](https://mechwild.com/product/puckbuddy/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/puckbuddy:default

Flashing example for this keyboard:

    make mechwild/puckbuddy:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (assigned to the top left key) and plug in the keyboard while holding it.
* **Physical reset button**: Press and hold the boot0 button on the blackpill, tap  and release the nrst button on the blackpill, then release the boot0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available. By default this is the top right key on layer 1.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).