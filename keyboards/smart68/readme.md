# Smart 68

![Smart 68 V1 and V2](https://i.imgur.com/Ed2e083h.jpg)
![Smart 68 front shot](https://i.imgur.com/0NgcWqyh.jpg)

A 68% keyboard with hot-swappable switches & backlight LEDs, and a
front-mounted Fn key/bar using an Omron switch.

* Keyboard Maintainer: [Shados](https://github.com/Shados)
* Hardware Supported: Smart 68 PCB
* Hardware Availability: [A 2016 Geekhack group buy](https://web.archive.org/web/20180703134842/https://geekhack.org/index.php?topic=83442.0)

Make example for this keyboard (after setting up your build environment):

    make smart68:default

Flashing example for this keyboard:

    make smart68:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

You can enter the bootloader in three different ways:

1. **Bootmagic reset**: Hold down the key at (3,5) in the matrix (the 'B' key
   in qwerty layouts) and plug in the keyboard. This will also work if the
   board is still running its original TMK firmware.
2. **Physical reset button**: Briefly press the button on the back of the PCB.
   This will also work if the board is still running its original TMK firmware.
3. **Keycode in layout**: Press the key mapped to `QK_BOOT` (Fn + Backspace, in
   the default layout). This will *not* work if the board is still running its
   original TMK firmware.
