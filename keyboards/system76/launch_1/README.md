## Flashing firmware:
* Clone this repository and `cd` into the `qmk_firmware` directory.
* After cloning, you probably need to run `make git-submodule`.
   - You may also need to install dependencies: `sudo apt install avrdude gcc-avr avr-libc`
* To build the firmware without flashing the keyboard, use `make (keyboard name):(layout name)`
   - For example, if you want to build the `default` layout for the Launch keyboard, run:
```
make system76/launch_1:default
```
* To flash the firmware, you'll use the same build command, but with `dfu` added to the end:
```
make system76/launch_1:default:dfu
```
   - After it builds, you will see a repeating message that says:
```
dfu-programmer: no device present.
ERROR: Bootloader not found. Trying again in 5s.
```
Next, unplug your keyboard from your computer, hold the ESC key (while the keyboard is unplugged), and plug the keyboard back in while holding the ESC key. Once the keyboard is plugged in, the ESC key can be released.
* To flash the firmware using ISP, you will need a USBasp device, and a tag connect cable.
  - Build the firmware and bootloader with:
```
make system76/launch_1:default:production
```
  - Run avrdude to flash the fuses:
```
avrdude -c usbasp -p atmega32u4 -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xCB:m
```
  - Run avrdude to flash the ROM:
```
avrdude -c usbasp -p atmega32u4 -U flash:w:system76_launch_1_default_production.hex
```

## Making your own layout:
If you want to create your own layout, go to the `keymaps` directory and copy one of the maps in there. It will likely be easiest to start with the default layout, but the other layouts in there may be helpful references. The name of the directory you create will be the name of your layout. To prevent build errors, it is recommended to use only lowercase letters, underscores, and numbers for the name of your layout.

Inside of each layout directory, there is a file called `keymap.c`. The commented out grid area in this file is a visual reference for the actual key assignments below it. When modifying a layout, modifying this visual reference first makes it easier to design a layout, as well as keeping the actual layout below it organized.

Once your layout is designed, change the keycodes below to match your design. A full list of available keycodes can be found in the [QMK docs](https://beta.docs.qmk.fm/reference/keycodes). Use the shorter keycode alias to help keep these lined up (e.g. use `KC_ESC` instead of `KC_ESCAPE`).
