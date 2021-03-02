# 0xCB 1337

### Macro Keypad

https://github.com/conor-burns/0xcb-1337(https://github.com/conor-burns/0xcb-1337)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Conor Burns](https://github.com/conor-burns)
* Hardware Supported: see github repo
* Hardware Availability: Soon on tindie or order your own parts - the hardware in the repo is Open Source :D

To go to bootloader press row 0 col 0 key (top left) while plugging in the board.

Env:
    export LTO=Y
    export CONFIG_USB_ACM=y
    qmk config user.keyboard=0xcb/1337
    qmk config user.keymap=default
    
Compile example:

    qmk compile

Flashing example for this keyboard:

    qmk flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
