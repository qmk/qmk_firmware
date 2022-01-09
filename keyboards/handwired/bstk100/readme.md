# bstk100

BUFFALO USB 10-Key keyboard BSTK100 modification by Pro Micro and QMK firmware .  
see [[FREE WING HOME PAGE]](http://www.neko.ne.jp/~freewing/) for more detail .  

![bstk100](https://i.imgur.com/9s5kxSB.jpeg)
![bstk100](https://i.imgur.com/rsilkiy.jpeg)
![bstk100](https://i.imgur.com/TuQlxat.jpeg)
![bstk100](https://i.imgur.com/w0g6Qlz.jpeg)
![bstk100](https://i.imgur.com/ORgbBQh.jpeg)
![bstk100](https://i.imgur.com/1MDm3zt.png)

* Keyboard Maintainer: [FREE WING GitHub](https://github.com/FREEWING-JP/qmk_firmware)
* Hardware Supported: Pro Micro ATmega32U4 5V/16MHz
* Hardware Availability: [BUFFALO USB 10-Key keyboard BSTK100BK](https://amzn.to/389GGtP), [Pro Micro ATmega32U4 5V/16MHz](https://amzn.to/3jePZPi)

Make example for this keyboard (after setting up your build environment):

    make handwired/bstk100:default

Enable VIA feature in QMK

    make handwired/bstk100:via

Flashing example for this keyboard:

    make handwired/bstk100:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in one way:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
