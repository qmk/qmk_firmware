# DB63

A 65% keyboard hotswap with RGB that runs ps2avrgb natively, with USB C, RGB underglow and backlight.

* Keyboard Maintainer: QMK Community
* Hardware Supported: DB63 (ATmega32A)
* [Keyboard layout](http://www.keyboard-layout-editor.com/#/gists/dadea703fc8bfc87dc7c480de9f3ef38)

Make example for this keyboard (after setting up your build environment):

    make db/db63:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make db/db63:default:flash

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Escape* while plugging in the keyboard. (*All backlight LEDs will flash which indicate the board is in bootloader mode.*)

**Tips**: Another trick to enable the board in reset mode is using BootMapper Client->Options->Set Bootloader. (*This is only available for the first time, before flashing QMK Firmware.*)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
