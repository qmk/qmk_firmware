# Overview

I have mostly ortholinear keyboards, which share a lot of functions.
For this purpose, I collected them here.

I have the following keymaps:

* Gherkin (Does not use the user space)
* Let's Split
* Let's Split It Up
* Planck

# Layout

I use DVORAK with an unorthodox Turkish layout.
If you wanna grab my code, andused a previous layout with a persistent base
layer change, change it to layer 0 before proceeding.

# Layers

* **Dvorak**: Base layer,withdvorak layout.
* **Alternative**: Has alternate characters.
* **Game**: Toggled from *Function*, comfortable for gaming use.
* **Numeric**: Has numericals and symbols. Can be locked.
* **Function**: Layer has media and function keys.
* **Mouse**: Manipulates mouse. Can be locked.
* **Music** Allows playing sounds like a keyboard.

# Functionality

* **RGB Backlight**: With layer indication, and ability to change base layer lighting mode.
* **Secrets**: By placing a secrets.h, and not tracking it, you can store passwords etc.
* **Mouse**: Mouse emulation, complete with diagonal keys.
* **Turkish**: An AltGr-like overlay that allows some non-common letters, in unicode.

I suggest checking out how I enabled shifting for Turkish layer,
how I planned out RGB lighting, and my mouse implementation; they might offer
some insight into fringe user cases.

# Issues

All features are too big for the 32kB bootloader.
Offenders are audio and rgb lights; it comes down to one or the other.
~The Proton board, and rev 6 should fix that.~

# Credits

I have previously written my keymap by myself before, but I rewrote it here,
heavily inspired by @drashna's user folder.
