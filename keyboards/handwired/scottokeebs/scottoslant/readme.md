# ScottoSlant

![ScottoSlant](https://i.imgur.com/p10NGimh.jpg)

A 37-key handwired 0.25u row-staggered keyboard with a 2u spacebar. Case files available [here](https://github.com/joe-scotto/scottokeebs).

* Keyboard Maintainer: [Joe Scotto](https://github.com/joe-scotto)
* Hardware Supported: ATmega32U4
* Hardware Availability: [Amazon](https://amazon.com)


Make example for this keyboard (after setting up your build environment):

    make handwired/scottokeebs/scottoslant:default

Flashing example for this keyboard:

    make handwired/scottokeebs/scottoslant:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available