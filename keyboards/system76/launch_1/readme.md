# System76 Launch Configurable Keyboard (launch_1)

![System76 Launch Configurable Keyboard](https://images.prismic.io/system76/b71307ac-dae6-4863-b7ca-804cd61c7ef8_launch_overhead.png?auto=compress,format&w=750)

The Launch Configurable Keyboard is engineered to be comfortable, fully customizable, and make your workflow more efficient.

- High-speed USB Hub
- Works on Linux, Windows and macOS
- 100% Open Source
- Made in Colorado

Additional Launch Keyboard resources:

- Keyboard Maintainer: [System76](https://github.com/system76)
- Hardware Supported: [System76 Launch GitHub Repository](https://github.com/system76/launch)
- Hardware Availability: [Shop System76](https://system76.com/accessories/launch)

## Prerequisites

Refer to [build environment setup](https://beta.docs.qmk.fm/tutorial/newbs_getting_started) instructions.

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (i.e., Escape) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `RESET` if it is available
<!-- - **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead -->

## Building Firmware

Start with QMK's [Complete Newbs Guide](https://beta.docs.qmk.fm/tutorial/newbs).

In summary:

- Clone this repository and `cd` into the `qmk_firmware` directory.
- After cloning, run `make git-submodule` as well as `./util/qmk_install`, if required.
- May also need to install dependencies, for example in Debian-based systems: `sudo apt install avrdude gcc-avr avr-libc`
- To build the firmware without flashing the keyboard, use `make (keyboard name):(layout name)`; see the [`make` instructions](https://beta.docs.qmk.fm/developing-qmk/qmk-reference/getting_started_make_guide) for more details.
- For example, to build the `default` layout for the Launch keyboard using `make`, run:

```bash
make -r system76/launch_1:default
```

- Equivalently, using the QMK CLI:

```bash
qmk compile -kb system76/launch_1 -km default
```

## Flashing Firmware (DFU)

To flash the firmware, use the same build command, but with `dfu` added to the end:

```bash
make -r system76/launch_1:default:dfu
```

- After it builds, there will be repeating message that says:

```console
dfu-programmer: no device present.
ERROR: Bootloader not found. Trying again in 5s.
```

Next, unplug the keyboard from the machine, hold down the Escape key (while the keyboard is unplugged), and plug the keyboard back in while still holding the Escape key down. Once the keyboard is plugged in, the Escape key can be released.

> Note: On some distributions, `dfu-programmer` has trouble detecting the keyboard unless `make` is run through `sudo`.

## Flashing Firmware (ISP)

To flash the firmware using ISP, use a USBasp device and a tag connect cable.

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
