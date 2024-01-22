# GMMK NUMPAD

![GMMK NUMPAD](https://i.imgur.com/JV4C5os.png)

A 17 Key macropad made and sold by Glorious LLC, equipped with a WB32 microcontroller, with support for a rotary encoder.

* Keyboard Maintainer: [GloriousThrall](https://github.com/GloriousThrall)
* Hardware Supported: GMMK Numpad
* Hardware Availability: [GloriousPCGaming.com](https://www.gloriousgaming.com/products/gmmk-numpad)

Make example for this keyboard (after setting up your build environment):

    make gmmk/numpad:default

Flashing example for this keyboard:

    make gmmk/numpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Num key and plug in the keyboard
* **Keycode in layout**: Press the Num+Del key which is mapped to `QK_BOOT`
* **Physical switch**: Pinhole located ubnde the zero key press while inserting the USB
* **From Glorious Core Firmware**: Press Enter+Plus at the same time while plugging in the USB

## Slider

The slider is currently compatible with [Midi2Vol](https://github.com/jesusvallejo/Midi2Vol), [Midi Mixer (Windows)](https://github.com/jpwilliams/midi-mixer-releases/releases), [Midi2Lightroom (Mac)](https://rsjaffe.github.io/MIDI2LR/), and [ControllerMate (Mac)](https://www.orderedbytes.com/controllermate/)

## Encoder Button

The Button is set to KC_CALC by default and is located at 2,3 on the matrix

## Broken

* Bluetooth functionality