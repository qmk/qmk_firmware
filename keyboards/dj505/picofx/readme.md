# dj505/picofx

![PicoFX controller](https://i.imgur.com/YNsJPg0.png)

PicoFX: A compact keyboard-style controller for the *Pump It Up* rhythm game series. This firmware is intended for using the controller with the [Pump It Up Rise](https://store.steampowered.com/app/2756930/PUMP_IT_UP_RISE/) home version of the game.

* Hardware Supported: [PicoFX](https://github.com/dj505/PicoFX) by dj505
* Keyboard Maintainer: [jjc1138](https://github.com/jjc1138)

## Keymaps

There are three keymaps provided, or you can build your own using the instructions below.

 * [default](keymaps/default/readme.md)
 * [menumode](keymaps/menumode/readme.md)
 * [allinone](keymaps/allinone/readme.md)

## Installation

### Build the firmware file

You can build the firmware by:

* Using the [QMK Configurator](https://config.qmk.fm/#/dj505/picofx/LAYOUT) with either the default keymap or your own keymap created using its visual configuration tool.

* Compiling it yourself. Start with the [Complete Newbs Guide](https://docs.qmk.fm/#/newbs) if you're brand new to QMK, follow the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools), and then run something like:

    make dj505/picofx:allinone

### Bootloader

Put the controller in bootloader mode in one of three ways:

* **Physical reset button**: Hold down the BOOTSEL button on the microcontroller when connecting the USB cable.
* **Bootmagic reset**: If a version of this firmware is already installed, hold down the Service button when connecting the USB cable.
* **Keycode in keymap**: If a version of this firmware is already installed with the 'menumode' or 'allinone' keymap, hold down the Service button and press the Test button. Or press a button mapped to `QK_BOOT` in your own keymap.

### Flashing

Copy the .uf2 firmware file to the RPI-RP2 drive that appeared on your computer when you connected the controller in bootloader mode, or use a command like this to do that automatically if you've compiled the firmware yourself:

    make dj505/picofx:allinone:flash
