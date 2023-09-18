# converter/thinkpad_t6x/rpi_pico

![converter/thinkpad_t6x/rpi_pico](https://i.imgur.com/wUG9p6eh.jpeg)

This is a converter PCB for Lenovo Thinkpad keyboards from a wide range of models (T60, T61, X220, ...), based on the Raspberry Pi Pico. The QMK implementation here is specific to the converter in the link below. Similar PCB designs to convert a Thinkpad keyboard to USB exist, but they use a different microcontroller and wiring of the keyboard connector with the MCU.

* Keyboard Maintainer: [Michael Büchler](https://github.com/strobo5)
* Hardware Supported: The linked converter PCB with keyboards from various Thinkpad models
* Hardware Availability: [Custom PCB](https://github.com/strobo5/T61_PiPico_Scanner)

Make example for this keyboard (after setting up your build environment):

    make converter/thinkpad_t6x/rpi_pico:default

Flashing example for this keyboard:

    make converter/thinkpad_t6x/rpi_pico:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
