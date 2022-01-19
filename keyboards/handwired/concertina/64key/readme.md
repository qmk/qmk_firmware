# Concertina 64-key

A diploid, concave, columnar keyboard, with vertical finger clusters
beneath large horizontal thumb clusters.

![Side view](https://viktor.eikman.se/image/concertina-1-side-view/display)

## Hardware

* Keyboard maintainer: [Viktor Eikman](https://github.com/veikman)
* Hardware supported: Concertina 64-key case, Pro Micro (ATmega32U4)
* Hardware availability: [viktor.eikman.se](https://viktor.eikman.se/article/the-concertina/)

This QMK model represents the printable keyboard shape identified as
`concertina_64key` in the DMOTE application’s list of GNU make
targets, available [here](https://github.com/veikman/dactyl-keyboard),
as of version 0.7.0 of that application. The QMK code is fully
compatible back to version 0.6.0, which introduced the Concertina.

A full set of printable caps to match the keymap is available in the
`dmote-keycap` application,
[here](https://github.com/veikman/dmote-keycap).

## Firmware

Brand new to QMK? Start [here](https://docs.qmk.fm/#/newbs).

The default keymap for this layout has a QWERTY base layer (0) but is
intended for running Colemak on the OS side. It has a separate key
layer (1) that forces Colemak from the QMK side in case the keyboard
has to be used with a computer that does not run Colemak. Layer 2
flips the navigation clusters around. Layer 3 is numbers and mouse
control.

### Building from the CLI

See the general [build
environment](https://docs.qmk.fm/#/getting_started_build_tools) and
[make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
to get set up.

To build firmware for the Concertina without the `qmk` utility:

    make handwired/concertina/64key:default

To also flash a connected Concertina:

    make handwired/concertina/64key:default:flash
