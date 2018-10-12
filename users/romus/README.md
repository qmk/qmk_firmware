# Overview

 This is a modified version of Let's Split keyboard from bbaserdem. I don't like standard Dvorak overuses right pinky
 so I shifted the columns out. I'm not sure if this is any good, time will tell.

 I have ortholinear Let's Split Eh, which share a lot of functions with other ortholinear keyboards.

# Layout

I use DVORAK with an unorthodox off layout.
If you wanna grab my code, and you used a layout with a persistent base
layer change, change it to layer 0 before proceeding.

# Layers

* **Dvorak**: Base layer,with dvorak layout.
* **Alternative**: Has alternate characters.
* **Game**: Toggled from *Function*, comfortable for gaming use.
* **Numeric**: Has numericals and symbols. Can be locked.
* **Function**: Layer has media and function keys.
* **Mouse**: Manipulates mouse. Can be locked.
* **Music** Allows playing sounds.

# Functionality

* **RGB Backlight**: With layer indication, and ability to change base layer lighting mode.
* **Secrets**: By placing a secrets.h, and not tracking it, passwords can be stored.
* **Mouse**: Mouse emulation, complete with diagonal keys.
* **Turkish**: An AltGr-like overlay that allows some non-common letters, in unicode.

I suggest checking out how I enabled Turkish keys,
how I planned out RGB lighting,
and my mouse implementation;
they might offer some insight into fringe user cases.

# Issues

All features are too big for the 32kB bootloader.
Offenders are audio and rgb lights; it comes down to one or the other.

~The Proton board, and rev 6 might fix that.~

# Credits

This is a modified version of Let's Split keyboard from bbaserdem who has previously written his keymap by himself before, but rewrote it here.
