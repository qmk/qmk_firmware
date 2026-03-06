# Mode M65 PCB V2

![Image Gallery](https://cdn.shopify.com/s/files/1/0279/3426/1330/files/Group_95_1024x1024.jpg)

The Mode M65 V2 is 65% PCB for the Mode line of keyboards. As of march 2026, the models compatible with this PCB are the Encore Envoy and SixtyFive. This firmware fits both solderable and hotswap variants.

* Keyboard Maintainer: [Gondolindrim](https://github.com/gondolindrim)
* Hardware Supported: proprietary PCB using STM32F401 controller
* Hardware Availability: at the Mode Designs website.

## Flashing instructions

First you need to put the PCB in DFU mode through the bootloader. This is done in 3 ways: 

* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (top Left most switch)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if available
* **Physical Reset Button**: hold down the button on the back of the PCB for at least five seconds.

Flashing example for this keyboard:

    make mode/m65v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
