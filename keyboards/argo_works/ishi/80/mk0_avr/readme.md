# Ishi 80 Mk 0

![argo_works/ishi/80/mk0_avr](https://i.imgur.com/TVn6zeqh.jpeg)

Ishi 80 is a 60% keyboard with a SouthPaw, Mirrored Numpad. 

Note: This firmware is for ATMega32U4 based daughterboards with the standard Pro-Micro footprint. It does not support the Encoder and OLED display functionality.

* Keyboard Maintainer: [Jason Devadoss](https://github.com/jasonj2232)
* Hardware Supported: Ishi80 Mk 0 with standard Pro Micro footprint daughterboards
* Hardware Availability: -

Make example for this keyboard (after setting up your build environment):

    make argo_works/ishi/80/mk0_avr:default

Flashing example for this keyboard:

    make argo_works/ishi/80/mk0_avr:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
