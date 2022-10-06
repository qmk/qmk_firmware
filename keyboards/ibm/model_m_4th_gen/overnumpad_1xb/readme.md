# ibm/model_m_4th_gen/overnumpad_1xb

![ibm/model_m_4th_gen/overnumpad_1xb](https://deskthority.net/wiki/images/thumb/1/11/IBM_Model_M_1391406_--_top.jpg/499px-IBM_Model_M_1391406_--_top.jpg)

This firmware is intended to support 4th generation IBM Model M keyboards (the ones that have their controllers under the locklights header).
* Confirmed to be working with:
  * PN: 1391412 Date: 20-03-97 Made in United Kingdom by IBM United Kingdom Limited, Greenock, Scotland, UK

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: OverNumpad controller v1.Xb
* Hardware Availability:
  * [controller](https://github.com/purdeaandrei/overnumpad_controller_1xb)

To place the keyboard into bootloader mode in order to flash it, hold the ESC key while plugging the board in.
It's possible to make this feature not work, by flashing the wrong firmware onto the keyboard.
If that happens, open up the keyboard, and press the RST&PROG button to enter bootloader mode.

Make example for this keyboard (after setting up your build environment):

    make ibm/model_m_4th_gen/overnumpad_1xb:default

Flashing example for this keyboard:

    make ibm/model_m_4th_gen/overnumpad_1xb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
