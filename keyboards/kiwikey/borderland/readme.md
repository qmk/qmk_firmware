# Borderland

![Borderland](https://i.imgur.com/3aMyUJb.jpg)

Another keyboard with well-known Arisu layout, comes with USB Type-C connection and Rotary Encoder. More information can be found at https://kiwikey.vn/borderland/

* Keyboard Maintainer: [KiwiKey](https://github.com/kiwikey)
* Hardware Supported: Borderland PCB rev1
* Hardware Availability: [KiwiKey Website](https://kiwikey.vn/)

Make example for this keyboard (after setting up your build environment):

    make kiwikey/borderland:default

Flashing example for this keyboard:

    make kiwikey/borderland:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET`, in default keymap it is `Fn+R`
