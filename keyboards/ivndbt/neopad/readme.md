# Neopad

Neopad is a little macropad with four switches and two rotary encoders, made by through hole components only.
_Actually the number of switches is six, because even the encoder are allowed to click._

![Neopad](https://i.imgur.com/TgOkj2Fh.jpg "Neopad first proto")

The Neopad in the photo above is the first prototype. See the project repository for revision 1 update and KiCad files.

* Keyboard maintainer: [ivndbt](https://github.com/ivndbt)
* Hardware supported: ProMicro, _Elite-C (not tested)_
* Project repository: [Neopad on github](https://github.com/ivndbt/neopad)

Make example for this keyboard (after setting up your build environment):

    make ivndbt/neopad/rev1:default

Flashing example for this keyboard:

    make ivndbt/neopad/rev1:default:flash

When asked by the terminal, press the dedicated `RESET` button (the one above the 2 LEDs) to enter the bootloader and let the OS detects the device.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

