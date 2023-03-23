<h1> PocketPad </h1>


The PocketPad is a small 18 key macropad with a numpad like layout that takes inspiration from the PocketType.

Keyboard Maintainer: ButterKeebs </br >
Hardware Supported: ATMega32u4 based Elite-C pin compatible MCUs. 6mm square TH switches (link here soon) </br >
Hardware Availability: Links to storefront when available </br > </br >
Make example for this keyboard (after setting up your build environment): 

```
make butterkeebs/pocketpad:default
```

Flashing example for this keyboard:

```
make butterkeebs/pocketpad:default:flash
```

See the <a href="https://docs.qmk.fm/#/getting_started_build_tools">build environment setup</a> and the <a href="https://github.com/qmk/qmk_firmware/blob/master/data/templates/keyboard/readme.md#:~:text=setup%20and%20the-,make%20instructions,-for%20more%20information">make instructions</a> for more information. Brand new to QMK? Start with our <a href="https://docs.qmk.fm/#/newbs)"> Complete Newbs Guide. </a>

Bootloader </br >
Enter the bootloader in 3 ways:

Physical reset button: Briefly press the button on the back of the PCB, if using PCB version 1, then hold a screwdriver to the third pin down on the right side of the MCU.

Keycode in layout: Press the key mapped to QK_BOOT if it is available
