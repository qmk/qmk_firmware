## Flashing firmware:
* Clone this repository and `cd` into the `qmk_firmware` directory.
* After cloning, you probably need to run `make git-submodule`.
   - You may also need to install dependencies: `sudo apt install avrdude gcc-avr avr-libc`
* To build the firmware without flashing the keyboard, use `make (keyboard name):(layout name)`
   - For example, if you want to build the `default` layout for the Launch keyboard, run:
```
make system76/launch_beta_1:default
```
* To flash the firmware, you'll use the same build command, but with `dfu` added to the end:
```
make system76/launch_beta_1:default:dfu
```
   - After it builds, you will see a message that says `Detecting USB port, reset your controller now...`. You then want to hit the "RESET" key on the keyboard if it is programmed into the layout.
   - In the default layout, it is Fn+Esc. If a RESET key is not programmed into the layout, you will have to manually reset the controller.
* To flash the firmware using ISP, you will need a USBasp device, and a tag connect cable.
  - Build the firmware and bootloader with:
```
make system76/launch_beta_1:default:production
```
  - Run avrdude to flash the fuses:
```
avrdude -c usbasp -p atmega32u4 -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xCB:m
```
  - Run avrdude to flash the ROM:
```
avrdude -c usbasp -p atmega32u4 -U flash:w:system76_launch_beta_1_default_production.hex
```

## Making your own layout:
If you want to create your own layout, go to the `keymaps` directory and copy one of the maps in there. You'll probably want to start with the default layout, but the other layouts in there may be helpful references. The name of the directory you create will be the name of your layout. Ensure that it has no spaces or strange symbols, as this could lead to build errors.

Inside of each layout directory, there is a file called `keymap.c`, which is what you will be customizing to create your own keymap. The commented out grid area in this file is a reference for the actual key assignments below it. When I am modifying a layout, I first update this grid. It helps me keep track of where I want everything. It does not matter what you label the keys in this grid since it is in a comment. Just try to keep it understandable for yourself and everyone else.

The keycodes below that do have to be typed correctly. A full list of keycodes can be found here: https://beta.docs.qmk.fm/reference/keycodes .  Use the shorter keycode alias to help keep these lined up (e.g. use `KC_ESC` instead of `KC_ESCAPE`).
