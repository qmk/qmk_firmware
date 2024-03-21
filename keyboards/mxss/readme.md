# MxSS - Polycarb 65% Kit for MX/SMK

![MxSS - Polycarb 65% Kit for MX/SMK](https://i.imgur.com/WDTWcmU.jpg)

### Information:

 - Case: Frosted Polycarbonate, CNC milled
 - Plate: Brass, mirror-finished and electroplated
 - Weight: Same as plate
 - PCB: Custom designed for the MxSS by kawasaki161, White solder mask and ENIG finish

### Details:

 - 2.9 degrees angle on the case
 - Top mount plate
 - Center USB, Type-B Mini
 - MX and SMK (White and Orange) switch support
 - Holtite support
 - RGB underglow
 - 1.5kg with plate and weight

* Keyboard Maintainer: [MxBlue](https://github.com/mxblu)
* Hardware Supported: Custom PCB, ATMega32u4
* Hardware Availability: https://geekhack.org/index.php?topic=94986.0

Make example for this keyboard (after setting up your build environment):

    make mxss:default

Flashing example for this keyboard:

    make mxss:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
