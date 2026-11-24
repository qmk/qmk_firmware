# MKS3 9-Key Numpad

A 9-key USB numpad based on the Waveshare RP2040-Zero, with 9 chained WS2812 LEDs
and an on-board status LED.

* Keyboard Maintainer: [kswlq](https://github.com/kswlq)
* Hardware Supported: RP2040-Zero (RP2040), 9x direct-wired switches, 9x WS2812
* Hardware Availability: <your store link>

## Layout

```
┌─────┬─────┬─────┬─────┬─────┐
│ K1  │ K2  │ K3  │ K4  │ K5  │
├─────┴┬────┴┬────┴┬────┴┬────┴─┐
│  K6  │  K7 │  K8 │  K9 │      │   second row shifted right by half a key
└──────┴─────┴─────┴─────┴──────┘
```

* Row 0: GP10 GP13 GP27 GP28 GP29
* Row 1: GP8 GP12 GP15 GP11 (5th column unused)
* Switches are wired to GND with the internal pull-up enabled.
* WS2812 data on GP14, on-board status LED on GP16.

## Build

```
make mingyu/mks3_numpad:default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader by either:

* holding the **BOOT** button while plugging in the USB cable, or
* double-tapping the **RESET** button (200 ms window).
