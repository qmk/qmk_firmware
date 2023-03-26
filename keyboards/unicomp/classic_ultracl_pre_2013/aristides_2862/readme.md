# unicomp/classic_ultracl_pre_2013/aristides_2862

![unicomp/classic_ultracl_pre_2013/aristides_2862](https://www.pckeyboard.com/mm5/graphics/00000001/UB4ZPHA_800x343.jpg)

Will support the following Unicomp Classic and Ultra Classic keyboards:
  * 104-key ANSI and 105-key ISO keyboards with pre-2013 bottom row are supported.

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: The "new" OEM controllers from Unicomp, called Aristides 2862.
* Hardware Availability:
  * [keyboard](https://www.pckeyboard.com/)

To place the keyboard into bootloader mode in order to flash it, hold the ESC key while plugging the board in.
It's possible to make this feature not work, by flashing the wrong firmware onto the keyboard.
If that happens, open up the keyboard, and hold the BOOTSEL button while plugging in the keyboard to enter bootloader mode.

Make example for this keyboard (after setting up your build environment):

    make unicomp/classic_ultracl_pre_2013/aristides_2862:default

Flashing example for this keyboard:

    make unicomp/classic_ultracl_pre_2013/aristides_2862:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
