# AMAG23 (Koolertron)

![Koolertron AMAG23](https://i.imgur.com/DakwCxk.jpg)

One Handed Macro Mechanical Keyboard, 23 Key with optional RGB backlighting.

- Keyboard Maintainer: [ianmclinden](https://github.com/ianmclinden)
- Hardware Supported: AMAG23 (AE-AMAG23-BKC) (ATmega32A)
- Hardware Availability:
    - [Newegg](https://www.newegg.com/p/32K-00H1-00001)
    - [Amazon](https://www.amazon.com/Koolertron-Mechanical-Keyboard-One-Handed-Programmable/dp/B07RM1TBR8)
    - [Koolertron](http://www.koolertron.com/koolertron-one-handed-macro-mechanical-keyboard-with-23-fully-programmable-keys-portable-mini-one-handed-mechanical-gaming-keypad-black-blue-switches-rgb-led.html)

Make example for this keyboard (after setting up your build environment):

    make amag23:default

Flashing example for this keyboard:

    make amag23:default:flash

**Reset Key**: Hold down the *Escape* key while plugging in the keyboard.

**Tips**:
- The keyboard comes with bootloadHID installed from factory.
- The RGB leds seem to be chained together in diagonal rows. The result is that only 7 individual colors are supported, and these are striped across the keypad.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
