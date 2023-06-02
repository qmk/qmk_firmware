# ScottoInvader

![ScottoInvader](https://i.imgur.com/rXssnx7h.jpeg)

A 36-key column-staggered ortholinear keyboard. Case files available [here](https://github.com/joe-scotto/scottokeebs).

* Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
* Hardware Supported: ATmega32U4
* Hardware Availability: [Amazon](https://amazon.com)

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottoinvader:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottoinvader:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available