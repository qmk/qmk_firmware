# unicomp/spacesaver_m_post_2013/overnumpad_1xb

![unicomp/spacesaver_m_post_2013/overnumpad_1xb](https://www.pckeyboard.com/mm5/graphics/00000001/UB4ZPHA_800x343.jpg)

Initially will support part number U242S6A, remains to be seen how compatible it is with other part numbers.

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: OverNumpad controller v1.Xb
* Hardware Availability: TODO
  * [controller](https://github.com/purdeaandrei/overnumpad_controller_1xb)
  * [keyboard](https://www.pckeyboard.com/)

To place the keyboard into bootloader mode in order to flash it, hold the ESC key while plugging the board in.
It's possible to make this feature not work, by flashing the wrong firmware onto the keyboard.
If that happens, open up the keyboard, and press the RST&PROG button to enter bootloader mode.

Make example for this keyboard (after setting up your build environment):

    make unicomp/spacesaver_m_post_2013/overnumpad_1xb:default

Flashing example for this keyboard:

    make unicomp/spacesaver_m_post_2013/overnumpad_1xb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
