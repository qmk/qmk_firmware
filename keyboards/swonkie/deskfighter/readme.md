# DeskFighter

![DeskFighter](https://raw.githubusercontent.com/Swonkie/DeskFighter/refs/heads/main/DeskFighter.jpg)

I designed this keyboard for my own personal use and documented the whole design and build process here:
https://haldimann.app/DeskFighter/

The idea is not so much that someone builds the exact same thing (of course that's possible), but customize it to their own preferences. The availability of all required files should make this relatively straightforward. But there's 3D printing and soldering involved as well as some other skills. It's best to read the article linked above to get an idea.

You can find the design and production files here:
https://github.com/Swonkie/DeskFighter

- Keyboard Maintainer: [Swonkie](https://github.com/Swonkie)
- Hardware Supported: Custom PCB, designed for STM32G431, STM32G491 or others (pin compatible) in LQFP48 package, but can be swapped for any other microcontroller that works with QMK.
- Hardware Availability: DIY, see link above.

Make example for this keyboard (after setting up your build environment):

    make swonkie/deskfighter:default

Flashing example for this keyboard:

    make swonkie/deskfighter:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

When flashing for the first time, the microcontroller contains no QMK firmware, just the factory bootloader, so you have to use the button on the underside:

1. Unplug the keyboard.
2. On the underside of the keyboard: hold down the `Bootloader` button while plugging it in.
3. When the red USB power LED lights up, wait at least a second, then let go of the button.

Once the default keymap is flashed, you can press `fn` + `esc` to enter the bootloader.

If the keyboard is in the bootloader, but you want to get it out of the bootloader without flashing, simply unplug and plug it in again.
