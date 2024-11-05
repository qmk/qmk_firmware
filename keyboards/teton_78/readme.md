# teton_78

![teton_78](https://imgur.com/IwQgOy3.jpg)

* This is my first keyboard design, and has a unique 68 xt layout. I hope you enjoy! 

* Keyboard Maintainer: [Bennett Balogh](https://github.com/AwesomeBalogh)
* Hardware Supported: *TAtmega34u4 mcu for teton_78's Hotswap and Solder PCBs*
* Hardware Availability: *N/A questions direct to Mountain Mech Designs discord: https://discord.gg/h9dMwRNfVy*

Make example for this keyboard (after setting up your build environment):

    make teton_78:default
    make teton_78:via

Flashing example for this keyboard:

    make teton_78:default:flash
    make teton_78:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
