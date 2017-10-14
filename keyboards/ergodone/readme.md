ErgoDone
========

![ErgoDone](https://i.imgur.com/QERsQGQ.jpg)

The ErgoDone is a modified version of the ErgoDox, made by K.T.E.C., with pre-soldered components. It has different wiring and uses a SparkFun Pro Micro instead of Teensy.

- Keyboard maintainer: [Yu He](http://github.com/yuhe00)
- Hardware supported: 
    - ErgoDone v1.3 (tested)
- Hardware availability:
    - [AliExpress](https://www.aliexpress.com/store/product/ergodone-Custom-Mechanical-Keyboard-TKG-TOOLS-PCB-programmed-Ergonomic-Keyboard-Kit-similar-with-infinity-ergodox/3034003_32830050940.html)
    - [KBDfans](https://kbdfans.myshopify.com/collections/pcb/products/ergodone-keyboard-pcb-1pcs-free-shipping)

# Building the firmware

[Install the build tools.](https://docs.qmk.fm/getting_started_build_tools.html)

In the root directory of the repository, build the firmware with a command like:

    make ergodone:default

For more information on the layout option and other ones, see the [`make` guide](https://docs.qmk.fm/getting_started_make_guide.html).

# Flashing the firmware onto the keyboard

The ErgoDone uses a customized HID bootloader rather than the Teensy one. It doesn't need an OS driver, and the required actions before flashing are a little different than with an ErgoDox.

1. To enter flash mode, disconnect the keyboard first. Then, on the left-hand device, in the top row, press and hold the two rightmost keys while reconnecting the keyboard.
![Ergodone Flash Mode](https://i.imgur.com/sNivAnr.jpg)
2. To flash the .hex file, use the `hid_bootloader_cli` utlity from the [TKG Toolkit](https://github.com/kairyu/tkg-toolkit) (as of 2017-10-03, only [this old version](https://github.com/kairyu/tkg-toolkit/blob/b14c67ca8bc84c07e5fc6b2e01ae4002b808243a/windows/bin/hid_bootloader_cli.exe) works under Windows):

       hid_bootloader_cli -mmcu=atmega32u4 ergodone_default.hex
