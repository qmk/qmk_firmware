# bear_face

![bear_face](https://i.imgur.com/W4eib5kh.png)

QMK-compatible replacement PCB for the Vortex Race 3

* Keyboard Maintainer: [Will Hedges](https://github.com/will-hedges)
* Hardware Supported: bear_face v1, v2, v3; atmega32u4
* Hardware Availability: [currently by request, Reddit mechmarket](https://www.reddit.com/message/compose?to=chemicalwill&subject=bear_face%20PCB)

Make example for this keyboard (after setting up your build environment):

    make bear_face/v1:default
    make bear_face/v2:default
    make bear_face/v3:default

Flashing example for this keyboard:

    make bear_face/v1:default:flash
    make bear_face/v2:default:flash
    make bear_face/v3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard
* **Physical reset button**: Briefly press the button on the front of the PCB to the right of Caps Lock
* **Keycode in layout**: Press Fn + R
