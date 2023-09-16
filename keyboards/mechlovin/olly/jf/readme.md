# Mechlovin Olly JF

![jf](https://i.imgur.com/IrfTGE7l.png)

Olly JF PCB, compatible Duck Jetfire keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://mechlovin.studio/)
* Hardware Supported: Jetfire Korean Kustom
* Hardware Availability: [Mechlovin' Studio](https://mechlovin.studio/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/olly/jf:default

Flashing example for this keyboard:

    make mechlovin/olly/jf:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

**Reset Key:** 3 ways to put the Olly JF into bootloader:
By keycode: Press the key mapped to `QK_BOOT` if it is available.
By Bootloader: hold ESC key while plugging in (jump to bootloader)
By Bootmagic: hold Insert key while pluging in (jump to bootloader and reset EEPROM)