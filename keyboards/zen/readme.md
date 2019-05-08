# Zen Keyboard

A split ergo keyboard with a few goals in mind:

- Be as thin as possible. Other split KBs (Let's Split, Nyquist, Iris) are 15.2mm thick. The Zen rev2 is only 13.2mm thick *including switches and caps* when using Kailh Choc low-profile switches, and 22.1mm using standard MX switches and DSA keycaps.
- Layout designed for gaming. 1.5u pinky keys, ortho alphas, and angled thumb keys. After trying Ortholinear, Atreus62, and Ergodox, this is the best layout for gaming and typing.
- Per-key RGB lighting. 34 WS2812b LEDs per side make it exceptionally bright
- Price. Using Arduino Pro Micro, SK6812 LEDs, and PCB FR4 for the case, the cost of each half without switches or caps can be reduced to under $20 when purchased at volume.
- Options. The Zen rev2 comes with rotary encoder support, SSD1306 OLED pinout, USB-C or TRRS interconnect, and jumpers to enable compatibility with the [QMK Proton-C](https://olkb.com/parts/qmk-proton-c) and the [Keeb.io Elite-C](https://keeb.io/products/elite-c-usb-c-pro-micro-replacement-arduino-compatible-atmega32u4)

Keyboard Maintainer: [Legonut](https://github.com/Legonut)
Hardware Supported: Zen rev1, Zen rev2
Hardware Availability: [RGBKB.net](https://www.rgbkb.net/)

A build guide and more info for this keyboard can be found here: [Zen Build Guide](https://rgbkb.gitbook.io/sol-build-guide/zygomorph-build-guide/untitled).

Make example for this keyboard (after setting up your build environment):

    make zen/rev2:default

To build for a Proton-C:

    make zen/rev2:default CTPC=yes

**Note:** The Proton-C does not have split keyboard, or encoder support. Also OLED driver support is untested. Will update as status changes.

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
