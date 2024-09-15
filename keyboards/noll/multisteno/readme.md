# Multisteno

![Multisteno](https://i.imgur.com/oRJYTJI.png)

* Keyboard Maintainer: [Nathan Olivares](https://github.com/nkotech)
* Hardware Supported: Multisteno v1.1.2X
* Hardware Availability: [Nolltronics](https://nolltronics.com/product/multisteno)

Make example for this keyboard (after setting up your build environment):

    make noll/multisteno:default

Flashing example for this keyboard:

    make noll/multisteno:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs). 

[Here's a quick video demonstrating how to flash firmware onto the ecosteno](https://youtu.be/dqeZ40PPEW4)

The steno protocol currently included in this project is Gemini PR. I'm not entirely sure why getting Gemini PR to work isn't as simple as changing steno_set_mode(STENO_MODE_GEMINI) in keymap.c, but for now, if you want to compile ecosteno firmware that works with Gemini PR, you'll need to remove some references to TX Bolt by following ecosteno-geminipr.diff in EcoSteno-Firmware/keyboards/noll/ (thanks to dnaq in the Plover discord). If you want to compile this firmware for TX Bolt, you should only need to change steno_set_mode in keymap.c