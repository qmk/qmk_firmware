# H75-RGB

75% PCB with LEDs lights used for Nyaong 75 keyboard. 

* Keyboard Maintainer: [hineybush](https://github.com/hineybush), [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: Hineybush H75_RGB
* Hardware Availability: Nyaong 75 GB

Make example for this keyboard (after setting up your build environment):

    make hineybush/h75_rgb:default

Flashing example for this keyboard:

    make hineybush/h75_rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
sssss
## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
