# Revolt

![Imgur](https://i.imgur.com/agVoXko.jpeg)

- Keyboard Maintainer: [Jacek Królikowski](https://github.com/nietaki)
- Hardware Supported: RPI 2040, Revolt Keyboard rev2
- Hardware Availability: 
  - [purchase from NTK studio](https://ntkstudio.net/products/revolt-keyboard/)
  - [make your own](https://github.com/nietaki/revolt-keyboard) (Kicad, CC-BY-SA-4.0 license)

## Non-basic functionality

- backlight cycling
- midi (advanced) functionality is enabled (although currently not mapped in the default keymap)
- capslock indicator is mapped to the LED on the underside of the RP2040 board
- You can use the custom keycodes: `RMS_ON` to disable the joystick mouse and `RMS_OFF` to enable it, `RMS_TOG` to toggle it.
  - it can be useful in case the joystick potentiometers wear out and you don't have a spare
  - this setting is **not** currently saved to EEPROM

## Revisions

The firmware revision you want to use is determined by the revision of the commander
PCB. You want the largest revision number that's less than or equal to your commander PCB revision.

So if you have commander PCB rev3, you want to use firmware rev2, unless rev3 is available. Firmware rev4 is likely incompatible with rev3 commander PCBs.

## Building

Make example for this keyboard (after setting up your build environment), using the `default` keymap:

    $ make revolt/rev2:default
    # alternatively, using qmk cli
    $ qmk compile -kb revolt/rev2 -km default

This will create a `revolt_rev2_default.uf2` file in the root `qmk_firmware` repo directory.

Flash the firmware by putting the kyboard into the bootloader mode and copying the compiled `.uf2` file into the `RPI-RP2` drive that appears.

## Bootloader

Enter the bootloader in one of 3 ways:

- **Bootmagic reset**: Hold down the top left key of the left hand board and plug in or reset the keyboard
- **Physical reset button**: Briefly press the reset button on the top side of the Commander board
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
