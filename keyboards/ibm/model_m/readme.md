# Model M

A custom IBM Model M compatible keyboard controller using QMK firmware. Uses two MCP23S17 SPI port expanders to scan the 8x16 key matrix, with standard Model M connector pinout compatibility.

* Keyboard Maintainer: [Richard George](https://github.com/rgeorge1926-oss)
* Hardware Supported: Model-C PCB with ATmega32U4 (Arduino Pro Micro) and two MCP23S17 port expanders

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb ibm/model_m -km default

Flashing example for this keyboard:

    qmk flash -kb ibm/model_m -km default

## Bootloader

* **Bootloader reset**: Hold the key at matrix position (0,5) (Esc) and plug in the keyboard
* **Physical reset**: Briefly short the RST pin on the Pro Micro to GND

See the [build environment setup](https://docs.qmk.fm/#/newbs_getting_started) and the [make instructions](https://docs.qmk.fm/#/faq_build) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
