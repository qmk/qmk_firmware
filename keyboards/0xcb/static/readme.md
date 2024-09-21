# 0xCB Static

Macro keypad

* Keyboard Maintainer: [Conor Burns](https://github.com/conor-burns)
* Hardware Supported: https://github.com/0xCB-dev/0xcb-static
* Hardware Availability: On CandyKeys or order your own parts - the hardware in the repo is Open Source :D
* PCB renders :)

![](https://github.com/0xCB-dev/0xcb-static/blob/main/PCB/rev1.0/top.png)

![](https://github.com/0xCB-dev/0xcb-static/blob/main/PCB/rev1.0/bottom.png)

More Pictures [here](https://0xcb.dev/static/)

To go to bootloader press ESC while plugging in or hold the RESET switch, then hold the BOOT switch, release RESET, release BOOT.
The board should now appear in lsusb (or device manager).

Make example for this keyboard (after setting up your build environment):

    make 0xcb/static:default

Flashing example for this keyboard:

    make 0xcb/static:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
