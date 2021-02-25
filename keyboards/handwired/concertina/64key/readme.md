The `64key` layout
==================

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
