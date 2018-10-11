# Overview
I have mostly ortholinear keyboards, which share a lot of functions.
For this purpose, I collected them here.

I have the following keymaps:

* Gherkin (Does not use the user space)
* XD75RE (Does not use the user space)
* Bigseries (Does not use the user space)
* Let's Split
* Let's Split Eh
* Planck

# Layout
I like using DVORAK, and meaning to teach myself turkish F.
My small keyboards are set so that they are in qwerty mode, but the letters
are arranged in a dvorak fashion.
I map caps-lock to keymap switching on software (linux) level, so to do F, I
use my XD75RE.

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

I suggest checking out how I set up unicode keys, RGB lighting, and mouse 
emulation. Should you want some inspiration.

# Issues

All features are too big for the 32kB bootloader.
Offenders are audio and rgb lights; it comes down to one or the other.
~The Proton board, and rev 6 might fix that.~
