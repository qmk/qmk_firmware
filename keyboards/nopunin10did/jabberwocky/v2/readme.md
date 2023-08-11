# Jabberwocky Gen. 2

![Jabberwocky v2 CNC Edition](https://i.imgur.com/xfpl9H2h.jpg)

A full-size, columnar-staggered, Alice-style keyboard. Specifically, this firmware is for the second generation (v2) of Jabberwocky PCBs, all of which use the same MCU (Atmega 32u4) and firmware.

| PCB Variant   | Numpad Side       | Daughterboard | Soldered / Hotswap        | In-switch LEDs        |
| ------------- | ----------------- | ------------- | ------------------------- | --------------------- |
| Blue          | Left (Sinister)   | Elite C       | Soldered (SMD DIY kit)    | Caps & Num Indicators |
| Red           | Right (Dexterous) | Elite C       | Soldered (SMD DIY kit)    | Caps & Num Indicators |
| Green\*       | Left (Sinister)   | Unified DB    | Soldered (switches only)  | Backlit + Indicators  |
| Yellow        | Right (Dexterous) | Unified DB    | Soldered (switches only)  | Backlit + Indicators  |
| Black\*       | Left (Sinister)   | Unified DB    | Hotswap Hybrid            | None                  |
| White         | Right (Dexterous) | Unified DB    | Hotswap Hybrid            | None                  |

\* *Only the Green and Black PCBs will be compatible with the upcoming Sinister Jabberwocky CNC case.*


For more information, join the [NoPunIn10Key Discord](https://discord.gg/sku2Y6w).

- Keyboard Maintainer: [Alex Ronke](https://nopunin10did.com/), also known as [NoPunIn10Did](https://github.com/NoPunIn10Did)
- Hardware Supported: Jabberwocky 2nd Generation PCBs
- Hardware Availability: Currently by request only

To reset the board into bootloader mode, do one of the following:

- If loaded with the default layout, use Function-Escape or Function-R *(the function buttons are the 1u keys next to B and N)*
- If using the Blue or Red PCBs, use the onboard Reset button on your Elite C
- If using any of the other PCBs, use the onboard Reset button on the PCB itself

Make example for this keyboard (after setting up your build environment):

    make nopunin10did/jabberwocky/v2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs). 
