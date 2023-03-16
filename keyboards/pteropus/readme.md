# pteropus keyboard

![pteropus](https://i.imgur.com/5AACuSX.jpg)

Another Miryoku inspired 36-key non-split keyboard

* Keyboard Maintainer: [hulahermit](https://github.com/hulahermit)
* Hardware Supported: Embeded type-c connector with STM32F072 microcontroller
* Hardware Availability: [pteropus](https://github.com/hulahermit/pteropus_keyboard)

Make example for this keyboard (after setting up your build environment):

    make pteropus:default
    make pteropus:manna-harbour_miryoku         // for Miryoku layout

Flashing example for this keyboard:

    make pteropus:default:flash
    make pteropus:manna-harbour_miryoku:flash     // for Miryoku layout

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Physical reset and boot button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
