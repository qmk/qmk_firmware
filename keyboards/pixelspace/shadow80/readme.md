# Shadow80

A 80% layout keyboard with 74 RGB.
We suggest that the default brightness limit of RGB is 210, Because the power may exceed the load capacity of USB.
(If you have a USB supply that supports external power, you can ignore this suggestion.)

This PCB about two versions ： hotswap and  solder.

* Keyboard Maintainer: [PixelSpace](https://github.com/PixelSpaceStudio)
* Hardware Supported: shadow80
* Hardware Availability: [PixelSpace](https://github.com/PixelSpaceStudio)

Make example for this keyboard (after setting up your build environment):

    make pixelspace/shadow80:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` 
