# troyle/macro_keys_dual

![troyle/macro_keys_dual](https://tom-royle.co.uk/images/troyle-macro-keyboard-v1.png)

A pretty simple macro keyboard that can use up to 2 rotary encoders

* Keyboard Maintainer: [Tom Royle](https://github.com/tom-royle)
* Hardware Supported: Sparkfun ProMicro in the troyle-macro-keyboard v1.0 PCB
* Hardware Availability: You will have to contact me some how :)

Make example for this keyboard (after setting up your build environment):

    make troyle/macro_keys_dual:default

Flashing example for this keyboard:

    make troyle/macro_keys_dual:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
