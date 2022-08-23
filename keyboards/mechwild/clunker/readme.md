# Clunker

![clunker](https://i.imgur.com/6X5ijDoh.jpg)

The Clunker is a 40% DIY kit with a knob and solenoid.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: Clunker v1.3
* Hardware Availability: [Clunker on MechWild](https://mechwild.com/product/clunker/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/clunker:default

Flashing example for this keyboard:

    make mechwild/clunker:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the top of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available