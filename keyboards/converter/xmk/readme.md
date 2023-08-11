# converter/xmk

`converter/xmk` is the QMK keyboard definition for [𝑥MK](https://github.com/manna-harbour/xmk).

* Keyboard Maintainer: [Manna Harbour](https://github.com/manna-harbour)
* Hardware Supported: Any QMK-compatible MCU board
* Hardware Availability: No additional hardware required

Make example for this keyboard (after setting up your build environment):

    make converter/xmk:default

Flashing example for this keyboard:

    make converter/xmk:default:flash

To flash pre-compiled firmware to a pro-micro on Linux without using the `qmk` CLI:

    avrdude -p atmega32u4 -c avr109 -U flash:w:converter_xmk_default.hex:i -P /dev/ttyACM0

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 4 ways:

* **Boot shell command**: Give the `boot` command to the `converter/xmk` shell, e.g. `echo "boot" > /dev/ttyACM0`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
