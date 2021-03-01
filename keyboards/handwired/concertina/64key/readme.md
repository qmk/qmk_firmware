# Concertina 64-key

![Concertina 64-key](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/handwired/concertina/64key/concertina-1-side-view.jpg)

A diploid, concave, columnar keyboard.

This folder represents the keyboard configuration identified as
`concertina_64key` in the DMOTE application’s list of GNU make targets, as of
version 0.7.0 of that application. The QMK code is fully compatible back to
version 0.6.0, which introduced the Concertina.

The default keymap for this layout has a QWERTY base layer but is intended for
running Colemak on the OS side. It has a separate key layer that forces Colemak
from the QMK side in case the keyboard has to be used with a computer that does
not run Colemak.

A full set of printable caps to match the keymap is available in the
`dmote-keycap` application, [here](https://github.com/veikman/dmote-keycap).

* Keyboard Maintainer: [Viktor Eikman](https://github.com/veikman)
* Hardware Supported: Concertina 64-key case, Pro Micro (ATmega32U4)
* Hardware Availability: [viktor.eikman.se](https://viktor.eikman.se/article/the-concertina/)

Make example for this keyboard (after setting up your build environment):

    make handwired/concertina/64key:default

Flashing example for this keyboard:

    make handwired/concertina/64key:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
