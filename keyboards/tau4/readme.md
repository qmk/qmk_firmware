# τ.4

![Tau.4](http://gaskell.tech/tau/images/tau4.jpg)

A 40% ortholinear keyboard, developed by Oliver Gaskell. More info on [gaskell.tech](https://gaskell.tech/tau/four.html)

* Keyboard Maintainer: [Oliver Gaskell](https://github.com/ogaskell)
* Hardware Supported: Tau4 PCB rev1.0, Tau4 PCB rev1.1
* Hardware Availability: Group Buy took place between 05 Feb 2021 to 05 Mar 2021. [More Details](https://gaskell.tech/tau/four.html)

Make example for this keyboard (after setting up your build environment):

    make tau4:default

Flashing example for this keyboard:

    make tau4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. (If you built with an encoder in the top left, the "key" will be that encoder.) This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Keycode in layout**: By default, `QK_BOOT` is assigned to the top right key on the `ADJUST` (fifth) layer.
