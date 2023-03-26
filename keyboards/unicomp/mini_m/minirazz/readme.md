# unicomp/mini_m/minirazz

![unicomp/mini_m/minirazz](https://i.imgur.com/JFXIz4O.jpeg)

Supports the Unicomp Mini M keyboard, with the "MiniRazz" open hardware replacement controller.

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: Unicomp Mini M Keyboard + MiniRazz controller
* Hardware Availability:
  * [controller](https://github.com/purdeaandrei/MiniRazz)
  * [keyboard](https://www.pckeyboard.com/)

To place the keyboard into bootloader mode in order to flash it, hold the ESC key while plugging the board in.
It's possible to make this feature not work, by flashing the wrong firmware onto the keyboard.
If that happens, open up the keyboard, and hold the pushbutton on the controller while plugging in the keyboard.

Make example for this keyboard (after setting up your build environment):

    make unicomp/mini_m/minirazz:default

Flashing example for this keyboard:

    make unicomp/mini_m/minirazz:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
