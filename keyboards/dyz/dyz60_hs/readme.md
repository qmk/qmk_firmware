# dyz60_hs

![dyz60 pcb](https://i.imgur.com/l9z5KuJh.jpg)

60% layout has flexcut with multiple layout and mounting support.

* Keyboard Maintainer: [dayatz](https://github.com/dayatz)
* Hardware Supported: dyz60_hs, ATmega32U4
* Hardware Availability: Local Indonesia GB.

#### Enter Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Esc key and plug in the keyboard
* **Physical reset pins**: Briefly short the reset pins on the bottom of Space key


#### Flashing

Make example for this keyboard (after setting up your build environment):

    make dyz/dyz60_hs:default

Flashing example for this keyboard:

    make dyz/dyz60_hs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
