# i75

![i75](https://1.bp.blogspot.com/-eRSwPnvgliI/WCYQ-aYihoI/AAAAAAAB_Bc/a7i1Envc1FYiEHeqvyHw80VxTAnafDsPgCLcB/s320/IMG_20161003_084555.jpg)
===

5x15 grid layout, multiple controllers supported
- Pro Micro
- PJRC Teensy 2.0
- PJRC Teensy LC/3.2 (**NB: Not currently ported**)

The matrix is a 9x9 grid. This uses all of the available pins on the Pro Micro. The other controllers have pins left over. The serial pins and pins connected to LEDs were avoided if possible.

* [The original TMK firmware](https://github.com/di0ib/tmk_keyboard/tree/master/keyboard/i75_ProMicro)

Keyboard Maintainer: QMK Community  
Hardware Supported: i75 PCB  
Hardware Availability: [i75 project on 40% Keyboards](http://www.40percent.club/2016/11/i75.html)

Make example for this keyboard (after setting up your build environment):

    make 40percentclub/i75:default

If you would like to use one of the alternative controllers:

    make 40percentclub/i75/promicro:default
    make 40percentclub/i75/teensy2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
