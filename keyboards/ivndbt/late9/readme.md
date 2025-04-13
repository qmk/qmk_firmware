# LATE-9


The LATE-9 is a multi-tap input keyboard based on mobile phones from the late '90s. LATE-9 is intended as a dev board with 18 buttons and an OLED screen, made by through-hole components only. With this, you can experiment QMK OLED capabilities with very little expense.

![LATE-9](https://i.imgur.com/QXycTC3h.jpg "LATE-9 first proto")

* Keyboard maintainer: [ivndbt](https://github.com/ivndbt)
* Hardware supported: ProMicro, _Elite-C (not tested)_
* Hardware Availability: LATE-9 is open source, check the [project repository](https://github.com/ivndbt/late-9) for gerbers.

Make example for this keyboard (after setting up your build environment):

    make ivndbt/late9/rev1:default

Flashing example for this keyboard:

    make ivndbt/late9/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

When asked by the terminal, short with a metal wire the pins on the backside of the board highlighted as `RST` (one is the `RESET` and the other one is `GROUND`) to enter the bootloader and let the OS detects the device.\
After installing this firmware you can use Bootmagic to enter the bootloader while plugging in your LATE-9. By default it's the button on the upper-left of the keyboard.