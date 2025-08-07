# Shadow80

![shadow80](https://imgur.com/XLjjdMzh.jpg)
An 80%/TenKeyLess sized keyboard with 74 RGB.
Before enabling the maximum brightness of RGB lights, please confirm whether the USB device power supply supports it.
This PCB has two versions: hotswap and solder.

* Keyboard Maintainer: [PixelSpace](https://github.com/PixelSpaceStudio)
* Hardware Supported: shadow80
* Hardware Availability: [PixelSpace](https://github.com/PixelSpaceStudio)

Make example for this keyboard (after setting up your build environment):

    make shadow80:default
       
Flashing example for this keyboard:

    make shadow80:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0)(always "ESC") in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` 
