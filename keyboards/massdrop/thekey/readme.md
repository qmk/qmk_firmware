# The Key

![The Key](https://i.imgur.com/hL5cRj9.jpg)


The Stack Overflow "The Key" is a 3 button macropad based on atmega32u4 with Kailh Black Box switches.

> Some say a programmer’s best solution is a simple two-step process: copy and paste. On April 1st, 2021, Stack Overflow proved it. On that fateful day, each time users went to copy a piece of code, they were met with a pop-up for a fake product. It was called The Key: an ultra-compact macropad advertised as the new (and only) way to copy and paste on the platform. As it turns out, roughly one fourth of Stack Overflow’s 15 million users tries to copy and paste within five minutes of visiting the site. An even greater number saw the joke and loved it, with many demanding that The Key be developed in earnest. So, naturally, we teamed up with Stack Overflow to make it happen. What started as an April Fool’s gag is now a full-fledged macropad—designed by our very own community member Cassidy, with a portion of proceeds benefiting digitalundivided.

Keyboard Maintainer: [Drop / Massdrop](https://github.com/Massdrop/qmk_firmware) 

Hardware Supported: Massdrop, Inc. **The Key**

Hardware Availability: Limited Release - https://drop.com/buy/stack-overflow-the-key-macropad


Make example for this keyboard (after setting up your build environment):
```bash
# default provided by Drop / Stack Overflow
make massdrop/thekey:default
# common modification where C = CTRL+C, V = CTRL+V
make massdrop/thekey:url-copy-paste
```

Flashing example for this keyboard:
```bash
# install in dfu mode
make massdrop/thekey:default:dfu
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
Make example for this keyboard (after setting up your build environment):

## Bootloader

Enter the bootloader as follows:
* **Bootmagic reset**: Hold down the "Stack Overflow" key, the "left-most" or furthest from the USB plug while inserting the USB cable for a few seconds. The LEDs will **NOT** turn on.
* **Physical reset button**: Briefly press and hold the reset button while pluggin in the USB port. The LEDs on the back will **NOT** turn on. Depending on your case revision, you may have to remove the 4 screws on the back plate to access the switch OR you can use the associated access hole on newer releases.
