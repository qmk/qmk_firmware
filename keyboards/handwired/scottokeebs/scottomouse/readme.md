# ScottoMouse

![ScottoMouse](https://i.imgur.com/yjnhyXWh.jpeg)

A 6-key macropad that utilizes [QMK mouse keys](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md) to emulate a mouse, case files available [here](https://github.com/joe-scotto/scottokeebs.git).

*   Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
*   Hardware Supported: Raspberry Pi Pico
*   Hardware Availability: [ScottoKeebs](https://scottokeebs.com), [Amazon](https://amazon.com), [Ali](https://amazon.com)

# Compiling

Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottomouse:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottomouse:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available