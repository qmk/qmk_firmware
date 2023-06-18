# unicomp/mini_m/justify_mike_smith

![unicomp/mini_m/justify_mike_smith](https://i.imgur.com/JFXIz4Oh.jpeg)

Supports the Unicomp Mini M keyboard, with the "Justify with Mike Smith" OEM controller.

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: Unicomp Mini M Keyboard + OEM Justify with Mike Smith controller
* Hardware Availability:
  * [keyboard](https://www.pckeyboard.com/)

To place the keyboard into bootloader mode in order to flash it, hold the ESC key while plugging the board in.
It's possible to make this feature not work, by flashing the wrong firmware onto the keyboard.
If that happens, open up the keyboard, and hold the pushbutton on the controller while plugging in the keyboard.

A couple features of this keyboard implementation:
* The QK_USER_0 keycode is defined as Scroll Lock, when pressed without modifiers, and Num Lock when pressed with shift.
  * You can disable this with `#define DISABLE_CUSTOM_NUMSLCK_KEYCODE` in your keymap's config.h
* Layer 1 is a special layer that is activated when the NumLock locklight is on. This is in order to support the embedded numpad.
  * You can disable this with `#define DISABLE_NUMPAD_LAYER` in your keymap's config.h
  * You can change the number of the activated layer by `#define NUMPAD_LAYER <number>` in your keymap's config.h

Make example for this keyboard (after setting up your build environment):

    make unicomp/mini_m/justify_mike_smith:default

Flashing example for this keyboard:

    make unicomp/mini_m/justify_mike_smith:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
