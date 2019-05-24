# EllipseRev1

![EllipseRev1](http://abstractkb.tk/wp-content/uploads/2019/03/ellipsetop.jpg)

A small keypad with more knobs than ever before!  3 Knobs and 3 MX-style switches on one little board.

At this time there are 2 small known issues with the Rev 1.  One of which is that backlight breathing does not work,
and the other issue that has been encountered is that the post_init_user function does not seem to be called.
Hopefully these issues can be resolved soon; this QMK file is being released as orders have started to ship and they need to be configurable.

Keyboard Maintainer: [AbstractKB](https://github.com/abstractkb)  
Hardware Supported: The Abstract Ellipse Rev1  
Hardware Availability: https://abstractkb.tk

Make example for this keyboard (after setting up your build environment):

    make abstract/ellipse/rev1:default:dfu

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
