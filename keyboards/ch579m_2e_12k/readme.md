# ch579m_2e_12k

A 12-key macropad with 2 rotary encoders, built on the WCH CH579M ARM Cortex-M0 MCU.

* Keyboard Maintainer: [Ryan McLean](https://github.com/ryanm101)
* Hardware Supported: Custom PCB, CH579M MCU
* Hardware Availability: [12 Key 2 Knob Mini Mechanical Keyboard](https://www.aliexpress.com/item/1005011856410871.html)

Make example for this keyboard (after setting up your build environment):

    make ch579m_2e_12k:default

Flashing example for this keyboard:

    make ch579m_2e_12k:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

To enter the bootloader:

* **Hold ENC1 at power-on**: Bootmagic lite — hold the left encoder button while plugging in
* **Hold ENC1 + press ENC2**: `QK_BOOT` keycode on layer 1
