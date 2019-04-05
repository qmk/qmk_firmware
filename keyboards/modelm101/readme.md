# modelm101

![IBM Model M 101 ANSI/102 ISO](https://i.imgur.com/DAE3W7g.jpg)

This is a configuration for the QMK firmware for reversible conversion of IBM's Model M keyboards (common 101-key ANSI and 102-key ISO models) from stock, power-hungry controller, to a modern one, running the USB bus.
Configuration is build for the Atmel AT90USB1286 controller, which you can easily use on the Teensy 2.0++ board (produced by PJRC).
Project is heavely based on 2 other projects:
1. Teensy 2.0++-based custom Model M controller running TMK firmware ('modelm" by [lmorchard](https://blog.lmorchard.com/2016/02/21/modelm-controller/)); - had a few issues.
2. Teensy 2.0++-based custom Model M 122-key controller running QMK firmware ("ibm122m" by [lukexorz](https://github.com/lukexorz)); - had wrong layout for 101/102-key boards and LED support.

Keyboard Maintainer: [iw0rm3r](https://github.com/iw0rm3r)  
Hardware Supported: Teensy 2.0++ board by PJRC  
Hardware Availability: https://www.pjrc.com/store/teensypp.html 

Make example for this keyboard (after setting up your build environment):

    make modelm101:default:teensy

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.