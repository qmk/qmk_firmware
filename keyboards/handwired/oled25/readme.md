# oled25

![oled25](https://i.imgur.com/b3ODB4gh.jpg)

A small numberpad/macropad 5x5 sized, with an OLED display.

* Keyboard Maintainer: [Antoni Małecki](https://github.com/asdfire1)
* Hardware Supported: Handwired, Arduino Pro Micro (type C), 3D printed case, SSD1306 128x32 OLED
* Hardware Availability: [Files for printing the case](https://www.printables.com/model/382329-oled25-5x5-macropad-numpad-with-oled-display)

Make example for this keyboard (after setting up your build environment):

    make handwired/oled25:default

Flashing example for this keyboard:

    make handwired/oled25:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset**: Short the reset pad on the Arduino
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
