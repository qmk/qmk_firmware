# Scotto34

![Scotto34](https://i.imgur.com/BkpEBQjh.jpg)

A low-profile 34-key split monoblock ortholinear keyboard that uses 18x17mm spaced Choc switches and an exposed controller in the middle. Case files available [here](https://github.com/joe-scotto/scottokeebs).

* Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
* Hardware Supported: RP2040
* Hardware Availability: [Amazon](https://amazon.com)

# Compiling

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scotto34:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scotto34:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available