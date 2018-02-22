# Overview

I have mostly ortholinear keyboards, which share a lot of functions.
For this purpose, I collected them here.

I have the following keymaps:

* Gherkin (Does not use the user space)
* Let's Split
* Planck
* xd75re

# Functionality

* **Gaming**: A layer for gaming, which is usually meant for QWERTY.
* **RGB Backlight**: With layer indication, and ability to change base layer.
* **Secrets**: By placing a secrets.h, and not tracking it, you can store passwords etc.
* **Music**: On Planck, there is a dedicated layer for music. (All masked) Also have sound effect for some layers.
* **Mouse**: Mouse emulation, complete with diagonal keys.
* **Turkish**: An AltGr-like overlay that allows some non-common letters, in unicode.

I suggest checking out how I enabled shifting for Turkish layer,
how I planned out RGB lighting, and my mouse implementation; they might offer
some insight into fringe user cases.

# Issues

All features are too big for the 32kB bootloader, not good for planck.
Biggest culprid is audio and rgb lights. It seems it comes down to one or the other.

# Credits

I have previously written my keymap by myself before, but I rewrote it here,
following @drashna's user folder. Heavily influenced/copied from there.
