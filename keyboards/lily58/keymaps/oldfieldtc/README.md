# Lily58 keyboard keymap

## Getting started
- [Set up the QMK environment](https://docs.qmk.fm/#/newbs_getting_started)
    - [Install QMK Toolbox](https://github.com/qmk/qmk_toolbox)
    - [Install QMK MSYS](https://github.com/qmk/qmk_distro_msys/releases/latest)
- Update `keymap.c` in `keyboards/lily58/keymaps/oldfieldtc`.
- Set the following user configs
    - `qmk config user.keyboard=lily58/rev1`
    - `qmk config user.keymap=oldfieldtc`
- Run `qmk compile -kb lily58/rev1 -km oldfieldtc`
- Once compiled, open QMK Toolbox and open the `lily58_rev1_oldfieldtc.hex` file that is found at the root of the `qmk_firmware` directory.
- Disconnect one keyboard half and press the reset button on the half that is connected. A `Atmel DFU device connected (libusb0): Atmel Corp. ATmega32U4 (03EB:2FF4:0000)` notice should appear in the window.
- Press 'Flash' and the keyboard should be flashed.
- Disconnect that keyboard half and repeat the previous two steps with the other half.
- Connect both halves together and the keyboard should now be flashed with the new keymap.

## Default layer
![Default keymap layer](https://user-images.githubusercontent.com/9656588/195990181-0f33ef49-0010-482c-bea8-fa84190cdf58.jpg)

[Default layer - Keyboard layout editor](http://www.keyboard-layout-editor.com/#/gists/8ff6160c16e9b9ee7e104538bfad4a59)

## Lower layer
![Lower keymap layer](https://user-images.githubusercontent.com/9656588/195990663-cae90d7a-988c-4230-a52b-8c70e0289443.jpg)

[Lower layer - Keyboard layout editor](http://www.keyboard-layout-editor.com/#/gists/7d77cd87c53d5eded50530242b852c20)

## Raise layer
![Raise keymap layer](https://user-images.githubusercontent.com/9656588/195990956-7ff1b698-7f76-452a-ae12-c5de638563a8.jpg)

[Raise layer - Keyboard layout editor](http://www.keyboard-layout-editor.com/#/gists/c7a63881a13e339f1b5b847637677e5f)

## Adjust layer
![Adjust keymap layer](https://user-images.githubusercontent.com/9656588/195991198-a00247ed-4c24-4a7e-852e-46f61d80bf6f.jpg)

[Adjust layer - Keyboard layout editor](http://www.keyboard-layout-editor.com/#/gists/15a25bc84fa69a1b9f228574674728d3)

