# ScottoSplit

![ScottoSplit](https://i.imgur.com/u6rSzyHh.jpg)

A 36-key split column-staggered ortholinear keyboard that uses a single MCU and VGA cable to connect the halves. Case files available [here](https://github.com/joe-scotto/scottokeebs).

*   Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
*   Hardware Supported: ATmega32U4
*   Hardware Availability: [Amazon](https://amazon.com)

Make example for this keyboard (after setting up your build environment):

    make handwired/jscotto/scottosplit:default

Flashing example for this keyboard:

    make handwired/jscotto/scottosplit:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available