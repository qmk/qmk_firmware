# ATM 98 HUB

A 98-key wired mechanical keyboard with a rotary encoder, RGB matrix lighting and an indicator LED strip, based on the WB32FQ95 MCU.

* Keyboard Maintainer: [isuua](https://github.com/isuua)
* Hardware Supported: ATM 98 HUB
* Hardware Availability: https://github.com/isuua/

Make example for this keyboard (after setting up your build environment):

    make atm_98:default

Flashing example for this keyboard:

    make atm_98:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymap, but you may assign this key in any keymaps you create
