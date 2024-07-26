# Ghost Squid Controller

This is the firmware for Rev. 20140518 of the Ghost Squid controller by [Bathroom Epiphanies](http://bathroomepiphanies.com/controllers/), a replacement controller for the [Cooler Master Quick Fire XT](https://www.coolermaster.com/catalog/peripheral/keyboards/quick-fire-xt/).

The code was adapted from the [BathroomEpiphanies QMK Firmware](https://github.com/BathroomEpiphanies/epiphanies_qmk_keyboard/tree/master/keyboards/ghost_squid_20140518).

* Keyboard Maintainer: QMK Community
* Hardware Supported: Ghost Squid
* Hardware Availability: [1upkeyboards](https://1upkeyboards.com/shop/controllers/qf-xt-ghost-squid-controller-2/)

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

104 key default layout:

    make bpiphany/ghost_squid:default

Flashing example for this keyboard:

    make bpiphany/ghost_squid:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
