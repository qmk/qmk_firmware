# handwired/3dp660_oled

![handwired/3dp660_oled](https://i.imgur.com/AQ6VQfgh.jpg)

*A handwired FC660 layout with OLED display support.*

* Keyboard Maintainer: [xia0](https://github.com/xia0)
* Hardware Supported: ATmega32U4 e.g. Arduino Pro Micro or Teensy 2.0
  * Note: If using a Pro Micro, pins B0 and D5 are required. [Click for details](https://golem.hu/guide/pro-micro-upgrade/).
* Hardware Availability: [Printables](https://www.printables.com/model/464322-3dp-fc660-v3-oled-hand-wired-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make handwired/3dp660_oled:default

Flashing example for this keyboard:

    make handwired/3dp660_oled:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the MCU or short RST to GND.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
