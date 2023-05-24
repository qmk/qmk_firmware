# The Kudox Full keyboard

![Kudox logo](https://raw.githubusercontent.com/kumaokobo/kudox-keyboard/master/img/kudox.png)

![Kudox Full image2](https://raw.githubusercontent.com/kumaokobo/kudox-keyboard/master/img/kudox-full-image2.jpg) | ![Kudox Full image1](https://raw.githubusercontent.com/kumaokobo/kudox-keyboard/master/img/kudox-full-image1.jpg)
:----:|:-----:
 front | angle

- Keyboard Maintainer: [Kumao Kobo](https://github.com/kumaokobo)
- Hardware Supported: Kudox Full PCB rev1.0 w/ Pro Micro
- Assembly guide: [Kudox Full/README](https://github.com/kumaokobo/kudox-keyboard/blob/master/kudox-full/README.md)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

## Building Firmware

Make example for this keyboard (after setting up your build environment):

    make kudox_full/rev1:default


Flashing example for this keyboard:

    make kudox_full/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
