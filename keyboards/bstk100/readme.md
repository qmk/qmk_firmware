# bstk100

![bstk100](https://i.imgur.com/9s5kxSB.jpeg)
![bstk100](https://i.imgur.com/rsilkiy.jpeg)
![bstk100](https://i.imgur.com/TuQlxat.jpeg)
![bstk100](https://i.imgur.com/w0g6Qlz.jpeg)
![bstk100](https://i.imgur.com/ORgbBQh.jpeg)
![bstk100](https://i.imgur.com/1MDm3zt.png)

*A short description of the keyboard/project*

* Keyboard Maintainer: [FREE WING](https://github.com/FREEWING-JP/qmk_firmware)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

BUFFALO USB 10-Key keyboard BSTK100BK  
[https://amzn.to/389GGtP](https://amzn.to/389GGtP)

Pro Micro ATmega32U4 5V/16MHz  
[https://amzn.to/3jePZPi](https://amzn.to/3jePZPi)

Make example for this keyboard (after setting up your build environment):

    make bstk100:default

Flashing example for this keyboard:

    make bstk100:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
