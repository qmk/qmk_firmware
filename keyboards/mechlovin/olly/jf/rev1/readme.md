# Mechlovin Olly JF Rev. 1

![jf](https://i.imgur.com/IrfTGE7h.png)

Olly JF PCB, compatible Duck Jetfire keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://mechlovin.studio/)
* Hardware Supported: Jetfire Korean Kustom
* Hardware Availability: [Mechlovin' Studio](https://mechlovin.studio/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/olly/jf/rev1:default

Flashing example for this keyboard:

    make mechlovin/olly/jf/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

By keycode: Press the key mapped to `QK_BOOT` if it is available.
By Bootloader: hold ESC key while plugging in (jump to bootloader)
By Bootmagic: hold Insert key while pluging in (jump to bootloader and reset EEPROM)