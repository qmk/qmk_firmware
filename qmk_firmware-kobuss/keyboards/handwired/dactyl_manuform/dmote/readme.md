DMOTE
======

The “Dactyl-ManuForm: Opposable Thumb Edition” is made from a Clojure
application maintained [here](https://github.com/veikman/dactyl-keyboard).
The application supports varied physical layouts and therefore matrices.
This physical variability is its main feature; its QMK firmware is ordinary.

Consult the general [Dactyl-ManuForm readme](../readme.md).

## The `62key` layout

This folder represents the default build target of the Clojure application
as of its version 0.4.0. The default keymap for this layout has a QWERTY base
layer but is intended for running Colemak on the OS side with the i3 tiling
window manager. It’s also got a layer that forces Colemak from the QMK side.
