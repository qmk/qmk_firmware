# handwired/tnx_corne_f401

![handwired/tnx_corne_f401](https://i.imgur.com/rHiwS60.jpeg)

*A handwired Corne keyboard using STM32 microcontrollers, with encoder support.*

* Keyboard Maintainer: [Assem Mohamed](https://github.com/ToYoNiX)
* Hardware Supported: STM32F401, STM32F411, or STM32F103 development boards with USB HID support
* Hardware Availability: Commonly available Blackpill F401 and Bluepill F103 boards, plus EC11 encoders and a TRRS cable

Make example for this keyboard (after setting up your build environment):

	make handwired/tnx_corne_f401:default

Flashing example for this keyboard:

	make handwired/tnx_corne_f401:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Double-press the reset button on the dev board to enter DFU mode
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
