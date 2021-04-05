# Splitty

![Splitty](http://ni.fr.eu.org/~nico/qmk/splitty/splitty_for_scale.jpg)

![Bottom view](http://ni.fr.eu.org/~nico/qmk/splitty/bottom_view.jpg)

![Side view](http://ni.fr.eu.org/~nico/qmk/splitty/stack_view.jpg)

![PCB](http://ni.fr.eu.org/~nico/qmk/splitty/splitty.png)

This is a split ergonomic keyboard initially based on the Ergodox layout
without the thumb cluster. It uses 32 keys per sides with Cherry MX
compatibles switches, thirty 1u and two vertical 1.5u caps.

The controller is integrated in order to make the keyboard as slim as possible.

It connects to the computer using a micro-B USB. Both sides are connected
together also using micro-B USB. Any connection mistake should not break
anything and the keyboard supports hot plugging.

* Keyboard Maintainer: [Nicolas Schodet](https://github.com/schodet)
* Hardware Supported: Splitty
* Hardware Availability: [Splitty](https://git.ni.fr.eu.org/splitty.git/about/)

Make example for this keyboard (after setting up your build environment):

    make splitty:default

Flashing example for this keyboard:

    make splitty:default:flash

Handedness should be programmed in EEPROM once, you can use these commands to
flash the firmware and the EEPROM:

    make splitty:default:dfu-split-left
    make splitty:default:dfu-split-right

If you do not have a reset keycode in your keymap, press the reset button or
short the corresponding contacts if not populated to enter bootloader.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
