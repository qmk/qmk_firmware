# Arrow Mechanics WINGS Mark 1

![Arrow Mechanics WINGS Mark 1](https://i.imgur.com/oQkDmSu.png)

ErgoDox-inspired SPLIT keyboard by [Arrow Mechanics](https://www.arrowmechanics.com/)
	
* 94 GATERON Low Profile 2.0 hotswap sockets
* RGB diode under each key for WS2812-driven lighting with [RGB Matrix](https://docs.qmk.fm/#/feature_rgb_matrix)
* 2 rotary encoders, one per half, with push-switches
* Buzzers for sound effects and/or [Music Mode](https://docs.qmk.fm/#/feature_audio?id=music-mode)
* Handy magnetic connectors for joining the halves together or splitting with the use of dedicated cable
* Anti-slip pads with magnetic expanding-legs for conveniently adjusting height/lean
* RP2040 Chip + 16MB Flash memory - Dual-core Cortex M0+
---
* Keyboard Maintainer: [arrowmechanics](https://github.com/arrowmechanics/)
* Hardware Supported: [Arrow Mechanics WINGS Keyboard set](https://www.arrowmechanics.com/produkty?view=product&id=8)
* Hardware Availability: [Official Arrow Mechanics E-SHOP](https://www.arrowmechanics.com/produkty?view=product&id=8)

Flashing example for this keyboard:

    qmk flash -kb arrowmechanics/wings -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:
* **Bootmagic reset**: Hold down the top-left corner key on power-up.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
