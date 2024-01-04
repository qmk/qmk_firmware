# momoka_ergo

![momoka_ergo](https://github.com/StefanGrindelwald/TestDemo/blob/master/Momoka_ergo.jpg?raw=true)

The MOMOKA Ergo is a split keyboard that is based on the Ergodox standard layout. It has 35 keys and 11 RGB backlights on each part. The two parts of the keyboard is connected by a TRRS cable.

* Keyboard Maintainer: [StefanGrindelwald](https://github.com/StefanGrindelwald)
* Hardware Supported: momoka.co/ergo
* Hardware Availability: momoka.co/ergo

Bootloader:

With the default keymap, you can easily use FN+Shift+D to enter the bootloader in left side and FN+shift+K in right side. Or you can just use the microswitch in the PCB.

Make example for this keyboard (after setting up your build environment):

    make momoka_ergo:default

Flashing example for this keyboard(Note that you need flash the both side keyboard respectively):

For the left side:

    make momoka_ergo:default:dfu-split-left

For the right side:

    make momoka_ergo:default:dfu-split-right
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
