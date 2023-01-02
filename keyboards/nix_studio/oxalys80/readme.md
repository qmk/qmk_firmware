# OXALYS80

A QMK-powered replacement PCB for custom TKL keyboards. This PCB has the same size of the b.87 PCB, Hiney H87a, and KBD8X.

* Keyboard Maintainer: [Nix Studio](https://github.com/Nix-Studio)
* Hardware Supported: oxalys80 ver. 1.0
* Hardware Availability: [Nix Studio](https://www.instagram.com/nix.studio/)

Make example for this keyboard (after setting up your build environment):

    make nix_studio/oxalys80:default

Flashing example for this keyboard:

    make nix_studio/oxalys80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## OXALYS80 Hardware Information

Controller: ATmega32U4

### Column Pin Configuration

| col: | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  |
|------|----|----|----|----|----|----|----|----|----|
| pin: | F0 | F1 | F4 | F5 | F6 | F7 | C7 | B0 | B1 |

### Row Pin Configuration

| row: | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 |
|------|----|----|----|----|----|----|----|----|----|----|----|----|
| pin: | C6 | B6 | B5 | B4 | D7 | D6 | D4 | D5 | D3 | D2 | D1 | D0 |

The OXALYS80 PCB utilizes duplex matrix organization.

### LED Pins

* Caps Lock LED: E6
* Scroll Lock LED: B2
* Num Lock LED: not supported
* Backlight Pin: B7
* RGB Data Pin: B3

## In-switch Indicators

To connect the Caps Lock LED to the main backlight matrix, turn switch to top position on SW3. To use the Caps Lock LED as an indicator, turn switch to bottom position on SW3.

To connect the Scroll Lock LED to the main backlight matrix, turn switch to left position on SW2. To use the Scroll Lock LED as an indicator, turn switch to right position on SW2.
