# converter/thinkpad_t6x/pico_t61

![converter/thinkpad_t6x/pico_t61](https://i.imgur.com/KDouWIc.jpeg)

This is a converter PCB for Lenovo Thinkpad keyboards from T60, T400 and X200 series, based on the Raspberry Pi Pico W. The QMK implementation here is specific to the converter in the link below. Similar PCB designs to convert a Thinkpad keyboard to USB exist, but they use a different microcontroller and wiring of the keyboard connector with the MCU.

* Keyboard Maintainer: [Al En](https://github.com/gitaen)
* Hardware Supported: The linked converter PCB with keyboards from various Thinkpad models
* Hardware Availability: [Custom PCB](https://github.com/thedalles77/USB_Laptop_Keyboard_Controller/tree/master/Example_Keyboards/Pico_T61_Keyboard)

Make example for this keyboard (after setting up your build environment):

    make converter/thinkpad_t6x/pico_t61:default

Flashing example for this keyboard:

    make converter/thinkpad_t6x/pico_t61:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (\`~) and plug in the keyboard
* **Physical BOOTSEL button**: Hold down the BOOTSEL button on the Raspberry PiPico W and plug the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
