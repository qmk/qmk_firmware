# System76 Launch Configurable Keyboard

## Building Firmware

- Clone this repository and `cd` into the `qmk_firmware` directory.
- After cloning, run `make git-submodule` as well as `./util/qmk_install`, if required.
  - May also need to install dependencies: `sudo apt install avrdude gcc-avr avr-libc`
- To build the firmware without flashing the keyboard, use `make (keyboard name):(layout name)`
  - For example, to build the `default` layout for the Launch keyboard, run:

```bash
make -r system76/launch_1:default
```

## Flashing Firmware (DFU)

- To flash the firmware, you'll use the same build command, but with `dfu` added to the end:

```bash
make -r system76/launch_1:default:dfu
```

- After it builds, you will see a repeating message that says:

```console
dfu-programmer: no device present.
ERROR: Bootloader not found. Trying again in 5s.
```

Next, unplug your keyboard from your computer, hold the ESC key (while the keyboard is unplugged), and plug the keyboard back in while holding the ESC key. Once the keyboard is plugged in, the ESC key can be released.

> Note: On some distributions, `dfu-programmer` has trouble detecting the keyboard unless `make` is run through `sudo`.

## Flashing Firmware (ISP)

To flash the firmware using ISP, use USBasp device and a tag connect cable.

Build the firmware and bootloader with:

```bash
make -r system76/launch_1:default:production
```

Run `avrdude` to flash the fuses:

```bash
avrdude -c usbasp -p atmega32u4 -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xCB:m
```

Run `avrdude` to flash the ROM:

```bash
avrdude -c usbasp -p atmega32u4 -U flash:w:system76_launch_1_default_production.hex
```

## Making a Custom Layout

To create a custom layout, go to the `keymaps` directory and copy one of the maps in there. It will likely be easiest to start with the default layout, but the other layouts in there may be helpful references. The name of the directory created will be the name of the layout. To prevent build errors, it is recommended to use only lowercase letters, underscores, and numbers for the layout name.

Inside of each layout directory, there is a file called `keymap.c`. The commented-out grid area in this file is a visual reference for the actual key assignments below it. When modifying a layout, modifying this visual reference first makes it easier to design a layout, as well as keeping the actual layout below it organized.

Once the layout is designed, change the keycodes below to match the design. A full list of available keycodes can be found in the [QMK documentation](https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes). Use the shorter keycode alias to help keep these lined up (e.g. use `KC_ESC` instead of `KC_ESCAPE`).
