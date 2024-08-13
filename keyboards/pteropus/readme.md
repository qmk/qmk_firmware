# pteropus keyboard

![pteropus](https://i.imgur.com/5AACuSXh.jpg)

Another Miryoku inspired 36-key non-split keyboard

* Keyboard Maintainer: [hulahermit](https://github.com/hulahermit)
* Hardware Supported: Embeded type-c connector with STM32F072 microcontroller
* Hardware Availability: [pteropus](https://github.com/hulahermit/pteropus_keyboard)

Make example for this keyboard (after setting up your build environment):

    make pteropus:default
    make pteropus:manna-harbour_miryoku

Flashing example for this keyboard:

    make pteropus:default:flash
    make pteropus:manna-harbour_miryoku:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Bootmagic reset**: Hold down the top-left key and plug in the keyboard.
* **Physical reset**: Hold the `BOOT` button down, then press the `RESET` button. Alternately, plug the keyboard in while holding down the `BOOT` button.
  The `BOOT` button can be released after a few seconds.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymap, but you may assign this key in any keymaps you create.
