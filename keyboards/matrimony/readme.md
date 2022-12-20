# Matrimony

* Keyboard Maintainer: [Joshua Cheung](https://github.com/hypanim)
* Hardware Supported: Elite-C
* Hardware Availability: https://www.reddit.com/r/mechmarket/comments/w1ytmc/gb_matrimony_split_keyboard/?utm_source=share&utm_medium=web2x&context=3

Both sides of the split keyboard are flashed with the same firmware. Make sure to set the eeprom of each side to their respective left/right configuration using QMK toolbox before flashing.

Enter the bootloader in one of 2 ways:

Bootmagic reset: For the left side, hold down the top-left key and plug in the keyboard. For the right side, hold down the top right key and plug in the keyboard.
Physical reset button: Briefly press the button on the Elite-C
```
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
