# ScottoMacrodeck

![ScottoMacrodeck](https://imgur.com/KVJuIVNh.jpeg)

An 11-key macropad designed specifically for someone who games with a single thumb, however, it can be used as a traditional macropad. Case files available [here](https://github.com/joe-scotto/scottokeebs).

* Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
* Hardware Supported: ATmega32U4
* Hardware Availability: [Amazon](https://amazon.com)

# Compiling

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottomacrodeck:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottomacrodeck:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available