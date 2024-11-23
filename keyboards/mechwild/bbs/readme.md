# BB Steno (BBS)

![BBS](https://i.imgur.com/XIjlzKOh.png)

A bare-bones stenography keyboard. No bells or whistles. Simple, cheap, effective, steno.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: BBS v0.1, v1.1
  * v0.1 PCBs were miswired for WS2812 RGB LED strips. As the data pin is the same, a strip could still be added with some handwiring.
* Hardware Availability: [BBS on MechWild](https://mechwild.com/product/bb-steno/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/bbs:default

Flashing example for this keyboard:

    make mechwild/bbs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (assigned to the top left key) and plug in the keyboard while holding it.
* **Physical reset button**: Press and hold the boot0 button on the blackpill, tap  and release the nrst button on the blackpill, then release the boot0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
