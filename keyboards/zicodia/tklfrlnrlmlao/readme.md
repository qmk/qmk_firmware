# TKLFRLNRLMLAO "LMAO"

![TKLFRLNRLMLAO "LMAO"](https://i.imgur.com/rmHpYEyh.jpeg)

A "totally normal" TKL.

This keyboard is a unique 40% keyboard, designed with form in mind over function. Purely designed to immitate the TKL layout in a small form factor.

What the name means:
- TKL = Ten-Key-Less
- FRL = Function-Row-Less
- NRL = Number-Row-Less
- ML = Modifier-less
- AO = Alpha-Only

Additionally, a WKL (Windows-Key-Less) option is available, which results in the variation WKLTKLFRLNRLMLAO "WLMAO"

* Keyboard Maintainer: [Zicodia](https://github.com/Zicodia)
* Hardware Supported: TKLFRLNRLMLAO PCB
* Hardware Availability: TBA

Make example for this keyboard (after setting up your build environment):

    make zicodia/tklfrlnrlmlao:default

Flashing example for this keyboard:

    make zicodia/tklfrlnrlmlao:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
