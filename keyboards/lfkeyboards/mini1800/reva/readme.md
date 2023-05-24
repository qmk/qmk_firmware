# Mini1800 RevA

* Keyboard Maintainer: [LFKeyboards](https://github.com/lfkeyboards)
* Hardware Supported: Mini1800 RevA (Green PCB with AT90USB1286)
* Hardware Availability: [LFKeyboards.com](https://www.lfkeyboards.com/)

Make example for this keyboard (after setting up your build environment):

    make lfkeyboards/mini1800/reva:default

Flashing example for this keyboard:

    make lfkeyboards/mini1800/reva:default:flash

## Bootloader

To reset the board into bootloader mode, do one of the following:

* **Physical reset button**: Briefly press the button on the bottom of the PCB (between Q and W keys)
* **Keycode in keymap**: Press the key mapped to `RESET` if it is available (`Fn`+`Right Shift`, then tap `Enter` by default)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
