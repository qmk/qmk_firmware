# dj505/picofx

![PicoFX controller](https://i.imgur.com/YNsJPg0.png)

PicoFX: A compact keyboard-style controller for the *Pump It Up* rhythm game series. This firmware is intended for using the controller with the [Pump It Up Rise](https://store.steampowered.com/app/2756930/PUMP_IT_UP_RISE/) home version of the game.

* Hardware Supported: [PicoFX](https://github.com/dj505/PicoFX)
* Keyboard Maintainer: [jjc1138](https://github.com/jjc1138)

Make example for this keyboard (after setting up your build environment):

    make dj505/picofx:default

Flashing example for this keyboard:

    make dj505/picofx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Keymaps

There are three keymaps provided, or you can build your own using the instructions below.

 * [default](keymaps/default/readme.md)
 * [menumode](keymaps/menumode/readme.md)
 * [allinone](keymaps/allinone/readme.md)

### Bootloader

Put the controller in bootloader mode in one of three ways:

* **Physical reset button**: Hold down the BOOTSEL button on the microcontroller when connecting the USB cable.
* **Bootmagic reset**: If a version of this firmware is already installed, hold down the top-left button on the keyboard when connecting the USB cable.
* **Keycode in keymap**: If a version of this firmware is already installed with the 'menumode' or 'allinone' keymap, hold down the Service button and press the Test button. Or press a button mapped to `QK_BOOT` in your own keymap.
