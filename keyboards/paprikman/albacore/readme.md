# Albacore

*A small 7-key macropad featuring hotswap and per-key RGB*

![Albacore](https://github.com/paprikman/my_files/blob/master/albacore_macropad.jpg)

* Keyboard Maintainer: paprikman
* Hardware Supported: Albacore hotswap pcb
* Hardware Availability: Private group buy

Build and flash firmware (via support is considered by default):

    qmk flash -kb paprikman/albacore -km via

There are several ways to enter the bootloader:
* **Using keycode**: Press the `RESET` key (if mapped)
* **Bootmagic reset**: Hold the left bottom key (default mod key) and plug the usb cable
* **Physical reset**: In the top right corner of the bottom part of the pcb you will find two pads. Shorten them with tweezers and plug the usb cable, then release. It is also possible to shorten these pads while the macropad is already connected (shorten and hold for a couple of seconds, then release).