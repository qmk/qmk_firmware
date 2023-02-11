# Blue Team Pad

![blue_team_pad](https://i.imgur.com/U8LNofvh.jpeg)

An open source macropad for the cyber security analyst.

The Blue Team Pad is a RP2040 based 4x5 macropad with two rotary encoders and OLED display.

It was specifically designed with the maximum possible space for macros supported by QMK. This allows the analyst to store various triage & remediation commands for quick access.

* Keyboard Maintainer: [Thomas Autiello Jr](https://github.com/fearherbs1)
* Hardware Supported: Custom RP2040 Based PCB
* Hardware Availability: https://github.com/fearherbs1/blue-team-pad 

Make example for this keyboard (after setting up your build environment):

    make fearherbs1/blue_team_pad:default

Flashing example for this keyboard:

    make fearherbs1/blue_team_pad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the upper left encoder and plug in the keyboard
* **Physical reset button**: Briefly short the two "BOOT" pads on the back side of the pcb
