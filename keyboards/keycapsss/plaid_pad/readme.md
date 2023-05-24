# Plaid-Pad
Rev1.1
<img src="https://i.imgur.com/Jovhxpr.jpg" width="400" alt="Plaid-Pad Rev1.1">
Rev3
<img src="https://i.imgur.com/KHPId3G.jpg" width="400" alt="Plaid-Pad Rev3 with Oled">  

Default Keymap
<img src="https://i.imgur.com/V82cMqq.png" width="400">

A 4x4 numpad/macro pad with only through hole components. It supports up to 4 rotary encoder. The positions for the encoder are interchangeable with keyboard switches.  

Below you can see the possible positions for the 4 rotary encoder (Rev1 only 2).  
*If you place a encoder in the top left corner (E1), you can't use another encoder in the lower right corner.*
```
Rev1.1 and higher           Rev1
,-----------------------,   ,-----------------------,
|  E1 |  E2 |  E3 |  E4 |   |  E1 |     |     |  E2 |
|-----+-----+-----+-----|   |-----+-----+-----+-----|
|     |     |     |  E3 |   |     |     |     |     |
|-----+-----+-----+-----|   |-----+-----+-----+-----|
|     |     |     |  E2 |   |     |     |     |     |
|-----+-----+-----+-----|   |-----+-----+-----+-----|
|     |     |     |  E1 |   |     |     |     |     |
`-----------------------'   `-----------------------'
```  

- Encoder E1 performs a tap on `KC_F17` and `KC_F18`.
- Encoder E2 performs a tap on `KC_F19` and `KC_F20`.
- Encoder E3 performs a tap on `KC_F21` and `KC_F22`.
- Encoder E4 performs a tap on `KC_F23` and `KC_F24`.

*The F17-F24 keys are intended to be customized via [Karabiner-Elements (OSX)](https://github.com/pqrs-org/Karabiner-Elements), or [AutoHotkey](https://github.com/Lexikos/AutoHotkey_L) (WIN)*

It's a great companion to the Plaid keyboard by [hsgw](https://github.com/hsgw/) and heavily inspired by it.
* Keyboard Maintainer: BenRoe [GitHub](https://github.com/BenRoe) / [Twitter](https://twitter.com/keycapsss)
* Hardware Supported: ATmega328P with VUSB ([see Bootloader section](#Bootloader))
* Hardware Availability: [Keycapsss.com](https://keycapsss.com)

## QMK Firmware
_Bootloader and Firmware ([default keymap](https://github.com/qmk/qmk_firmware/tree/master/keyboards/keycapsss/plaid_pad)) are already on the ATmega328P chip._

Make example for this keyboard (after [setting up your build environment](https://docs.qmk.fm/#/getting_started_build_tools)):

    make keycapsss/plaid_pad:default
    // or
    qmk compile -kb keycapsss/plaid_pad -km default

Flashing example for this keyboard:

    make keycapsss/plaid_pad:default:flash
    // or
    qmk flash -kb keycapsss/plaid_pad -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
- same `usbasploader` as used for Plaid ([Instructions](https://github.com/hsgw/plaid/blob/master/doc/en/bootloader.md), [Repository](https://github.com/hsgw/USBaspLoader/tree/plaid))

### Enter bootloader mode (to flash a new firmware)
- Plug in the USB cable
- Push and hold RESET switch
- Push and hold BOOT switch
- Release RESET switch
- Release BOOT switch

alternative method:
- Unplug the USB cable
- Hold down the BOOT switch
- Plug in the USB cable
- Release the BOOT switch

alternative method ([Bootmagic Lite](https://docs.qmk.fm/#/feature_bootmagic?id=bootmagic-lite)):
- Unplug the USB cable
- Hold down the most top left key
- Plug in the USB cable
- Release the most top left key

If you succeed to enter bootloader mode, you can see usbasp in device manager, or `*** USBAsp device connected ...` in [QMK Toolbox](https://github.com/qmk/qmk_toolbox).
